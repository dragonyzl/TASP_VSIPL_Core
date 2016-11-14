#ifndef VI_ft_d_h
#define VI_ft_d_h 1

#define VI_ft_d_2PI 6.2831853071795864769252866
#define VI_ft_d_PI  3.1415926535897932384626433


/* building blocks */
void VI_dft_d(vsip_fft_d*);
void VI_fft2_d(vsip_fft_d*);
void VI_ifft2_d(vsip_fft_d*);
void VI_fft3_d(vsip_fft_d*);
void VI_ifft3_d(vsip_fft_d*);
void VI_fft4_d(vsip_fft_d*);
void VI_ifft4_d(vsip_fft_d*);
void VI_fft5_d(vsip_fft_d*);
void VI_ifft5_d(vsip_fft_d*);
void VI_fft7_d(vsip_fft_d*);
void VI_ifft7_d(vsip_fft_d*);
void VI_fft8_d(vsip_fft_d*);
void VI_ifft8_d(vsip_fft_d*);
vsip_fft_d *VI_mod_type(vsip_fft_d* , vsip_ffttype);
void VI_p0pF_d(vsip_fft_d*);

/* Utility Function to determine If length is a Power of 2, 3, 4 */
/* and return -1 if not and power if true */
/* nu(length) */
vsip_length VI_nuV_d(vsip_length, vsip_scalar_vi*,vsip_scalar_vi*,vsip_scalar_vi*);

/* Utility Functions for unsorting */
vsip_scalar_vi VI_jofk_d(vsip_scalar_vi, vsip_scalar_vi *, vsip_scalar_vi *, vsip_scalar_vi,vsip_length);
void VI_sort_copy_d(vsip_fft_d*);
void VI_fft_wt_d(vsip_fft_d*);
void VI_cvgather_d(const vsip_cvview_d*,const vsip_scalar_vi*,const vsip_cvview_d*);
void VI_ccfftip_d(const vsip_fft_d*, const vsip_cvview_d*);
#endif /*VI_ft_d.h*/
