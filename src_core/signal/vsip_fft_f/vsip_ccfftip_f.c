/* Created by RJudd January 7, 1999 */
/* SPAWARSYSCEN D881 */
/**********************************************************************
// For TASP VSIPL Documentation and Code neither the United States    /
// Government, the United States Navy, nor any of their employees,    /
// makes any warranty, express or implied, including the warranties   /
// of merchantability and fitness for a particular purpose, or        /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/
/* $Id: vsip_ccfftip_f.c,v 1.1 1999/12/02 18:50:58 judd Exp judd $ */
#include<vsip.h>
#include<vsip_fftattributes_f.h>
#include<vsip_cvviewattributes_f.h>
#include"VI_ft_f.h"


void vsip_ccfftip_f(const vsip_fft_f *Offt, 
                    const vsip_cvview_f *y)
{
     vsip_fft_f Nfft = *Offt;
     vsip_fft_f *fft = &Nfft;
     VI_ccfftip_f(fft,y);
}

void vsip_ccfftip_f_para(const vsip_fft_f *Offt, 
                    const vsip_cvview_f *y)
{
     vsip_fft_f Nfft = *Offt;
     vsip_fft_f *fft = &Nfft;
     VI_ccfftip_f_para(fft,y);
}

