/* Created By RJudd March 19, 1998 */
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
/* $Id: vsip_blockadmit_vi.c,v 1.1 1999/12/04 02:57:03 judd Exp judd $ */
/* Modified RJudd September 19, 1998 to float from double */
/* Modified RJudd January 1, 1999 for vector index */
/* Modified RJudd February 27, 1999 to return 0 on success */
#include<vsip.h>
#include<vsip_blockattributes_vi.h>

int (vsip_blockadmit_vi)(vsip_block_vi* b,
                        vsip_scalar_bl update) {
  int blockadmit;
  if ((vsip_scalar_vi*)NULL == b->array) blockadmit = 1; /* don't admit a block with no data */
  else   
  if (b->kind != 1) blockadmit = 1;   /* b->kind =1 => public; don't admit if not public */
  else{  
  b->admit = 1;                       /* admit = 1 implies admitted   */
  blockadmit = 0;                     /* return zero on success. */
  }
  return blockadmit;
}

