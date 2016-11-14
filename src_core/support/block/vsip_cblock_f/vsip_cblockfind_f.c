/* Modified RJudd June 20, 1998 */
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
/* $Id: vsip_cblockfind_f.c,v 1.1 1999/12/04 02:47:43 judd Exp judd $ */
/* Modified to vsip_cblockfind_f.c */
/* Modified RJudd July 11, 1998 */
/* modifiaction of complex block */
/* vsip_blockfind_f.c Version 0.000 March 28, 1997
// 
// This file contains the vsip_blockfind_f function definition.
//
// Copyright (c) Hughes Research Laboratories, Inc. 1997 
// A non-exclusive, non-royalty bearing license is hereby granted to all 
// persons to copy, modify, distribute and produce derivative works for 
// any purpose, provided that this copyright notice and following disclaimer 
// appear on all copies.  
// 
// THIS LICENSE INCLUDES NO WARRANTEES, EXPRESSED OR IMPLIED, WHETHER ORAL 
// OR WRITTEN, WITH RESPECT TO THE SOFTWARE OR OTHER MATERIAL, INCLUDING 
// BUT NOT LIMITED TO ANY IMPLIED WARRANTIES OF MERCHANTABILITY, OR FITNESS 
// FOR A PARTICULAR PURPOSE, OR ARISING FROM A COURSE OF PERFORMANCE, OR 
// DEALING, OR FROM USAGE OR TRADE, OR OF NON-INFRINGEMENT OF ANY PATENTS 
// OF THIRD PARTIES.
//
// This material is based upon work supported by Ft. Huachuca/DARPA under
// Contract No.  DABT63-96-C-0060.  Any opinions, findings and conclusions
// or recommendations expressed in this material are those of the author(s)
// and do not necessarily reflect the views of Ft. Huachuca/DARPA.
//
// Author: E. Robert Tisdale
//
// Revision History:
// Mar. 28, 1997	Added copyright notice.				*/

#include<vsip.h>
#include<vsip_cblockattributes_f.h>

void (vsip_cblockfind_f)(const vsip_cblock_f* b,
                         vsip_scalar_f* *Rp,
                         vsip_scalar_f* *Ip) {
  /* Return a pointer to the public data array(s)
     if vsip_cblock_f *b is public, otherwise return a null pointer. */
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_cblockcheck_valid_f("vsip_cblockfind_f", b);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  *Rp = ((b->kind && !(b->admit))? b->R->array: (vsip_scalar_f*)NULL);
  *Ip = (b->cstride == 1) ? b->I->array : (vsip_scalar_f*)NULL;
   return;
  }

