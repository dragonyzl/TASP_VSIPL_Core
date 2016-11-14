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
/* $Id: vsip_ccfftmip_d.c,v 1.1 1999/12/05 01:58:58 judd Exp judd $ */
#include<vsip.h>
#include<vsip_cmviewattributes_d.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_fftmattributes_d.h>
#include"VI_ftm_d.h"


void vsip_ccfftmip_d(const vsip_fftm_d *Offt, 
                    const vsip_cmview_d *y)
{
     vsip_fftm_d Nfft = *Offt;
     vsip_fftm_d *fft = &Nfft;
     VI_ccfftmip_d(fft,y);
}

