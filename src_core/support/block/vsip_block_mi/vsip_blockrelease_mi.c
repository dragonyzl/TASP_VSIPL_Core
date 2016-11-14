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
/* $Id: vsip_blockrelease_mi.c,v 1.1 1999/12/04 02:51:09 judd Exp judd $ */
/* Modified RJudd September 19, 1998 to float from double */
/* Modified RJudd January 1, 1999 to vector index */
#include<vsip.h>
#include<vsip_blockattributes_mi.h>

vsip_scalar_vi* (vsip_blockrelease_mi)(vsip_block_mi* b,
                        vsip_scalar_bl update) {	
  if ((vsip_block_mi*) NULL == b) return (vsip_scalar_vi*)NULL;
  else
  if (b->kind != 1) return (vsip_scalar_vi*)NULL; 
  else{
  b->admit = 0;                       /* admit = 0 implies released */
  return b->array;
  }
}

