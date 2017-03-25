#include "mkl_cblas.h"
#include "plasma.h"
#include "mkl_lapacke.h"

using namespace std;
enum functions_enum
{
    CORE_DLANGE = 0,
    CORE_CHER2K = 1,
    CORE_ZGEADD = 2,
    CORE_SSYR2K = 3,
    CORE_CTSMLQ = 4,
    CORE_DGESSQ = 5,
    CORE_ZUNMLQ = 6,
    CORE_ZLASET = 7,
    CORE_ZSYR2K = 8,
    CORE_CSYMM = 9,
    CORE_CPARFB = 10,
    CORE_DLAUUM = 11,
    CORE_CUNMQR = 12,
    CORE_ZTSLQT = 13,
    CORE_SPEMV = 14,
    CORE_CGEADD = 15,
    CORE_STRSM = 16,
    CORE_DTTQRT = 17,
    CORE_DTRTRI = 18,
    CORE_CGELQT = 19,
    CORE_CLANGE = 20,
    CORE_SLASCL = 21,
    CORE_CSYR2K = 22,
    CORE_ZTSQRT = 23,
    CORE_ZGESSQ = 24,
    CORE_ZTRMM = 25,
    CORE_DTRSSQ = 26,
    CORE_DLASCL = 27,
    CORE_CTRMM = 28,
    CORE_DSYMM = 29,
    CORE_DGEQRT = 30,
    CORE_CPAMM = 31,
    CORE_ZLACPY_TILE2LAPACK_BAND = 32,
    CORE_CGETRF = 33,
    CORE_SLAUUM = 34,
    CORE_CGEMM = 35,
    CORE_ZHER2K = 36,
    CORE_SSYSSQ = 37,
    CORE_DPAMM = 38,
    CORE_STTQRT = 39,
    CORE_DTRMM = 40,
    CORE_SSYSWP = 41,
    CORE_SSYMM = 42,
    CORE_CSYSSQ = 43,
    CORE_DPEMV = 44,
    CORE_CGESSQ = 45,
    CORE_CLANSY = 46,
    CORE_DORMLQ = 47,
    CORE_ZHESSQ = 48,
    CORE_CLACPY = 49,
    CORE_DLANTR = 50,
    CORE_SLASET = 51,
    CORE_CTTQRT = 52,
    CORE_SGEQRT = 53,
    CORE_SLACPY_LAPACK2TILE_BAND = 54,
    CORE_DLACPY_LAPACK2TILE_BAND = 55,
    CORE_STRMM = 56,
    CORE_SSYGST = 57,
    CORE_CGEQRT = 58,
    CORE_ZTRTRI = 59,
    CORE_ZTSMLQ = 60,
    CORE_ZSYMM = 61,
    CORE_CLACPY_TILE2LAPACK_BAND = 62,
    CORE_DORMQR = 63,
    CORE_STSMQR = 64,
    CORE_CTRSSQ = 65,
    CORE_SLANSY = 66,
    CORE_DGETRF = 67,
    CORE_CTRADD = 68,
    CORE_CHESWP = 69,
    CORE_STTMLQ = 70,
    CORE_ZHESWP = 71,
    CORE_CHEGST = 72,
    CORE_DTTLQT = 73,
    CORE_CTSMQR = 74,
    CORE_STSQRT = 75,
    CORE_CLAUUM = 76,
    CORE_SLACPY = 77,
    CORE_ZLASCL = 78,
    CORE_STRTRI = 79,
    CORE_CSYRK = 80,
    CORE_SGELQT = 81,
    CORE_CLASET = 82,
    CORE_SLACPY_TILE2LAPACK_BAND = 83,
    CORE_SORMQR = 84,
    CORE_STRADD = 85,
    CORE_DTTMLQ = 86,
    CORE_SCABS1 = 87,
    CORE_SLANGE = 88,
    CORE_ZLANHE = 89,
    CORE_SGESWP = 90,
    CORE_DTRADD = 91,
    CORE_DSYRK = 92,
    CORE_DSYSWP = 93,
    CORE_DTRSM = 94,
    CORE_STSLQT = 95,
    CORE_ZTRSSQ = 96,
    CORE_CLASCL = 97,
    CORE_ZGELQT = 98,
    CORE_CHESSQ = 99,
    CORE_DGEADD = 100,
    CORE_DTSMLQ = 101,
    CORE_DLANSY = 102,
    CORE_ZTTLQT = 103,
    CORE_ZHEMM = 104,
    CORE_CLACPY_LAPACK2TILE_BAND = 105,
    CORE_SGEADD = 106,
    CORE_ZGEMM = 107,
    CORE_CHERK = 108,
    CORE_DTSMQR = 109,
    CORE_CLANTR = 110,
    CORE_ZGESWP = 111,
    CORE_ZTTQRT = 112,
    CORE_ZHERK = 113,
    CORE_ZGEQRT = 114,
    CORE_CTRSM = 115,
    CORE_DTSQRT = 116,
    CORE_SGEMM = 117,
    CORE_SPOTRF = 118,
    CORE_ZPEMV = 119,
    CORE_ZPAMM = 120,
    CORE_SORMLQ = 121,
    CORE_ZTRADD = 122,
    CORE_ZLAUUM = 123,
    CORE_DPARFB = 124,
    CORE_DGELQT = 125,
    CORE_SGETRF = 126,
    CORE_ZPARFB = 127,
    CORE_SPAMM = 128,
    CORE_CHEMM = 129,
    CORE_DSYSSQ = 130,
    CORE_DSYGST = 131,
    CORE_ZTTMQR = 132,
    CORE_DLACPY = 133,
    CORE_SPARFB = 134,
    CORE_ZTRSM = 135,
    CORE_ZUNMQR = 136,
    CORE_ZGETRF = 137,
    CORE_CUNMLQ = 138,
    CORE_SGESSQ = 139,
    CORE_CTTLQT = 140,
    CORE_CPEMV = 141,
    CORE_ZLANTR = 142,
    CORE_ZLANGE = 143,
    CORE_SLANTR = 144,
    CORE_ZLACPY = 145,
    CORE_CTTMLQ = 146,
    CORE_DGEMM = 147,
    CORE_ZPOTRF = 148,
    CORE_STRSSQ = 149,
    CORE_CTSLQT = 150,
    CORE_CLANHE = 151,
    CORE_STSMLQ = 152,
    CORE_DLASET = 153,
    CORE_DTSLQT = 154,
    CORE_ZTTMLQ = 155,
    CORE_DLACPY_TILE2LAPACK_BAND = 156,
    CORE_SSYRK = 157,
    CORE_CTSQRT = 158,
    CORE_ZSYRK = 159,
    CORE_DSYR2K = 160,
    CORE_ZLANSY = 161,
    CORE_DTTMQR = 162,
    CORE_DCABS1 = 163,
    CORE_CTTMQR = 164,
    CORE_ZLACPY_LAPACK2TILE_BAND = 165,
    CORE_DPOTRF = 166,
    CORE_CTRTRI = 167,
    CORE_STTMQR = 168,
    CORE_DGESWP = 169,
    CORE_STTLQT = 170,
    CORE_CPOTRF = 171,
    CORE_ZTSMQR = 172,
    CORE_CGESWP = 173,
    CORE_ZHEGST = 174,
    CORE_ZSYSSQ = 175,

