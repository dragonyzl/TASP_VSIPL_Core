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

/* vsip_cvcheck_lengths_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_cvcheck_lengths_f function definition.
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

void (vsip_cvcheck_lengths_f)(const char* name,
  int one, const vsip_cvview_f* u,
  int two, const vsip_cvview_f* v) {
  vsip_length	n_v = v->length;
  if (0 < n_v) {
    vsip_length	n_u = u->length;
    if (0 < n_u) {
      if (n_u != n_v) { /* Both operands must have the same length.	*/
	vsip_report_error("In function %s,\n"
	  "operand #%i length = %lu != %lu = operand #%i length.\n",
	  name, one, (unsigned long int)n_u, (unsigned long int)n_v, two);
	exit(EXIT_FAILURE);
	}
      }
    else {				/* 0 == n_u			*/
      vsip_report_error("In function %s,\n"
	"operand #%i has zero length.\n", name, one);
      exit(EXIT_FAILURE);
      }
    }
  else {				/* 0 == n_v			*/
    vsip_report_error("In function %s,\n"
      "operand #%i has zero length.\n", name, two);
      exit(EXIT_FAILURE);
    }
  }

