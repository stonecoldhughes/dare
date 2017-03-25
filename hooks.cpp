#include "profile.h"

extern class Profile profile;

using namespace std;

extern "C" void core_dlange(
                           plasma_enum_t norm,
                           int m,
                           int n,
                           const double *A,
                           int lda,
                           double *work,
                           double *result
                           )
{

    int count = profile.core_count[CORE_DLANGE]++;

    profile.time_kernel((unsigned long)CORE_DLANGE, count);
    ((core_dlange_hook_type)profile.core[CORE_DLANGE])(
                                                          norm,
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          work,
                                                          result
                                                          );

    profile.time_kernel((unsigned long)CORE_DLANGE, count);

    return;
}

extern "C" void core_cher2k(
                           plasma_enum_t uplo,
                           plasma_enum_t trans,
                           int n,
                           int k,
                           plasma_complex32_t alpha,
                           const plasma_complex32_t *A,
                           int lda,
                           const plasma_complex32_t *B,
                           int ldb,
                           float beta,
                           plasma_complex32_t *C,
                           int ldc
                           )
{

    int count = profile.core_count[CORE_CHER2K]++;

    profile.time_kernel((unsigned long)CORE_CHER2K, count);
    ((core_cher2k_hook_type)profile.core[CORE_CHER2K])(
                                                          uplo,
                                                          trans,
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

    profile.time_kernel((unsigned long)CORE_CHER2K, count);

    return;
}

extern "C" int core_zgeadd(
                          plasma_enum_t transa,
                          int m,
                          int n,
                          plasma_complex64_t alpha,
                          const plasma_complex64_t *A,
                          int lda,
                          plasma_complex64_t beta,
                          plasma_complex64_t *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_ZGEADD]++;

    profile.time_kernel((unsigned long)CORE_ZGEADD, count);
    int ret_val;

    ret_val = ((core_zgeadd_hook_type)profile.core[CORE_ZGEADD])(
                                                                transa,
                                                                m,
                                                                n,
                                                                alpha,
                                                                A,
                                                                lda,
                                                                beta,
                                                                B,
                                                                ldb
                                                                );

    profile.time_kernel((unsigned long)CORE_ZGEADD, count);

    return ret_val;
}

extern "C" void core_ssyr2k(
                           plasma_enum_t uplo,
                           plasma_enum_t trans,
                           int n,
                           int k,
                           float alpha,
                           const float *A,
                           int lda,
                           const float *B,
                           int ldb,
                           float beta,
                           float *C,
                           int ldc
                           )
{

    int count = profile.core_count[CORE_SSYR2K]++;

    profile.time_kernel((unsigned long)CORE_SSYR2K, count);
    ((core_ssyr2k_hook_type)profile.core[CORE_SSYR2K])(
                                                          uplo,
                                                          trans,
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

    profile.time_kernel((unsigned long)CORE_SSYR2K, count);

    return;
}

extern "C" int core_ctsmlq(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int ib,
                          plasma_complex32_t *A1,
                          int lda1,
                          plasma_complex32_t *A2,
                          int lda2,
                          const plasma_complex32_t *V,
                          int ldv,
                          const plasma_complex32_t *T,
                          int ldt,
                          plasma_complex32_t *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_CTSMLQ]++;

    profile.time_kernel((unsigned long)CORE_CTSMLQ, count);
    int ret_val;

    ret_val = ((core_ctsmlq_hook_type)profile.core[CORE_CTSMLQ])(
                                                                side,
                                                                trans,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_CTSMLQ, count);

    return ret_val;
}

extern "C" void core_dgessq(
                           int m,
                           int n,
                           const double *A,
                           int lda,
                           double *scale,
                           double *sumsq
                           )
{

    int count = profile.core_count[CORE_DGESSQ]++;

    profile.time_kernel((unsigned long)CORE_DGESSQ, count);
    ((core_dgessq_hook_type)profile.core[CORE_DGESSQ])(
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          scale,
                                                          sumsq
                                                          );

    profile.time_kernel((unsigned long)CORE_DGESSQ, count);

    return;
}

extern "C" int core_zunmlq(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m,
                          int n,
                          int k,
                          int ib,
                          const plasma_complex64_t *A,
                          int lda,
                          const plasma_complex64_t *T,
                          int ldt,
                          plasma_complex64_t *C,
                          int ldc,
                          plasma_complex64_t *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_ZUNMLQ]++;

    profile.time_kernel((unsigned long)CORE_ZUNMLQ, count);
    int ret_val;

    ret_val = ((core_zunmlq_hook_type)profile.core[CORE_ZUNMLQ])(
                                                                side,
                                                                trans,
                                                                m,
                                                                n,
                                                                k,
                                                                ib,
                                                                A,
                                                                lda,
                                                                T,
                                                                ldt,
                                                                C,
                                                                ldc,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_ZUNMLQ, count);

    return ret_val;
}

extern "C" void core_zlaset(
                           plasma_enum_t uplo,
                           int m,
                           int n,
                           plasma_complex64_t alpha,
                           plasma_complex64_t beta,
                           plasma_complex64_t *A,
                           int lda
                           )
{

    int count = profile.core_count[CORE_ZLASET]++;

    profile.time_kernel((unsigned long)CORE_ZLASET, count);
    ((core_zlaset_hook_type)profile.core[CORE_ZLASET])(
                                                          uplo,
                                                          m,
                                                          n,
                                                          alpha,
                                                          beta,
                                                          A,
                                                          lda
                                                          );

    profile.time_kernel((unsigned long)CORE_ZLASET, count);

    return;
}

extern "C" void core_zsyr2k(
                           plasma_enum_t uplo,
                           plasma_enum_t trans,
                           int n,
                           int k,
                           plasma_complex64_t alpha,
                           const plasma_complex64_t *A,
                           int lda,
                           const plasma_complex64_t *B,
                           int ldb,
                           plasma_complex64_t beta,
                           plasma_complex64_t *C,
                           int ldc
                           )
{

    int count = profile.core_count[CORE_ZSYR2K]++;

    profile.time_kernel((unsigned long)CORE_ZSYR2K, count);
    ((core_zsyr2k_hook_type)profile.core[CORE_ZSYR2K])(
                                                          uplo,
                                                          trans,
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

    profile.time_kernel((unsigned long)CORE_ZSYR2K, count);

    return;
}

extern "C" void core_csymm(
                          plasma_enum_t side,
                          plasma_enum_t uplo,
                          int m,
                          int n,
                          plasma_complex32_t alpha,
                          const plasma_complex32_t *A,
                          int lda,
                          const plasma_complex32_t *B,
                          int ldb,
                          plasma_complex32_t beta,
                          plasma_complex32_t *C,
                          int ldc
                          )
{

    int count = profile.core_count[CORE_CSYMM]++;

    profile.time_kernel((unsigned long)CORE_CSYMM, count);
    ((core_csymm_hook_type)profile.core[CORE_CSYMM])(
                                                        side,
                                                        uplo,
                                                        m,
                                                        n,
                                                        alpha,
                                                        A,
                                                        lda,
                                                        B,
                                                        ldb,
                                                        beta,
                                                        C,
                                                        ldc
                                                        );

    profile.time_kernel((unsigned long)CORE_CSYMM, count);

    return;
}

extern "C" int core_cparfb(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          plasma_enum_t direct,
                          plasma_enum_t storev,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int l,
                          plasma_complex32_t *A1,
                          int lda1,
                          plasma_complex32_t *A2,
                          int lda2,
                          const plasma_complex32_t *V,
                          int ldv,
                          const plasma_complex32_t *T,
                          int ldt,
                          plasma_complex32_t *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_CPARFB]++;

    profile.time_kernel((unsigned long)CORE_CPARFB, count);
    int ret_val;

    ret_val = ((core_cparfb_hook_type)profile.core[CORE_CPARFB])(
                                                                side,
                                                                trans,
                                                                direct,
                                                                storev,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                l,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_CPARFB, count);

    return ret_val;
}

extern "C" int core_dlauum(
                          plasma_enum_t uplo,
                          int n,
                          double *A,
                          int lda
                          )
{

    int count = profile.core_count[CORE_DLAUUM]++;

    profile.time_kernel((unsigned long)CORE_DLAUUM, count);
    int ret_val;

    ret_val = ((core_dlauum_hook_type)profile.core[CORE_DLAUUM])(
                                                                uplo,
                                                                n,
                                                                A,
                                                                lda
                                                                );

    profile.time_kernel((unsigned long)CORE_DLAUUM, count);

    return ret_val;
}

extern "C" int core_cunmqr(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m,
                          int n,
                          int k,
                          int ib,
                          const plasma_complex32_t *A,
                          int lda,
                          const plasma_complex32_t *T,
                          int ldt,
                          plasma_complex32_t *C,
                          int ldc,
                          plasma_complex32_t *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_CUNMQR]++;

    profile.time_kernel((unsigned long)CORE_CUNMQR, count);
    int ret_val;

    ret_val = ((core_cunmqr_hook_type)profile.core[CORE_CUNMQR])(
                                                                side,
                                                                trans,
                                                                m,
                                                                n,
                                                                k,
                                                                ib,
                                                                A,
                                                                lda,
                                                                T,
                                                                ldt,
                                                                C,
                                                                ldc,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_CUNMQR, count);

    return ret_val;
}

extern "C" int core_ztslqt(
                          int m,
                          int n,
                          int ib,
                          plasma_complex64_t *A1,
                          int lda1,
                          plasma_complex64_t *A2,
                          int lda2,
                          plasma_complex64_t *T,
                          int ldt,
                          plasma_complex64_t *tau,
                          plasma_complex64_t *work
                          )
{

    int count = profile.core_count[CORE_ZTSLQT]++;

    profile.time_kernel((unsigned long)CORE_ZTSLQT, count);
    int ret_val;

    ret_val = ((core_ztslqt_hook_type)profile.core[CORE_ZTSLQT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_ZTSLQT, count);

    return ret_val;
}

extern "C" int core_spemv(
                         plasma_enum_t trans,
                         int storev,
                         int m,
                         int n,
                         int l,
                         float alpha,
                         const float *A,
                         int lda,
                         const float *X,
                         int incx,
                         float beta,
                         float *Y,
                         int incy,
                         float *work
                         )
{

    int count = profile.core_count[CORE_SPEMV]++;

    profile.time_kernel((unsigned long)CORE_SPEMV, count);
    int ret_val;

    ret_val = ((core_spemv_hook_type)profile.core[CORE_SPEMV])(
                                                              trans,
                                                              storev,
                                                              m,
                                                              n,
                                                              l,
                                                              alpha,
                                                              A,
                                                              lda,
                                                              X,
                                                              incx,
                                                              beta,
                                                              Y,
                                                              incy,
                                                              work
                                                              );

    profile.time_kernel((unsigned long)CORE_SPEMV, count);

    return ret_val;
}

extern "C" int core_cgeadd(
                          plasma_enum_t transa,
                          int m,
                          int n,
                          plasma_complex32_t alpha,
                          const plasma_complex32_t *A,
                          int lda,
                          plasma_complex32_t beta,
                          plasma_complex32_t *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_CGEADD]++;

    profile.time_kernel((unsigned long)CORE_CGEADD, count);
    int ret_val;

    ret_val = ((core_cgeadd_hook_type)profile.core[CORE_CGEADD])(
                                                                transa,
                                                                m,
                                                                n,
                                                                alpha,
                                                                A,
                                                                lda,
                                                                beta,
                                                                B,
                                                                ldb
                                                                );

    profile.time_kernel((unsigned long)CORE_CGEADD, count);

    return ret_val;
}

extern "C" void core_strsm(
                          plasma_enum_t side,
                          plasma_enum_t uplo,
                          plasma_enum_t transa,
                          plasma_enum_t diag,
                          int m,
                          int n,
                          float alpha,
                          const float *A,
                          int lda,
                          float *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_STRSM]++;

    profile.time_kernel((unsigned long)CORE_STRSM, count);
    ((core_strsm_hook_type)profile.core[CORE_STRSM])(
                                                        side,
                                                        uplo,
                                                        transa,
                                                        diag,
                                                        m,
                                                        n,
                                                        alpha,
                                                        A,
                                                        lda,
                                                        B,
                                                        ldb
                                                        );

    profile.time_kernel((unsigned long)CORE_STRSM, count);

    return;
}

