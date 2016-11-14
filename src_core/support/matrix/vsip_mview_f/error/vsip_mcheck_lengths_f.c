/* Modified RJudd April 20, 1998 */
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
/* 1,2 to row,col */
/* vsip_mcheck_lengths_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_mcheck_lengths_f function definition.
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

extern int (vsip_report_error)(const char*, ...);

void (vsip_mcheck_lengths_f)(const char* name,
  int one, const vsip_mview_f* U,
  int two, const vsip_mview_f* V) {
  vsip_length	n2_V = vsip_mgetcollength_f(V);
  if (0 < n2_V) {
    vsip_length	n2_U = vsip_mgetcollength_f(U);
    if (0 < n2_U) {
      /* Both operands must have the same number of rows.		*/
      if (n2_U == n2_V) {
	vsip_length	n1_V = vsip_mgetrowlength_f(V);
	if (0 < n1_V) {
	  vsip_length	n1_U = vsip_mgetrowlength_f(U);
	  if (0 < n1_U) {
	    /* Both operands must have the same number of columns.	*/
	    if (n1_U != n1_V) {
	      vsip_report_error("In function %s,\n"
		"operand #%i columns = %lu != %lu = operand #%i columns.\n",
		name,
		one, (unsigned long int)n1_U, (unsigned long int)n1_V, two);
	      exit(EXIT_FAILURE);
	      }
	    }
	  else {			/* 0 == n1_U			*/
	    vsip_report_error("In function %s,\n"
	      "operand #%i has no columns.\n", name, one);
	    exit(EXIT_FAILURE);
	    }
	  }
	else {				/* 0 == n1_V			*/
	  vsip_report_error("In function %s,\n"
	    "operand #%i has no columns.\n", name, two);
	    exit(EXIT_FAILURE);
	  }
	}
      else {
	vsip_report_error("In function %s,\n"
	  "operand #%i rows = %lu != %lu = operand #%i rows.\n", name,
	  one, (unsigned long int)n2_U, (unsigned long int)n2_V, two);
	exit(EXIT_FAILURE);
	}
      }
    else {				/* 0 == n2_U			*/
      vsip_report_error("In function %s,\n"
	"operand #%i has no rows.\n", name, one);
      exit(EXIT_FAILURE);
      }
    }
  else {				/* 0 == n2_V			*/
    vsip_report_error("In function %s,\n"
      "operand #%i has no rows.\n", name, two);
      exit(EXIT_FAILURE);
    }
  }

