#ifndef VI_ftm_f_h
#define VI_ftm_f_h 1

#define VI_ftm_f_2PI 6.2831853071795864769252866
#define VI_ftm_f_PI  3.1415926535897932384626433


/* building blocks */
void VI_dftm_f(vsip_fftm_f*);
void VI_dftm_f_para(vsip_fftm_f*);
void VI_fft2m_f(vsip_fftm_f*);
void VI_ifft2m_f(vsip_fftm_f*);
void VI_fft3m_f(vsip_fftm_f*);
void VI_ifft3m_f(vsip_fftm_f*);
void VI_fft4m_f(vsip_fftm_f*);
void VI_ifft4m_f(vsip_fftm_f*);
void VI_fft5m_f(vsip_fftm_f*);
void VI_ifft5m_f(vsip_fftm_f*);
void VI_fft7m_f(vsip_fftm_f*);
void VI_ifft7m_f(vsip_fftm_f*);
void VI_fft8m_f(vsip_fftm_f*);
void VI_ifft8m_f(vsip_fftm_f*);
vsip_fftm_f *VI_modm_type(vsip_fftm_f* , vsip_fftmtype);
void VI_p0pFm_f(vsip_fftm_f*);
void VI_p0pFm_f_para(vsip_fftm_f*);


/* Utility Function to determine If length is a Power of 2, 3, 4 */
/* and return -1 if not and power if true */
/* nu(length) */
vsip_length VI_nuV_f(vsip_length, vsip_scalar_vi*,vsip_scalar_vi*,vsip_scalar_vi*);

/* Utility Functions for unsorting */
vsip_scalar_vi VI_jofk_f(vsip_scalar_vi, vsip_scalar_vi *, vsip_scalar_vi *, vsip_scalar_vi,vsip_length);
void VI_sortm_copy_f(vsip_fftm_f*);
void VI_sortm_copy_f_para(vsip_fftm_f*);
void VI_fft_wtm_f(vsip_fftm_f*);
void VI_cvgather_f(const vsip_cvview_f*,const vsip_scalar_vi*,const vsip_cvview_f*);
void VI_ccfftmip_f(const vsip_fftm_f*, const vsip_cmview_f*);
void VI_ccfftmip_f_para(const vsip_fftm_f*, const vsip_cmview_f*);
#endif /*VI_ftm_f.h*/
