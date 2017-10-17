#include "plasma_trace.h"

static int ColorMap[MAP_SIZE];
static const char *Label[sizeof(Color)/sizeof(Color[0])] = { NULL };
static int NumColors = sizeof(Color)/sizeof(Color[0]);

static int Trace = 1;
static int NumThreads;
static int    EventNumThread  [MAX_THREADS];
static double EventStartThread[MAX_THREADS][MAX_THREAD_EVENTS];
static double EventStopThread [MAX_THREADS][MAX_THREAD_EVENTS];
static int    EventColorThread[MAX_THREADS][MAX_THREAD_EVENTS];

void trace_off() {Trace = 0;}
void trace_on()  {Trace = 1;}

//------------------------------------------------------------------------------
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
static inline unsigned int color_index(const char *str)
{
    unsigned int hash = 23;
    unsigned int c;
    unsigned char *ustr = (unsigned char*)str;
    while ((c = *ustr++) != '\0')
        hash = hash*307+c;
    return hash%MAP_SIZE;
}

//------------------------------------------------------------------------------
void trace_cpu_start()
{
    int thread_num = omp_get_thread_num() & (MAX_THREADS-1);
    thread_num &= (MAX_THREADS-1);

    int event_num = EventNumThread[thread_num];
    EventStartThread[thread_num][event_num] = omp_get_wtime();
}

//------------------------------------------------------------------------------
void trace_cpu_stop(const char *color)
{
    int thread_num = omp_get_thread_num();
    thread_num &= (MAX_THREADS-1);

    int event_num = EventNumThread[thread_num];
    EventStopThread[thread_num][event_num] = omp_get_wtime();
    EventColorThread[thread_num][event_num] = ColorMap[color_index(color)];

    EventNumThread[thread_num] += Trace;
    EventNumThread[thread_num] &= (MAX_THREAD_EVENTS-1);
}

//------------------------------------------------------------------------------
void trace_label(const char *color, const char *label)
{
    Label[ColorMap[color_index(color)]] = label;
}

//------------------------------------------------------------------------------
static void trace_finish()
{
    double min_time = INFINITY;
    double max_time = 0.0;

    for (int thread = 0; thread < NumThreads; thread++)
        if (EventNumThread[thread] > 0)
            if (EventStartThread[thread][0] < min_time)
                min_time = EventStartThread[thread][0];

    for (int thread = 0; thread < NumThreads; thread++)
        if (EventNumThread[thread] > 0)
            if (EventStopThread[thread][EventNumThread[thread]-1] > max_time)
                max_time = EventStopThread[thread][EventNumThread[thread]-1];

    double total_time = max_time - min_time;
    double hscale = IMAGE_WIDTH / total_time;
    double vscale = IMAGE_HEIGHT / (NumThreads + 1);

    char file_name[32];
    snprintf(file_name, 32, "trace_%ld.svg", (unsigned long int)time(NULL));
    FILE *trace_file = fopen(file_name, "w");
    assert(trace_file != NULL);

    fprintf(trace_file,
            "<svg viewBox=\"0 0 %d %d\">\n", IMAGE_WIDTH, IMAGE_HEIGHT);

    // output events
    int thread;
    int event;
    for (thread = 0; thread < NumThreads; thread++) {
        for (event = 0; event < EventNumThread[thread]; event++) {
            double start = EventStartThread[thread][event]-min_time;
            double stop = EventStopThread[thread][event]-min_time;
            fprintf(
                trace_file,
                "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" "
                "fill=\"#%06x\" stroke=\"#000000\" stroke-width=\"1\" "
                "inkscape:label=\"%s\"/>\n",
                start * hscale,
                thread * vscale,
                (stop-start) * hscale,
                0.9 * vscale,
                Color[EventColorThread[thread][event]].value,
                Label[EventColorThread[thread][event]]);
        }
    }

    // output legend
    int x = 0;
    int y = IMAGE_HEIGHT+50;
    for (int color = 0; color < NumColors; color++) {
        if (Label[color] != NULL) {
            fprintf(
                trace_file,
                "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" "
                "fill=\"#%06x\" stroke=\"#000000\" stroke-width=\"1\"/>\n"
                "<text x=\"%d\" y=\"%d\" "
                "font-family=\"monospace\" font-size=\"35\" fill=\"black\">"
                "%s</text>\n",
                x, y,
                50, 50,
                Color[color].value,
                x+75, y+36,
                Label[color]);
            x += 150;
            x += strlen(Label[color])*22;
            if (x > IMAGE_WIDTH) {
                x = 0;
                y += 100;
            }
        }
    }

    // output xticks time scale
    // xtick spacing is power of 10, with at most 20 tick marks
    double pwr = ceil( log10( total_time / 20 ));
    double xtick = pow( 10., pwr );
    int decimal_places = (pwr < 0 ? (int)-pwr : 0);
    for (double t = 0; t < total_time; t += xtick) {
        fprintf(
            trace_file,
            "<line x1=\"%f\" x2=\"%f\" y1=\"%f\" y2=\"%f\" "
            "stroke=\"#000000\" stroke-width=\"1\" />\n"
            "<text x=\"%f\" y=\"%f\" "
            "font-family=\"monospace\" font-size=\"35\">%.*f</text>\n",
            hscale * t,
            hscale * t,
            vscale * NumThreads,
            vscale * (NumThreads + 0.9),
            hscale * (t + 0.05*xtick),
            vscale * (NumThreads + 0.9),
            decimal_places, t);
    }

    fprintf(trace_file, "</svg>\n");
    fclose(trace_file);
    fprintf(stderr, "trace file: %s\n", file_name);
}

//------------------------------------------------------------------------------
__attribute__ ((constructor))
static void trace_init()
{
    // Check if the maximums are powers of two.
    assert (__builtin_popcount(MAX_THREADS) == 1);
    assert (__builtin_popcount(MAX_THREAD_EVENTS) == 1);

    // Initialize the color map.
    for (int i = 0; i < NumColors; i++)
        ColorMap[color_index(Color[i].color)] = i;

    // Clip the number of threads.
    NumThreads = omp_get_max_threads() < MAX_THREADS ?
        omp_get_max_threads() : MAX_THREADS;

    // Register the destructor.
    atexit(trace_finish);
}