extern "C" int core_dttqrt(
                          int m,
                          int n,
                          int ib,
                          double *A1,
                          int lda1,
                          double *A2,
                          int lda2,
                          double *T,
                          int ldt,
                          double *tau,
                          double *work
                          )
{

    int count = profile.core_count[CORE_DTTQRT]++;

    profile.time_kernel((unsigned long)CORE_DTTQRT, count);
    int ret_val;

    ret_val = ((core_dttqrt_hook_type)profile.core[CORE_DTTQRT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_DTTQRT, count);

    return ret_val;
}

extern "C" int core_dtrtri(
                          plasma_enum_t uplo,
                          plasma_enum_t diag,
                          int n,
                          double *A,
                          int lda
                          )
{

    int count = profile.core_count[CORE_DTRTRI]++;

    profile.time_kernel((unsigned long)CORE_DTRTRI, count);
    int ret_val;

    ret_val = ((core_dtrtri_hook_type)profile.core[CORE_DTRTRI])(
                                                                uplo,
                                                                diag,
                                                                n,
                                                                A,
                                                                lda
                                                                );

    profile.time_kernel((unsigned long)CORE_DTRTRI, count);

    return ret_val;
}

extern "C" int core_cgelqt(
                          int m,
                          int n,
                          int ib,
                          plasma_complex32_t *A,
                          int lda,
                          plasma_complex32_t *T,
                          int ldt,
                          plasma_complex32_t *tau,
                          plasma_complex32_t *work
                          )
{

    int count = profile.core_count[CORE_CGELQT]++;

    profile.time_kernel((unsigned long)CORE_CGELQT, count);
    int ret_val;

    ret_val = ((core_cgelqt_hook_type)profile.core[CORE_CGELQT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A,
                                                                lda,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_CGELQT, count);

    return ret_val;
}

extern "C" void core_clange(
                           plasma_enum_t norm,
                           int m,
                           int n,
                           const plasma_complex32_t *A,
                           int lda,
                           float *work,
                           float *result
                           )
{

    int count = profile.core_count[CORE_CLANGE]++;

    profile.time_kernel((unsigned long)CORE_CLANGE, count);
    ((core_clange_hook_type)profile.core[CORE_CLANGE])(
                                                          norm,
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          work,
                                                          result
                                                          );

    profile.time_kernel((unsigned long)CORE_CLANGE, count);

    return;
}

extern "C" void core_slascl(
                           plasma_enum_t uplo,
                           float cfrom,
                           float cto,
                           int m,
                           int n,
                           float *A,
                           int lda
                           )
{

    int count = profile.core_count[CORE_SLASCL]++;

    profile.time_kernel((unsigned long)CORE_SLASCL, count);
    ((core_slascl_hook_type)profile.core[CORE_SLASCL])(
                                                          uplo,
                                                          cfrom,
                                                          cto,
                                                          m,
                                                          n,
                                                          A,
                                                          lda
                                                          );

    profile.time_kernel((unsigned long)CORE_SLASCL, count);

    return;
}

extern "C" void core_csyr2k(
                           plasma_enum_t uplo,
                           plasma_enum_t trans,
                           int n,
                           int k,
                           plasma_complex32_t alpha,
                           const plasma_complex32_t *A,
                           int lda,
                           const plasma_complex32_t *B,
                           int ldb,
                           plasma_complex32_t beta,
                           plasma_complex32_t *C,
                           int ldc
                           )
{

    int count = profile.core_count[CORE_CSYR2K]++;

    profile.time_kernel((unsigned long)CORE_CSYR2K, count);
    ((core_csyr2k_hook_type)profile.core[CORE_CSYR2K])(
                                                          uplo,
                                                          trans,
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

    profile.time_kernel((unsigned long)CORE_CSYR2K, count);

    return;
}

extern "C" int core_ztsqrt(
                          int m,
                          int n,
                          int ib,
                          plasma_complex64_t *A1,
                          int lda1,
                          plasma_complex64_t *A2,
                          int lda2,
                          plasma_complex64_t *T,
                          int ldt,
                          plasma_complex64_t *tau,
                          plasma_complex64_t *work
                          )
{

    int count = profile.core_count[CORE_ZTSQRT]++;

    profile.time_kernel((unsigned long)CORE_ZTSQRT, count);
    int ret_val;

    ret_val = ((core_ztsqrt_hook_type)profile.core[CORE_ZTSQRT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_ZTSQRT, count);

    return ret_val;
}

extern "C" void core_zgessq(
                           int m,
                           int n,
                           const plasma_complex64_t *A,
                           int lda,
                           double *scale,
                           double *sumsq
                           )
{

    int count = profile.core_count[CORE_ZGESSQ]++;

    profile.time_kernel((unsigned long)CORE_ZGESSQ, count);
    ((core_zgessq_hook_type)profile.core[CORE_ZGESSQ])(
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          scale,
                                                          sumsq
                                                          );

    profile.time_kernel((unsigned long)CORE_ZGESSQ, count);

    return;
}

extern "C" void core_ztrmm(
                          plasma_enum_t side,
                          plasma_enum_t uplo,
                          plasma_enum_t transa,
                          plasma_enum_t diag,
                          int m,
                          int n,
                          plasma_complex64_t alpha,
                          const plasma_complex64_t *A,
                          int lda,
                          plasma_complex64_t *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_ZTRMM]++;

    profile.time_kernel((unsigned long)CORE_ZTRMM, count);
    ((core_ztrmm_hook_type)profile.core[CORE_ZTRMM])(
                                                        side,
                                                        uplo,
                                                        transa,
                                                        diag,
                                                        m,
                                                        n,
                                                        alpha,
                                                        A,
                                                        lda,
                                                        B,
                                                        ldb
                                                        );

    profile.time_kernel((unsigned long)CORE_ZTRMM, count);

    return;
}

extern "C" void core_dtrssq(
                           plasma_enum_t uplo,
                           plasma_enum_t diag,
                           int m,
                           int n,
                           const double *A,
                           int lda,
                           double *scale,
                           double *sumsq
                           )
{

    int count = profile.core_count[CORE_DTRSSQ]++;

    profile.time_kernel((unsigned long)CORE_DTRSSQ, count);
    ((core_dtrssq_hook_type)profile.core[CORE_DTRSSQ])(
                                                          uplo,
                                                          diag,
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          scale,
                                                          sumsq
                                                          );

    profile.time_kernel((unsigned long)CORE_DTRSSQ, count);

    return;
}

extern "C" void core_dlascl(
                           plasma_enum_t uplo,
                           double cfrom,
                           double cto,
                           int m,
                           int n,
                           double *A,
                           int lda
                           )
{

    int count = profile.core_count[CORE_DLASCL]++;

    profile.time_kernel((unsigned long)CORE_DLASCL, count);
    ((core_dlascl_hook_type)profile.core[CORE_DLASCL])(
                                                          uplo,
                                                          cfrom,
                                                          cto,
                                                          m,
                                                          n,
                                                          A,
                                                          lda
                                                          );

    profile.time_kernel((unsigned long)CORE_DLASCL, count);

    return;
}

extern "C" void core_ctrmm(
                          plasma_enum_t side,
                          plasma_enum_t uplo,
                          plasma_enum_t transa,
                          plasma_enum_t diag,
                          int m,
                          int n,
                          plasma_complex32_t alpha,
                          const plasma_complex32_t *A,
                          int lda,
                          plasma_complex32_t *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_CTRMM]++;

    profile.time_kernel((unsigned long)CORE_CTRMM, count);
    ((core_ctrmm_hook_type)profile.core[CORE_CTRMM])(
                                                        side,
                                                        uplo,
                                                        transa,
                                                        diag,
                                                        m,
                                                        n,
                                                        alpha,
                                                        A,
                                                        lda,
                                                        B,
                                                        ldb
                                                        );

    profile.time_kernel((unsigned long)CORE_CTRMM, count);

    return;
}

extern "C" void core_dsymm(
                          plasma_enum_t side,
                          plasma_enum_t uplo,
                          int m,
                          int n,
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

    int count = profile.core_count[CORE_DSYMM]++;

    profile.time_kernel((unsigned long)CORE_DSYMM, count);
    ((core_dsymm_hook_type)profile.core[CORE_DSYMM])(
                                                        side,
                                                        uplo,
                                                        m,
                                                        n,
                                                        alpha,
                                                        A,
                                                        lda,
                                                        B,
                                                        ldb,
                                                        beta,
                                                        C,
                                                        ldc
                                                        );

    profile.time_kernel((unsigned long)CORE_DSYMM, count);

    return;
}

extern "C" int core_dgeqrt(
                          int m,
                          int n,
                          int ib,
                          double *A,
                          int lda,
                          double *T,
                          int ldt,
                          double *tau,
                          double *work
                          )
{

    int count = profile.core_count[CORE_DGEQRT]++;

    profile.time_kernel((unsigned long)CORE_DGEQRT, count);
    int ret_val;

    ret_val = ((core_dgeqrt_hook_type)profile.core[CORE_DGEQRT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A,
                                                                lda,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_DGEQRT, count);

    return ret_val;
}

extern "C" int core_cpamm(
                         int op,
                         plasma_enum_t side,
                         plasma_enum_t storev,
                         int m,
                         int n,
                         int k,
                         int l,
                         const plasma_complex32_t *A1,
                         int lda1,
                         plasma_complex32_t *A2,
                         int lda2,
                         const plasma_complex32_t *V,
                         int ldv,
                         plasma_complex32_t *W,
                         int ldw
                         )
{

    int count = profile.core_count[CORE_CPAMM]++;

    profile.time_kernel((unsigned long)CORE_CPAMM, count);
    int ret_val;

    ret_val = ((core_cpamm_hook_type)profile.core[CORE_CPAMM])(
                                                              op,
                                                              side,
                                                              storev,
                                                              m,
                                                              n,
                                                              k,
                                                              l,
                                                              A1,
                                                              lda1,
                                                              A2,
                                                              lda2,
                                                              V,
                                                              ldv,
                                                              W,
                                                              ldw
                                                              );

    profile.time_kernel((unsigned long)CORE_CPAMM, count);

    return ret_val;
}

extern "C" void core_zlacpy_tile2lapack_band(
                                            plasma_enum_t uplo,
                                            int it,
                                            int jt,
                                            int m,
                                            int n,
                                            int nb,
                                            int kl,
                                            int ku,
                                            const plasma_complex64_t *B,
                                            int ldb,
                                            plasma_complex64_t *A,
                                            int lda
                                            )
{

    int count = profile.core_count[CORE_ZLACPY_TILE2LAPACK_BAND]++;

    profile.time_kernel((unsigned long)CORE_ZLACPY_TILE2LAPACK_BAND, count);
    ((core_zlacpy_tile2lapack_band_hook_type)profile.core[CORE_ZLACPY_TILE2LAPACK_BAND])(
                                                                                            uplo,
                                                                                            it,
                                                                                            jt,
                                                                                            m,
                                                                                            n,
                                                                                            nb,
                                                                                            kl,
                                                                                            ku,
                                                                                            B,
                                                                                            ldb,
                                                                                            A,
                                                                                            lda
                                                                                            );

    profile.time_kernel((unsigned long)CORE_ZLACPY_TILE2LAPACK_BAND, count);

    return;
}

extern "C" int core_cgetrf(
                          plasma_desc_t A,
                          int *ipiv,
                          int ib,
                          int rank,
                          int size,
                          plasma_barrier_t *barrier
                          )
{

    int count = profile.core_count[CORE_CGETRF]++;

    profile.time_kernel((unsigned long)CORE_CGETRF, count);
    int ret_val;

    ret_val = ((core_cgetrf_hook_type)profile.core[CORE_CGETRF])(
                                                                A,
                                                                ipiv,
                                                                ib,
                                                                rank,
                                                                size,
                                                                barrier
                                                                );

    profile.time_kernel((unsigned long)CORE_CGETRF, count);

    return ret_val;
}

extern "C" int core_slauum(
                          plasma_enum_t uplo,
                          int n,
                          float *A,
                          int lda
                          )
{

    int count = profile.core_count[CORE_SLAUUM]++;

    profile.time_kernel((unsigned long)CORE_SLAUUM, count);
    int ret_val;

    ret_val = ((core_slauum_hook_type)profile.core[CORE_SLAUUM])(
                                                                uplo,
                                                                n,
                                                                A,
                                                                lda
                                                                );

    profile.time_kernel((unsigned long)CORE_SLAUUM, count);

    return ret_val;
}

extern "C" void core_cgemm(
                          plasma_enum_t transa,
                          plasma_enum_t transb,
                          int m,
                          int n,
                          int k,
                          plasma_complex32_t alpha,
                          const plasma_complex32_t *A,
                          int lda,
                          const plasma_complex32_t *B,
                          int ldb,
                          plasma_complex32_t beta,
                          plasma_complex32_t *C,
                          int ldc
                          )
{

    int count = profile.core_count[CORE_CGEMM]++;

    profile.time_kernel((unsigned long)CORE_CGEMM, count);
    ((core_cgemm_hook_type)profile.core[CORE_CGEMM])(
                                                        transa,
                                                        transb,
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

    profile.time_kernel((unsigned long)CORE_CGEMM, count);

    return;
}

extern "C" void core_zher2k(
                           plasma_enum_t uplo,
                           plasma_enum_t trans,
                           int n,
                           int k,
                           plasma_complex64_t alpha,
                           const plasma_complex64_t *A,
                           int lda,
                           const plasma_complex64_t *B,
                           int ldb,
                           double beta,
                           plasma_complex64_t *C,
                           int ldc
                           )
{

    int count = profile.core_count[CORE_ZHER2K]++;

    profile.time_kernel((unsigned long)CORE_ZHER2K, count);
    ((core_zher2k_hook_type)profile.core[CORE_ZHER2K])(
                                                          uplo,
                                                          trans,
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

    profile.time_kernel((unsigned long)CORE_ZHER2K, count);

    return;
}

extern "C" void core_ssyssq(
                           plasma_enum_t uplo,
                           int n,
                           const float *A,
                           int lda,
                           float *scale,
                           float *sumsq
                           )
{

    int count = profile.core_count[CORE_SSYSSQ]++;

    profile.time_kernel((unsigned long)CORE_SSYSSQ, count);
    ((core_ssyssq_hook_type)profile.core[CORE_SSYSSQ])(
                                                          uplo,
                                                          n,
                                                          A,
                                                          lda,
                                                          scale,
                                                          sumsq
                                                          );

    profile.time_kernel((unsigned long)CORE_SSYSSQ, count);

    return;
}

extern "C" int core_dpamm(
                         int op,
                         plasma_enum_t side,
                         plasma_enum_t storev,
                         int m,
                         int n,
                         int k,
                         int l,
                         const double *A1,
                         int lda1,
                         double *A2,
                         int lda2,
                         const double *V,
                         int ldv,
                         double *W,
                         int ldw
                         )
{

    int count = profile.core_count[CORE_DPAMM]++;

    profile.time_kernel((unsigned long)CORE_DPAMM, count);
    int ret_val;

    ret_val = ((core_dpamm_hook_type)profile.core[CORE_DPAMM])(
                                                              op,
                                                              side,
                                                              storev,
                                                              m,
                                                              n,
                                                              k,
                                                              l,
                                                              A1,
                                                              lda1,
                                                              A2,
                                                              lda2,
                                                              V,
                                                              ldv,
                                                              W,
                                                              ldw
                                                              );

    profile.time_kernel((unsigned long)CORE_DPAMM, count);

    return ret_val;
}

extern "C" int core_sttqrt(
                          int m,
                          int n,
                          int ib,
                          float *A1,
                          int lda1,
                          float *A2,
                          int lda2,
                          float *T,
                          int ldt,
                          float *tau,
                          float *work
                          )
{

    int count = profile.core_count[CORE_STTQRT]++;

    profile.time_kernel((unsigned long)CORE_STTQRT, count);
    int ret_val;

    ret_val = ((core_sttqrt_hook_type)profile.core[CORE_STTQRT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_STTQRT, count);

    return ret_val;
}

extern "C" void core_dtrmm(
                          plasma_enum_t side,
                          plasma_enum_t uplo,
                          plasma_enum_t transa,
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

    int count = profile.core_count[CORE_DTRMM]++;

    profile.time_kernel((unsigned long)CORE_DTRMM, count);
    ((core_dtrmm_hook_type)profile.core[CORE_DTRMM])(
                                                        side,
                                                        uplo,
                                                        transa,
                                                        diag,
                                                        m,
                                                        n,
                                                        alpha,
                                                        A,
                                                        lda,
                                                        B,
                                                        ldb
                                                        );

    profile.time_kernel((unsigned long)CORE_DTRMM, count);

    return;
}

extern "C" void core_ssyswp(
                           int uplo,
                           plasma_desc_t A,
                           int k1,
                           int k2,
                           const int *ipiv,
                           int incx
                           )
{

    int count = profile.core_count[CORE_SSYSWP]++;

    profile.time_kernel((unsigned long)CORE_SSYSWP, count);
    ((core_ssyswp_hook_type)profile.core[CORE_SSYSWP])(
                                                          uplo,
                                                          A,
                                                          k1,
                                                          k2,
                                                          ipiv,
                                                          incx
                                                          );

    profile.time_kernel((unsigned long)CORE_SSYSWP, count);

    return;
}

extern "C" void core_ssymm(
                          plasma_enum_t side,
                          plasma_enum_t uplo,
                          int m,
                          int n,
                          float alpha,
                          const float *A,
                          int lda,
                          const float *B,
                          int ldb,
                          float beta,
                          float *C,
                          int ldc
                          )
{

    int count = profile.core_count[CORE_SSYMM]++;

    profile.time_kernel((unsigned long)CORE_SSYMM, count);
    ((core_ssymm_hook_type)profile.core[CORE_SSYMM])(
                                                        side,
                                                        uplo,
                                                        m,
                                                        n,
                                                        alpha,
                                                        A,
                                                        lda,
                                                        B,
                                                        ldb,
                                                        beta,
                                                        C,
                                                        ldc
                                                        );

    profile.time_kernel((unsigned long)CORE_SSYMM, count);

    return;
}

extern "C" void core_csyssq(
                           plasma_enum_t uplo,
                           int n,
                           const plasma_complex32_t *A,
                           int lda,
                           float *scale,
                           float *sumsq
                           )
{

    int count = profile.core_count[CORE_CSYSSQ]++;

    profile.time_kernel((unsigned long)CORE_CSYSSQ, count);
    ((core_csyssq_hook_type)profile.core[CORE_CSYSSQ])(
                                                          uplo,
                                                          n,
                                                          A,
                                                          lda,
                                                          scale,
                                                          sumsq
                                                          );

    profile.time_kernel((unsigned long)CORE_CSYSSQ, count);

    return;
}

extern "C" int core_dpemv(
                         plasma_enum_t trans,
                         int storev,
                         int m,
                         int n,
                         int l,
                         double alpha,
                         const double *A,
                         int lda,
                         const double *X,
                         int incx,
                         double beta,
                         double *Y,
                         int incy,
                         double *work
                         )
{

    int count = profile.core_count[CORE_DPEMV]++;

    profile.time_kernel((unsigned long)CORE_DPEMV, count);
    int ret_val;

    ret_val = ((core_dpemv_hook_type)profile.core[CORE_DPEMV])(
                                                              trans,
                                                              storev,
                                                              m,
                                                              n,
                                                              l,
                                                              alpha,
                                                              A,
                                                              lda,
                                                              X,
                                                              incx,
                                                              beta,
                                                              Y,
                                                              incy,
                                                              work
                                                              );

    profile.time_kernel((unsigned long)CORE_DPEMV, count);

    return ret_val;
}

extern "C" void core_cgessq(
                           int m,
                           int n,
                           const plasma_complex32_t *A,
                           int lda,
                           float *scale,
                           float *sumsq
                           )
{

    int count = profile.core_count[CORE_CGESSQ]++;

    profile.time_kernel((unsigned long)CORE_CGESSQ, count);
    ((core_cgessq_hook_type)profile.core[CORE_CGESSQ])(
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          scale,
                                                          sumsq
                                                          );

    profile.time_kernel((unsigned long)CORE_CGESSQ, count);

    return;
}

extern "C" void core_clansy(
                           plasma_enum_t norm,
                           plasma_enum_t uplo,
                           int n,
                           const plasma_complex32_t *A,
                           int lda,
                           float *work,
                           float *value
                           )
{

    int count = profile.core_count[CORE_CLANSY]++;

    profile.time_kernel((unsigned long)CORE_CLANSY, count);
    ((core_clansy_hook_type)profile.core[CORE_CLANSY])(
                                                          norm,
                                                          uplo,
                                                          n,
                                                          A,
                                                          lda,
                                                          work,
                                                          value
                                                          );

    profile.time_kernel((unsigned long)CORE_CLANSY, count);

    return;
}

extern "C" int core_dormlq(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m,
                          int n,
                          int k,
                          int ib,
                          const double *A,
                          int lda,
                          const double *T,
                          int ldt,
                          double *C,
                          int ldc,
                          double *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_DORMLQ]++;

    profile.time_kernel((unsigned long)CORE_DORMLQ, count);
    int ret_val;

    ret_val = ((core_dormlq_hook_type)profile.core[CORE_DORMLQ])(
                                                                side,
                                                                trans,
                                                                m,
                                                                n,
                                                                k,
                                                                ib,
                                                                A,
                                                                lda,
                                                                T,
                                                                ldt,
                                                                C,
                                                                ldc,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_DORMLQ, count);

    return ret_val;
}

extern "C" void core_zhessq(
                           plasma_enum_t uplo,
                           int n,
                           const plasma_complex64_t *A,
                           int lda,
                           double *scale,
                           double *sumsq
                           )
{

    int count = profile.core_count[CORE_ZHESSQ]++;

    profile.time_kernel((unsigned long)CORE_ZHESSQ, count);
    ((core_zhessq_hook_type)profile.core[CORE_ZHESSQ])(
                                                          uplo,
                                                          n,
                                                          A,
                                                          lda,
                                                          scale,
                                                          sumsq
                                                          );

    profile.time_kernel((unsigned long)CORE_ZHESSQ, count);

    return;
}

extern "C" void core_clacpy(
                           plasma_enum_t uplo,
                           plasma_enum_t transa,
                           int m,
                           int n,
                           const plasma_complex32_t *A,
                           int lda,
                           plasma_complex32_t *B,
                           int ldb
                           )
{

    int count = profile.core_count[CORE_CLACPY]++;

    profile.time_kernel((unsigned long)CORE_CLACPY, count);
    ((core_clacpy_hook_type)profile.core[CORE_CLACPY])(
                                                          uplo,
                                                          transa,
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          B,
                                                          ldb
                                                          );

    profile.time_kernel((unsigned long)CORE_CLACPY, count);

    return;
}

extern "C" void core_dlantr(
                           plasma_enum_t norm,
                           plasma_enum_t uplo,
                           plasma_enum_t diag,
                           int m,
                           int n,
                           const double *A,
                           int lda,
                           double *work,
                           double *value
                           )
{

    int count = profile.core_count[CORE_DLANTR]++;

    profile.time_kernel((unsigned long)CORE_DLANTR, count);
    ((core_dlantr_hook_type)profile.core[CORE_DLANTR])(
                                                          norm,
                                                          uplo,
                                                          diag,
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          work,
                                                          value
                                                          );

    profile.time_kernel((unsigned long)CORE_DLANTR, count);

    return;
}

extern "C" void core_slaset(
                           plasma_enum_t uplo,
                           int m,
                           int n,
                           float alpha,
                           float beta,
                           float *A,
                           int lda
                           )
{

    int count = profile.core_count[CORE_SLASET]++;

    profile.time_kernel((unsigned long)CORE_SLASET, count);
    ((core_slaset_hook_type)profile.core[CORE_SLASET])(
                                                          uplo,
                                                          m,
                                                          n,
                                                          alpha,
                                                          beta,
                                                          A,
                                                          lda
                                                          );

    profile.time_kernel((unsigned long)CORE_SLASET, count);

    return;
}

extern "C" int core_cttqrt(
                          int m,
                          int n,
                          int ib,
                          plasma_complex32_t *A1,
                          int lda1,
                          plasma_complex32_t *A2,
                          int lda2,
                          plasma_complex32_t *T,
                          int ldt,
                          plasma_complex32_t *tau,
                          plasma_complex32_t *work
                          )
{

    int count = profile.core_count[CORE_CTTQRT]++;

    profile.time_kernel((unsigned long)CORE_CTTQRT, count);
    int ret_val;

    ret_val = ((core_cttqrt_hook_type)profile.core[CORE_CTTQRT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_CTTQRT, count);

    return ret_val;
}

extern "C" int core_sgeqrt(
                          int m,
                          int n,
                          int ib,
                          float *A,
                          int lda,
                          float *T,
                          int ldt,
                          float *tau,
                          float *work
                          )
{

    int count = profile.core_count[CORE_SGEQRT]++;

    profile.time_kernel((unsigned long)CORE_SGEQRT, count);
    int ret_val;

    ret_val = ((core_sgeqrt_hook_type)profile.core[CORE_SGEQRT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A,
                                                                lda,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_SGEQRT, count);

    return ret_val;
}

extern "C" void core_slacpy_lapack2tile_band(
                                            plasma_enum_t uplo,
                                            int it,
                                            int jt,
                                            int m,
                                            int n,
                                            int nb,
                                            int kl,
                                            int ku,
                                            const float *A,
                                            int lda,
                                            float *B,
                                            int ldb
                                            )
{

    int count = profile.core_count[CORE_SLACPY_LAPACK2TILE_BAND]++;

    profile.time_kernel((unsigned long)CORE_SLACPY_LAPACK2TILE_BAND, count);
    ((core_slacpy_lapack2tile_band_hook_type)profile.core[CORE_SLACPY_LAPACK2TILE_BAND])(
                                                                                            uplo,
                                                                                            it,
                                                                                            jt,
                                                                                            m,
                                                                                            n,
                                                                                            nb,
                                                                                            kl,
                                                                                            ku,
                                                                                            A,
                                                                                            lda,
                                                                                            B,
                                                                                            ldb
                                                                                            );

    profile.time_kernel((unsigned long)CORE_SLACPY_LAPACK2TILE_BAND, count);

    return;
}

extern "C" void core_dlacpy_lapack2tile_band(
                                            plasma_enum_t uplo,
                                            int it,
                                            int jt,
                                            int m,
                                            int n,
                                            int nb,
                                            int kl,
                                            int ku,
                                            const double *A,
                                            int lda,
                                            double *B,
                                            int ldb
                                            )
{

    int count = profile.core_count[CORE_DLACPY_LAPACK2TILE_BAND]++;

    profile.time_kernel((unsigned long)CORE_DLACPY_LAPACK2TILE_BAND, count);
    ((core_dlacpy_lapack2tile_band_hook_type)profile.core[CORE_DLACPY_LAPACK2TILE_BAND])(
                                                                                            uplo,
                                                                                            it,
                                                                                            jt,
                                                                                            m,
                                                                                            n,
                                                                                            nb,
                                                                                            kl,
                                                                                            ku,
                                                                                            A,
                                                                                            lda,
                                                                                            B,
                                                                                            ldb
                                                                                            );

    profile.time_kernel((unsigned long)CORE_DLACPY_LAPACK2TILE_BAND, count);

    return;
}

extern "C" void core_strmm(
                          plasma_enum_t side,
                          plasma_enum_t uplo,
                          plasma_enum_t transa,
                          plasma_enum_t diag,
                          int m,
                          int n,
                          float alpha,
                          const float *A,
                          int lda,
                          float *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_STRMM]++;

    profile.time_kernel((unsigned long)CORE_STRMM, count);
    ((core_strmm_hook_type)profile.core[CORE_STRMM])(
                                                        side,
                                                        uplo,
                                                        transa,
                                                        diag,
                                                        m,
                                                        n,
                                                        alpha,
                                                        A,
                                                        lda,
                                                        B,
                                                        ldb
                                                        );

    profile.time_kernel((unsigned long)CORE_STRMM, count);

    return;
}

extern "C" int core_ssygst(
                          int itype,
                          plasma_enum_t uplo,
                          int n,
                          float *A,
                          int lda,
                          float *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_SSYGST]++;

    profile.time_kernel((unsigned long)CORE_SSYGST, count);
    int ret_val;

    ret_val = ((core_ssygst_hook_type)profile.core[CORE_SSYGST])(
                                                                itype,
                                                                uplo,
                                                                n,
                                                                A,
                                                                lda,
                                                                B,
                                                                ldb
                                                                );

    profile.time_kernel((unsigned long)CORE_SSYGST, count);

    return ret_val;
}

extern "C" int core_cgeqrt(
                          int m,
                          int n,
                          int ib,
                          plasma_complex32_t *A,
                          int lda,
                          plasma_complex32_t *T,
                          int ldt,
                          plasma_complex32_t *tau,
                          plasma_complex32_t *work
                          )
{

    int count = profile.core_count[CORE_CGEQRT]++;

    profile.time_kernel((unsigned long)CORE_CGEQRT, count);
    int ret_val;

    ret_val = ((core_cgeqrt_hook_type)profile.core[CORE_CGEQRT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A,
                                                                lda,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_CGEQRT, count);

    return ret_val;
}

extern "C" int core_ztrtri(
                          plasma_enum_t uplo,
                          plasma_enum_t diag,
                          int n,
                          plasma_complex64_t *A,
                          int lda
                          )
{

    int count = profile.core_count[CORE_ZTRTRI]++;

    profile.time_kernel((unsigned long)CORE_ZTRTRI, count);
    int ret_val;

    ret_val = ((core_ztrtri_hook_type)profile.core[CORE_ZTRTRI])(
                                                                uplo,
                                                                diag,
                                                                n,
                                                                A,
                                                                lda
                                                                );

    profile.time_kernel((unsigned long)CORE_ZTRTRI, count);

    return ret_val;
}

extern "C" int core_ztsmlq(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int ib,
                          plasma_complex64_t *A1,
                          int lda1,
                          plasma_complex64_t *A2,
                          int lda2,
                          const plasma_complex64_t *V,
                          int ldv,
                          const plasma_complex64_t *T,
                          int ldt,
                          plasma_complex64_t *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_ZTSMLQ]++;

    profile.time_kernel((unsigned long)CORE_ZTSMLQ, count);
    int ret_val;

    ret_val = ((core_ztsmlq_hook_type)profile.core[CORE_ZTSMLQ])(
                                                                side,
                                                                trans,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_ZTSMLQ, count);

    return ret_val;
}

extern "C" void core_zsymm(
                          plasma_enum_t side,
                          plasma_enum_t uplo,
                          int m,
                          int n,
                          plasma_complex64_t alpha,
                          const plasma_complex64_t *A,
                          int lda,
                          const plasma_complex64_t *B,
                          int ldb,
                          plasma_complex64_t beta,
                          plasma_complex64_t *C,
                          int ldc
                          )
{

    int count = profile.core_count[CORE_ZSYMM]++;

    profile.time_kernel((unsigned long)CORE_ZSYMM, count);
    ((core_zsymm_hook_type)profile.core[CORE_ZSYMM])(
                                                        side,
                                                        uplo,
                                                        m,
                                                        n,
                                                        alpha,
                                                        A,
                                                        lda,
                                                        B,
                                                        ldb,
                                                        beta,
                                                        C,
                                                        ldc
                                                        );

    profile.time_kernel((unsigned long)CORE_ZSYMM, count);

    return;
}

extern "C" void core_clacpy_tile2lapack_band(
                                            plasma_enum_t uplo,
                                            int it,
                                            int jt,
                                            int m,
                                            int n,
                                            int nb,
                                            int kl,
                                            int ku,
                                            const plasma_complex32_t *B,
                                            int ldb,
                                            plasma_complex32_t *A,
                                            int lda
                                            )
{

    int count = profile.core_count[CORE_CLACPY_TILE2LAPACK_BAND]++;

    profile.time_kernel((unsigned long)CORE_CLACPY_TILE2LAPACK_BAND, count);
    ((core_clacpy_tile2lapack_band_hook_type)profile.core[CORE_CLACPY_TILE2LAPACK_BAND])(
                                                                                            uplo,
                                                                                            it,
                                                                                            jt,
                                                                                            m,
                                                                                            n,
                                                                                            nb,
                                                                                            kl,
                                                                                            ku,
                                                                                            B,
                                                                                            ldb,
                                                                                            A,
                                                                                            lda
                                                                                            );

    profile.time_kernel((unsigned long)CORE_CLACPY_TILE2LAPACK_BAND, count);

    return;
}

extern "C" int core_dormqr(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m,
                          int n,
                          int k,
                          int ib,
                          const double *A,
                          int lda,
                          const double *T,
                          int ldt,
                          double *C,
                          int ldc,
                          double *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_DORMQR]++;

    profile.time_kernel((unsigned long)CORE_DORMQR, count);
    int ret_val;

    ret_val = ((core_dormqr_hook_type)profile.core[CORE_DORMQR])(
                                                                side,
                                                                trans,
                                                                m,
                                                                n,
                                                                k,
                                                                ib,
                                                                A,
                                                                lda,
                                                                T,
                                                                ldt,
                                                                C,
                                                                ldc,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_DORMQR, count);

    return ret_val;
}

extern "C" int core_stsmqr(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int ib,
                          float *A1,
                          int lda1,
                          float *A2,
                          int lda2,
                          const float *V,
                          int ldv,
                          const float *T,
                          int ldt,
                          float *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_STSMQR]++;

    profile.time_kernel((unsigned long)CORE_STSMQR, count);
    int ret_val;

    ret_val = ((core_stsmqr_hook_type)profile.core[CORE_STSMQR])(
                                                                side,
                                                                trans,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_STSMQR, count);

    return ret_val;
}

extern "C" void core_ctrssq(
                           plasma_enum_t uplo,
                           plasma_enum_t diag,
                           int m,
                           int n,
                           const plasma_complex32_t *A,
                           int lda,
                           float *scale,
                           float *sumsq
                           )
{

    int count = profile.core_count[CORE_CTRSSQ]++;

    profile.time_kernel((unsigned long)CORE_CTRSSQ, count);
    ((core_ctrssq_hook_type)profile.core[CORE_CTRSSQ])(
                                                          uplo,
                                                          diag,
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          scale,
                                                          sumsq
                                                          );

    profile.time_kernel((unsigned long)CORE_CTRSSQ, count);

    return;
}

extern "C" void core_slansy(
                           plasma_enum_t norm,
                           plasma_enum_t uplo,
                           int n,
                           const float *A,
                           int lda,
                           float *work,
                           float *value
                           )
{

    int count = profile.core_count[CORE_SLANSY]++;

    profile.time_kernel((unsigned long)CORE_SLANSY, count);
    ((core_slansy_hook_type)profile.core[CORE_SLANSY])(
                                                          norm,
                                                          uplo,
                                                          n,
                                                          A,
                                                          lda,
                                                          work,
                                                          value
                                                          );

    profile.time_kernel((unsigned long)CORE_SLANSY, count);

    return;
}

extern "C" int core_dgetrf(
                          plasma_desc_t A,
                          int *ipiv,
                          int ib,
                          int rank,
                          int size,
                          plasma_barrier_t *barrier
                          )
{

    int count = profile.core_count[CORE_DGETRF]++;

    profile.time_kernel((unsigned long)CORE_DGETRF, count);
    int ret_val;

    ret_val = ((core_dgetrf_hook_type)profile.core[CORE_DGETRF])(
                                                                A,
                                                                ipiv,
                                                                ib,
                                                                rank,
                                                                size,
                                                                barrier
                                                                );

    profile.time_kernel((unsigned long)CORE_DGETRF, count);

    return ret_val;
}

extern "C" int core_ctradd(
                          plasma_enum_t uplo,
                          plasma_enum_t transa,
                          int m,
                          int n,
                          plasma_complex32_t alpha,
                          const plasma_complex32_t *A,
                          int lda,
                          plasma_complex32_t beta,
                          plasma_complex32_t *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_CTRADD]++;

    profile.time_kernel((unsigned long)CORE_CTRADD, count);
    int ret_val;

    ret_val = ((core_ctradd_hook_type)profile.core[CORE_CTRADD])(
                                                                uplo,
                                                                transa,
                                                                m,
                                                                n,
                                                                alpha,
                                                                A,
                                                                lda,
                                                                beta,
                                                                B,
                                                                ldb
                                                                );

    profile.time_kernel((unsigned long)CORE_CTRADD, count);

    return ret_val;
}

extern "C" void core_cheswp(
                           int uplo,
                           plasma_desc_t A,
                           int k1,
                           int k2,
                           const int *ipiv,
                           int incx
                           )
{

    int count = profile.core_count[CORE_CHESWP]++;

    profile.time_kernel((unsigned long)CORE_CHESWP, count);
    ((core_cheswp_hook_type)profile.core[CORE_CHESWP])(
                                                          uplo,
                                                          A,
                                                          k1,
                                                          k2,
                                                          ipiv,
                                                          incx
                                                          );

    profile.time_kernel((unsigned long)CORE_CHESWP, count);

    return;
}

extern "C" int core_sttmlq(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int ib,
                          float *A1,
                          int lda1,
                          float *A2,
                          int lda2,
                          const float *V,
                          int ldv,
                          const float *T,
                          int ldt,
                          float *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_STTMLQ]++;

    profile.time_kernel((unsigned long)CORE_STTMLQ, count);
    int ret_val;

    ret_val = ((core_sttmlq_hook_type)profile.core[CORE_STTMLQ])(
                                                                side,
                                                                trans,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_STTMLQ, count);

    return ret_val;
}

extern "C" void core_zheswp(
                           int uplo,
                           plasma_desc_t A,
                           int k1,
                           int k2,
                           const int *ipiv,
                           int incx
                           )
{

    int count = profile.core_count[CORE_ZHESWP]++;

    profile.time_kernel((unsigned long)CORE_ZHESWP, count);
    ((core_zheswp_hook_type)profile.core[CORE_ZHESWP])(
                                                          uplo,
                                                          A,
                                                          k1,
                                                          k2,
                                                          ipiv,
                                                          incx
                                                          );

    profile.time_kernel((unsigned long)CORE_ZHESWP, count);

    return;
}

extern "C" int core_chegst(
                          int itype,
                          plasma_enum_t uplo,
                          int n,
                          plasma_complex32_t *A,
                          int lda,
                          plasma_complex32_t *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_CHEGST]++;

    profile.time_kernel((unsigned long)CORE_CHEGST, count);
    int ret_val;

    ret_val = ((core_chegst_hook_type)profile.core[CORE_CHEGST])(
                                                                itype,
                                                                uplo,
                                                                n,
                                                                A,
                                                                lda,
                                                                B,
                                                                ldb
                                                                );

    profile.time_kernel((unsigned long)CORE_CHEGST, count);

    return ret_val;
}

