#include "profile.h"

using namespace std;

/*Plasma init needs to serve as the constructor*/
extern "C" int plasma_init()
{
    profile.setup();

    profile.call_plasma_init();

    return 0;
}

/*This needs to serve as the destructor*/
extern "C" int plasma_finalize()
{
    profile.finish();

    profile.call_plasma_finalize();

    return 0;
}

extern "C" void cblas_dgemm(
                           const  CBLAS_LAYOUT Layout,
                           const  CBLAS_TRANSPOSE TransA,
                           const  CBLAS_TRANSPOSE TransB,
                           const MKL_INT M,
                           const MKL_INT N,
                           const MKL_INT K,
                           const double alpha,
                           const double *A,
                           const MKL_INT lda,
                           const double *B,
                           const MKL_INT ldb,
                           const double beta,
                           double *C,
                           const MKL_INT ldc
                           )
{
    int count = profile.cblas_dgemm_count++;

    ompt_control((unsigned long)CBLAS_DGEMM, count);

    profile.call_cblas_dgemm(
                            Layout,
                            TransA,
                            TransB,
                            M,
                            N,
                            K,
                            alpha,
                            A,
                            lda,
                            B,
                            ldb,
                            beta,
                            C,
                            ldc
                            );

    ompt_control((unsigned long)CBLAS_DGEMM, count);
}

extern "C" void cblas_dsyrk(
                           const  CBLAS_LAYOUT Layout,
                           const  CBLAS_UPLO Uplo,
                           const  CBLAS_TRANSPOSE Trans,
                           const MKL_INT N,
                           const MKL_INT K,
                           const double alpha,
                           const double *A,
                           const MKL_INT lda,
                           const double beta,
                           double *C,
                           const MKL_INT ldc
                           )
{
    int count = profile.cblas_dsyrk_count++;

    ompt_control((unsigned long)CBLAS_DSYRK, count);

    profile.call_cblas_dsyrk(
                            Layout,
                            Uplo,
                            Trans,
                            N,
                            K,
                            alpha,
                            A,
                            lda,
                            beta,
                            C,
                            ldc
                            );

    ompt_control((unsigned long)CBLAS_DSYRK, count);

    return;
}


extern "C" void cblas_dtrsm(
                           const  CBLAS_LAYOUT Layout,
                           const  CBLAS_SIDE Side,
                           const  CBLAS_UPLO Uplo,
                           const  CBLAS_TRANSPOSE TransA,
                           const  CBLAS_DIAG Diag,
                           const MKL_INT M,
                           const MKL_INT N,
                           const double alpha,
                           const double *A,
                           const MKL_INT lda,
                           double *B,
                           const MKL_INT ldb
                           )
{
    int count = profile.cblas_dtrsm_count++;

    ompt_control((unsigned long)CBLAS_DTRSM, count);

    profile.call_cblas_dtrsm(
                            Layout,
                            Side,
                            Uplo,
                            TransA,
                            Diag,
                            M,
                            N,
                            alpha,
                            A,
                            lda,
                            B, 
                            ldb
                            );

    ompt_control((unsigned long)CBLAS_DTRSM, count);

    return;
}

extern "C" lapack_int LAPACKE_dpotrf(
                                    int matrix_layout,
                                    char uplo,
                                    lapack_int n,
                                    double* a,
                                    lapack_int lda
                                    )
{
    int count = profile.lapacke_dpotrf_count++;

    ompt_control((unsigned long)LAPACKE_DPOTRF, count);

    profile.call_lapacke_dpotrf(
                               matrix_layout,
                               uplo,
                               n,
                               a,
                               lda
                               );

    ompt_control((unsigned long)LAPACKE_DPOTRF, count);

    return 0;
}