    TABLE_SIZE
};

const string kernel_table[] =
{
    "core_dlange",
    "core_cher2k",
    "core_zgeadd",
    "core_ssyr2k",
    "core_ctsmlq",
    "core_dgessq",
    "core_zunmlq",
    "core_zlaset",
    "core_zsyr2k",
    "core_csymm",
    "core_cparfb",
    "core_dlauum",
    "core_cunmqr",
    "core_ztslqt",
    "core_spemv",
    "core_cgeadd",
    "core_strsm",
    "core_dttqrt",
    "core_dtrtri",
    "core_cgelqt",
    "core_clange",
    "core_slascl",
    "core_csyr2k",
    "core_ztsqrt",
    "core_zgessq",
    "core_ztrmm",
    "core_dtrssq",
    "core_dlascl",
    "core_ctrmm",
    "core_dsymm",
    "core_dgeqrt",
    "core_cpamm",
    "core_zlacpy_tile2lapack_band",
    "core_cgetrf",
    "core_slauum",
    "core_cgemm",
    "core_zher2k",
    "core_ssyssq",
    "core_dpamm",
    "core_sttqrt",
    "core_dtrmm",
    "core_ssyswp",
    "core_ssymm",
    "core_csyssq",
    "core_dpemv",
    "core_cgessq",
    "core_clansy",
    "core_dormlq",
    "core_zhessq",
    "core_clacpy",
    "core_dlantr",
    "core_slaset",
    "core_cttqrt",
    "core_sgeqrt",
    "core_slacpy_lapack2tile_band",
    "core_dlacpy_lapack2tile_band",
    "core_strmm",
    "core_ssygst",
    "core_cgeqrt",
    "core_ztrtri",
    "core_ztsmlq",
    "core_zsymm",
    "core_clacpy_tile2lapack_band",
    "core_dormqr",
    "core_stsmqr",
    "core_ctrssq",
    "core_slansy",
    "core_dgetrf",
    "core_ctradd",
    "core_cheswp",
    "core_sttmlq",
    "core_zheswp",
    "core_chegst",
    "core_dttlqt",
    "core_ctsmqr",
    "core_stsqrt",
    "core_clauum",
    "core_slacpy",
    "core_zlascl",
    "core_strtri",
    "core_csyrk",
    "core_sgelqt",
    "core_claset",
    "core_slacpy_tile2lapack_band",
    "core_sormqr",
    "core_stradd",
    "core_dttmlq",
    "core_scabs1",
    "core_slange",
    "core_zlanhe",
    "core_sgeswp",
    "core_dtradd",
    "core_dsyrk",
    "core_dsyswp",
    "core_dtrsm",
    "core_stslqt",
    "core_ztrssq",
    "core_clascl",
    "core_zgelqt",
    "core_chessq",
    "core_dgeadd",
    "core_dtsmlq",
    "core_dlansy",
    "core_zttlqt",
    "core_zhemm",
    "core_clacpy_lapack2tile_band",
    "core_sgeadd",
    "core_zgemm",
    "core_cherk",
    "core_dtsmqr",
    "core_clantr",
    "core_zgeswp",
    "core_zttqrt",
    "core_zherk",
    "core_zgeqrt",
    "core_ctrsm",
    "core_dtsqrt",
    "core_sgemm",
    "core_spotrf",
    "core_zpemv",
    "core_zpamm",
    "core_sormlq",
    "core_ztradd",
    "core_zlauum",
    "core_dparfb",
    "core_dgelqt",
    "core_sgetrf",
    "core_zparfb",
    "core_spamm",
    "core_chemm",
    "core_dsyssq",
    "core_dsygst",
    "core_zttmqr",
    "core_dlacpy",
    "core_sparfb",
    "core_ztrsm",
    "core_zunmqr",
    "core_zgetrf",
    "core_cunmlq",
    "core_sgessq",
    "core_cttlqt",
    "core_cpemv",
    "core_zlantr",
    "core_zlange",
    "core_slantr",
    "core_zlacpy",
    "core_cttmlq",
    "core_dgemm",
    "core_zpotrf",
    "core_strssq",
    "core_ctslqt",
    "core_clanhe",
    "core_stsmlq",
    "core_dlaset",
    "core_dtslqt",
    "core_zttmlq",
    "core_dlacpy_tile2lapack_band",
    "core_ssyrk",
    "core_ctsqrt",
    "core_zsyrk",
    "core_dsyr2k",
    "core_zlansy",
    "core_dttmqr",
    "core_dcabs1",
    "core_cttmqr",
    "core_zlacpy_lapack2tile_band",
    "core_dpotrf",
    "core_ctrtri",
    "core_sttmqr",
    "core_dgeswp",
    "core_sttlqt",
    "core_cpotrf",
    "core_ztsmqr",
    "core_cgeswp",
    "core_zhegst",
    "core_zsyssq",
};