extern "C" int core_dttlqt(
                          int m,
                          int n,
                          int ib,
                          double *A1,
                          int lda1,
                          double *A2,
                          int lda2,
                          double *T,
                          int ldt,
                          double *tau,
                          double *work
                          )
{

    int count = profile.core_count[CORE_DTTLQT]++;

    profile.time_kernel((unsigned long)CORE_DTTLQT, count);
    int ret_val;

    ret_val = ((core_dttlqt_hook_type)profile.core[CORE_DTTLQT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_DTTLQT, count);

    return ret_val;
}

extern "C" int core_ctsmqr(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int ib,
                          plasma_complex32_t *A1,
                          int lda1,
                          plasma_complex32_t *A2,
                          int lda2,
                          const plasma_complex32_t *V,
                          int ldv,
                          const plasma_complex32_t *T,
                          int ldt,
                          plasma_complex32_t *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_CTSMQR]++;

    profile.time_kernel((unsigned long)CORE_CTSMQR, count);
    int ret_val;

    ret_val = ((core_ctsmqr_hook_type)profile.core[CORE_CTSMQR])(
                                                                side,
                                                                trans,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_CTSMQR, count);

    return ret_val;
}

extern "C" int core_stsqrt(
                          int m,
                          int n,
                          int ib,
                          float *A1,
                          int lda1,
                          float *A2,
                          int lda2,
                          float *T,
                          int ldt,
                          float *tau,
                          float *work
                          )
{

    int count = profile.core_count[CORE_STSQRT]++;

    profile.time_kernel((unsigned long)CORE_STSQRT, count);
    int ret_val;

    ret_val = ((core_stsqrt_hook_type)profile.core[CORE_STSQRT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_STSQRT, count);

    return ret_val;
}

extern "C" int core_clauum(
                          plasma_enum_t uplo,
                          int n,
                          plasma_complex32_t *A,
                          int lda
                          )
{

    int count = profile.core_count[CORE_CLAUUM]++;

    profile.time_kernel((unsigned long)CORE_CLAUUM, count);
    int ret_val;

    ret_val = ((core_clauum_hook_type)profile.core[CORE_CLAUUM])(
                                                                uplo,
                                                                n,
                                                                A,
                                                                lda
                                                                );

    profile.time_kernel((unsigned long)CORE_CLAUUM, count);

    return ret_val;
}

extern "C" void core_slacpy(
                           plasma_enum_t uplo,
                           plasma_enum_t transa,
                           int m,
                           int n,
                           const float *A,
                           int lda,
                           float *B,
                           int ldb
                           )
{

    int count = profile.core_count[CORE_SLACPY]++;

    profile.time_kernel((unsigned long)CORE_SLACPY, count);
    ((core_slacpy_hook_type)profile.core[CORE_SLACPY])(
                                                          uplo,
                                                          transa,
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          B,
                                                          ldb
                                                          );

    profile.time_kernel((unsigned long)CORE_SLACPY, count);

    return;
}

extern "C" void core_zlascl(
                           plasma_enum_t uplo,
                           double cfrom,
                           double cto,
                           int m,
                           int n,
                           plasma_complex64_t *A,
                           int lda
                           )
{

    int count = profile.core_count[CORE_ZLASCL]++;

    profile.time_kernel((unsigned long)CORE_ZLASCL, count);
    ((core_zlascl_hook_type)profile.core[CORE_ZLASCL])(
                                                          uplo,
                                                          cfrom,
                                                          cto,
                                                          m,
                                                          n,
                                                          A,
                                                          lda
                                                          );

    profile.time_kernel((unsigned long)CORE_ZLASCL, count);

    return;
}

extern "C" int core_strtri(
                          plasma_enum_t uplo,
                          plasma_enum_t diag,
                          int n,
                          float *A,
                          int lda
                          )
{

    int count = profile.core_count[CORE_STRTRI]++;

    profile.time_kernel((unsigned long)CORE_STRTRI, count);
    int ret_val;

    ret_val = ((core_strtri_hook_type)profile.core[CORE_STRTRI])(
                                                                uplo,
                                                                diag,
                                                                n,
                                                                A,
                                                                lda
                                                                );

    profile.time_kernel((unsigned long)CORE_STRTRI, count);

    return ret_val;
}

extern "C" void core_csyrk(
                          plasma_enum_t uplo,
                          plasma_enum_t trans,
                          int n,
                          int k,
                          plasma_complex32_t alpha,
                          const plasma_complex32_t *A,
                          int lda,
                          plasma_complex32_t beta,
                          plasma_complex32_t *C,
                          int ldc
                          )
{

    int count = profile.core_count[CORE_CSYRK]++;

    profile.time_kernel((unsigned long)CORE_CSYRK, count);
    ((core_csyrk_hook_type)profile.core[CORE_CSYRK])(
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

    profile.time_kernel((unsigned long)CORE_CSYRK, count);

    return;
}

extern "C" int core_sgelqt(
                          int m,
                          int n,
                          int ib,
                          float *A,
                          int lda,
                          float *T,
                          int ldt,
                          float *tau,
                          float *work
                          )
{

    int count = profile.core_count[CORE_SGELQT]++;

    profile.time_kernel((unsigned long)CORE_SGELQT, count);
    int ret_val;

    ret_val = ((core_sgelqt_hook_type)profile.core[CORE_SGELQT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A,
                                                                lda,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_SGELQT, count);

    return ret_val;
}

extern "C" void core_claset(
                           plasma_enum_t uplo,
                           int m,
                           int n,
                           plasma_complex32_t alpha,
                           plasma_complex32_t beta,
                           plasma_complex32_t *A,
                           int lda
                           )
{

    int count = profile.core_count[CORE_CLASET]++;

    profile.time_kernel((unsigned long)CORE_CLASET, count);
    ((core_claset_hook_type)profile.core[CORE_CLASET])(
                                                          uplo,
                                                          m,
                                                          n,
                                                          alpha,
                                                          beta,
                                                          A,
                                                          lda
                                                          );

    profile.time_kernel((unsigned long)CORE_CLASET, count);

    return;
}

extern "C" void core_slacpy_tile2lapack_band(
                                            plasma_enum_t uplo,
                                            int it,
                                            int jt,
                                            int m,
                                            int n,
                                            int nb,
                                            int kl,
                                            int ku,
                                            const float *B,
                                            int ldb,
                                            float *A,
                                            int lda
                                            )
{

    int count = profile.core_count[CORE_SLACPY_TILE2LAPACK_BAND]++;

    profile.time_kernel((unsigned long)CORE_SLACPY_TILE2LAPACK_BAND, count);
    ((core_slacpy_tile2lapack_band_hook_type)profile.core[CORE_SLACPY_TILE2LAPACK_BAND])(
                                                                                            uplo,
                                                                                            it,
                                                                                            jt,
                                                                                            m,
                                                                                            n,
                                                                                            nb,
                                                                                            kl,
                                                                                            ku,
                                                                                            B,
                                                                                            ldb,
                                                                                            A,
                                                                                            lda
                                                                                            );

    profile.time_kernel((unsigned long)CORE_SLACPY_TILE2LAPACK_BAND, count);

    return;
}

extern "C" int core_sormqr(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m,
                          int n,
                          int k,
                          int ib,
                          const float *A,
                          int lda,
                          const float *T,
                          int ldt,
                          float *C,
                          int ldc,
                          float *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_SORMQR]++;

    profile.time_kernel((unsigned long)CORE_SORMQR, count);
    int ret_val;

    ret_val = ((core_sormqr_hook_type)profile.core[CORE_SORMQR])(
                                                                side,
                                                                trans,
                                                                m,
                                                                n,
                                                                k,
                                                                ib,
                                                                A,
                                                                lda,
                                                                T,
                                                                ldt,
                                                                C,
                                                                ldc,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_SORMQR, count);

    return ret_val;
}

extern "C" int core_stradd(
                          plasma_enum_t uplo,
                          plasma_enum_t transa,
                          int m,
                          int n,
                          float alpha,
                          const float *A,
                          int lda,
                          float beta,
                          float *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_STRADD]++;

    profile.time_kernel((unsigned long)CORE_STRADD, count);
    int ret_val;

    ret_val = ((core_stradd_hook_type)profile.core[CORE_STRADD])(
                                                                uplo,
                                                                transa,
                                                                m,
                                                                n,
                                                                alpha,
                                                                A,
                                                                lda,
                                                                beta,
                                                                B,
                                                                ldb
                                                                );

    profile.time_kernel((unsigned long)CORE_STRADD, count);

    return ret_val;
}

extern "C" int core_dttmlq(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int ib,
                          double *A1,
                          int lda1,
                          double *A2,
                          int lda2,
                          const double *V,
                          int ldv,
                          const double *T,
                          int ldt,
                          double *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_DTTMLQ]++;

    profile.time_kernel((unsigned long)CORE_DTTMLQ, count);
    int ret_val;

    ret_val = ((core_dttmlq_hook_type)profile.core[CORE_DTTMLQ])(
                                                                side,
                                                                trans,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_DTTMLQ, count);

    return ret_val;
}

