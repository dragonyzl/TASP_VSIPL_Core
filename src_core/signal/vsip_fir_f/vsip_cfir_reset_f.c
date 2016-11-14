/* Created RJudd December 28, 1999 */
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
/* $Id: vsip_cfir_reset_f.c,v 1.1 1999/12/31 14:51:16 judd Exp $ */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_cfirattributes_f.h>
#include<VI_functions_f.h>

void vsip_cfir_reset_f(
              vsip_cfir_f *fir)
{
    fir->p = 0;
    fir->s->length = fir->M - 1;
    {  vsip_vview_f R,I;
       /* vsip_cvfill_f(vsip_cmplx_f(0,0),fir->s); */
       VI_vrealview_f(fir->s,&R);
       VI_vimagview_f(fir->s,&I);
       vsip_vfill_f(0,&R);
       vsip_vfill_f(0,&I);
    }
    return;
}
