/* Created RJudd December 14, 1998 */
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
/* $Id: vsip_cfir_create_d.c,v 1.1 1999/12/05 01:55:29 judd Exp $ */

#include<vsip.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_cfirattributes_d.h>
#include<VI_functions_d.h>

vsip_cfir_d *vsip_cfir_create_d(
              const vsip_cvview_d *kernel,
              vsip_symmetry symm,
              vsip_length N,
              vsip_length D,
              vsip_obj_state state,
              unsigned int ntimes,
              vsip_alg_hint hint)
{
    vsip_length klength = 0;
    vsip_cfir_d *fir = (vsip_cfir_d*)malloc(sizeof(vsip_cfir_d));
    if(fir == NULL){ return (vsip_cfir_d*) NULL;
    } else {
        switch(symm){
           case 0: klength = kernel->length;
                   break;
           case 1: klength = 2 * kernel->length - 1;
                   break;
           case 2: klength = 2 * kernel->length;
                   break;
        }
        fir->h = vsip_cvcreate_d(klength,VSIP_MEM_NONE);
        fir->s = vsip_cvcreate_d(klength-1,VSIP_MEM_NONE);
    }
    if((fir->h == NULL) | (fir->s == NULL)){ 
        vsip_cfir_destroy_d(fir);
        return (vsip_cfir_d*) NULL;
    } else {
       fir->N = N;
       fir->M = klength;
       fir->D = D;
       fir->p = 0;
       fir->ntimes = ntimes;
       fir->symm = symm;
       fir->hint = hint;
       switch(symm){
           case 0:{
              fir->h->offset = fir->h->length - 1;
              fir->h->stride = -1;
              vsip_cvcopy_d_d(kernel,fir->h);
           }
           break;
           case 1: {
              fir->h->length = kernel->length;
              vsip_cvcopy_d_d(kernel,fir->h);
              fir->h->offset = klength - 1;
              fir->h->stride = -1;
              vsip_cvconj_d(kernel,fir->h);
              fir->h->length = klength;
           }
           break;
           case 2: {
              fir->h->length = kernel->length;
              vsip_cvcopy_d_d(kernel,fir->h);
              fir->h->offset = klength - 1;
              fir->h->stride = -1;
              vsip_cvconj_d(kernel,fir->h);
              fir->h->length = klength;
           }
           break;
       }
       fir->state = state;
       fir->h->offset = 0;
       fir->h->stride = 1;
       {  vsip_vview_d R,I;
          /* vsip_cvfill_d(vsip_cmplx_d(0,0),fir->s); */
          VI_vrealview_d(fir->s,&R);
          VI_vimagview_d(fir->s,&I);
          vsip_vfill_d(0,&R);
          vsip_vfill_d(0,&I);
       }
       return fir;
    }
}