extern "C" float core_scabs1(
                            plasma_complex32_t alpha
                            )
{

    int count = profile.core_count[CORE_SCABS1]++;

    profile.time_kernel((unsigned long)CORE_SCABS1, count);
    float ret_val;

    ret_val = ((core_scabs1_hook_type)profile.core[CORE_SCABS1])(
                                                                alpha
                                                                );

    profile.time_kernel((unsigned long)CORE_SCABS1, count);

    return ret_val;
}

extern "C" void core_slange(
                           plasma_enum_t norm,
                           int m,
                           int n,
                           const float *A,
                           int lda,
                           float *work,
                           float *result
                           )
{

    int count = profile.core_count[CORE_SLANGE]++;

    profile.time_kernel((unsigned long)CORE_SLANGE, count);
    ((core_slange_hook_type)profile.core[CORE_SLANGE])(
                                                          norm,
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          work,
                                                          result
                                                          );

    profile.time_kernel((unsigned long)CORE_SLANGE, count);

    return;
}

extern "C" void core_zlanhe(
                           plasma_enum_t norm,
                           plasma_enum_t uplo,
                           int n,
                           const plasma_complex64_t *A,
                           int lda,
                           double *work,
                           double *value
                           )
{

    int count = profile.core_count[CORE_ZLANHE]++;

    profile.time_kernel((unsigned long)CORE_ZLANHE, count);
    ((core_zlanhe_hook_type)profile.core[CORE_ZLANHE])(
                                                          norm,
                                                          uplo,
                                                          n,
                                                          A,
                                                          lda,
                                                          work,
                                                          value
                                                          );

    profile.time_kernel((unsigned long)CORE_ZLANHE, count);

    return;
}

