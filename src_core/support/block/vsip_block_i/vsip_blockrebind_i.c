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
/* $Id: vsip_blockrebind_i.c,v 1.1 1999/12/04 02:55:49 judd Exp judd $ */
/* Modified March 19 to vsip_blockrebind_i */
#include<vsip.h>
#include<vsip_blockattributes_i.h>

vsip_scalar_i* (vsip_blockrebind_i)(vsip_block_i *b,
                        vsip_scalar_i *data) {	
  if ((vsip_block_i*) NULL == b) return (vsip_scalar_i*)NULL;
  else
  if (b->admit != 0) return (vsip_scalar_i*)NULL; 
  else{
  vsip_scalar_i *oldArray = b->array;
  b->array = data;
  return oldArray;
  }
}