typedef void (*core_dlange_hook_type)(
                                     plasma_enum_t norm,
                                     int m,
                                     int n,
                                     const double *A,
                                     int lda,
                                     double *work,
                                     double *result
                                     );

typedef void (*core_cher2k_hook_type)(
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
                                     );

typedef int (*core_zgeadd_hook_type)(
                                    plasma_enum_t transa,
                                    int m,
                                    int n,
                                    plasma_complex64_t alpha,
                                    const plasma_complex64_t *A,
                                    int lda,
                                    plasma_complex64_t beta,
                                    plasma_complex64_t *B,
                                    int ldb
                                    );

typedef void (*core_ssyr2k_hook_type)(
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
                                     );

typedef int (*core_ctsmlq_hook_type)(
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
                                    );

typedef void (*core_dgessq_hook_type)(
                                     int m,
                                     int n,
                                     const double *A,
                                     int lda,
                                     double *scale,
                                     double *sumsq
                                     );

typedef int (*core_zunmlq_hook_type)(
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
                                    );

typedef void (*core_zlaset_hook_type)(
                                     plasma_enum_t uplo,
                                     int m,
                                     int n,
                                     plasma_complex64_t alpha,
                                     plasma_complex64_t beta,
                                     plasma_complex64_t *A,
                                     int lda
                                     );

typedef void (*core_zsyr2k_hook_type)(
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
                                     );

typedef void (*core_csymm_hook_type)(
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
                                    );

typedef int (*core_cparfb_hook_type)(
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
                                    );

typedef int (*core_dlauum_hook_type)(
                                    plasma_enum_t uplo,
                                    int n,
                                    double *A,
                                    int lda
                                    );

typedef int (*core_cunmqr_hook_type)(
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
                                    );

typedef int (*core_ztslqt_hook_type)(
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
                                    );

typedef int (*core_spemv_hook_type)(
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
                                   );

typedef int (*core_cgeadd_hook_type)(
                                    plasma_enum_t transa,
                                    int m,
                                    int n,
                                    plasma_complex32_t alpha,
                                    const plasma_complex32_t *A,
                                    int lda,
                                    plasma_complex32_t beta,
                                    plasma_complex32_t *B,
                                    int ldb
                                    );

