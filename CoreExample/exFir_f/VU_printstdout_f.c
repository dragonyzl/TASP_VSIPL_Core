/* Created RJudd October 1998 */
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
/* $Id$ */


#include<vsip.h>

void VU_printstdout_f(vsip_vview_f *x,vsip_scalar_vi n0,vsip_scalar_vi nf)
{
    vsip_length n;
    for(n=n0; n<nf; n++) printf("%f\n",vsip_vget_f(x,n));
    return;
}
