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
/* $Id: vsip_blockrebind_d.c,v 1.1 1999/12/04 03:17:49 judd Exp judd $ */
/* Modified RJudd September 19, 1998 to float from double */
#include<vsip.h>
#include<vsip_blockattributes_d.h>

vsip_scalar_d* (vsip_blockrebind_d)(vsip_block_d *b,
                        vsip_scalar_d *data) {	
  if (b == (vsip_block_d*) NULL) return (vsip_scalar_d*)NULL;
  else
  if (b->admit != 0) return (vsip_scalar_d*)NULL; 
  else{
  vsip_scalar_d *oldArray = b->array;
  b->array = data;
  return oldArray;
  }
}

