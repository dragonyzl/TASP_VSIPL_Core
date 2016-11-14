#ifndef _vsip_cblockattributes_f_h
#define _vsip_cblockattributes_f_h 1
/* Modified RJudd June 20, 1998 */
/* SPAWARSYSCEN D881 */
/* to vsip_cblockattributes_f.h */
/* Modified RJudd July 10, 1998 */
/* change to cblock */ 
/* vsip_cblockattributes_f.h */
/* vsip_blockattributes_f.h Version 0.000 February 28, 1997
// 
// This file contains the PRIVATE vsip_blockattributes_f definition.
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
// Feb. 28, 1997    Added copyright notice.
// Mar. 31, 1997    Modified to conform with VSIP decoder ring.    */

#include<vsip.h>
#include<VI.h>
#include<vsip_blockattributes_f.h>

extern int    vsip_privateblock_total;
extern int    vsip_public_block_total;
extern
void (vsip_cblockcheck_valid_f)(const char*, const vsip_cblock_f*);
extern int (vsip_report_error)(const char*, ...);

struct vsip_cblockattributes_f {
  vsip_block_f *R,
               *I;            /* external data array                      */
  int           kind;         /* 0 ==> private, 1 ==> public              */
  int           admit;        /* 0 ==> No,      1 ==> Yes                 */
  int           cstride;      /* 1 for split, 2 for interleaved           */
#ifdef VSIP_DEVELOPMENT_MODE
  size_t     size;            /* data array size in bytes                 */
  int        bindings;        /* reference counter                        */
  int        markings;        /* valid|destoyed block object              */
#endif /* VSIP_DEVELOPMENT_MODE */
  };
#endif /* _vsip_cblockattributes_f_h */

