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

/* vsip_error_mask.c Version 0.000 February 28, 1997
// 
// This file contains the private vsip_error_mask
// and public access function definitions.
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
// This file contains a prototype object oriented ANSI C language definition
// for the application programmer's interface
// to the VSIP (Vector Signal Image Processing) library.
//
// Revision History:
// Feb. 28, 1997	Added copyright notice.
// Mar. 31, 1997	Modified to conform with VSIP decoder ring.	*/

#include<vsip.h>
#include<VI.h>

#ifdef VSIP_DEVELOPMENT_MODE
/* private global (not thread safe) error mask				*/
static
vsip_error	vsip_error_mask = (vsip_error)0;

/* public access functions						*/
vsip_error (vsip_set_error_mask)(vsip_error mask) {
  vsip_error	temp = vsip_error_mask; vsip_error_mask |= mask; return temp; }
void (vsip_put_error_mask)(vsip_error mask) { vsip_error_mask = mask; }
int vsip_check_error(vsip_error mask) { return mask !=(mask&vsip_error_mask); }
#endif /* VSIP_DEVELOPMENT_MODE */
