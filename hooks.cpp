#include "profile.h"

using namespace std;

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

extern "C" void core_dsyrk(
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
                          )
{
    int count = profile.core_dsyrk_count++;

    ompt_control((unsigned long)CORE_DSYRK, count);
    
    profile.call_core_dsyrk(
                           uplo,
                           trans,
                           n,
                           k,
                           alpha,
                           A,
                           lda,
                           beta,
                           C,
                           ldc
                           );

    ompt_control((unsigned long)CORE_DSYRK, count);

    return;
}

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

extern "C" int core_dpotrf(
                          plasma_enum_t uplo,
                          int n,
                          double *A,
                          int lda
                          )
{
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
