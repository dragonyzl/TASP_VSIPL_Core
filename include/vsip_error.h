#ifndef _vsip_public_error_h
#define _vsip_public_error_h 1
/* vsip_public_error.h Version 0.000 March 28, 1997
// 
// This file contains public VSIP error type definitions.
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

#ifdef VSIP_DEVELOPMENT_MODE
/* public enumerated errors						*/
typedef enum {	vsip_invalid_structure_object   = 1 << 0,
		vsip_bad_public_array_pointer	= 1 << 1,
		vsip_bad_private_array_storage	= 1 << 2,
		vsip_non_zero_binding_counter	= 1 << 3,
		vsip_view_outside_data_array	= 1 << 4,
		vsip_view_index_exceeds_length	= 1 << 5,
		vsip_nonconformal_view_lengths	= 1 << 6,
		vsip_clobbered_source_operand	= 1 << 7
  } vsip_error;

vsip_error vsip_set_error_mask(vsip_error mask);
void vsip_put_error_mask(vsip_error mask);
int vsip_check_error(vsip_error mask);

#define VSIP_SET_ERROR_MASK(t, m) vsip_error t = vsip_set_error_mask((vsip_error)(m));
#define VSIP_PUT_ERROR_MASK(m) vsip_put_error_mask((vsip_error)(m));
#else
#define VSIP_SET_ERROR_MASK(t, m)
#define VSIP_PUT_ERROR_MASK(m)
#endif /* VSIP_DEVELOPMENT_MODE */

#endif /* _vsip_public_error_h */
