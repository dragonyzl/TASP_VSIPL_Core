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

/* vsip_vcheck_clobber.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_vcheck_clobber function definition.
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
#include<VI.h>

/* This function compares two vector views of a memory block and warns
// the application programmer if they overlap unless they both have
// the same stride and their elements are not interleaved.  Diagrams
// like the one below may help the reader to understand the algorithm.
// 
//    vector
//     view
//    offset
//
//	^
//	|
//	|	 /	 /
//	|	/|      /|
//	|      / | s_u / | s_v
//	|     /__|    /__|
//	|    /	     /
//	|   /	    /
//	|  /	   /
//	| /	  /
//  o_u	|/	 /
//	|       /
//	|      /
//	|     /
//	|    /
//	|   /
//	|  /
//	| /
//	|/
//  o_v	|
//	+--------------------> vector view index			*/

extern int (vsip_report_error)(const char*, ...);

void (vsip_vcheck_clobber)(const char* name,
  vsip_offset o_u, vsip_stride s_u, vsip_length n_u,
  vsip_offset o_v, vsip_stride s_v, vsip_length n_v) {

  /* In order to simplify the analysis,
    negative strides are converted to positive strides and the offset
    is adjusted to reference exactly the same elements in reverse order.*/
  if (s_u < 0) { s_u = -s_u; o_u -= (n_u-1)*s_u; }
  if (s_v < 0) { s_v = -s_v; o_v -= (n_v-1)*s_v; }

  if (o_u < o_v) {			/* swap source and destination	*/
    vsip_offset	o   = o_v;  vsip_stride	s   = s_v;  vsip_length	n   = n_v;
		o_v = o_u;		s_v = s_u;		n_v = n_u;
		o_u = o;		s_u = s;		n_u = n;
    }

  /* It is probably a mistake if the application programmer creates a view
    which overlaps another view unless the strides are equal and no element
    of one view coincides with any element of the other view as when the
    real imaginary views of a complex data array are interleaved.	*/
  if ((o_u - o_v) <= (n_v-1)*s_v) {		/* overlapping views	*/
    if (s_u == s_v) {				/*   equal strides	*/
      if (0 != s_v && 0 == (o_u - o_v)%s_v) {	/* coincident views	*/
	vsip_report_error("In function %s,\n"
	  "source and destination operands coincide.\n", name);
	}
      }
    else {					/* unequal strides	*/
      vsip_report_error("In function %s,\n"
	"source and destination operands overlap.\n", name);
      }
    }
  }

