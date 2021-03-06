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
/* $Id: vsip_blockrebind_si.c,v 1.1 1999/12/05 16:36:24 judd Exp judd $ */
/* Modified March 19 to vsip_blockrebind_si */
#include<vsip.h>
#include<vsip_blockattributes_si.h>

vsip_scalar_si* (vsip_blockrebind_si)(vsip_block_si *b,
                        vsip_scalar_si *data) {	
  if ((vsip_block_si*) NULL == b) return (vsip_scalar_si*)NULL;
  else
  if (b->admit != 0) return (vsip_scalar_si*)NULL; 
  else{
  vsip_scalar_si *oldArray = b->array;
  b->array = data;
  return oldArray;
  }
}

