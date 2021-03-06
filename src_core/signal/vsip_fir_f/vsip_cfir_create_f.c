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
/* $Id: vsip_cfir_create_f.c,v 1.1 1999/12/02 18:55:53 judd Exp $ */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_cfirattributes_f.h>
#include<VI_functions_f.h>

vsip_cfir_f *vsip_cfir_create_f(
              const vsip_cvview_f *kernel,
              vsip_symmetry symm,
              vsip_length N,
              vsip_length D,
              vsip_obj_state state,
              unsigned int ntimes,
              vsip_alg_hint hint)
{
    vsip_length klength = 0;
    vsip_cfir_f *fir = (vsip_cfir_f*)malloc(sizeof(vsip_cfir_f));
    if(fir == NULL){ return (vsip_cfir_f*) NULL;
    } else {
        switch(symm){
           case 0: klength = kernel->length;
                   break;
           case 1: klength = 2 * kernel->length - 1;
                   break;
           case 2: klength = 2 * kernel->length;
                   break;
        }
        fir->h = vsip_cvcreate_f(klength,VSIP_MEM_NONE);
        fir->s = vsip_cvcreate_f(klength-1,VSIP_MEM_NONE);
    }
    if((fir->h == NULL) | (fir->s == NULL)){ 
        vsip_cfir_destroy_f(fir);
        return (vsip_cfir_f*) NULL;
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
              vsip_cvcopy_f_f(kernel,fir->h);
           }
           break;
           case 1: {
              fir->h->length = kernel->length;
              vsip_cvcopy_f_f(kernel,fir->h);
              fir->h->offset = klength - 1;
              fir->h->stride = -1;
              vsip_cvconj_f(kernel,fir->h);
              fir->h->length = klength;
           }
           break;
           case 2: {
              fir->h->length = kernel->length;
              vsip_cvcopy_f_f(kernel,fir->h);
              fir->h->offset = klength - 1;
              fir->h->stride = -1;
              vsip_cvconj_f(kernel,fir->h);
              fir->h->length = klength;
           }
           break;
       }
       fir->state = state;
       fir->h->offset = 0;
       fir->h->stride = 1;
       {  vsip_vview_f R,I;
          /* vsip_cvfill_f(vsip_cmplx_f(0,0),fir->s); */
          VI_vrealview_f(fir->s,&R);
          VI_vimagview_f(fir->s,&I);
          vsip_vfill_f(0,&R);
          vsip_vfill_f(0,&I);
       }
       return fir;
    }
}
