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

/* vsip_vcheck_valid_si.c Version 0.000 March 28, 1997
// 
// This file contains the private vsip_vcheck_valid_si function definition.
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
#include<vsip_vviewattributes_si.h>

extern void (vsip_blockcheck_valid_si)(const char*,
  const vsip_block_si*);
extern void (vsip_vcheck_markings)(const char*, int);
extern int (vsip_report_error)(const char*, ...);

void (vsip_vcheck_valid_si)(const char* name,
  const vsip_vview_si* v) {
  if (NULL == v) {
    vsip_report_error("In function %s,\n"
      "a null pointer to the vview object was detected.\n", name);
    exit(EXIT_FAILURE);
    }
  else {
#ifdef VSIP_DEVELOPMENT_MODE
    vsip_vcheck_markings(name, v->markings);
#endif /* VSIP_DEVELOPMENT_MODE */
    vsip_blockcheck_valid_si(name, v->block);
    }
  }