extern "C" void core_sgeswp(
                           plasma_enum_t colrow,
                           plasma_desc_t A,
                           int k1,
                           int k2,
                           const int *ipiv,
                           int incx
                           )
{

    int count = profile.core_count[CORE_SGESWP]++;

    profile.time_kernel((unsigned long)CORE_SGESWP, count);
    ((core_sgeswp_hook_type)profile.core[CORE_SGESWP])(
                                                          colrow,
                                                          A,
                                                          k1,
                                                          k2,
                                                          ipiv,
                                                          incx
                                                          );

    profile.time_kernel((unsigned long)CORE_SGESWP, count);

    return;
}

extern "C" int core_dtradd(
                          plasma_enum_t uplo,
                          plasma_enum_t transa,
                          int m,
                          int n,
                          double alpha,
                          const double *A,
                          int lda,
                          double beta,
                          double *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_DTRADD]++;

    profile.time_kernel((unsigned long)CORE_DTRADD, count);
    int ret_val;

    ret_val = ((core_dtradd_hook_type)profile.core[CORE_DTRADD])(
                                                                uplo,
                                                                transa,
                                                                m,
                                                                n,
                                                                alpha,
                                                                A,
                                                                lda,
                                                                beta,
                                                                B,
                                                                ldb
                                                                );

    profile.time_kernel((unsigned long)CORE_DTRADD, count);

    return ret_val;
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

    int count = profile.core_count[CORE_DSYRK]++;

    profile.time_kernel((unsigned long)CORE_DSYRK, count);
    ((core_dsyrk_hook_type)profile.core[CORE_DSYRK])(
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

    profile.time_kernel((unsigned long)CORE_DSYRK, count);

    return;
}

extern "C" void core_dsyswp(
                           int uplo,
                           plasma_desc_t A,
                           int k1,
                           int k2,
                           const int *ipiv,
                           int incx
                           )
{

    int count = profile.core_count[CORE_DSYSWP]++;

    profile.time_kernel((unsigned long)CORE_DSYSWP, count);
    ((core_dsyswp_hook_type)profile.core[CORE_DSYSWP])(
                                                          uplo,
                                                          A,
                                                          k1,
                                                          k2,
                                                          ipiv,
                                                          incx
                                                          );

    profile.time_kernel((unsigned long)CORE_DSYSWP, count);

    return;
}

extern "C" void core_dtrsm(
                          plasma_enum_t side,
                          plasma_enum_t uplo,
                          plasma_enum_t transa,
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

    int count = profile.core_count[CORE_DTRSM]++;

    profile.time_kernel((unsigned long)CORE_DTRSM, count);
    ((core_dtrsm_hook_type)profile.core[CORE_DTRSM])(
                                                        side,
                                                        uplo,
                                                        transa,
                                                        diag,
                                                        m,
                                                        n,
                                                        alpha,
                                                        A,
                                                        lda,
                                                        B,
                                                        ldb
                                                        );

    profile.time_kernel((unsigned long)CORE_DTRSM, count);

    return;
}

extern "C" int core_stslqt(
                          int m,
                          int n,
                          int ib,
                          float *A1,
                          int lda1,
                          float *A2,
                          int lda2,
                          float *T,
                          int ldt,
                          float *tau,
                          float *work
                          )
{

    int count = profile.core_count[CORE_STSLQT]++;

    profile.time_kernel((unsigned long)CORE_STSLQT, count);
    int ret_val;

    ret_val = ((core_stslqt_hook_type)profile.core[CORE_STSLQT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_STSLQT, count);

    return ret_val;
}

extern "C" void core_ztrssq(
                           plasma_enum_t uplo,
                           plasma_enum_t diag,
                           int m,
                           int n,
                           const plasma_complex64_t *A,
                           int lda,
                           double *scale,
                           double *sumsq
                           )
{

    int count = profile.core_count[CORE_ZTRSSQ]++;

    profile.time_kernel((unsigned long)CORE_ZTRSSQ, count);
    ((core_ztrssq_hook_type)profile.core[CORE_ZTRSSQ])(
                                                          uplo,
                                                          diag,
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          scale,
                                                          sumsq
                                                          );

    profile.time_kernel((unsigned long)CORE_ZTRSSQ, count);

    return;
}

extern "C" void core_clascl(
                           plasma_enum_t uplo,
                           float cfrom,
                           float cto,
                           int m,
                           int n,
                           plasma_complex32_t *A,
                           int lda
                           )
{

    int count = profile.core_count[CORE_CLASCL]++;

    profile.time_kernel((unsigned long)CORE_CLASCL, count);
    ((core_clascl_hook_type)profile.core[CORE_CLASCL])(
                                                          uplo,
                                                          cfrom,
                                                          cto,
                                                          m,
                                                          n,
                                                          A,
                                                          lda
                                                          );

    profile.time_kernel((unsigned long)CORE_CLASCL, count);

    return;
}

extern "C" int core_zgelqt(
                          int m,
                          int n,
                          int ib,
                          plasma_complex64_t *A,
                          int lda,
                          plasma_complex64_t *T,
                          int ldt,
                          plasma_complex64_t *tau,
                          plasma_complex64_t *work
                          )
{

    int count = profile.core_count[CORE_ZGELQT]++;

    profile.time_kernel((unsigned long)CORE_ZGELQT, count);
    int ret_val;

    ret_val = ((core_zgelqt_hook_type)profile.core[CORE_ZGELQT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A,
                                                                lda,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_ZGELQT, count);

    return ret_val;
}

extern "C" void core_chessq(
                           plasma_enum_t uplo,
                           int n,
                           const plasma_complex32_t *A,
                           int lda,
                           float *scale,
                           float *sumsq
                           )
{

    int count = profile.core_count[CORE_CHESSQ]++;

    profile.time_kernel((unsigned long)CORE_CHESSQ, count);
    ((core_chessq_hook_type)profile.core[CORE_CHESSQ])(
                                                          uplo,
                                                          n,
                                                          A,
                                                          lda,
                                                          scale,
                                                          sumsq
                                                          );

    profile.time_kernel((unsigned long)CORE_CHESSQ, count);

    return;
}

extern "C" int core_dgeadd(
                          plasma_enum_t transa,
                          int m,
                          int n,
                          double alpha,
                          const double *A,
                          int lda,
                          double beta,
                          double *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_DGEADD]++;

    profile.time_kernel((unsigned long)CORE_DGEADD, count);
    int ret_val;

    ret_val = ((core_dgeadd_hook_type)profile.core[CORE_DGEADD])(
                                                                transa,
                                                                m,
                                                                n,
                                                                alpha,
                                                                A,
                                                                lda,
                                                                beta,
                                                                B,
                                                                ldb
                                                                );

    profile.time_kernel((unsigned long)CORE_DGEADD, count);

    return ret_val;
}

extern "C" int core_dtsmlq(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int ib,
                          double *A1,
                          int lda1,
                          double *A2,
                          int lda2,
                          const double *V,
                          int ldv,
                          const double *T,
                          int ldt,
                          double *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_DTSMLQ]++;

    profile.time_kernel((unsigned long)CORE_DTSMLQ, count);
    int ret_val;

    ret_val = ((core_dtsmlq_hook_type)profile.core[CORE_DTSMLQ])(
                                                                side,
                                                                trans,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_DTSMLQ, count);

    return ret_val;
}

extern "C" void core_dlansy(
                           plasma_enum_t norm,
                           plasma_enum_t uplo,
                           int n,
                           const double *A,
                           int lda,
                           double *work,
                           double *value
                           )
{

    int count = profile.core_count[CORE_DLANSY]++;

    profile.time_kernel((unsigned long)CORE_DLANSY, count);
    ((core_dlansy_hook_type)profile.core[CORE_DLANSY])(
                                                          norm,
                                                          uplo,
                                                          n,
                                                          A,
                                                          lda,
                                                          work,
                                                          value
                                                          );

    profile.time_kernel((unsigned long)CORE_DLANSY, count);

    return;
}

extern "C" int core_zttlqt(
                          int m,
                          int n,
                          int ib,
                          plasma_complex64_t *A1,
                          int lda1,
                          plasma_complex64_t *A2,
                          int lda2,
                          plasma_complex64_t *T,
                          int ldt,
                          plasma_complex64_t *tau,
                          plasma_complex64_t *work
                          )
{

    int count = profile.core_count[CORE_ZTTLQT]++;

    profile.time_kernel((unsigned long)CORE_ZTTLQT, count);
    int ret_val;

    ret_val = ((core_zttlqt_hook_type)profile.core[CORE_ZTTLQT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_ZTTLQT, count);

    return ret_val;
}

extern "C" void core_zhemm(
                          plasma_enum_t side,
                          plasma_enum_t uplo,
                          int m,
                          int n,
                          plasma_complex64_t alpha,
                          const plasma_complex64_t *A,
                          int lda,
                          const plasma_complex64_t *B,
                          int ldb,
                          plasma_complex64_t beta,
                          plasma_complex64_t *C,
                          int ldc
                          )
{

    int count = profile.core_count[CORE_ZHEMM]++;

    profile.time_kernel((unsigned long)CORE_ZHEMM, count);
    ((core_zhemm_hook_type)profile.core[CORE_ZHEMM])(
                                                        side,
                                                        uplo,
                                                        m,
                                                        n,
                                                        alpha,
                                                        A,
                                                        lda,
                                                        B,
                                                        ldb,
                                                        beta,
                                                        C,
                                                        ldc
                                                        );

    profile.time_kernel((unsigned long)CORE_ZHEMM, count);

    return;
}

extern "C" void core_clacpy_lapack2tile_band(
                                            plasma_enum_t uplo,
                                            int it,
                                            int jt,
                                            int m,
                                            int n,
                                            int nb,
                                            int kl,
                                            int ku,
                                            const plasma_complex32_t *A,
                                            int lda,
                                            plasma_complex32_t *B,
                                            int ldb
                                            )
{

    int count = profile.core_count[CORE_CLACPY_LAPACK2TILE_BAND]++;

    profile.time_kernel((unsigned long)CORE_CLACPY_LAPACK2TILE_BAND, count);
    ((core_clacpy_lapack2tile_band_hook_type)profile.core[CORE_CLACPY_LAPACK2TILE_BAND])(
                                                                                            uplo,
                                                                                            it,
                                                                                            jt,
                                                                                            m,
                                                                                            n,
                                                                                            nb,
                                                                                            kl,
                                                                                            ku,
                                                                                            A,
                                                                                            lda,
                                                                                            B,
                                                                                            ldb
                                                                                            );

    profile.time_kernel((unsigned long)CORE_CLACPY_LAPACK2TILE_BAND, count);

    return;
}

extern "C" int core_sgeadd(
                          plasma_enum_t transa,
                          int m,
                          int n,
                          float alpha,
                          const float *A,
                          int lda,
                          float beta,
                          float *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_SGEADD]++;

    profile.time_kernel((unsigned long)CORE_SGEADD, count);
    int ret_val;

    ret_val = ((core_sgeadd_hook_type)profile.core[CORE_SGEADD])(
                                                                transa,
                                                                m,
                                                                n,
                                                                alpha,
                                                                A,
                                                                lda,
                                                                beta,
                                                                B,
                                                                ldb
                                                                );

    profile.time_kernel((unsigned long)CORE_SGEADD, count);

    return ret_val;
}

