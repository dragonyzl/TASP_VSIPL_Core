/* Modified RJudd June 27, 1998 */
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
/* $Id$ */
/* To add complex block support */
/* vsip_cvcheck_clobber_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_cvcheck_clobber_f function definition.
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
#include<vsip_cvviewattributes_f.h>

extern int (vsip_report_error)(const char*, ...);
extern void (vsip_vcheck_clobber)(const char*,
  vsip_offset, vsip_stride, vsip_length,
  vsip_offset, vsip_stride, vsip_length);

void (vsip_cvcheck_clobber_f)(const char* name,
  vsip_cvview_f* u, vsip_cvview_f* v) {
  vsip_cblock_f*        b_v = v->block;
  vsip_cblock_f*        b_u = u->block;
  /*  Memory blocks are supposed to be disjoint.			*/
  if (b_u == b_v) {
    vsip_length	        n_v = v->length;
    if (0 < n_v) {
      vsip_length       n_u = u->length;
      if (0 < n_u) {
	vsip_offset     o_v = v->offset;
	vsip_offset     o_u = u->offset;
	vsip_stride     s_v = v->stride;
	vsip_stride     s_u = u->stride;
	/* Element by element operations may overwrite a source operand
	  as long as the source and destination match element for element.*/
	if (o_u != o_v || s_u != s_v) {
	  vsip_vcheck_clobber(name, o_u, s_u, n_u, o_v, s_v, n_v);
	  }
	/* The length of destination operand
	  must be no greater than one if the stride is zero.	*/
	if (0 == s_v && 1 < n_v) {
	  vsip_report_error("In function %s,\n"
	    "the destination operand stride = 0 and length = %lu > 1.\n",
	    name, (unsigned long int)n_v);
	  }
	}
      else {				/* 0 == n_u			*/
	vsip_report_error("In function %s,\n"
	  "the source operand has zero length.\n", name);
	exit(EXIT_FAILURE);
	}
      }
    else {				/* 0 == n_v			*/
      vsip_report_error("In function %s,\n"
	"the destination operand has zero length.\n", name);
      exit(EXIT_FAILURE);
      }
    }
  else {				/* b_u != b_v			*/
    /* It is probably a mistake if the application programmer creates
      a public memory block which overlaps another memory block
      but this may or may not be the correct place to check for it.	*/
    }
  }

