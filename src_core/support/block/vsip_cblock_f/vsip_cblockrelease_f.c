/* Created by RJudd March 19, 1998 */
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
/* $Id: vsip_cblockrelease_f.c,v 1.1 1999/12/04 02:47:45 judd Exp judd $ */
/* Modified by RJudd June 20, 1998 */
/* for complex blocks */
#include<vsip.h>
#include<vsip_cblockattributes_f.h>

void (vsip_cblockrelease_f)(vsip_cblock_f* b,
                        vsip_scalar_bl update,
                        vsip_scalar_f* *Rp,
                        vsip_scalar_f* *Ip)
{
  if ((vsip_cblock_f*) NULL == b) {
     *Rp = (vsip_scalar_f*)NULL; *Ip = (vsip_scalar_f*)NULL;
  } else {
     if (b->kind == 0) {
        *Rp = (vsip_scalar_f*)NULL; *Ip = (vsip_scalar_f*)NULL;
     } else {
       b->admit = 0;                       /* admit = 0 implies released */
       b->R->admit = 0;
       b->I->admit = 0;
       *Rp = b->R->array;
       *Ip = (b->cstride == 1) ? b->I->array : (vsip_scalar_f*)NULL;
     }
  }
  return;
}
