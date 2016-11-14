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
/* $Id: vsip_cfir_reset_d.c,v 1.1 1999/12/31 14:50:18 judd Exp $ */

#include<vsip.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_cfirattributes_d.h>
#include<VI_functions_d.h>

void vsip_cfir_reset_d(
              vsip_cfir_d *fir)
{
    fir->p = 0;
    fir->s->length = fir->M - 1;
    {  vsip_vview_d R,I;
       /* vsip_cvfill_d(vsip_cmplx_d(0,0),fir->s); */
       VI_vrealview_d(fir->s,&R);
       VI_vimagview_d(fir->s,&I);
       vsip_vfill_d(0,&R);
       vsip_vfill_d(0,&I);
    }
    return;
}
