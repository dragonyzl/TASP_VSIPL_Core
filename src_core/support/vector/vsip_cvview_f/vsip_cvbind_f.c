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
/* $Id: vsip_cvbind_f.c,v 1.1 1999/12/04 02:38:09 judd Exp judd $ */

/* vsip_cvbind_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_cvbind_f function definition.
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
#include"vsip_cvviewattributes_f.h"

extern void (vsip_cblockcheck_valid_f)(const char*,
  const vsip_cblock_f*);
extern void (vsip_cvcheck_outside_f)(const char*,
  const vsip_cblock_f*, vsip_offset, vsip_stride, vsip_length);

void (vsip_cvviewinit_f)(vsip_cvview_f* v,
  const vsip_cblock_f* b, vsip_offset o, vsip_stride s, vsip_length n) {
  if (NULL != v) {			/* Initialize a vector view.	*/
    v->block  = (vsip_cblock_f*)b;
    v->offset = o;
    v->stride = s;
    v->length = n;
#ifdef VSIP_DEVELOPMENT_MODE
    v->markings = vsip_valid_structure_object;
    if (vsip_check_error(vsip_invalid_structure_object)) {
      vsip_cblockcheck_valid_f("vsip_cvviewinit_f", b);
      }
    if (vsip_check_error(vsip_view_outside_data_array)) {
      vsip_cvcheck_outside_f("vsip_cvviewinit_f",
      b, o, s, n);
      }
    /* ++b->bindings; */		/* increment reference counter	*/
    { /* Prevent compilers from complaining about const b->bindings.	*/
      int*	p = (int*)(&(b->bindings));
      ++(*p);
      }
    ++vsip_vector_object_total;
#endif /* VSIP_DEVELOPMENT_MODE */
    }
  }

vsip_cvview_f* (vsip_cvbind_f)(
  const vsip_cblock_f* b, vsip_offset o, vsip_stride s, vsip_length n) {
#ifdef VSIP_DEVELOPMENT_MODE
    if (vsip_check_error(vsip_invalid_structure_object)) {
      vsip_cblockcheck_valid_f("vsip_cvbind_f", b);
      }
    if (vsip_check_error(vsip_view_outside_data_array)) {
      vsip_cvcheck_outside_f("vsip_cvbind_f",
      b, o, s, n);
      }
#endif /* VSIP_DEVELOPMENT_MODE */
  { /* Prevent error checking in vsip_cvviewinit_f.	*/
    VSIP_SET_ERROR_MASK(mask,
      vsip_invalid_structure_object|vsip_view_outside_data_array)
    vsip_cvview_f* v = (vsip_cvview_f*)malloc(sizeof(vsip_cvview_f));
    vsip_cvviewinit_f(v, b, o, s, n);
    VSIP_PUT_ERROR_MASK(mask)
    return v;
    }
  }

