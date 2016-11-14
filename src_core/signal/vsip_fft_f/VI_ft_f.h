#ifndef VI_ft_f_h
#define VI_ft_f_h 1

#define VI_ft_f_2PI 6.2831853071795864769252866
#define VI_ft_f_PI  3.1415926535897932384626433


/* building blocks */
void VI_dft_f(vsip_fft_f*);
void VI_fft2_f(vsip_fft_f*);
void VI_ifft2_f(vsip_fft_f*);
void VI_fft3_f(vsip_fft_f*);
void VI_ifft3_f(vsip_fft_f*);
void VI_fft4_f(vsip_fft_f*);
void VI_ifft4_f(vsip_fft_f*);
void VI_fft5_f(vsip_fft_f*);
void VI_ifft5_f(vsip_fft_f*);
void VI_fft7_f(vsip_fft_f*);
void VI_ifft7_f(vsip_fft_f*);
void VI_fft8_f(vsip_fft_f*);
void VI_ifft8_f(vsip_fft_f*);
vsip_fft_f *VI_mod_type(vsip_fft_f* , vsip_ffttype);
void VI_p0pF_f(vsip_fft_f*);

/* Utility Function to determine If length is a Power of 2, 3, 4 */
/* and return -1 if not and power if true */
/* nu(length) */
vsip_length VI_nuV_f(vsip_length, vsip_scalar_vi*,vsip_scalar_vi*,vsip_scalar_vi*);

/* Utility Functions for unsorting */
vsip_scalar_vi VI_jofk_f(vsip_scalar_vi, vsip_scalar_vi *, vsip_scalar_vi *, vsip_scalar_vi,vsip_length);
void VI_sort_copy_f(vsip_fft_f*);
void VI_fft_wt_f(vsip_fft_f*);
void VI_cvgather_f(const vsip_cvview_f*,const vsip_scalar_vi*,const vsip_cvview_f*);
void VI_ccfftip_f(const vsip_fft_f*, const vsip_cvview_f*);
#endif /*VI_ft_f.h*/