typedef void (*core_strsm_hook_type)(
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
                                    );

typedef int (*core_dttqrt_hook_type)(
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
                                    );

typedef int (*core_dtrtri_hook_type)(
                                    plasma_enum_t uplo,
                                    plasma_enum_t diag,
                                    int n,
                                    double *A,
                                    int lda
                                    );

typedef int (*core_cgelqt_hook_type)(
                                    int m,
                                    int n,
                                    int ib,
                                    plasma_complex32_t *A,
                                    int lda,
                                    plasma_complex32_t *T,
                                    int ldt,
                                    plasma_complex32_t *tau,
                                    plasma_complex32_t *work
                                    );

typedef void (*core_clange_hook_type)(
                                     plasma_enum_t norm,
                                     int m,
                                     int n,
                                     const plasma_complex32_t *A,
                                     int lda,
                                     float *work,
                                     float *result
                                     );

typedef void (*core_slascl_hook_type)(
                                     plasma_enum_t uplo,
                                     float cfrom,
                                     float cto,
                                     int m,
                                     int n,
                                     float *A,
                                     int lda
                                     );

typedef void (*core_csyr2k_hook_type)(
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
                                     );

typedef int (*core_ztsqrt_hook_type)(
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
                                    );

typedef void (*core_zgessq_hook_type)(
                                     int m,
                                     int n,
                                     const plasma_complex64_t *A,
                                     int lda,
                                     double *scale,
                                     double *sumsq
                                     );

typedef void (*core_ztrmm_hook_type)(
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
                                    );

typedef void (*core_dtrssq_hook_type)(
                                     plasma_enum_t uplo,
                                     plasma_enum_t diag,
                                     int m,
                                     int n,
                                     const double *A,
                                     int lda,
                                     double *scale,
                                     double *sumsq
                                     );

typedef void (*core_dlascl_hook_type)(
                                     plasma_enum_t uplo,
                                     double cfrom,
                                     double cto,
                                     int m,
                                     int n,
                                     double *A,
                                     int lda
                                     );

typedef void (*core_ctrmm_hook_type)(
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
                                    );

typedef void (*core_dsymm_hook_type)(
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
                                    );

typedef int (*core_dgeqrt_hook_type)(
                                    int m,
                                    int n,
                                    int ib,
                                    double *A,
                                    int lda,
                                    double *T,
                                    int ldt,
                                    double *tau,
                                    double *work
                                    );

typedef int (*core_cpamm_hook_type)(
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
                                   );

typedef void (*core_zlacpy_tile2lapack_band_hook_type)(
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
                                                      );

typedef int (*core_cgetrf_hook_type)(
                                    plasma_desc_t A,
                                    int *ipiv,
                                    int ib,
                                    int rank,
                                    int size,
                                    plasma_barrier_t *barrier
                                    );

typedef int (*core_slauum_hook_type)(
                                    plasma_enum_t uplo,
                                    int n,
                                    float *A,
                                    int lda
                                    );

typedef void (*core_cgemm_hook_type)(
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
                                    );

typedef void (*core_zher2k_hook_type)(
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
                                     );

typedef void (*core_ssyssq_hook_type)(
                                     plasma_enum_t uplo,
                                     int n,
                                     const float *A,
                                     int lda,
                                     float *scale,
                                     float *sumsq
                                     );

typedef int (*core_dpamm_hook_type)(
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
                                   );

typedef int (*core_sttqrt_hook_type)(
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
                                    );

typedef void (*core_dtrmm_hook_type)(
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
                                    );

typedef void (*core_ssyswp_hook_type)(
                                     int uplo,
                                     plasma_desc_t A,
                                     int k1,
                                     int k2,
                                     const int *ipiv,
                                     int incx
                                     );

typedef void (*core_ssymm_hook_type)(
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
                                    );

typedef void (*core_csyssq_hook_type)(
                                     plasma_enum_t uplo,
                                     int n,
                                     const plasma_complex32_t *A,
                                     int lda,
                                     float *scale,
                                     float *sumsq
                                     );

typedef int (*core_dpemv_hook_type)(
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
                                   );

typedef void (*core_cgessq_hook_type)(
                                     int m,
                                     int n,
                                     const plasma_complex32_t *A,
                                     int lda,
                                     float *scale,
                                     float *sumsq
                                     );

typedef void (*core_clansy_hook_type)(
                                     plasma_enum_t norm,
                                     plasma_enum_t uplo,
                                     int n,
                                     const plasma_complex32_t *A,
                                     int lda,
                                     float *work,
                                     float *value
                                     );

typedef int (*core_dormlq_hook_type)(
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
                                    );

