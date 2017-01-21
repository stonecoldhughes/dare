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

extern "C" void core_dgemm(
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
                          )
{
    int count = profile.core_dgemm_count++;

    ompt_control((unsigned long)CORE_DGEMM, count);

    profile.call_core_dgemm(
                           transA,
                           transB,
                           m,
                           n,
                           k,
                           alpha,
                           A,
                           lda,
                           B,
                           ldb,
                           beta,
                           C,
                           ldc
                           );
    
    ompt_control((unsigned long)CORE_DGEMM, count);

    return;
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

/* Captain! Test code */
void cblas_dtrsm (const CBLAS_LAYOUT Layout, const CBLAS_SIDE side, const CBLAS_UPLO
uplo, const CBLAS_TRANSPOSE transa, const CBLAS_DIAG diag, const MKL_INT m, const
MKL_INT n, const double alpha, const double *a, const MKL_INT lda, double *b, const
MKL_INT ldb)
{
    //printf("Ahoy! cblas_dtrsm() hooked!\n");
    return;
}

extern "C" void core_dtrsm(plasma_enum_t side, plasma_enum_t uplo,
 plasma_enum_t transA, plasma_enum_t diag,
 int m, int n,
 double alpha, const double *A, int lda,
 double *B, int ldb)
{
    printf("Ahoy! core_dtrsm() hooked\n");
    return;
}
/*
extern "C" void core_dtrsm(
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
                          )
{
    int count = profile.core_dtrsm_count++;

    ompt_control((unsigned long)CORE_DTRSM, count);
    
    profile.call_core_dtrsm(
                           side,
                           uplo,
                           transA,
                           diag,
                           m,
                           n,
                           alpha,
                           A,
                           lda,
                           B,
                           ldb
                           );

    ompt_control((unsigned long)CORE_DTRSM, count);

    return;
}
*/
extern "C" int core_dpotrf(
                          plasma_enum_t uplo,
                          int n,
                          double *A,
                          int lda
                          )
{
    printf("Hello, World!\n");
    int count = profile.core_dpotrf_count++;

    ompt_control((unsigned long)CORE_DPOTRF, count);

    profile.call_core_dpotrf(
                            uplo,
                            n,
                            A,
                            lda
                            );

    ompt_control((unsigned long)CORE_DPOTRF, count);

    return 0;
}
