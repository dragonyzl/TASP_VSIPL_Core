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
/* $Id: vsip_cblockrebind_d.c,v 1.1 1999/12/04 03:19:10 judd Exp judd $ */
/* Modified RJudd July 11, 1998 */
/* complex block modification */
#include<vsip.h>
#include<vsip_cblockattributes_d.h>

void (vsip_cblockrebind_d)(vsip_cblock_d *b,
                        vsip_scalar_d *Rp,
                        vsip_scalar_d *Ip,
                        vsip_scalar_d* *pRp,
                        vsip_scalar_d* *pIp) {	
  if (b == (vsip_cblock_d*) NULL){
     *pRp = (vsip_scalar_d*) NULL; *pIp = (vsip_scalar_d*) NULL; 
  } else {
    if (b->admit != 0) {
     *pRp = (vsip_scalar_d*) NULL; *pIp = (vsip_scalar_d*) NULL; 
    } else {
       *pRp = b->R->array;
       *pIp = (b->cstride == 1) ? b->I->array : (vsip_scalar_d*) NULL;
       b->R->array = Rp;
       b->cstride = ((Ip == NULL) ? 2 : 1);
       b->R->rstride = b->cstride;
       b->I->rstride = b->cstride;
       b->I->array = (b->cstride == 1) ? Ip : Rp + 1;
#ifdef VSIP_DEVELOPMENT_MODE
       b->R->size = (b->cstride == 2) ? b->size : b->size / 2;
       b->I->size = b->R->size - (b->cstride -1) * sizeof(vsip_scalar_d);
#endif /* VSIP_DEVELOPMENT_MODE */
    }
  return;
  }
}
