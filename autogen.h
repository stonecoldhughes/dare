#include "ompt.h"
#include "plasma.h"
#include "mkl_cblas.h"
#include "mkl_lapacke.h"

using namespace std;

typedef enum functions_enum
{
    CORE_DGEMM = 0,
    CORE_DSYRK = 1,
    CORE_DTRSM = 2,
    CORE_DPOTRF = 3,
    
    TABLE_SIZE
} functions_enum;

/*Enumerated types*/
const string kernel_table[] =
{
    "core_dgemm",
    "core_dsyrk",
    "core_dtrsm",
    "core_dpotrf"
};

/* Captain! Put all these in a generated header file */
typedef void (*core_dgemm_hook_type)(
                                    plasma_enum_t transA,
                                    plasma_enum_t transB,
                                    int m,
                                    int n,
                                    int k,
                                    double alpha,
                                    const double *A,
                                    int lda,
                                    const double *B,
                                    int ldb,
                                    double beta,
                                    double *C,
                                    int ldc
                                    );

typedef void (*core_dpotrf_hook_type)(
                                     plasma_enum_t uplo,
                                     int n,
                                     double *A,
                                     int lda
                                     );

typedef void (*core_dtrsm_hook_type)(
                                    plasma_enum_t side,
                                    plasma_enum_t uplo,
                                    plasma_enum_t transA,
                                    plasma_enum_t diag,
                                    int m,
                                    int n,
                                    double alpha,
                                    const double *A,
                                    int lda,
                                    double *B,
                                    int ldb
                                    );

typedef void (*core_dsyrk_hook_type)(
                                    plasma_enum_t uplo,
                                    plasma_enum_t trans,
                                    int n,
                                    int k,
                                    double alpha,
                                    const double *A,
                                    int lda,
                                    double beta,
                                    double *C,
                                    int ldc
                                    );
