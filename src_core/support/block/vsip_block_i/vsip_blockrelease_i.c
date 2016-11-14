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
/* $Id: vsip_blockrelease_i.c,v 1.1 1999/12/04 02:55:50 judd Exp judd $ */
/* Modified March 19, 1998 to vsip_blockrelease_i */
#include<vsip.h>
#include<vsip_blockattributes_i.h>

vsip_scalar_i* (vsip_blockrelease_i)(vsip_block_i* b,
                        vsip_scalar_bl update) {	
  if ((vsip_block_i*) NULL == b) return (vsip_scalar_i*)NULL;
  else
  if (b->kind == 0) return (vsip_scalar_i*)NULL; 
  else{
  b->admit = 0;                       /* admit = 0 implies released */
  return b->array;
  }
}

