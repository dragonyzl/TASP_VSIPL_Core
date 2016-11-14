/* Created RJudd August 29, 1999 */
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
/* $Id: vsip_qrd_destroy_d.c,v 1.2 1999/12/05 16:12:07 judd Exp $ */
/* vsip_qrd_destry_d */

#include<vsip.h>
#include<vsip_qrdattributes_d.h>

int vsip_qrd_destroy_d(
         vsip_qr_d* qr)
{
   if(qr != NULL){
      vsip_valldestroy_d(qr->w);
      vsip_valldestroy_d(qr->v);
      free(qr->beta);
      free(qr);
   }
   return 0;
}
