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

/* vsip_mcheck_outside.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_mcheck_outside function definition.
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

void (vsip_mcheck_outside)(const char* name, vsip_length N, vsip_offset o,
  vsip_stride s2, vsip_length n2, vsip_stride s1, vsip_length n1) {
  if (N <= o) {
    vsip_report_error("In function %s, %lu = offset is too large.\n",
      name, (unsigned long int)o);
    }
  else {
    if (0 < n1) {
      if ((s1 < 0 && o < -s1*(n1-1)) || (0 < s1 && N <= o + s1*(n1-1))) {
	vsip_report_error(
	  "In function %s, too many columns = %lu for stride = %li.\n",
	  name, (unsigned long int)n1, (signed long int)s1);
	}
      }
    else {				/* 0 == n1			*/
      vsip_report_error("In function %s, %lu = columns.\n",
	name, (unsigned long int)n1);
      }
    if (0 < n2) {
      if ((s2 < 0 && o < -s2*(n2-1)) || (0 < s2 && N <= o + s2*(n2-1))) {
	vsip_report_error(
	  "In function %s, too many rows = %lu for stride = %li.\n",
	  name, (unsigned long int)n2, (signed long int)s2);
	}
      }
    else {				/* 0 == n1			*/
      vsip_report_error("In function %s, %lu = rows.\n",
	name, (unsigned long int)n2);
      }
    if (s1 < 0) {
      if (s2 < 0) {
	if ((-s1)*(n1-1) + (-s2)*(n2-1) <= o) return;
	}
      else
      if (0 == s2) {
	return;
	}
      else {				/* 0 < s2			*/
	vsip_offset	o2 = o + s2*(n2-1);
	if ((-s1)*(n1-1) <= o2 && o2 < N + (-s1)*(n1-1)) return;
	}
      }
    else
    if (0 == s1) {
      return;
      }
    else {				/* 0 < s1			*/
      if (s2 < 0) {
	vsip_offset	o1 = o + s1*(n1-1);
	if ((-s2)*(n2-1) <= o1 && o1 < N + (-s2)*(n2-1)) return;
	}
      else
      if (0 == s2) {
	return;
	}
      else {				/* 0 < s2			*/
	if (o + s1*(n1-1) + s2*(n2-1) < N) return;
	}
      }
    vsip_report_error("In function %s, "
      "too many columns = %lu for stride = %li or\n"
      "too many rows = %lu for stride = %li.\n", name,
      (unsigned long int)n1, (signed long int)s1,
      (unsigned long int)n2, (signed long int)s2);
    }
  }

