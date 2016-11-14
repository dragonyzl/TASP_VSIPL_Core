/* Created by RJudd September 9, 1998 */
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
/* $Id: vsip_rcfftmop_d.c,v 1.1 1999/12/05 01:59:02 judd Exp judd $ */

#include<vsip.h>
#include<vsip_cmviewattributes_d.h>
#include<vsip_mviewattributes_d.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_fftmattributes_d.h>
#include<VI_functions_d.h>
#include"VI_ftm_d.h"

void vsip_rcfftmop_d(
           const vsip_fftm_d   *Offt, 
           const vsip_mview_d  *X,
           const vsip_cmview_d *Z)
{
     vsip_fftm_d Nfft = *Offt;
     vsip_fftm_d *fft = &Nfft;
     vsip_length n;
     /* makes */
     vsip_cmview_d ca1 = *Z; vsip_cmview_d *Y = &ca1;
     vsip_mview_d ra1;
     vsip_mview_d *Y_r = VI_mrealview_d(Y,&ra1);
     vsip_mview_d ra2;
     vsip_mview_d *Y_i = VI_mimagview_d(Y,&ra2);
     vsip_mview_d ra3 = *X; vsip_mview_d *X_e = &ra3;
     vsip_mview_d ca2 = *X; vsip_mview_d *X_o = &ca2;
     vsip_cvview_d ca3 = *fft->temp; vsip_cvview_d *t = &ca3;
     vsip_cvview_d ca4 = *fft->temp; vsip_cvview_d *ang = &ca4;
     vsip_cvview_d Z0,*z;
     if(fft->major == VSIP_ROW){
           z = VI_cmrowview_d(Z,0,&Z0);
     }else{
           z = VI_cmcolview_d(Z,0,&Z0);
     }
     /* end makes */
     /* change ang view to to proper portion of temp */
     ang->offset = fft->MN + 1;
     ang->length = fft->MN + 1;
     /* copy even x to imaginary y, odd x to real y: note y is z clone */
     if(fft->major == VSIP_ROW){
         X_e->row_length = fft->MN;
         X_o->row_length = fft->MN;
         X_e->row_stride = 2 * X->row_stride;
         X_o->row_stride = 2 * X->row_stride;
         X_e->offset = X->offset + X->row_stride;
         Y_i->row_length = fft->MN;
         Y_r->row_length = fft->MN;
         vsip_mcopy_d_d(X_e,Y_i);
         vsip_mcopy_d_d(X_o,Y_r);
         Y->row_length = fft->MN; 
     }else{
         X_e->col_length = fft->MN;
         X_o->col_length = fft->MN;
         X_e->col_stride = 2 * X->col_stride;
         X_o->col_stride = 2 * X->col_stride;    
         X_e->offset = X->offset + X->col_stride;
         Y_i->col_length = fft->MN;
         Y_r->col_length = fft->MN;
         vsip_mcopy_d_d(X_e,Y_i);
         vsip_mcopy_d_d(X_o,Y_r);
         Y->col_length = fft->MN;
     }
     /* do fft on y */
     VI_ccfftmip_d(fft,Y); /* function resides in ccfftop code */
     
     n = fft->mN;
     while(n-- >0){
        vsip_cvput_d(z,fft->MN,vsip_cvget_d(z,0));
        /* copy z to t in reverse order */
        t->stride = -1;
        t->offset = fft->MN ;
        t->length = fft->MN + 1;
        vsip_cvcopy_d_d(z,t);
        /* reset t to normal */
        t->stride = 1;
        t->offset = 0;
        {   /* this is where the sorting work is done */
            vsip_cvview_d *w = ang; /* these first three steps are just to make*/
            vsip_cvview_d *f = z;   /* it easier to use already developed code */
            vsip_cvview_d *b = t;
            /* register */ vsip_length n = b->length;
            vsip_stride cwst = w->block->cstride;
            vsip_stride cfst = f->block->cstride;
            vsip_stride cbst = b->block->cstride;
            vsip_scalar_d *wpr = (vsip_scalar_d *)((w->block->R->array) + cwst * w->offset),
                          *fpr = (vsip_scalar_d *)((f->block->R->array) + cfst * f->offset),
                          *bpr = (vsip_scalar_d *)((b->block->R->array) + cbst * b->offset);
            vsip_scalar_d *wpi = (vsip_scalar_d *)((w->block->I->array) + cwst * w->offset),
                          *fpi = (vsip_scalar_d *)((f->block->I->array) + cfst * f->offset),
                          *bpi = (vsip_scalar_d *)((b->block->I->array) + cbst * b->offset);
            /* register */ vsip_stride wst = cwst * w->stride,
                                       fst = cfst * f->stride,
                                       bst = cbst * b->stride;
            vsip_scalar_d temp;
            while(n-- > 0){
                temp = 0.5 * (*bpr + *fpr + *wpr * (*bpi + *fpi) + *wpi * (*fpr - *bpr));
                *fpi = 0.5 * (*fpi - *bpi + *wpr * (*bpr - *fpr) + *wpi * (*bpi + *fpi));
                *fpr = temp;
                wpr += wst; wpi += wst;
                fpr += fst; fpi += fst;
                bpr += bst; bpi += bst;
            }  
         }   
         z->offset += fft->yst;
     }
     return;
}