typedef void (*core_zhessq_hook_type)(
                                     plasma_enum_t uplo,
                                     int n,
                                     const plasma_complex64_t *A,
                                     int lda,
                                     double *scale,
                                     double *sumsq
                                     );

typedef void (*core_clacpy_hook_type)(
                                     plasma_enum_t uplo,
                                     plasma_enum_t transa,
                                     int m,
                                     int n,
                                     const plasma_complex32_t *A,
                                     int lda,
                                     plasma_complex32_t *B,
                                     int ldb
                                     );

typedef void (*core_dlantr_hook_type)(
                                     plasma_enum_t norm,
                                     plasma_enum_t uplo,
                                     plasma_enum_t diag,
                                     int m,
                                     int n,
                                     const double *A,
                                     int lda,
                                     double *work,
                                     double *value
                                     );

typedef void (*core_slaset_hook_type)(
                                     plasma_enum_t uplo,
                                     int m,
                                     int n,
                                     float alpha,
                                     float beta,
                                     float *A,
                                     int lda
                                     );

typedef int (*core_cttqrt_hook_type)(
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
                                    );

typedef int (*core_sgeqrt_hook_type)(
                                    int m,
                                    int n,
                                    int ib,
                                    float *A,
                                    int lda,
                                    float *T,
                                    int ldt,
                                    float *tau,
                                    float *work
                                    );

typedef void (*core_slacpy_lapack2tile_band_hook_type)(
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
                                                      );

typedef void (*core_dlacpy_lapack2tile_band_hook_type)(
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
                                                      );

typedef void (*core_strmm_hook_type)(
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
                                    );

typedef int (*core_ssygst_hook_type)(
                                    int itype,
                                    plasma_enum_t uplo,
                                    int n,
                                    float *A,
                                    int lda,
                                    float *B,
                                    int ldb
                                    );

typedef int (*core_cgeqrt_hook_type)(
                                    int m,
                                    int n,
                                    int ib,
                                    plasma_complex32_t *A,
                                    int lda,
                                    plasma_complex32_t *T,
                                    int ldt,
                                    plasma_complex32_t *tau,
                                    plasma_complex32_t *work
                                    );

typedef int (*core_ztrtri_hook_type)(
                                    plasma_enum_t uplo,
                                    plasma_enum_t diag,
                                    int n,
                                    plasma_complex64_t *A,
                                    int lda
                                    );

typedef int (*core_ztsmlq_hook_type)(
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
                                    );

typedef void (*core_zsymm_hook_type)(
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
                                    );

typedef void (*core_clacpy_tile2lapack_band_hook_type)(
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
                                                      );

typedef int (*core_dormqr_hook_type)(
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
                                    );

typedef int (*core_stsmqr_hook_type)(
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
                                    );

typedef void (*core_ctrssq_hook_type)(
                                     plasma_enum_t uplo,
                                     plasma_enum_t diag,
                                     int m,
                                     int n,
                                     const plasma_complex32_t *A,
                                     int lda,
                                     float *scale,
                                     float *sumsq
                                     );

typedef void (*core_slansy_hook_type)(
                                     plasma_enum_t norm,
                                     plasma_enum_t uplo,
                                     int n,
                                     const float *A,
                                     int lda,
                                     float *work,
                                     float *value
                                     );

typedef int (*core_dgetrf_hook_type)(
                                    plasma_desc_t A,
                                    int *ipiv,
                                    int ib,
                                    int rank,
                                    int size,
                                    plasma_barrier_t *barrier
                                    );

typedef int (*core_ctradd_hook_type)(
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
                                    );

typedef void (*core_cheswp_hook_type)(
                                     int uplo,
                                     plasma_desc_t A,
                                     int k1,
                                     int k2,
                                     const int *ipiv,
                                     int incx
                                     );

typedef int (*core_sttmlq_hook_type)(
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
                                    );

typedef void (*core_zheswp_hook_type)(
                                     int uplo,
                                     plasma_desc_t A,
                                     int k1,
                                     int k2,
                                     const int *ipiv,
                                     int incx
                                     );

typedef int (*core_chegst_hook_type)(
                                    int itype,
                                    plasma_enum_t uplo,
                                    int n,
                                    plasma_complex32_t *A,
                                    int lda,
                                    plasma_complex32_t *B,
                                    int ldb
                                    );

typedef int (*core_dttlqt_hook_type)(
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
                                    );

typedef int (*core_ctsmqr_hook_type)(
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
                                    );

typedef int (*core_stsqrt_hook_type)(
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
                                    );

typedef int (*core_clauum_hook_type)(
                                    plasma_enum_t uplo,
                                    int n,
                                    plasma_complex32_t *A,
                                    int lda
                                    );

typedef void (*core_slacpy_hook_type)(
                                     plasma_enum_t uplo,
                                     plasma_enum_t transa,
                                     int m,
                                     int n,
                                     const float *A,
                                     int lda,
                                     float *B,
                                     int ldb
                                     );

