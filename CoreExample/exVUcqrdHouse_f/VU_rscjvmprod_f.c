/* Created RJudd July 9, 1999 */
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
/* $Id$ */

/*          -T ->              */
/* w = beta A  v               */

#include<vsip.h>

void VU_rscjvmprod_f(
     vsip_scalar_f beta,
     vsip_cvview_f *v,
     vsip_cmview_f *A,
     vsip_cvview_f *w)
{
     vsip_cvconj_f(v,v);
     vsip_cvmprod_f(v,A,w);
     vsip_cvconj_f(v,v);
     vsip_rscvmul_f(beta,w,w);
     return;
}
     
     
