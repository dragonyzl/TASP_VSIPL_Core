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
/* $Id: vsip_blockrebind_f.c,v 1.1 1999/12/04 02:52:48 judd Exp judd $ */
/* Modified RJudd September 19, 1998 to float from double */
#include<vsip.h>
#include<vsip_blockattributes_f.h>

vsip_scalar_f* (vsip_blockrebind_f)(vsip_block_f *b,
                        vsip_scalar_f *data) {	
  if (b == (vsip_block_f*) NULL) return (vsip_scalar_f*)NULL;
  else
  if (b->admit != 0) return (vsip_scalar_f*)NULL; 
  else{
  vsip_scalar_f *oldArray = b->array;
  b->array = data;
  return oldArray;
  }
}