typedef void (*core_zlascl_hook_type)(
                                     plasma_enum_t uplo,
                                     double cfrom,
                                     double cto,
                                     int m,
                                     int n,
                                     plasma_complex64_t *A,
                                     int lda
                                     );

typedef int (*core_strtri_hook_type)(
                                    plasma_enum_t uplo,
                                    plasma_enum_t diag,
                                    int n,
                                    float *A,
                                    int lda
                                    );

typedef void (*core_csyrk_hook_type)(
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
                                    );

typedef int (*core_sgelqt_hook_type)(
                                    int m,
                                    int n,
                                    int ib,
                                    float *A,
                                    int lda,
                                    float *T,
                                    int ldt,
                                    float *tau,
                                    float *work
                                    );

typedef void (*core_claset_hook_type)(
                                     plasma_enum_t uplo,
                                     int m,
                                     int n,
                                     plasma_complex32_t alpha,
                                     plasma_complex32_t beta,
                                     plasma_complex32_t *A,
                                     int lda
                                     );

typedef void (*core_slacpy_tile2lapack_band_hook_type)(
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
                                                      );

typedef int (*core_sormqr_hook_type)(
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
                                    );

typedef int (*core_stradd_hook_type)(
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
                                    );

typedef int (*core_dttmlq_hook_type)(
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
                                    );

typedef float (*core_scabs1_hook_type)(
                                      plasma_complex32_t alpha
                                      );

typedef void (*core_slange_hook_type)(
                                     plasma_enum_t norm,
                                     int m,
                                     int n,
                                     const float *A,
                                     int lda,
                                     float *work,
                                     float *result
                                     );

typedef void (*core_zlanhe_hook_type)(
                                     plasma_enum_t norm,
                                     plasma_enum_t uplo,
                                     int n,
                                     const plasma_complex64_t *A,
                                     int lda,
                                     double *work,
                                     double *value
                                     );

typedef void (*core_sgeswp_hook_type)(
                                     plasma_enum_t colrow,
                                     plasma_desc_t A,
                                     int k1,
                                     int k2,
                                     const int *ipiv,
                                     int incx
                                     );

