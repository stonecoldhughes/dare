#include "ompt.h"
#include "plasma.h"
#include "mkl_cblas.h"
#include "mkl_lapacke.h"

using namespace std;

/*Typedefs*/
typedef int (*callback_typecast)(ompt_event_t, ompt_callback_t);

typedef void (*plasma_init_hook_type)(void);

typedef void (*plasma_finalize_hook_type)(void);

typedef void (*cblas_dgemm_hook_type)(
                                     const CBLAS_LAYOUT,
                                     const CBLAS_TRANSPOSE,
                                     const CBLAS_TRANSPOSE,
                                     const MKL_INT,
                                     const MKL_INT,
                                     const MKL_INT,
                                     const double,
                                     const double *,
                                     const MKL_INT,
                                     const double *,
                                     const MKL_INT,
                                     const double,
                                     double *,
                                     const MKL_INT
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

typedef void (*cblas_dsyrk_hook_type)(
                                     const  CBLAS_LAYOUT,
                                     const  CBLAS_UPLO,
                                     const  CBLAS_TRANSPOSE,
                                     const MKL_INT,
                                     const MKL_INT,
                                     const double,
                                     const double *,
                                     const MKL_INT,
                                     const double,
                                     double *,
                                     const MKL_INT
                                     );