extern "C" void core_zgemm(
                          plasma_enum_t transa,
                          plasma_enum_t transb,
                          int m,
                          int n,
                          int k,
                          plasma_complex64_t alpha,
                          const plasma_complex64_t *A,
                          int lda,
                          const plasma_complex64_t *B,
                          int ldb,
                          plasma_complex64_t beta,
                          plasma_complex64_t *C,
                          int ldc
                          )
{

    int count = profile.core_count[CORE_ZGEMM]++;

    profile.time_kernel((unsigned long)CORE_ZGEMM, count);
    ((core_zgemm_hook_type)profile.core[CORE_ZGEMM])(
                                                        transa,
                                                        transb,
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

    profile.time_kernel((unsigned long)CORE_ZGEMM, count);

    return;
}

extern "C" void core_cherk(
                          plasma_enum_t uplo,
                          plasma_enum_t trans,
                          int n,
                          int k,
                          float alpha,
                          const plasma_complex32_t *A,
                          int lda,
                          float beta,
                          plasma_complex32_t *C,
                          int ldc
                          )
{

    int count = profile.core_count[CORE_CHERK]++;

    profile.time_kernel((unsigned long)CORE_CHERK, count);
    ((core_cherk_hook_type)profile.core[CORE_CHERK])(
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

    profile.time_kernel((unsigned long)CORE_CHERK, count);

    return;
}

extern "C" int core_dtsmqr(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int ib,
                          double *A1,
                          int lda1,
                          double *A2,
                          int lda2,
                          const double *V,
                          int ldv,
                          const double *T,
                          int ldt,
                          double *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_DTSMQR]++;

    profile.time_kernel((unsigned long)CORE_DTSMQR, count);
    int ret_val;

    ret_val = ((core_dtsmqr_hook_type)profile.core[CORE_DTSMQR])(
                                                                side,
                                                                trans,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_DTSMQR, count);

    return ret_val;
}

extern "C" void core_clantr(
                           plasma_enum_t norm,
                           plasma_enum_t uplo,
                           plasma_enum_t diag,
                           int m,
                           int n,
                           const plasma_complex32_t *A,
                           int lda,
                           float *work,
                           float *value
                           )
{

    int count = profile.core_count[CORE_CLANTR]++;

    profile.time_kernel((unsigned long)CORE_CLANTR, count);
    ((core_clantr_hook_type)profile.core[CORE_CLANTR])(
                                                          norm,
                                                          uplo,
                                                          diag,
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          work,
                                                          value
                                                          );

    profile.time_kernel((unsigned long)CORE_CLANTR, count);

    return;
}

extern "C" void core_zgeswp(
                           plasma_enum_t colrow,
                           plasma_desc_t A,
                           int k1,
                           int k2,
                           const int *ipiv,
                           int incx
                           )
{

    int count = profile.core_count[CORE_ZGESWP]++;

    profile.time_kernel((unsigned long)CORE_ZGESWP, count);
    ((core_zgeswp_hook_type)profile.core[CORE_ZGESWP])(
                                                          colrow,
                                                          A,
                                                          k1,
                                                          k2,
                                                          ipiv,
                                                          incx
                                                          );

    profile.time_kernel((unsigned long)CORE_ZGESWP, count);

    return;
}

extern "C" int core_zttqrt(
                          int m,
                          int n,
                          int ib,
                          plasma_complex64_t *A1,
                          int lda1,
                          plasma_complex64_t *A2,
                          int lda2,
                          plasma_complex64_t *T,
                          int ldt,
                          plasma_complex64_t *tau,
                          plasma_complex64_t *work
                          )
{

    int count = profile.core_count[CORE_ZTTQRT]++;

    profile.time_kernel((unsigned long)CORE_ZTTQRT, count);
    int ret_val;

    ret_val = ((core_zttqrt_hook_type)profile.core[CORE_ZTTQRT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_ZTTQRT, count);

    return ret_val;
}

extern "C" void core_zherk(
                          plasma_enum_t uplo,
                          plasma_enum_t trans,
                          int n,
                          int k,
                          double alpha,
                          const plasma_complex64_t *A,
                          int lda,
                          double beta,
                          plasma_complex64_t *C,
                          int ldc
                          )
{

    int count = profile.core_count[CORE_ZHERK]++;

    profile.time_kernel((unsigned long)CORE_ZHERK, count);
    ((core_zherk_hook_type)profile.core[CORE_ZHERK])(
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

    profile.time_kernel((unsigned long)CORE_ZHERK, count);

    return;
}

extern "C" int core_zgeqrt(
                          int m,
                          int n,
                          int ib,
                          plasma_complex64_t *A,
                          int lda,
                          plasma_complex64_t *T,
                          int ldt,
                          plasma_complex64_t *tau,
                          plasma_complex64_t *work
                          )
{

    int count = profile.core_count[CORE_ZGEQRT]++;

    profile.time_kernel((unsigned long)CORE_ZGEQRT, count);
    int ret_val;

    ret_val = ((core_zgeqrt_hook_type)profile.core[CORE_ZGEQRT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A,
                                                                lda,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_ZGEQRT, count);

    return ret_val;
}

extern "C" void core_ctrsm(
                          plasma_enum_t side,
                          plasma_enum_t uplo,
                          plasma_enum_t transa,
                          plasma_enum_t diag,
                          int m,
                          int n,
                          plasma_complex32_t alpha,
                          const plasma_complex32_t *A,
                          int lda,
                          plasma_complex32_t *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_CTRSM]++;

    profile.time_kernel((unsigned long)CORE_CTRSM, count);
    ((core_ctrsm_hook_type)profile.core[CORE_CTRSM])(
                                                        side,
                                                        uplo,
                                                        transa,
                                                        diag,
                                                        m,
                                                        n,
                                                        alpha,
                                                        A,
                                                        lda,
                                                        B,
                                                        ldb
                                                        );

    profile.time_kernel((unsigned long)CORE_CTRSM, count);

    return;
}

extern "C" int core_dtsqrt(
                          int m,
                          int n,
                          int ib,
                          double *A1,
                          int lda1,
                          double *A2,
                          int lda2,
                          double *T,
                          int ldt,
                          double *tau,
                          double *work
                          )
{

    int count = profile.core_count[CORE_DTSQRT]++;

    profile.time_kernel((unsigned long)CORE_DTSQRT, count);
    int ret_val;

    ret_val = ((core_dtsqrt_hook_type)profile.core[CORE_DTSQRT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_DTSQRT, count);

    return ret_val;
}

extern "C" void core_sgemm(
                          plasma_enum_t transa,
                          plasma_enum_t transb,
                          int m,
                          int n,
                          int k,
                          float alpha,
                          const float *A,
                          int lda,
                          const float *B,
                          int ldb,
                          float beta,
                          float *C,
                          int ldc
                          )
{

    int count = profile.core_count[CORE_SGEMM]++;

    profile.time_kernel((unsigned long)CORE_SGEMM, count);
    ((core_sgemm_hook_type)profile.core[CORE_SGEMM])(
                                                        transa,
                                                        transb,
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

    profile.time_kernel((unsigned long)CORE_SGEMM, count);

    return;
}

extern "C" int core_spotrf(
                          plasma_enum_t uplo,
                          int n,
                          float *A,
                          int lda
                          )
{

    int count = profile.core_count[CORE_SPOTRF]++;

    profile.time_kernel((unsigned long)CORE_SPOTRF, count);
    int ret_val;

    ret_val = ((core_spotrf_hook_type)profile.core[CORE_SPOTRF])(
                                                                uplo,
                                                                n,
                                                                A,
                                                                lda
                                                                );

    profile.time_kernel((unsigned long)CORE_SPOTRF, count);

    return ret_val;
}

extern "C" int core_zpemv(
                         plasma_enum_t trans,
                         int storev,
                         int m,
                         int n,
                         int l,
                         plasma_complex64_t alpha,
                         const plasma_complex64_t *A,
                         int lda,
                         const plasma_complex64_t *X,
                         int incx,
                         plasma_complex64_t beta,
                         plasma_complex64_t *Y,
                         int incy,
                         plasma_complex64_t *work
                         )
{

    int count = profile.core_count[CORE_ZPEMV]++;

    profile.time_kernel((unsigned long)CORE_ZPEMV, count);
    int ret_val;

    ret_val = ((core_zpemv_hook_type)profile.core[CORE_ZPEMV])(
                                                              trans,
                                                              storev,
                                                              m,
                                                              n,
                                                              l,
                                                              alpha,
                                                              A,
                                                              lda,
                                                              X,
                                                              incx,
                                                              beta,
                                                              Y,
                                                              incy,
                                                              work
                                                              );

    profile.time_kernel((unsigned long)CORE_ZPEMV, count);

    return ret_val;
}

extern "C" int core_zpamm(
                         int op,
                         plasma_enum_t side,
                         plasma_enum_t storev,
                         int m,
                         int n,
                         int k,
                         int l,
                         const plasma_complex64_t *A1,
                         int lda1,
                         plasma_complex64_t *A2,
                         int lda2,
                         const plasma_complex64_t *V,
                         int ldv,
                         plasma_complex64_t *W,
                         int ldw
                         )
{

    int count = profile.core_count[CORE_ZPAMM]++;

    profile.time_kernel((unsigned long)CORE_ZPAMM, count);
    int ret_val;

    ret_val = ((core_zpamm_hook_type)profile.core[CORE_ZPAMM])(
                                                              op,
                                                              side,
                                                              storev,
                                                              m,
                                                              n,
                                                              k,
                                                              l,
                                                              A1,
                                                              lda1,
                                                              A2,
                                                              lda2,
                                                              V,
                                                              ldv,
                                                              W,
                                                              ldw
                                                              );

    profile.time_kernel((unsigned long)CORE_ZPAMM, count);

    return ret_val;
}

extern "C" int core_sormlq(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m,
                          int n,
                          int k,
                          int ib,
                          const float *A,
                          int lda,
                          const float *T,
                          int ldt,
                          float *C,
                          int ldc,
                          float *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_SORMLQ]++;

    profile.time_kernel((unsigned long)CORE_SORMLQ, count);
    int ret_val;

    ret_val = ((core_sormlq_hook_type)profile.core[CORE_SORMLQ])(
                                                                side,
                                                                trans,
                                                                m,
                                                                n,
                                                                k,
                                                                ib,
                                                                A,
                                                                lda,
                                                                T,
                                                                ldt,
                                                                C,
                                                                ldc,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_SORMLQ, count);

    return ret_val;
}

extern "C" int core_ztradd(
                          plasma_enum_t uplo,
                          plasma_enum_t transa,
                          int m,
                          int n,
                          plasma_complex64_t alpha,
                          const plasma_complex64_t *A,
                          int lda,
                          plasma_complex64_t beta,
                          plasma_complex64_t *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_ZTRADD]++;

    profile.time_kernel((unsigned long)CORE_ZTRADD, count);
    int ret_val;

    ret_val = ((core_ztradd_hook_type)profile.core[CORE_ZTRADD])(
                                                                uplo,
                                                                transa,
                                                                m,
                                                                n,
                                                                alpha,
                                                                A,
                                                                lda,
                                                                beta,
                                                                B,
                                                                ldb
                                                                );

    profile.time_kernel((unsigned long)CORE_ZTRADD, count);

    return ret_val;
}

extern "C" int core_zlauum(
                          plasma_enum_t uplo,
                          int n,
                          plasma_complex64_t *A,
                          int lda
                          )
{

    int count = profile.core_count[CORE_ZLAUUM]++;

    profile.time_kernel((unsigned long)CORE_ZLAUUM, count);
    int ret_val;

    ret_val = ((core_zlauum_hook_type)profile.core[CORE_ZLAUUM])(
                                                                uplo,
                                                                n,
                                                                A,
                                                                lda
                                                                );

    profile.time_kernel((unsigned long)CORE_ZLAUUM, count);

    return ret_val;
}

extern "C" int core_dparfb(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          plasma_enum_t direct,
                          plasma_enum_t storev,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int l,
                          double *A1,
                          int lda1,
                          double *A2,
                          int lda2,
                          const double *V,
                          int ldv,
                          const double *T,
                          int ldt,
                          double *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_DPARFB]++;

    profile.time_kernel((unsigned long)CORE_DPARFB, count);
    int ret_val;

    ret_val = ((core_dparfb_hook_type)profile.core[CORE_DPARFB])(
                                                                side,
                                                                trans,
                                                                direct,
                                                                storev,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                l,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_DPARFB, count);

    return ret_val;
}

extern "C" int core_dgelqt(
                          int m,
                          int n,
                          int ib,
                          double *A,
                          int lda,
                          double *T,
                          int ldt,
                          double *tau,
                          double *work
                          )
{

    int count = profile.core_count[CORE_DGELQT]++;

    profile.time_kernel((unsigned long)CORE_DGELQT, count);
    int ret_val;

    ret_val = ((core_dgelqt_hook_type)profile.core[CORE_DGELQT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A,
                                                                lda,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_DGELQT, count);

    return ret_val;
}

extern "C" int core_sgetrf(
                          plasma_desc_t A,
                          int *ipiv,
                          int ib,
                          int rank,
                          int size,
                          plasma_barrier_t *barrier
                          )
{

    int count = profile.core_count[CORE_SGETRF]++;

    profile.time_kernel((unsigned long)CORE_SGETRF, count);
    int ret_val;

    ret_val = ((core_sgetrf_hook_type)profile.core[CORE_SGETRF])(
                                                                A,
                                                                ipiv,
                                                                ib,
                                                                rank,
                                                                size,
                                                                barrier
                                                                );

    profile.time_kernel((unsigned long)CORE_SGETRF, count);

    return ret_val;
}

extern "C" int core_zparfb(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          plasma_enum_t direct,
                          plasma_enum_t storev,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int l,
                          plasma_complex64_t *A1,
                          int lda1,
                          plasma_complex64_t *A2,
                          int lda2,
                          const plasma_complex64_t *V,
                          int ldv,
                          const plasma_complex64_t *T,
                          int ldt,
                          plasma_complex64_t *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_ZPARFB]++;

    profile.time_kernel((unsigned long)CORE_ZPARFB, count);
    int ret_val;

    ret_val = ((core_zparfb_hook_type)profile.core[CORE_ZPARFB])(
                                                                side,
                                                                trans,
                                                                direct,
                                                                storev,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                l,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_ZPARFB, count);

    return ret_val;
}

extern "C" int core_spamm(
                         int op,
                         plasma_enum_t side,
                         plasma_enum_t storev,
                         int m,
                         int n,
                         int k,
                         int l,
                         const float *A1,
                         int lda1,
                         float *A2,
                         int lda2,
                         const float *V,
                         int ldv,
                         float *W,
                         int ldw
                         )
{

    int count = profile.core_count[CORE_SPAMM]++;

    profile.time_kernel((unsigned long)CORE_SPAMM, count);
    int ret_val;

    ret_val = ((core_spamm_hook_type)profile.core[CORE_SPAMM])(
                                                              op,
                                                              side,
                                                              storev,
                                                              m,
                                                              n,
                                                              k,
                                                              l,
                                                              A1,
                                                              lda1,
                                                              A2,
                                                              lda2,
                                                              V,
                                                              ldv,
                                                              W,
                                                              ldw
                                                              );

    profile.time_kernel((unsigned long)CORE_SPAMM, count);

    return ret_val;
}

extern "C" void core_chemm(
                          plasma_enum_t side,
                          plasma_enum_t uplo,
                          int m,
                          int n,
                          plasma_complex32_t alpha,
                          const plasma_complex32_t *A,
                          int lda,
                          const plasma_complex32_t *B,
                          int ldb,
                          plasma_complex32_t beta,
                          plasma_complex32_t *C,
                          int ldc
                          )
{

    int count = profile.core_count[CORE_CHEMM]++;

    profile.time_kernel((unsigned long)CORE_CHEMM, count);
    ((core_chemm_hook_type)profile.core[CORE_CHEMM])(
                                                        side,
                                                        uplo,
                                                        m,
                                                        n,
                                                        alpha,
                                                        A,
                                                        lda,
                                                        B,
                                                        ldb,
                                                        beta,
                                                        C,
                                                        ldc
                                                        );

    profile.time_kernel((unsigned long)CORE_CHEMM, count);

    return;
}

extern "C" void core_dsyssq(
                           plasma_enum_t uplo,
                           int n,
                           const double *A,
                           int lda,
                           double *scale,
                           double *sumsq
                           )
{

    int count = profile.core_count[CORE_DSYSSQ]++;

    profile.time_kernel((unsigned long)CORE_DSYSSQ, count);
    ((core_dsyssq_hook_type)profile.core[CORE_DSYSSQ])(
                                                          uplo,
                                                          n,
                                                          A,
                                                          lda,
                                                          scale,
                                                          sumsq
                                                          );

    profile.time_kernel((unsigned long)CORE_DSYSSQ, count);

    return;
}

extern "C" int core_dsygst(
                          int itype,
                          plasma_enum_t uplo,
                          int n,
                          double *A,
                          int lda,
                          double *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_DSYGST]++;

    profile.time_kernel((unsigned long)CORE_DSYGST, count);
    int ret_val;

    ret_val = ((core_dsygst_hook_type)profile.core[CORE_DSYGST])(
                                                                itype,
                                                                uplo,
                                                                n,
                                                                A,
                                                                lda,
                                                                B,
                                                                ldb
                                                                );

    profile.time_kernel((unsigned long)CORE_DSYGST, count);

    return ret_val;
}

extern "C" int core_zttmqr(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int ib,
                          plasma_complex64_t *A1,
                          int lda1,
                          plasma_complex64_t *A2,
                          int lda2,
                          const plasma_complex64_t *V,
                          int ldv,
                          const plasma_complex64_t *T,
                          int ldt,
                          plasma_complex64_t *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_ZTTMQR]++;

    profile.time_kernel((unsigned long)CORE_ZTTMQR, count);
    int ret_val;

    ret_val = ((core_zttmqr_hook_type)profile.core[CORE_ZTTMQR])(
                                                                side,
                                                                trans,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_ZTTMQR, count);

    return ret_val;
}

