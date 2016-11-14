/* Modified By RJudd May 31, 1998 */
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
/* $Id: vsip_cmcreate_f.c,v 1.1 1999/12/04 02:44:07 judd Exp judd $ */
/* to put in row/col major option */
/* Modified RJudd June 28, 1998 */ 
/* To add complex block support */
/* Modified RJudd to fix row col again Feb 14, 1999 */
/* vsip_cmcreate_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_cmcreate_f function definition.
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
// Feb. 28, 1997	Added copyright notice.
// Mar. 31, 1997	Modified to conform with VSIP decoder ring.	*/

#include<vsip.h>

vsip_cmview_f* (vsip_cmcreate_f)(
  vsip_length m, vsip_length n, vsip_major rc, vsip_memory_hint h) {
  vsip_cblock_f* b = vsip_cblockcreate_f((size_t)(m*n), h);
  return (NULL == b)?
    (vsip_cmview_f*)NULL: (
      (rc == VSIP_ROW) 
      ?
      vsip_cmbind_f(b, (vsip_offset)0,
        (vsip_stride)n, m, (vsip_stride)1, n)
      :
      vsip_cmbind_f(b, (vsip_offset)0,
        (vsip_stride)1, m, (vsip_stride)m, n)
    );
  }

