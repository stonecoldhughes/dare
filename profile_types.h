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

typedef void (*lapacke_dpotrf_hook_type)(
                                        int matrix_layout,
                                        char uplo,
                                        lapack_int n,
                                        double* a,
                                        lapack_int lda
                                        );

typedef void (*cblas_dtrsm_hook_type)(
                                     const  CBLAS_LAYOUT,
                                     const  CBLAS_SIDE,
                                     const  CBLAS_UPLO,
                                     const  CBLAS_TRANSPOSE,
                                     const  CBLAS_DIAG,
                                     const MKL_INT,
                                     const MKL_INT,
                                     const double,
                                     const double *,
                                     const MKL_INT,
                                     double *, 
                                     const MKL_INT
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
