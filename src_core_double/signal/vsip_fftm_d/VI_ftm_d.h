#ifndef VI_ftm_d_h
#define VI_ftm_d_h 1

#define VI_ftm_d_2PI 6.2831853071795864769252866
#define VI_ftm_d_PI  3.1415926535897932384626433


/* building blocks */
void VI_dftm_d(vsip_fftm_d*);
void VI_fft2m_d(vsip_fftm_d*);
void VI_ifft2m_d(vsip_fftm_d*);
void VI_fft3m_d(vsip_fftm_d*);
void VI_ifft3m_d(vsip_fftm_d*);
void VI_fft4m_d(vsip_fftm_d*);
void VI_ifft4m_d(vsip_fftm_d*);
void VI_fft5m_d(vsip_fftm_d*);
void VI_ifft5m_d(vsip_fftm_d*);
void VI_fft7m_d(vsip_fftm_d*);
void VI_ifft7m_d(vsip_fftm_d*);
void VI_fft8m_d(vsip_fftm_d*);
void VI_ifft8m_d(vsip_fftm_d*);
vsip_fftm_d *VI_modm_type(vsip_fftm_d* , vsip_fftmtype);
void VI_p0pFm_d(vsip_fftm_d*);

/* Utility Function to determine If length is a Power of 2, 3, 4 */
/* and return -1 if not and power if true */
/* nu(length) */
vsip_length VI_nuV_d(vsip_length, vsip_scalar_vi*,vsip_scalar_vi*,vsip_scalar_vi*);

/* Utility Functions for unsorting */
vsip_scalar_vi VI_jofk_d(vsip_scalar_vi, vsip_scalar_vi *, vsip_scalar_vi *, vsip_scalar_vi,vsip_length);
void VI_sortm_copy_d(vsip_fftm_d*);
void VI_fft_wtm_d(vsip_fftm_d*);
void VI_cvgather_d(const vsip_cvview_d*,const vsip_scalar_vi*,const vsip_cvview_d*);
void VI_ccfftmip_d(const vsip_fftm_d*, const vsip_cmview_d*);
#endif /*VI_ftm_d.h*/