extern "C" void core_dlacpy(
                           plasma_enum_t uplo,
                           plasma_enum_t transa,
                           int m,
                           int n,
                           const double *A,
                           int lda,
                           double *B,
                           int ldb
                           )
{

    int count = profile.core_count[CORE_DLACPY]++;

    profile.time_kernel((unsigned long)CORE_DLACPY, count);
    ((core_dlacpy_hook_type)profile.core[CORE_DLACPY])(
                                                          uplo,
                                                          transa,
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          B,
                                                          ldb
                                                          );

    profile.time_kernel((unsigned long)CORE_DLACPY, count);

    return;
}

extern "C" int core_sparfb(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          plasma_enum_t direct,
                          plasma_enum_t storev,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int l,
                          float *A1,
                          int lda1,
                          float *A2,
                          int lda2,
                          const float *V,
                          int ldv,
                          const float *T,
                          int ldt,
                          float *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_SPARFB]++;

    profile.time_kernel((unsigned long)CORE_SPARFB, count);
    int ret_val;

    ret_val = ((core_sparfb_hook_type)profile.core[CORE_SPARFB])(
                                                                side,
                                                                trans,
                                                                direct,
                                                                storev,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                l,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_SPARFB, count);

    return ret_val;
}

extern "C" void core_ztrsm(
                          plasma_enum_t side,
                          plasma_enum_t uplo,
                          plasma_enum_t transa,
                          plasma_enum_t diag,
                          int m,
                          int n,
                          plasma_complex64_t alpha,
                          const plasma_complex64_t *A,
                          int lda,
                          plasma_complex64_t *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_ZTRSM]++;

    profile.time_kernel((unsigned long)CORE_ZTRSM, count);
    ((core_ztrsm_hook_type)profile.core[CORE_ZTRSM])(
                                                        side,
                                                        uplo,
                                                        transa,
                                                        diag,
                                                        m,
                                                        n,
                                                        alpha,
                                                        A,
                                                        lda,
                                                        B,
                                                        ldb
                                                        );

    profile.time_kernel((unsigned long)CORE_ZTRSM, count);

    return;
}

extern "C" int core_zunmqr(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m,
                          int n,
                          int k,
                          int ib,
                          const plasma_complex64_t *A,
                          int lda,
                          const plasma_complex64_t *T,
                          int ldt,
                          plasma_complex64_t *C,
                          int ldc,
                          plasma_complex64_t *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_ZUNMQR]++;

    profile.time_kernel((unsigned long)CORE_ZUNMQR, count);
    int ret_val;

    ret_val = ((core_zunmqr_hook_type)profile.core[CORE_ZUNMQR])(
                                                                side,
                                                                trans,
                                                                m,
                                                                n,
                                                                k,
                                                                ib,
                                                                A,
                                                                lda,
                                                                T,
                                                                ldt,
                                                                C,
                                                                ldc,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_ZUNMQR, count);

    return ret_val;
}

extern "C" int core_zgetrf(
                          plasma_desc_t A,
                          int *ipiv,
                          int ib,
                          int rank,
                          int size,
                          plasma_barrier_t *barrier
                          )
{

    int count = profile.core_count[CORE_ZGETRF]++;

    profile.time_kernel((unsigned long)CORE_ZGETRF, count);
    int ret_val;

    ret_val = ((core_zgetrf_hook_type)profile.core[CORE_ZGETRF])(
                                                                A,
                                                                ipiv,
                                                                ib,
                                                                rank,
                                                                size,
                                                                barrier
                                                                );

    profile.time_kernel((unsigned long)CORE_ZGETRF, count);

    return ret_val;
}

extern "C" int core_cunmlq(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m,
                          int n,
                          int k,
                          int ib,
                          const plasma_complex32_t *A,
                          int lda,
                          const plasma_complex32_t *T,
                          int ldt,
                          plasma_complex32_t *C,
                          int ldc,
                          plasma_complex32_t *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_CUNMLQ]++;

    profile.time_kernel((unsigned long)CORE_CUNMLQ, count);
    int ret_val;

    ret_val = ((core_cunmlq_hook_type)profile.core[CORE_CUNMLQ])(
                                                                side,
                                                                trans,
                                                                m,
                                                                n,
                                                                k,
                                                                ib,
                                                                A,
                                                                lda,
                                                                T,
                                                                ldt,
                                                                C,
                                                                ldc,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_CUNMLQ, count);

    return ret_val;
}

extern "C" void core_sgessq(
                           int m,
                           int n,
                           const float *A,
                           int lda,
                           float *scale,
                           float *sumsq
                           )
{

    int count = profile.core_count[CORE_SGESSQ]++;

    profile.time_kernel((unsigned long)CORE_SGESSQ, count);
    ((core_sgessq_hook_type)profile.core[CORE_SGESSQ])(
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          scale,
                                                          sumsq
                                                          );

    profile.time_kernel((unsigned long)CORE_SGESSQ, count);

    return;
}

extern "C" int core_cttlqt(
                          int m,
                          int n,
                          int ib,
                          plasma_complex32_t *A1,
                          int lda1,
                          plasma_complex32_t *A2,
                          int lda2,
                          plasma_complex32_t *T,
                          int ldt,
                          plasma_complex32_t *tau,
                          plasma_complex32_t *work
                          )
{

    int count = profile.core_count[CORE_CTTLQT]++;

    profile.time_kernel((unsigned long)CORE_CTTLQT, count);
    int ret_val;

    ret_val = ((core_cttlqt_hook_type)profile.core[CORE_CTTLQT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_CTTLQT, count);

    return ret_val;
}

extern "C" int core_cpemv(
                         plasma_enum_t trans,
                         int storev,
                         int m,
                         int n,
                         int l,
                         plasma_complex32_t alpha,
                         const plasma_complex32_t *A,
                         int lda,
                         const plasma_complex32_t *X,
                         int incx,
                         plasma_complex32_t beta,
                         plasma_complex32_t *Y,
                         int incy,
                         plasma_complex32_t *work
                         )
{

    int count = profile.core_count[CORE_CPEMV]++;

    profile.time_kernel((unsigned long)CORE_CPEMV, count);
    int ret_val;

    ret_val = ((core_cpemv_hook_type)profile.core[CORE_CPEMV])(
                                                              trans,
                                                              storev,
                                                              m,
                                                              n,
                                                              l,
                                                              alpha,
                                                              A,
                                                              lda,
                                                              X,
                                                              incx,
                                                              beta,
                                                              Y,
                                                              incy,
                                                              work
                                                              );

    profile.time_kernel((unsigned long)CORE_CPEMV, count);

    return ret_val;
}

extern "C" void core_zlantr(
                           plasma_enum_t norm,
                           plasma_enum_t uplo,
                           plasma_enum_t diag,
                           int m,
                           int n,
                           const plasma_complex64_t *A,
                           int lda,
                           double *work,
                           double *value
                           )
{

    int count = profile.core_count[CORE_ZLANTR]++;

    profile.time_kernel((unsigned long)CORE_ZLANTR, count);
    ((core_zlantr_hook_type)profile.core[CORE_ZLANTR])(
                                                          norm,
                                                          uplo,
                                                          diag,
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          work,
                                                          value
                                                          );

    profile.time_kernel((unsigned long)CORE_ZLANTR, count);

    return;
}

extern "C" void core_zlange(
                           plasma_enum_t norm,
                           int m,
                           int n,
                           const plasma_complex64_t *A,
                           int lda,
                           double *work,
                           double *result
                           )
{

    int count = profile.core_count[CORE_ZLANGE]++;

    profile.time_kernel((unsigned long)CORE_ZLANGE, count);
    ((core_zlange_hook_type)profile.core[CORE_ZLANGE])(
                                                          norm,
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          work,
                                                          result
                                                          );

    profile.time_kernel((unsigned long)CORE_ZLANGE, count);

    return;
}

extern "C" void core_slantr(
                           plasma_enum_t norm,
                           plasma_enum_t uplo,
                           plasma_enum_t diag,
                           int m,
                           int n,
                           const float *A,
                           int lda,
                           float *work,
                           float *value
                           )
{

    int count = profile.core_count[CORE_SLANTR]++;

    profile.time_kernel((unsigned long)CORE_SLANTR, count);
    ((core_slantr_hook_type)profile.core[CORE_SLANTR])(
                                                          norm,
                                                          uplo,
                                                          diag,
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          work,
                                                          value
                                                          );

    profile.time_kernel((unsigned long)CORE_SLANTR, count);

    return;
}

extern "C" void core_zlacpy(
                           plasma_enum_t uplo,
                           plasma_enum_t transa,
                           int m,
                           int n,
                           const plasma_complex64_t *A,
                           int lda,
                           plasma_complex64_t *B,
                           int ldb
                           )
{

    int count = profile.core_count[CORE_ZLACPY]++;

    profile.time_kernel((unsigned long)CORE_ZLACPY, count);
    ((core_zlacpy_hook_type)profile.core[CORE_ZLACPY])(
                                                          uplo,
                                                          transa,
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          B,
                                                          ldb
                                                          );

    profile.time_kernel((unsigned long)CORE_ZLACPY, count);

    return;
}

extern "C" int core_cttmlq(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int ib,
                          plasma_complex32_t *A1,
                          int lda1,
                          plasma_complex32_t *A2,
                          int lda2,
                          const plasma_complex32_t *V,
                          int ldv,
                          const plasma_complex32_t *T,
                          int ldt,
                          plasma_complex32_t *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_CTTMLQ]++;

    profile.time_kernel((unsigned long)CORE_CTTMLQ, count);
    int ret_val;

    ret_val = ((core_cttmlq_hook_type)profile.core[CORE_CTTMLQ])(
                                                                side,
                                                                trans,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_CTTMLQ, count);

    return ret_val;
}