typedef int (*core_dtradd_hook_type)(
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

typedef void (*core_dsyswp_hook_type)(
                                     int uplo,
                                     plasma_desc_t A,
                                     int k1,
                                     int k2,
                                     const int *ipiv,
                                     int incx
                                     );

typedef void (*core_dtrsm_hook_type)(
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
                                    );

typedef int (*core_stslqt_hook_type)(
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
                                    );

typedef void (*core_ztrssq_hook_type)(
                                     plasma_enum_t uplo,
                                     plasma_enum_t diag,
                                     int m,
                                     int n,
                                     const plasma_complex64_t *A,
                                     int lda,
                                     double *scale,
                                     double *sumsq
                                     );

typedef void (*core_clascl_hook_type)(
                                     plasma_enum_t uplo,
                                     float cfrom,
                                     float cto,
                                     int m,
                                     int n,
                                     plasma_complex32_t *A,
                                     int lda
                                     );

typedef int (*core_zgelqt_hook_type)(
                                    int m,
                                    int n,
                                    int ib,
                                    plasma_complex64_t *A,
                                    int lda,
                                    plasma_complex64_t *T,
                                    int ldt,
                                    plasma_complex64_t *tau,
                                    plasma_complex64_t *work
                                    );

typedef void (*core_chessq_hook_type)(
                                     plasma_enum_t uplo,
                                     int n,
                                     const plasma_complex32_t *A,
                                     int lda,
                                     float *scale,
                                     float *sumsq
                                     );

typedef int (*core_dgeadd_hook_type)(
                                    plasma_enum_t transa,
                                    int m,
                                    int n,
                                    double alpha,
                                    const double *A,
                                    int lda,
                                    double beta,
                                    double *B,
                                    int ldb
                                    );

typedef int (*core_dtsmlq_hook_type)(
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
                                    );

typedef void (*core_dlansy_hook_type)(
                                     plasma_enum_t norm,
                                     plasma_enum_t uplo,
                                     int n,
                                     const double *A,
                                     int lda,
                                     double *work,
                                     double *value
                                     );

typedef int (*core_zttlqt_hook_type)(
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
                                    );

typedef void (*core_zhemm_hook_type)(
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
                                    );

typedef void (*core_clacpy_lapack2tile_band_hook_type)(
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
                                                      );

typedef int (*core_sgeadd_hook_type)(
                                    plasma_enum_t transa,
                                    int m,
                                    int n,
                                    float alpha,
                                    const float *A,
                                    int lda,
                                    float beta,
                                    float *B,
                                    int ldb
                                    );

typedef void (*core_zgemm_hook_type)(
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
                                    );

typedef void (*core_cherk_hook_type)(
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
                                    );

typedef int (*core_dtsmqr_hook_type)(
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
                                    );

typedef void (*core_clantr_hook_type)(
                                     plasma_enum_t norm,
                                     plasma_enum_t uplo,
                                     plasma_enum_t diag,
                                     int m,
                                     int n,
                                     const plasma_complex32_t *A,
                                     int lda,
                                     float *work,
                                     float *value
                                     );

typedef void (*core_zgeswp_hook_type)(
                                     plasma_enum_t colrow,
                                     plasma_desc_t A,
                                     int k1,
                                     int k2,
                                     const int *ipiv,
                                     int incx
                                     );

typedef int (*core_zttqrt_hook_type)(
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
                                    );

typedef void (*core_zherk_hook_type)(
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
                                    );

typedef int (*core_zgeqrt_hook_type)(
                                    int m,
                                    int n,
                                    int ib,
                                    plasma_complex64_t *A,
                                    int lda,
                                    plasma_complex64_t *T,
                                    int ldt,
                                    plasma_complex64_t *tau,
                                    plasma_complex64_t *work
                                    );

typedef void (*core_ctrsm_hook_type)(
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
                                    );

typedef int (*core_dtsqrt_hook_type)(
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
                                    );

typedef void (*core_sgemm_hook_type)(
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
                                    );

typedef int (*core_spotrf_hook_type)(
                                    plasma_enum_t uplo,
                                    int n,
                                    float *A,
                                    int lda
                                    );

typedef int (*core_zpemv_hook_type)(
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
                                   );

typedef int (*core_zpamm_hook_type)(
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
                                   );

typedef int (*core_sormlq_hook_type)(
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
                                    );

typedef int (*core_ztradd_hook_type)(
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
                                    );

typedef int (*core_zlauum_hook_type)(
                                    plasma_enum_t uplo,
                                    int n,
                                    plasma_complex64_t *A,
                                    int lda
                                    );

typedef int (*core_dparfb_hook_type)(
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
                                    );

typedef int (*core_dgelqt_hook_type)(
                                    int m,
                                    int n,
                                    int ib,
                                    double *A,
                                    int lda,
                                    double *T,
                                    int ldt,
                                    double *tau,
                                    double *work
                                    );

typedef int (*core_sgetrf_hook_type)(
                                    plasma_desc_t A,
                                    int *ipiv,
                                    int ib,
                                    int rank,
                                    int size,
                                    plasma_barrier_t *barrier
                                    );

typedef int (*core_zparfb_hook_type)(
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
                                    );

typedef int (*core_spamm_hook_type)(
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
                                   );

typedef void (*core_chemm_hook_type)(
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
                                    );

typedef void (*core_dsyssq_hook_type)(
                                     plasma_enum_t uplo,
                                     int n,
                                     const double *A,
                                     int lda,
                                     double *scale,
                                     double *sumsq
                                     );

typedef int (*core_dsygst_hook_type)(
                                    int itype,
                                    plasma_enum_t uplo,
                                    int n,
                                    double *A,
                                    int lda,
                                    double *B,
                                    int ldb
                                    );

typedef int (*core_zttmqr_hook_type)(
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
                                    );

typedef void (*core_dlacpy_hook_type)(
                                     plasma_enum_t uplo,
                                     plasma_enum_t transa,
                                     int m,
                                     int n,
                                     const double *A,
                                     int lda,
                                     double *B,
                                     int ldb
                                     );

typedef int (*core_sparfb_hook_type)(
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
                                    );

typedef void (*core_ztrsm_hook_type)(
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
                                    );

typedef int (*core_zunmqr_hook_type)(
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
                                    );

typedef int (*core_zgetrf_hook_type)(
                                    plasma_desc_t A,
                                    int *ipiv,
                                    int ib,
                                    int rank,
                                    int size,
                                    plasma_barrier_t *barrier
                                    );

typedef int (*core_cunmlq_hook_type)(
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
                                    );

typedef void (*core_sgessq_hook_type)(
                                     int m,
                                     int n,
                                     const float *A,
                                     int lda,
                                     float *scale,
                                     float *sumsq
                                     );

typedef int (*core_cttlqt_hook_type)(
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
                                    );

typedef int (*core_cpemv_hook_type)(
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
                                   );

typedef void (*core_zlantr_hook_type)(
                                     plasma_enum_t norm,
                                     plasma_enum_t uplo,
                                     plasma_enum_t diag,
                                     int m,
                                     int n,
                                     const plasma_complex64_t *A,
                                     int lda,
                                     double *work,
                                     double *value
                                     );

typedef void (*core_zlange_hook_type)(
                                     plasma_enum_t norm,
                                     int m,
                                     int n,
                                     const plasma_complex64_t *A,
                                     int lda,
                                     double *work,
                                     double *result
                                     );

typedef void (*core_slantr_hook_type)(
                                     plasma_enum_t norm,
                                     plasma_enum_t uplo,
                                     plasma_enum_t diag,
                                     int m,
                                     int n,
                                     const float *A,
                                     int lda,
                                     float *work,
                                     float *value
                                     );

typedef void (*core_zlacpy_hook_type)(
                                     plasma_enum_t uplo,
                                     plasma_enum_t transa,
                                     int m,
                                     int n,
                                     const plasma_complex64_t *A,
                                     int lda,
                                     plasma_complex64_t *B,
                                     int ldb
                                     );

typedef int (*core_cttmlq_hook_type)(
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
                                    );

typedef void (*core_dgemm_hook_type)(
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
                                    );

typedef int (*core_zpotrf_hook_type)(
                                    plasma_enum_t uplo,
                                    int n,
                                    plasma_complex64_t *A,
                                    int lda
                                    );

typedef void (*core_strssq_hook_type)(
                                     plasma_enum_t uplo,
                                     plasma_enum_t diag,
                                     int m,
                                     int n,
                                     const float *A,
                                     int lda,
                                     float *scale,
                                     float *sumsq
                                     );

typedef int (*core_ctslqt_hook_type)(
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
                                    );

typedef void (*core_clanhe_hook_type)(
                                     plasma_enum_t norm,
                                     plasma_enum_t uplo,
                                     int n,
                                     const plasma_complex32_t *A,
                                     int lda,
                                     float *work,
                                     float *value
                                     );

typedef int (*core_stsmlq_hook_type)(
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
                                    );

typedef void (*core_dlaset_hook_type)(
                                     plasma_enum_t uplo,
                                     int m,
                                     int n,
                                     double alpha,
                                     double beta,
                                     double *A,
                                     int lda
                                     );

typedef int (*core_dtslqt_hook_type)(
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
                                    );

typedef int (*core_zttmlq_hook_type)(
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
                                    );

typedef void (*core_dlacpy_tile2lapack_band_hook_type)(
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
                                                      );

typedef void (*core_ssyrk_hook_type)(
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
                                    );

typedef int (*core_ctsqrt_hook_type)(
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
                                    );

typedef void (*core_zsyrk_hook_type)(
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
                                    );

typedef void (*core_dsyr2k_hook_type)(
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
                                     );

typedef void (*core_zlansy_hook_type)(
                                     plasma_enum_t norm,
                                     plasma_enum_t uplo,
                                     int n,
                                     const plasma_complex64_t *A,
                                     int lda,
                                     double *work,
                                     double *value
                                     );

typedef int (*core_dttmqr_hook_type)(
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
                                    );

typedef double (*core_dcabs1_hook_type)(
                                       plasma_complex64_t alpha
                                       );

typedef int (*core_cttmqr_hook_type)(
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
                                    );

typedef void (*core_zlacpy_lapack2tile_band_hook_type)(
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
                                                      );

typedef int (*core_dpotrf_hook_type)(
                                    plasma_enum_t uplo,
                                    int n,
                                    double *A,
                                    int lda
                                    );

typedef int (*core_ctrtri_hook_type)(
                                    plasma_enum_t uplo,
                                    plasma_enum_t diag,
                                    int n,
                                    plasma_complex32_t *A,
                                    int lda
                                    );

typedef int (*core_sttmqr_hook_type)(
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
                                    );

typedef void (*core_dgeswp_hook_type)(
                                     plasma_enum_t colrow,
                                     plasma_desc_t A,
                                     int k1,
                                     int k2,
                                     const int *ipiv,
                                     int incx
                                     );

typedef int (*core_sttlqt_hook_type)(
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
                                    );

typedef int (*core_cpotrf_hook_type)(
                                    plasma_enum_t uplo,
                                    int n,
                                    plasma_complex32_t *A,
                                    int lda
                                    );

typedef int (*core_ztsmqr_hook_type)(
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
                                    );

typedef void (*core_cgeswp_hook_type)(
                                     plasma_enum_t colrow,
                                     plasma_desc_t A,
                                     int k1,
                                     int k2,
                                     const int *ipiv,
                                     int incx
                                     );

typedef int (*core_zhegst_hook_type)(
                                    int itype,
                                    plasma_enum_t uplo,
                                    int n,
                                    plasma_complex64_t *A,
                                    int lda,
                                    plasma_complex64_t *B,
                                    int ldb
                                    );

typedef void (*core_zsyssq_hook_type)(
                                     plasma_enum_t uplo,
                                     int n,
                                     const plasma_complex64_t *A,
                                     int lda,
                                     double *scale,
                                     double *sumsq
                                     );
