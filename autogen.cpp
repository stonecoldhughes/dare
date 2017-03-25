#include "profile.h"

using namespace std;

atomic<unsigned long> Profile::core_count[TABLE_SIZE];

/*This will obtain function pointers to hooks in the PLASMA library*/
Profile::Profile()
{
    void (*fptr)();

    /* Obtain a handle to the core_blas library */
    core_blas_file = dlopen("/Users/hhughe11/plasma/lib/libcoreblas.so", RTLD_LAZY);
    if(core_blas_file == NULL) {printf("core_blas_file null\n"); exit(0);}
    
    /* hook core_dlange() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dlange");
    if(fptr == NULL) {printf("core_dlange() hook NULL\n"); exit(0);}
    core[CORE_DLANGE] = fptr;
    
    /* hook core_cher2k() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cher2k");
    if(fptr == NULL) {printf("core_cher2k() hook NULL\n"); exit(0);}
    core[CORE_CHER2K] = fptr;
    
    /* hook core_zgeadd() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zgeadd");
    if(fptr == NULL) {printf("core_zgeadd() hook NULL\n"); exit(0);}
    core[CORE_ZGEADD] = fptr;
    
    /* hook core_ssyr2k() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ssyr2k");
    if(fptr == NULL) {printf("core_ssyr2k() hook NULL\n"); exit(0);}
    core[CORE_SSYR2K] = fptr;
    
    /* hook core_ctsmlq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ctsmlq");
    if(fptr == NULL) {printf("core_ctsmlq() hook NULL\n"); exit(0);}
    core[CORE_CTSMLQ] = fptr;
    
    /* hook core_dgessq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dgessq");
    if(fptr == NULL) {printf("core_dgessq() hook NULL\n"); exit(0);}
    core[CORE_DGESSQ] = fptr;
    
    /* hook core_zunmlq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zunmlq");
    if(fptr == NULL) {printf("core_zunmlq() hook NULL\n"); exit(0);}
    core[CORE_ZUNMLQ] = fptr;
    
    /* hook core_zlaset() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zlaset");
    if(fptr == NULL) {printf("core_zlaset() hook NULL\n"); exit(0);}
    core[CORE_ZLASET] = fptr;
    
    /* hook core_zsyr2k() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zsyr2k");
    if(fptr == NULL) {printf("core_zsyr2k() hook NULL\n"); exit(0);}
    core[CORE_ZSYR2K] = fptr;
    
    /* hook core_csymm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_csymm");
    if(fptr == NULL) {printf("core_csymm() hook NULL\n"); exit(0);}
    core[CORE_CSYMM] = fptr;
    
    /* hook core_cparfb() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cparfb");
    if(fptr == NULL) {printf("core_cparfb() hook NULL\n"); exit(0);}
    core[CORE_CPARFB] = fptr;
    
    /* hook core_dlauum() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dlauum");
    if(fptr == NULL) {printf("core_dlauum() hook NULL\n"); exit(0);}
    core[CORE_DLAUUM] = fptr;
    
    /* hook core_cunmqr() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cunmqr");
    if(fptr == NULL) {printf("core_cunmqr() hook NULL\n"); exit(0);}
    core[CORE_CUNMQR] = fptr;
    
    /* hook core_ztslqt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ztslqt");
    if(fptr == NULL) {printf("core_ztslqt() hook NULL\n"); exit(0);}
    core[CORE_ZTSLQT] = fptr;
    
    /* hook core_spemv() */
    fptr = (void (*)())dlsym(core_blas_file, "core_spemv");
    if(fptr == NULL) {printf("core_spemv() hook NULL\n"); exit(0);}
    core[CORE_SPEMV] = fptr;
    
    /* hook core_cgeadd() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cgeadd");
    if(fptr == NULL) {printf("core_cgeadd() hook NULL\n"); exit(0);}
    core[CORE_CGEADD] = fptr;
    
    /* hook core_strsm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_strsm");
    if(fptr == NULL) {printf("core_strsm() hook NULL\n"); exit(0);}
    core[CORE_STRSM] = fptr;
    
    /* hook core_dttqrt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dttqrt");
    if(fptr == NULL) {printf("core_dttqrt() hook NULL\n"); exit(0);}
    core[CORE_DTTQRT] = fptr;
    
    /* hook core_dtrtri() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dtrtri");
    if(fptr == NULL) {printf("core_dtrtri() hook NULL\n"); exit(0);}
    core[CORE_DTRTRI] = fptr;
    
    /* hook core_cgelqt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cgelqt");
    if(fptr == NULL) {printf("core_cgelqt() hook NULL\n"); exit(0);}
    core[CORE_CGELQT] = fptr;
    
    /* hook core_clange() */
    fptr = (void (*)())dlsym(core_blas_file, "core_clange");
    if(fptr == NULL) {printf("core_clange() hook NULL\n"); exit(0);}
    core[CORE_CLANGE] = fptr;
    
    /* hook core_slascl() */
    fptr = (void (*)())dlsym(core_blas_file, "core_slascl");
    if(fptr == NULL) {printf("core_slascl() hook NULL\n"); exit(0);}
    core[CORE_SLASCL] = fptr;
    
    /* hook core_csyr2k() */
    fptr = (void (*)())dlsym(core_blas_file, "core_csyr2k");
    if(fptr == NULL) {printf("core_csyr2k() hook NULL\n"); exit(0);}
    core[CORE_CSYR2K] = fptr;
    
    /* hook core_ztsqrt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ztsqrt");
    if(fptr == NULL) {printf("core_ztsqrt() hook NULL\n"); exit(0);}
    core[CORE_ZTSQRT] = fptr;
    
    /* hook core_zgessq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zgessq");
    if(fptr == NULL) {printf("core_zgessq() hook NULL\n"); exit(0);}
    core[CORE_ZGESSQ] = fptr;
    
    /* hook core_ztrmm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ztrmm");
    if(fptr == NULL) {printf("core_ztrmm() hook NULL\n"); exit(0);}
    core[CORE_ZTRMM] = fptr;
    
    /* hook core_dtrssq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dtrssq");
    if(fptr == NULL) {printf("core_dtrssq() hook NULL\n"); exit(0);}
    core[CORE_DTRSSQ] = fptr;
    
    /* hook core_dlascl() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dlascl");
    if(fptr == NULL) {printf("core_dlascl() hook NULL\n"); exit(0);}
    core[CORE_DLASCL] = fptr;
    
    /* hook core_ctrmm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ctrmm");
    if(fptr == NULL) {printf("core_ctrmm() hook NULL\n"); exit(0);}
    core[CORE_CTRMM] = fptr;
    
    /* hook core_dsymm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dsymm");
    if(fptr == NULL) {printf("core_dsymm() hook NULL\n"); exit(0);}
    core[CORE_DSYMM] = fptr;
    
    /* hook core_dgeqrt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dgeqrt");
    if(fptr == NULL) {printf("core_dgeqrt() hook NULL\n"); exit(0);}
    core[CORE_DGEQRT] = fptr;
    
    /* hook core_cpamm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cpamm");
    if(fptr == NULL) {printf("core_cpamm() hook NULL\n"); exit(0);}
    core[CORE_CPAMM] = fptr;
    
    /* hook core_zlacpy_tile2lapack_band() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zlacpy_tile2lapack_band");
    if(fptr == NULL) {printf("core_zlacpy_tile2lapack_band() hook NULL\n"); exit(0);}
    core[CORE_ZLACPY_TILE2LAPACK_BAND] = fptr;
    
    /* hook core_cgetrf() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cgetrf");
    if(fptr == NULL) {printf("core_cgetrf() hook NULL\n"); exit(0);}
    core[CORE_CGETRF] = fptr;
    
    /* hook core_slauum() */
    fptr = (void (*)())dlsym(core_blas_file, "core_slauum");
    if(fptr == NULL) {printf("core_slauum() hook NULL\n"); exit(0);}
    core[CORE_SLAUUM] = fptr;
    
    /* hook core_cgemm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cgemm");
    if(fptr == NULL) {printf("core_cgemm() hook NULL\n"); exit(0);}
    core[CORE_CGEMM] = fptr;
    
    /* hook core_zher2k() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zher2k");
    if(fptr == NULL) {printf("core_zher2k() hook NULL\n"); exit(0);}
    core[CORE_ZHER2K] = fptr;
    
    /* hook core_ssyssq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ssyssq");
    if(fptr == NULL) {printf("core_ssyssq() hook NULL\n"); exit(0);}
    core[CORE_SSYSSQ] = fptr;
    
    /* hook core_dpamm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dpamm");
    if(fptr == NULL) {printf("core_dpamm() hook NULL\n"); exit(0);}
    core[CORE_DPAMM] = fptr;
    
    /* hook core_sttqrt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_sttqrt");
    if(fptr == NULL) {printf("core_sttqrt() hook NULL\n"); exit(0);}
    core[CORE_STTQRT] = fptr;
    
    /* hook core_dtrmm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dtrmm");
    if(fptr == NULL) {printf("core_dtrmm() hook NULL\n"); exit(0);}
    core[CORE_DTRMM] = fptr;
    
    /* hook core_ssyswp() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ssyswp");
    if(fptr == NULL) {printf("core_ssyswp() hook NULL\n"); exit(0);}
    core[CORE_SSYSWP] = fptr;
    
    /* hook core_ssymm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ssymm");
    if(fptr == NULL) {printf("core_ssymm() hook NULL\n"); exit(0);}
    core[CORE_SSYMM] = fptr;
    
    /* hook core_csyssq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_csyssq");
    if(fptr == NULL) {printf("core_csyssq() hook NULL\n"); exit(0);}
    core[CORE_CSYSSQ] = fptr;
    
    /* hook core_dpemv() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dpemv");
    if(fptr == NULL) {printf("core_dpemv() hook NULL\n"); exit(0);}
    core[CORE_DPEMV] = fptr;
    
    /* hook core_cgessq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cgessq");
    if(fptr == NULL) {printf("core_cgessq() hook NULL\n"); exit(0);}
    core[CORE_CGESSQ] = fptr;
    
    /* hook core_clansy() */
    fptr = (void (*)())dlsym(core_blas_file, "core_clansy");
    if(fptr == NULL) {printf("core_clansy() hook NULL\n"); exit(0);}
    core[CORE_CLANSY] = fptr;
    
    /* hook core_dormlq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dormlq");
    if(fptr == NULL) {printf("core_dormlq() hook NULL\n"); exit(0);}
    core[CORE_DORMLQ] = fptr;
    
    /* hook core_zhessq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zhessq");
    if(fptr == NULL) {printf("core_zhessq() hook NULL\n"); exit(0);}
    core[CORE_ZHESSQ] = fptr;
    
    /* hook core_clacpy() */
    fptr = (void (*)())dlsym(core_blas_file, "core_clacpy");
    if(fptr == NULL) {printf("core_clacpy() hook NULL\n"); exit(0);}
    core[CORE_CLACPY] = fptr;
    
    /* hook core_dlantr() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dlantr");
    if(fptr == NULL) {printf("core_dlantr() hook NULL\n"); exit(0);}
    core[CORE_DLANTR] = fptr;
    
    /* hook core_slaset() */
    fptr = (void (*)())dlsym(core_blas_file, "core_slaset");
    if(fptr == NULL) {printf("core_slaset() hook NULL\n"); exit(0);}
    core[CORE_SLASET] = fptr;
    
    /* hook core_cttqrt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cttqrt");
    if(fptr == NULL) {printf("core_cttqrt() hook NULL\n"); exit(0);}
    core[CORE_CTTQRT] = fptr;
    
    /* hook core_sgeqrt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_sgeqrt");
    if(fptr == NULL) {printf("core_sgeqrt() hook NULL\n"); exit(0);}
    core[CORE_SGEQRT] = fptr;
    
    /* hook core_slacpy_lapack2tile_band() */
    fptr = (void (*)())dlsym(core_blas_file, "core_slacpy_lapack2tile_band");
    if(fptr == NULL) {printf("core_slacpy_lapack2tile_band() hook NULL\n"); exit(0);}
    core[CORE_SLACPY_LAPACK2TILE_BAND] = fptr;
    
    /* hook core_dlacpy_lapack2tile_band() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dlacpy_lapack2tile_band");
    if(fptr == NULL) {printf("core_dlacpy_lapack2tile_band() hook NULL\n"); exit(0);}
    core[CORE_DLACPY_LAPACK2TILE_BAND] = fptr;
    
    /* hook core_strmm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_strmm");
    if(fptr == NULL) {printf("core_strmm() hook NULL\n"); exit(0);}
    core[CORE_STRMM] = fptr;
    
    /* hook core_ssygst() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ssygst");
    if(fptr == NULL) {printf("core_ssygst() hook NULL\n"); exit(0);}
    core[CORE_SSYGST] = fptr;
    
    /* hook core_cgeqrt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cgeqrt");
    if(fptr == NULL) {printf("core_cgeqrt() hook NULL\n"); exit(0);}
    core[CORE_CGEQRT] = fptr;
    
    /* hook core_ztrtri() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ztrtri");
    if(fptr == NULL) {printf("core_ztrtri() hook NULL\n"); exit(0);}
    core[CORE_ZTRTRI] = fptr;
    
    /* hook core_ztsmlq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ztsmlq");
    if(fptr == NULL) {printf("core_ztsmlq() hook NULL\n"); exit(0);}
    core[CORE_ZTSMLQ] = fptr;
    
    /* hook core_zsymm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zsymm");
    if(fptr == NULL) {printf("core_zsymm() hook NULL\n"); exit(0);}
    core[CORE_ZSYMM] = fptr;
    
    /* hook core_clacpy_tile2lapack_band() */
    fptr = (void (*)())dlsym(core_blas_file, "core_clacpy_tile2lapack_band");
    if(fptr == NULL) {printf("core_clacpy_tile2lapack_band() hook NULL\n"); exit(0);}
    core[CORE_CLACPY_TILE2LAPACK_BAND] = fptr;
    
    /* hook core_dormqr() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dormqr");
    if(fptr == NULL) {printf("core_dormqr() hook NULL\n"); exit(0);}
    core[CORE_DORMQR] = fptr;
    
    /* hook core_stsmqr() */
    fptr = (void (*)())dlsym(core_blas_file, "core_stsmqr");
    if(fptr == NULL) {printf("core_stsmqr() hook NULL\n"); exit(0);}
    core[CORE_STSMQR] = fptr;
    
    /* hook core_ctrssq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ctrssq");
    if(fptr == NULL) {printf("core_ctrssq() hook NULL\n"); exit(0);}
    core[CORE_CTRSSQ] = fptr;
    
    /* hook core_slansy() */
    fptr = (void (*)())dlsym(core_blas_file, "core_slansy");
    if(fptr == NULL) {printf("core_slansy() hook NULL\n"); exit(0);}
    core[CORE_SLANSY] = fptr;
    
    /* hook core_dgetrf() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dgetrf");
    if(fptr == NULL) {printf("core_dgetrf() hook NULL\n"); exit(0);}
    core[CORE_DGETRF] = fptr;
    
    /* hook core_ctradd() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ctradd");
    if(fptr == NULL) {printf("core_ctradd() hook NULL\n"); exit(0);}
    core[CORE_CTRADD] = fptr;
    
    /* hook core_cheswp() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cheswp");
    if(fptr == NULL) {printf("core_cheswp() hook NULL\n"); exit(0);}
    core[CORE_CHESWP] = fptr;
    
    /* hook core_sttmlq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_sttmlq");
    if(fptr == NULL) {printf("core_sttmlq() hook NULL\n"); exit(0);}
    core[CORE_STTMLQ] = fptr;
    
    /* hook core_zheswp() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zheswp");
    if(fptr == NULL) {printf("core_zheswp() hook NULL\n"); exit(0);}
    core[CORE_ZHESWP] = fptr;
    
    /* hook core_chegst() */
    fptr = (void (*)())dlsym(core_blas_file, "core_chegst");
    if(fptr == NULL) {printf("core_chegst() hook NULL\n"); exit(0);}
    core[CORE_CHEGST] = fptr;
    
    /* hook core_dttlqt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dttlqt");
    if(fptr == NULL) {printf("core_dttlqt() hook NULL\n"); exit(0);}
    core[CORE_DTTLQT] = fptr;
    
    /* hook core_ctsmqr() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ctsmqr");
    if(fptr == NULL) {printf("core_ctsmqr() hook NULL\n"); exit(0);}
    core[CORE_CTSMQR] = fptr;
    
    /* hook core_stsqrt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_stsqrt");
    if(fptr == NULL) {printf("core_stsqrt() hook NULL\n"); exit(0);}
    core[CORE_STSQRT] = fptr;
    
    /* hook core_clauum() */
    fptr = (void (*)())dlsym(core_blas_file, "core_clauum");
    if(fptr == NULL) {printf("core_clauum() hook NULL\n"); exit(0);}
    core[CORE_CLAUUM] = fptr;
    
    /* hook core_slacpy() */
    fptr = (void (*)())dlsym(core_blas_file, "core_slacpy");
    if(fptr == NULL) {printf("core_slacpy() hook NULL\n"); exit(0);}
    core[CORE_SLACPY] = fptr;
    
    /* hook core_zlascl() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zlascl");
    if(fptr == NULL) {printf("core_zlascl() hook NULL\n"); exit(0);}
    core[CORE_ZLASCL] = fptr;
    
    /* hook core_strtri() */
    fptr = (void (*)())dlsym(core_blas_file, "core_strtri");
    if(fptr == NULL) {printf("core_strtri() hook NULL\n"); exit(0);}
    core[CORE_STRTRI] = fptr;
    
    /* hook core_csyrk() */
    fptr = (void (*)())dlsym(core_blas_file, "core_csyrk");
    if(fptr == NULL) {printf("core_csyrk() hook NULL\n"); exit(0);}
    core[CORE_CSYRK] = fptr;
    
    /* hook core_sgelqt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_sgelqt");
    if(fptr == NULL) {printf("core_sgelqt() hook NULL\n"); exit(0);}
    core[CORE_SGELQT] = fptr;
    
    /* hook core_claset() */
    fptr = (void (*)())dlsym(core_blas_file, "core_claset");
    if(fptr == NULL) {printf("core_claset() hook NULL\n"); exit(0);}
    core[CORE_CLASET] = fptr;
    
    /* hook core_slacpy_tile2lapack_band() */
    fptr = (void (*)())dlsym(core_blas_file, "core_slacpy_tile2lapack_band");
    if(fptr == NULL) {printf("core_slacpy_tile2lapack_band() hook NULL\n"); exit(0);}
    core[CORE_SLACPY_TILE2LAPACK_BAND] = fptr;
    
    /* hook core_sormqr() */
    fptr = (void (*)())dlsym(core_blas_file, "core_sormqr");
    if(fptr == NULL) {printf("core_sormqr() hook NULL\n"); exit(0);}
    core[CORE_SORMQR] = fptr;
    
    /* hook core_stradd() */
    fptr = (void (*)())dlsym(core_blas_file, "core_stradd");
    if(fptr == NULL) {printf("core_stradd() hook NULL\n"); exit(0);}
    core[CORE_STRADD] = fptr;
    
    /* hook core_dttmlq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dttmlq");
    if(fptr == NULL) {printf("core_dttmlq() hook NULL\n"); exit(0);}
    core[CORE_DTTMLQ] = fptr;
    
    /* hook core_scabs1() */
    fptr = (void (*)())dlsym(core_blas_file, "core_scabs1");
    if(fptr == NULL) {printf("core_scabs1() hook NULL\n"); exit(0);}
    core[CORE_SCABS1] = fptr;
    
    /* hook core_slange() */
    fptr = (void (*)())dlsym(core_blas_file, "core_slange");
    if(fptr == NULL) {printf("core_slange() hook NULL\n"); exit(0);}
    core[CORE_SLANGE] = fptr;
    
    /* hook core_zlanhe() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zlanhe");
    if(fptr == NULL) {printf("core_zlanhe() hook NULL\n"); exit(0);}
    core[CORE_ZLANHE] = fptr;
    
    /* hook core_sgeswp() */
    fptr = (void (*)())dlsym(core_blas_file, "core_sgeswp");
    if(fptr == NULL) {printf("core_sgeswp() hook NULL\n"); exit(0);}
    core[CORE_SGESWP] = fptr;
    
    /* hook core_dtradd() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dtradd");
    if(fptr == NULL) {printf("core_dtradd() hook NULL\n"); exit(0);}
    core[CORE_DTRADD] = fptr;
    
    /* hook core_dsyrk() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dsyrk");
    if(fptr == NULL) {printf("core_dsyrk() hook NULL\n"); exit(0);}
    core[CORE_DSYRK] = fptr;
    
    /* hook core_dsyswp() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dsyswp");
    if(fptr == NULL) {printf("core_dsyswp() hook NULL\n"); exit(0);}
    core[CORE_DSYSWP] = fptr;
    
    /* hook core_dtrsm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dtrsm");
    if(fptr == NULL) {printf("core_dtrsm() hook NULL\n"); exit(0);}
    core[CORE_DTRSM] = fptr;
    
    /* hook core_stslqt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_stslqt");
    if(fptr == NULL) {printf("core_stslqt() hook NULL\n"); exit(0);}
    core[CORE_STSLQT] = fptr;
    
    /* hook core_ztrssq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ztrssq");
    if(fptr == NULL) {printf("core_ztrssq() hook NULL\n"); exit(0);}
    core[CORE_ZTRSSQ] = fptr;
    
    /* hook core_clascl() */
    fptr = (void (*)())dlsym(core_blas_file, "core_clascl");
    if(fptr == NULL) {printf("core_clascl() hook NULL\n"); exit(0);}
    core[CORE_CLASCL] = fptr;
    
    /* hook core_zgelqt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zgelqt");
    if(fptr == NULL) {printf("core_zgelqt() hook NULL\n"); exit(0);}
    core[CORE_ZGELQT] = fptr;
    
    /* hook core_chessq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_chessq");
    if(fptr == NULL) {printf("core_chessq() hook NULL\n"); exit(0);}
    core[CORE_CHESSQ] = fptr;
    
    /* hook core_dgeadd() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dgeadd");
    if(fptr == NULL) {printf("core_dgeadd() hook NULL\n"); exit(0);}
    core[CORE_DGEADD] = fptr;
    
    /* hook core_dtsmlq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dtsmlq");
    if(fptr == NULL) {printf("core_dtsmlq() hook NULL\n"); exit(0);}
    core[CORE_DTSMLQ] = fptr;
    
    /* hook core_dlansy() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dlansy");
    if(fptr == NULL) {printf("core_dlansy() hook NULL\n"); exit(0);}
    core[CORE_DLANSY] = fptr;
    
    /* hook core_zttlqt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zttlqt");
    if(fptr == NULL) {printf("core_zttlqt() hook NULL\n"); exit(0);}
    core[CORE_ZTTLQT] = fptr;
    
    /* hook core_zhemm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zhemm");
    if(fptr == NULL) {printf("core_zhemm() hook NULL\n"); exit(0);}
    core[CORE_ZHEMM] = fptr;
    
    /* hook core_clacpy_lapack2tile_band() */
    fptr = (void (*)())dlsym(core_blas_file, "core_clacpy_lapack2tile_band");
    if(fptr == NULL) {printf("core_clacpy_lapack2tile_band() hook NULL\n"); exit(0);}
    core[CORE_CLACPY_LAPACK2TILE_BAND] = fptr;
    
    /* hook core_sgeadd() */
    fptr = (void (*)())dlsym(core_blas_file, "core_sgeadd");
    if(fptr == NULL) {printf("core_sgeadd() hook NULL\n"); exit(0);}
    core[CORE_SGEADD] = fptr;
    
    /* hook core_zgemm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zgemm");
    if(fptr == NULL) {printf("core_zgemm() hook NULL\n"); exit(0);}
    core[CORE_ZGEMM] = fptr;
    
    /* hook core_cherk() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cherk");
    if(fptr == NULL) {printf("core_cherk() hook NULL\n"); exit(0);}
    core[CORE_CHERK] = fptr;
    
    /* hook core_dtsmqr() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dtsmqr");
    if(fptr == NULL) {printf("core_dtsmqr() hook NULL\n"); exit(0);}
    core[CORE_DTSMQR] = fptr;
    
    /* hook core_clantr() */
    fptr = (void (*)())dlsym(core_blas_file, "core_clantr");
    if(fptr == NULL) {printf("core_clantr() hook NULL\n"); exit(0);}
    core[CORE_CLANTR] = fptr;
    
    /* hook core_zgeswp() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zgeswp");
    if(fptr == NULL) {printf("core_zgeswp() hook NULL\n"); exit(0);}
    core[CORE_ZGESWP] = fptr;
    
    /* hook core_zttqrt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zttqrt");
    if(fptr == NULL) {printf("core_zttqrt() hook NULL\n"); exit(0);}
    core[CORE_ZTTQRT] = fptr;
    
    /* hook core_zherk() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zherk");
    if(fptr == NULL) {printf("core_zherk() hook NULL\n"); exit(0);}
    core[CORE_ZHERK] = fptr;
    
    /* hook core_zgeqrt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zgeqrt");
    if(fptr == NULL) {printf("core_zgeqrt() hook NULL\n"); exit(0);}
    core[CORE_ZGEQRT] = fptr;
    
    /* hook core_ctrsm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ctrsm");
    if(fptr == NULL) {printf("core_ctrsm() hook NULL\n"); exit(0);}
    core[CORE_CTRSM] = fptr;
    
    /* hook core_dtsqrt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dtsqrt");
    if(fptr == NULL) {printf("core_dtsqrt() hook NULL\n"); exit(0);}
    core[CORE_DTSQRT] = fptr;
    
    /* hook core_sgemm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_sgemm");
    if(fptr == NULL) {printf("core_sgemm() hook NULL\n"); exit(0);}
    core[CORE_SGEMM] = fptr;
    
    /* hook core_spotrf() */
    fptr = (void (*)())dlsym(core_blas_file, "core_spotrf");
    if(fptr == NULL) {printf("core_spotrf() hook NULL\n"); exit(0);}
    core[CORE_SPOTRF] = fptr;
    
    /* hook core_zpemv() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zpemv");
    if(fptr == NULL) {printf("core_zpemv() hook NULL\n"); exit(0);}
    core[CORE_ZPEMV] = fptr;
    
    /* hook core_zpamm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zpamm");
    if(fptr == NULL) {printf("core_zpamm() hook NULL\n"); exit(0);}
    core[CORE_ZPAMM] = fptr;
    
    /* hook core_sormlq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_sormlq");
    if(fptr == NULL) {printf("core_sormlq() hook NULL\n"); exit(0);}
    core[CORE_SORMLQ] = fptr;
    
    /* hook core_ztradd() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ztradd");
    if(fptr == NULL) {printf("core_ztradd() hook NULL\n"); exit(0);}
    core[CORE_ZTRADD] = fptr;
    
    /* hook core_zlauum() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zlauum");
    if(fptr == NULL) {printf("core_zlauum() hook NULL\n"); exit(0);}
    core[CORE_ZLAUUM] = fptr;
    
    /* hook core_dparfb() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dparfb");
    if(fptr == NULL) {printf("core_dparfb() hook NULL\n"); exit(0);}
    core[CORE_DPARFB] = fptr;
    
    /* hook core_dgelqt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dgelqt");
    if(fptr == NULL) {printf("core_dgelqt() hook NULL\n"); exit(0);}
    core[CORE_DGELQT] = fptr;
    
    /* hook core_sgetrf() */
    fptr = (void (*)())dlsym(core_blas_file, "core_sgetrf");
    if(fptr == NULL) {printf("core_sgetrf() hook NULL\n"); exit(0);}
    core[CORE_SGETRF] = fptr;
    
    /* hook core_zparfb() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zparfb");
    if(fptr == NULL) {printf("core_zparfb() hook NULL\n"); exit(0);}
    core[CORE_ZPARFB] = fptr;
    
    /* hook core_spamm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_spamm");
    if(fptr == NULL) {printf("core_spamm() hook NULL\n"); exit(0);}
    core[CORE_SPAMM] = fptr;
    
    /* hook core_chemm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_chemm");
    if(fptr == NULL) {printf("core_chemm() hook NULL\n"); exit(0);}
    core[CORE_CHEMM] = fptr;
    
    /* hook core_dsyssq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dsyssq");
    if(fptr == NULL) {printf("core_dsyssq() hook NULL\n"); exit(0);}
    core[CORE_DSYSSQ] = fptr;
    
    /* hook core_dsygst() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dsygst");
    if(fptr == NULL) {printf("core_dsygst() hook NULL\n"); exit(0);}
    core[CORE_DSYGST] = fptr;
    
    /* hook core_zttmqr() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zttmqr");
    if(fptr == NULL) {printf("core_zttmqr() hook NULL\n"); exit(0);}
    core[CORE_ZTTMQR] = fptr;
    
    /* hook core_dlacpy() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dlacpy");
    if(fptr == NULL) {printf("core_dlacpy() hook NULL\n"); exit(0);}
    core[CORE_DLACPY] = fptr;
    
    /* hook core_sparfb() */
    fptr = (void (*)())dlsym(core_blas_file, "core_sparfb");
    if(fptr == NULL) {printf("core_sparfb() hook NULL\n"); exit(0);}
    core[CORE_SPARFB] = fptr;
    
    /* hook core_ztrsm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ztrsm");
    if(fptr == NULL) {printf("core_ztrsm() hook NULL\n"); exit(0);}
    core[CORE_ZTRSM] = fptr;
    
    /* hook core_zunmqr() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zunmqr");
    if(fptr == NULL) {printf("core_zunmqr() hook NULL\n"); exit(0);}
    core[CORE_ZUNMQR] = fptr;
    
    /* hook core_zgetrf() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zgetrf");
    if(fptr == NULL) {printf("core_zgetrf() hook NULL\n"); exit(0);}
    core[CORE_ZGETRF] = fptr;
    
    /* hook core_cunmlq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cunmlq");
    if(fptr == NULL) {printf("core_cunmlq() hook NULL\n"); exit(0);}
    core[CORE_CUNMLQ] = fptr;
    
    /* hook core_sgessq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_sgessq");
    if(fptr == NULL) {printf("core_sgessq() hook NULL\n"); exit(0);}
    core[CORE_SGESSQ] = fptr;
    
    /* hook core_cttlqt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cttlqt");
    if(fptr == NULL) {printf("core_cttlqt() hook NULL\n"); exit(0);}
    core[CORE_CTTLQT] = fptr;
    
    /* hook core_cpemv() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cpemv");
    if(fptr == NULL) {printf("core_cpemv() hook NULL\n"); exit(0);}
    core[CORE_CPEMV] = fptr;
    
    /* hook core_zlantr() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zlantr");
    if(fptr == NULL) {printf("core_zlantr() hook NULL\n"); exit(0);}
    core[CORE_ZLANTR] = fptr;
    
    /* hook core_zlange() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zlange");
    if(fptr == NULL) {printf("core_zlange() hook NULL\n"); exit(0);}
    core[CORE_ZLANGE] = fptr;
    
    /* hook core_slantr() */
    fptr = (void (*)())dlsym(core_blas_file, "core_slantr");
    if(fptr == NULL) {printf("core_slantr() hook NULL\n"); exit(0);}
    core[CORE_SLANTR] = fptr;
    
    /* hook core_zlacpy() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zlacpy");
    if(fptr == NULL) {printf("core_zlacpy() hook NULL\n"); exit(0);}
    core[CORE_ZLACPY] = fptr;
    
    /* hook core_cttmlq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cttmlq");
    if(fptr == NULL) {printf("core_cttmlq() hook NULL\n"); exit(0);}
    core[CORE_CTTMLQ] = fptr;
    
    /* hook core_dgemm() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dgemm");
    if(fptr == NULL) {printf("core_dgemm() hook NULL\n"); exit(0);}
    core[CORE_DGEMM] = fptr;
    
    /* hook core_zpotrf() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zpotrf");
    if(fptr == NULL) {printf("core_zpotrf() hook NULL\n"); exit(0);}
    core[CORE_ZPOTRF] = fptr;
    
    /* hook core_strssq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_strssq");
    if(fptr == NULL) {printf("core_strssq() hook NULL\n"); exit(0);}
    core[CORE_STRSSQ] = fptr;
    
    /* hook core_ctslqt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ctslqt");
    if(fptr == NULL) {printf("core_ctslqt() hook NULL\n"); exit(0);}
    core[CORE_CTSLQT] = fptr;
    
    /* hook core_clanhe() */
    fptr = (void (*)())dlsym(core_blas_file, "core_clanhe");
    if(fptr == NULL) {printf("core_clanhe() hook NULL\n"); exit(0);}
    core[CORE_CLANHE] = fptr;
    
    /* hook core_stsmlq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_stsmlq");
    if(fptr == NULL) {printf("core_stsmlq() hook NULL\n"); exit(0);}
    core[CORE_STSMLQ] = fptr;
    
    /* hook core_dlaset() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dlaset");
    if(fptr == NULL) {printf("core_dlaset() hook NULL\n"); exit(0);}
    core[CORE_DLASET] = fptr;
    
    /* hook core_dtslqt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dtslqt");
    if(fptr == NULL) {printf("core_dtslqt() hook NULL\n"); exit(0);}
    core[CORE_DTSLQT] = fptr;
    
    /* hook core_zttmlq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zttmlq");
    if(fptr == NULL) {printf("core_zttmlq() hook NULL\n"); exit(0);}
    core[CORE_ZTTMLQ] = fptr;
    
    /* hook core_dlacpy_tile2lapack_band() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dlacpy_tile2lapack_band");
    if(fptr == NULL) {printf("core_dlacpy_tile2lapack_band() hook NULL\n"); exit(0);}
    core[CORE_DLACPY_TILE2LAPACK_BAND] = fptr;
    
    /* hook core_ssyrk() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ssyrk");
    if(fptr == NULL) {printf("core_ssyrk() hook NULL\n"); exit(0);}
    core[CORE_SSYRK] = fptr;
    
    /* hook core_ctsqrt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ctsqrt");
    if(fptr == NULL) {printf("core_ctsqrt() hook NULL\n"); exit(0);}
    core[CORE_CTSQRT] = fptr;
    
    /* hook core_zsyrk() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zsyrk");
    if(fptr == NULL) {printf("core_zsyrk() hook NULL\n"); exit(0);}
    core[CORE_ZSYRK] = fptr;
    
    /* hook core_dsyr2k() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dsyr2k");
    if(fptr == NULL) {printf("core_dsyr2k() hook NULL\n"); exit(0);}
    core[CORE_DSYR2K] = fptr;
    
    /* hook core_zlansy() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zlansy");
    if(fptr == NULL) {printf("core_zlansy() hook NULL\n"); exit(0);}
    core[CORE_ZLANSY] = fptr;
    
    /* hook core_dttmqr() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dttmqr");
    if(fptr == NULL) {printf("core_dttmqr() hook NULL\n"); exit(0);}
    core[CORE_DTTMQR] = fptr;
    
    /* hook core_dcabs1() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dcabs1");
    if(fptr == NULL) {printf("core_dcabs1() hook NULL\n"); exit(0);}
    core[CORE_DCABS1] = fptr;
    
    /* hook core_cttmqr() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cttmqr");
    if(fptr == NULL) {printf("core_cttmqr() hook NULL\n"); exit(0);}
    core[CORE_CTTMQR] = fptr;
    
    /* hook core_zlacpy_lapack2tile_band() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zlacpy_lapack2tile_band");
    if(fptr == NULL) {printf("core_zlacpy_lapack2tile_band() hook NULL\n"); exit(0);}
    core[CORE_ZLACPY_LAPACK2TILE_BAND] = fptr;
    
    /* hook core_dpotrf() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dpotrf");
    if(fptr == NULL) {printf("core_dpotrf() hook NULL\n"); exit(0);}
    core[CORE_DPOTRF] = fptr;
    
    /* hook core_ctrtri() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ctrtri");
    if(fptr == NULL) {printf("core_ctrtri() hook NULL\n"); exit(0);}
    core[CORE_CTRTRI] = fptr;
    
    /* hook core_sttmqr() */
    fptr = (void (*)())dlsym(core_blas_file, "core_sttmqr");
    if(fptr == NULL) {printf("core_sttmqr() hook NULL\n"); exit(0);}
    core[CORE_STTMQR] = fptr;
    
    /* hook core_dgeswp() */
    fptr = (void (*)())dlsym(core_blas_file, "core_dgeswp");
    if(fptr == NULL) {printf("core_dgeswp() hook NULL\n"); exit(0);}
    core[CORE_DGESWP] = fptr;
    
    /* hook core_sttlqt() */
    fptr = (void (*)())dlsym(core_blas_file, "core_sttlqt");
    if(fptr == NULL) {printf("core_sttlqt() hook NULL\n"); exit(0);}
    core[CORE_STTLQT] = fptr;
    
    /* hook core_cpotrf() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cpotrf");
    if(fptr == NULL) {printf("core_cpotrf() hook NULL\n"); exit(0);}
    core[CORE_CPOTRF] = fptr;
    
    /* hook core_ztsmqr() */
    fptr = (void (*)())dlsym(core_blas_file, "core_ztsmqr");
    if(fptr == NULL) {printf("core_ztsmqr() hook NULL\n"); exit(0);}
    core[CORE_ZTSMQR] = fptr;
    
    /* hook core_cgeswp() */
    fptr = (void (*)())dlsym(core_blas_file, "core_cgeswp");
    if(fptr == NULL) {printf("core_cgeswp() hook NULL\n"); exit(0);}
    core[CORE_CGESWP] = fptr;
    
    /* hook core_zhegst() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zhegst");
    if(fptr == NULL) {printf("core_zhegst() hook NULL\n"); exit(0);}
    core[CORE_ZHEGST] = fptr;
    
    /* hook core_zsyssq() */
    fptr = (void (*)())dlsym(core_blas_file, "core_zsyssq");
    if(fptr == NULL) {printf("core_zsyssq() hook NULL\n"); exit(0);}
    core[CORE_ZSYSSQ] = fptr;
    
    /*set atomic counters*/
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        core_count[i] = 0;
    }
    
    return;
}