extern "C" void core_dgemm(
                          plasma_enum_t transa,
                          plasma_enum_t transb,
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

    int count = profile.core_count[CORE_DGEMM]++;

    profile.time_kernel((unsigned long)CORE_DGEMM, count);
    ((core_dgemm_hook_type)profile.core[CORE_DGEMM])(
                                                        transa,
                                                        transb,
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

    profile.time_kernel((unsigned long)CORE_DGEMM, count);

    return;
}

extern "C" int core_zpotrf(
                          plasma_enum_t uplo,
                          int n,
                          plasma_complex64_t *A,
                          int lda
                          )
{

    int count = profile.core_count[CORE_ZPOTRF]++;

    profile.time_kernel((unsigned long)CORE_ZPOTRF, count);
    int ret_val;

    ret_val = ((core_zpotrf_hook_type)profile.core[CORE_ZPOTRF])(
                                                                uplo,
                                                                n,
                                                                A,
                                                                lda
                                                                );

    profile.time_kernel((unsigned long)CORE_ZPOTRF, count);

    return ret_val;
}

extern "C" void core_strssq(
                           plasma_enum_t uplo,
                           plasma_enum_t diag,
                           int m,
                           int n,
                           const float *A,
                           int lda,
                           float *scale,
                           float *sumsq
                           )
{

    int count = profile.core_count[CORE_STRSSQ]++;

    profile.time_kernel((unsigned long)CORE_STRSSQ, count);
    ((core_strssq_hook_type)profile.core[CORE_STRSSQ])(
                                                          uplo,
                                                          diag,
                                                          m,
                                                          n,
                                                          A,
                                                          lda,
                                                          scale,
                                                          sumsq
                                                          );

    profile.time_kernel((unsigned long)CORE_STRSSQ, count);

    return;
}

extern "C" int core_ctslqt(
                          int m,
                          int n,
                          int ib,
                          plasma_complex32_t *A1,
                          int lda1,
                          plasma_complex32_t *A2,
                          int lda2,
                          plasma_complex32_t *T,
                          int ldt,
                          plasma_complex32_t *tau,
                          plasma_complex32_t *work
                          )
{

    int count = profile.core_count[CORE_CTSLQT]++;

    profile.time_kernel((unsigned long)CORE_CTSLQT, count);
    int ret_val;

    ret_val = ((core_ctslqt_hook_type)profile.core[CORE_CTSLQT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_CTSLQT, count);

    return ret_val;
}

extern "C" void core_clanhe(
                           plasma_enum_t norm,
                           plasma_enum_t uplo,
                           int n,
                           const plasma_complex32_t *A,
                           int lda,
                           float *work,
                           float *value
                           )
{

    int count = profile.core_count[CORE_CLANHE]++;

    profile.time_kernel((unsigned long)CORE_CLANHE, count);
    ((core_clanhe_hook_type)profile.core[CORE_CLANHE])(
                                                          norm,
                                                          uplo,
                                                          n,
                                                          A,
                                                          lda,
                                                          work,
                                                          value
                                                          );

    profile.time_kernel((unsigned long)CORE_CLANHE, count);

    return;
}

extern "C" int core_stsmlq(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int ib,
                          float *A1,
                          int lda1,
                          float *A2,
                          int lda2,
                          const float *V,
                          int ldv,
                          const float *T,
                          int ldt,
                          float *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_STSMLQ]++;

    profile.time_kernel((unsigned long)CORE_STSMLQ, count);
    int ret_val;

    ret_val = ((core_stsmlq_hook_type)profile.core[CORE_STSMLQ])(
                                                                side,
                                                                trans,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_STSMLQ, count);

    return ret_val;
}

extern "C" void core_dlaset(
                           plasma_enum_t uplo,
                           int m,
                           int n,
                           double alpha,
                           double beta,
                           double *A,
                           int lda
                           )
{

    int count = profile.core_count[CORE_DLASET]++;

    profile.time_kernel((unsigned long)CORE_DLASET, count);
    ((core_dlaset_hook_type)profile.core[CORE_DLASET])(
                                                          uplo,
                                                          m,
                                                          n,
                                                          alpha,
                                                          beta,
                                                          A,
                                                          lda
                                                          );

    profile.time_kernel((unsigned long)CORE_DLASET, count);

    return;
}

extern "C" int core_dtslqt(
                          int m,
                          int n,
                          int ib,
                          double *A1,
                          int lda1,
                          double *A2,
                          int lda2,
                          double *T,
                          int ldt,
                          double *tau,
                          double *work
                          )
{

    int count = profile.core_count[CORE_DTSLQT]++;

    profile.time_kernel((unsigned long)CORE_DTSLQT, count);
    int ret_val;

    ret_val = ((core_dtslqt_hook_type)profile.core[CORE_DTSLQT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_DTSLQT, count);

    return ret_val;
}

extern "C" int core_zttmlq(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int ib,
                          plasma_complex64_t *A1,
                          int lda1,
                          plasma_complex64_t *A2,
                          int lda2,
                          const plasma_complex64_t *V,
                          int ldv,
                          const plasma_complex64_t *T,
                          int ldt,
                          plasma_complex64_t *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_ZTTMLQ]++;

    profile.time_kernel((unsigned long)CORE_ZTTMLQ, count);
    int ret_val;

    ret_val = ((core_zttmlq_hook_type)profile.core[CORE_ZTTMLQ])(
                                                                side,
                                                                trans,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_ZTTMLQ, count);

    return ret_val;
}

extern "C" void core_dlacpy_tile2lapack_band(
                                            plasma_enum_t uplo,
                                            int it,
                                            int jt,
                                            int m,
                                            int n,
                                            int nb,
                                            int kl,
                                            int ku,
                                            const double *B,
                                            int ldb,
                                            double *A,
                                            int lda
                                            )
{

    int count = profile.core_count[CORE_DLACPY_TILE2LAPACK_BAND]++;

    profile.time_kernel((unsigned long)CORE_DLACPY_TILE2LAPACK_BAND, count);
    ((core_dlacpy_tile2lapack_band_hook_type)profile.core[CORE_DLACPY_TILE2LAPACK_BAND])(
                                                                                            uplo,
                                                                                            it,
                                                                                            jt,
                                                                                            m,
                                                                                            n,
                                                                                            nb,
                                                                                            kl,
                                                                                            ku,
                                                                                            B,
                                                                                            ldb,
                                                                                            A,
                                                                                            lda
                                                                                            );

    profile.time_kernel((unsigned long)CORE_DLACPY_TILE2LAPACK_BAND, count);

    return;
}

extern "C" void core_ssyrk(
                          plasma_enum_t uplo,
                          plasma_enum_t trans,
                          int n,
                          int k,
                          float alpha,
                          const float *A,
                          int lda,
                          float beta,
                          float *C,
                          int ldc
                          )
{

    int count = profile.core_count[CORE_SSYRK]++;

    profile.time_kernel((unsigned long)CORE_SSYRK, count);
    ((core_ssyrk_hook_type)profile.core[CORE_SSYRK])(
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

    profile.time_kernel((unsigned long)CORE_SSYRK, count);

    return;
}

extern "C" int core_ctsqrt(
                          int m,
                          int n,
                          int ib,
                          plasma_complex32_t *A1,
                          int lda1,
                          plasma_complex32_t *A2,
                          int lda2,
                          plasma_complex32_t *T,
                          int ldt,
                          plasma_complex32_t *tau,
                          plasma_complex32_t *work
                          )
{

    int count = profile.core_count[CORE_CTSQRT]++;

    profile.time_kernel((unsigned long)CORE_CTSQRT, count);
    int ret_val;

    ret_val = ((core_ctsqrt_hook_type)profile.core[CORE_CTSQRT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_CTSQRT, count);

    return ret_val;
}

extern "C" void core_zsyrk(
                          plasma_enum_t uplo,
                          plasma_enum_t trans,
                          int n,
                          int k,
                          plasma_complex64_t alpha,
                          const plasma_complex64_t *A,
                          int lda,
                          plasma_complex64_t beta,
                          plasma_complex64_t *C,
                          int ldc
                          )
{

    int count = profile.core_count[CORE_ZSYRK]++;

    profile.time_kernel((unsigned long)CORE_ZSYRK, count);
    ((core_zsyrk_hook_type)profile.core[CORE_ZSYRK])(
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

    profile.time_kernel((unsigned long)CORE_ZSYRK, count);

    return;
}

extern "C" void core_dsyr2k(
                           plasma_enum_t uplo,
                           plasma_enum_t trans,
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

    int count = profile.core_count[CORE_DSYR2K]++;

    profile.time_kernel((unsigned long)CORE_DSYR2K, count);
    ((core_dsyr2k_hook_type)profile.core[CORE_DSYR2K])(
                                                          uplo,
                                                          trans,
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

    profile.time_kernel((unsigned long)CORE_DSYR2K, count);

    return;
}

extern "C" void core_zlansy(
                           plasma_enum_t norm,
                           plasma_enum_t uplo,
                           int n,
                           const plasma_complex64_t *A,
                           int lda,
                           double *work,
                           double *value
                           )
{

    int count = profile.core_count[CORE_ZLANSY]++;

    profile.time_kernel((unsigned long)CORE_ZLANSY, count);
    ((core_zlansy_hook_type)profile.core[CORE_ZLANSY])(
                                                          norm,
                                                          uplo,
                                                          n,
                                                          A,
                                                          lda,
                                                          work,
                                                          value
                                                          );

    profile.time_kernel((unsigned long)CORE_ZLANSY, count);

    return;
}

extern "C" int core_dttmqr(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int ib,
                          double *A1,
                          int lda1,
                          double *A2,
                          int lda2,
                          const double *V,
                          int ldv,
                          const double *T,
                          int ldt,
                          double *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_DTTMQR]++;

    profile.time_kernel((unsigned long)CORE_DTTMQR, count);
    int ret_val;

    ret_val = ((core_dttmqr_hook_type)profile.core[CORE_DTTMQR])(
                                                                side,
                                                                trans,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_DTTMQR, count);

    return ret_val;
}

extern "C" double core_dcabs1(
                             plasma_complex64_t alpha
                             )
{

    int count = profile.core_count[CORE_DCABS1]++;

    profile.time_kernel((unsigned long)CORE_DCABS1, count);
    double ret_val;

    ret_val = ((core_dcabs1_hook_type)profile.core[CORE_DCABS1])(
                                                                alpha
                                                                );

    profile.time_kernel((unsigned long)CORE_DCABS1, count);

    return ret_val;
}

extern "C" int core_cttmqr(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int ib,
                          plasma_complex32_t *A1,
                          int lda1,
                          plasma_complex32_t *A2,
                          int lda2,
                          const plasma_complex32_t *V,
                          int ldv,
                          const plasma_complex32_t *T,
                          int ldt,
                          plasma_complex32_t *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_CTTMQR]++;

    profile.time_kernel((unsigned long)CORE_CTTMQR, count);
    int ret_val;

    ret_val = ((core_cttmqr_hook_type)profile.core[CORE_CTTMQR])(
                                                                side,
                                                                trans,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_CTTMQR, count);

    return ret_val;
}

extern "C" void core_zlacpy_lapack2tile_band(
                                            plasma_enum_t uplo,
                                            int it,
                                            int jt,
                                            int m,
                                            int n,
                                            int nb,
                                            int kl,
                                            int ku,
                                            const plasma_complex64_t *A,
                                            int lda,
                                            plasma_complex64_t *B,
                                            int ldb
                                            )
{

    int count = profile.core_count[CORE_ZLACPY_LAPACK2TILE_BAND]++;

    profile.time_kernel((unsigned long)CORE_ZLACPY_LAPACK2TILE_BAND, count);
    ((core_zlacpy_lapack2tile_band_hook_type)profile.core[CORE_ZLACPY_LAPACK2TILE_BAND])(
                                                                                            uplo,
                                                                                            it,
                                                                                            jt,
                                                                                            m,
                                                                                            n,
                                                                                            nb,
                                                                                            kl,
                                                                                            ku,
                                                                                            A,
                                                                                            lda,
                                                                                            B,
                                                                                            ldb
                                                                                            );

    profile.time_kernel((unsigned long)CORE_ZLACPY_LAPACK2TILE_BAND, count);

    return;
}

extern "C" int core_dpotrf(
                          plasma_enum_t uplo,
                          int n,
                          double *A,
                          int lda
                          )
{

    int count = profile.core_count[CORE_DPOTRF]++;

    profile.time_kernel((unsigned long)CORE_DPOTRF, count);
    int ret_val;

    ret_val = ((core_dpotrf_hook_type)profile.core[CORE_DPOTRF])(
                                                                uplo,
                                                                n,
                                                                A,
                                                                lda
                                                                );

    profile.time_kernel((unsigned long)CORE_DPOTRF, count);

    return ret_val;
}

extern "C" int core_ctrtri(
                          plasma_enum_t uplo,
                          plasma_enum_t diag,
                          int n,
                          plasma_complex32_t *A,
                          int lda
                          )
{

    int count = profile.core_count[CORE_CTRTRI]++;

    profile.time_kernel((unsigned long)CORE_CTRTRI, count);
    int ret_val;

    ret_val = ((core_ctrtri_hook_type)profile.core[CORE_CTRTRI])(
                                                                uplo,
                                                                diag,
                                                                n,
                                                                A,
                                                                lda
                                                                );

    profile.time_kernel((unsigned long)CORE_CTRTRI, count);

    return ret_val;
}

extern "C" int core_sttmqr(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int ib,
                          float *A1,
                          int lda1,
                          float *A2,
                          int lda2,
                          const float *V,
                          int ldv,
                          const float *T,
                          int ldt,
                          float *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_STTMQR]++;

    profile.time_kernel((unsigned long)CORE_STTMQR, count);
    int ret_val;

    ret_val = ((core_sttmqr_hook_type)profile.core[CORE_STTMQR])(
                                                                side,
                                                                trans,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_STTMQR, count);

    return ret_val;
}

extern "C" void core_dgeswp(
                           plasma_enum_t colrow,
                           plasma_desc_t A,
                           int k1,
                           int k2,
                           const int *ipiv,
                           int incx
                           )
{

    int count = profile.core_count[CORE_DGESWP]++;

    profile.time_kernel((unsigned long)CORE_DGESWP, count);
    ((core_dgeswp_hook_type)profile.core[CORE_DGESWP])(
                                                          colrow,
                                                          A,
                                                          k1,
                                                          k2,
                                                          ipiv,
                                                          incx
                                                          );

    profile.time_kernel((unsigned long)CORE_DGESWP, count);

    return;
}

extern "C" int core_sttlqt(
                          int m,
                          int n,
                          int ib,
                          float *A1,
                          int lda1,
                          float *A2,
                          int lda2,
                          float *T,
                          int ldt,
                          float *tau,
                          float *work
                          )
{

    int count = profile.core_count[CORE_STTLQT]++;

    profile.time_kernel((unsigned long)CORE_STTLQT, count);
    int ret_val;

    ret_val = ((core_sttlqt_hook_type)profile.core[CORE_STTLQT])(
                                                                m,
                                                                n,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                T,
                                                                ldt,
                                                                tau,
                                                                work
                                                                );

    profile.time_kernel((unsigned long)CORE_STTLQT, count);

    return ret_val;
}

extern "C" int core_cpotrf(
                          plasma_enum_t uplo,
                          int n,
                          plasma_complex32_t *A,
                          int lda
                          )
{

    int count = profile.core_count[CORE_CPOTRF]++;

    profile.time_kernel((unsigned long)CORE_CPOTRF, count);
    int ret_val;

    ret_val = ((core_cpotrf_hook_type)profile.core[CORE_CPOTRF])(
                                                                uplo,
                                                                n,
                                                                A,
                                                                lda
                                                                );

    profile.time_kernel((unsigned long)CORE_CPOTRF, count);

    return ret_val;
}

extern "C" int core_ztsmqr(
                          plasma_enum_t side,
                          plasma_enum_t trans,
                          int m1,
                          int n1,
                          int m2,
                          int n2,
                          int k,
                          int ib,
                          plasma_complex64_t *A1,
                          int lda1,
                          plasma_complex64_t *A2,
                          int lda2,
                          const plasma_complex64_t *V,
                          int ldv,
                          const plasma_complex64_t *T,
                          int ldt,
                          plasma_complex64_t *work,
                          int ldwork
                          )
{

    int count = profile.core_count[CORE_ZTSMQR]++;

    profile.time_kernel((unsigned long)CORE_ZTSMQR, count);
    int ret_val;

    ret_val = ((core_ztsmqr_hook_type)profile.core[CORE_ZTSMQR])(
                                                                side,
                                                                trans,
                                                                m1,
                                                                n1,
                                                                m2,
                                                                n2,
                                                                k,
                                                                ib,
                                                                A1,
                                                                lda1,
                                                                A2,
                                                                lda2,
                                                                V,
                                                                ldv,
                                                                T,
                                                                ldt,
                                                                work,
                                                                ldwork
                                                                );

    profile.time_kernel((unsigned long)CORE_ZTSMQR, count);

    return ret_val;
}

extern "C" void core_cgeswp(
                           plasma_enum_t colrow,
                           plasma_desc_t A,
                           int k1,
                           int k2,
                           const int *ipiv,
                           int incx
                           )
{

    int count = profile.core_count[CORE_CGESWP]++;

    profile.time_kernel((unsigned long)CORE_CGESWP, count);
    ((core_cgeswp_hook_type)profile.core[CORE_CGESWP])(
                                                          colrow,
                                                          A,
                                                          k1,
                                                          k2,
                                                          ipiv,
                                                          incx
                                                          );

    profile.time_kernel((unsigned long)CORE_CGESWP, count);

    return;
}

extern "C" int core_zhegst(
                          int itype,
                          plasma_enum_t uplo,
                          int n,
                          plasma_complex64_t *A,
                          int lda,
                          plasma_complex64_t *B,
                          int ldb
                          )
{

    int count = profile.core_count[CORE_ZHEGST]++;

    profile.time_kernel((unsigned long)CORE_ZHEGST, count);
    int ret_val;

    ret_val = ((core_zhegst_hook_type)profile.core[CORE_ZHEGST])(
                                                                itype,
                                                                uplo,
                                                                n,
                                                                A,
                                                                lda,
                                                                B,
                                                                ldb
                                                                );

    profile.time_kernel((unsigned long)CORE_ZHEGST, count);

    return ret_val;
}

extern "C" void core_zsyssq(
                           plasma_enum_t uplo,
                           int n,
                           const plasma_complex64_t *A,
                           int lda,
                           double *scale,
                           double *sumsq
                           )
{

    int count = profile.core_count[CORE_ZSYSSQ]++;

    profile.time_kernel((unsigned long)CORE_ZSYSSQ, count);
    ((core_zsyssq_hook_type)profile.core[CORE_ZSYSSQ])(
                                                          uplo,
                                                          n,
                                                          A,
                                                          lda,
                                                          scale,
                                                          sumsq
                                                          );

    profile.time_kernel((unsigned long)CORE_ZSYSSQ, count);

    return;
}

