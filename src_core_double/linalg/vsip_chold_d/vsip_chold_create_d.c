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
/* $Id: vsip_chold_create_d.c,v 1.1 1999/12/05 16:07:39 judd Exp judd $ */

/* Created By RJudd April 19, 1998 */ 
/* SPAWARSYSCEN D881 */
/* Modified May 8, 1998 */
/*
 *  vsip/CORE/src/linalg/vsip_chold_d/vsip_chold_create_d.c
 *  Vsip Library Component
 *
 *  Avijit Purkayastha 
 *  High Performance Computing Laboratory
 *  Department of Computer Science and NSF Engineering Research Center
 *  Mississippi State University, Mississippi State, MS 39762
 *                             and
 *  Department of Mathematics
 *  University of Puerto Rico, Mayaguez, PR 00681.
 *  
 *  Contact Information:
 *  Phone: (601) 325-2565; Fax: (601) 325-7692
 *  avijit@erc.msstate.edu; avijit@cs.upr.clu.edu
 *
 * -  -   -   -   -   -   -  -  -  -  -  -  -  -  -  -  -  -  -  -   -
 *
 * Copyright (C) Mississippi State University, 1998.
 *
 * Permission is hereby granted for using this software to all persons to
 * copy, modify, distribute and produce derivative works for any purpose
 * and without any restrictions, provided that this copyright notice and the
 * following disclaimer appear on all copies. This computer code also does
 * not make any warranty, express or implied, or assumes any legal liability
 * or  responsibility for  the accuracy, completeness or usefulness of any
 * of any information, apparatus, product or  process  disclosed, or
 * represents that its  use would not infringe privately owned rights.
 *
 * Work supported under contract from DARPA (TASP) through the US Air Force
 * Rome Laboratory, under contracts F30602-95-1-0036 and F30602-96-1-0329.
 * Any opinions, findings and conclusions or recommendations expressed
 * in this material are those of the author(s) and do not necessarily
 * reflect the views of U.S. Department of Energy or Mississippi State
 * University or University of Puerto Rico.
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -
 *
 *  Author: A. Purkayastha
 *
 *  created:          june-25-98 (AP) (modified from r. judds version
 *                    for lud)
 *  last update:      july-13-98 (AP)
 *                    chaned API to fit the VSIP spec...
 *                    created no views, only placed the values of
 *                    N and uplo
 *                   
 *                    july-17-98 (AP)
 *                    changed how vsip_chol_attr fits in with chold object
 *                    in choldattributes.h, according new spec.
 *
 *                    february-19-99 (AP)
 *                    made the attribute structure public, hence its not
 *                    necessary to create it here.
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -   -
 */

#include<vsip.h>
#include<vsip_choldattributes_d.h>

vsip_chol_d* (vsip_chold_create_d)(
              const vsip_mat_uplo uplo,  vsip_length N)
{
  vsip_chol_d *chold = (vsip_chol_d*) malloc(sizeof(vsip_chol_d));
  if(chold == NULL) return (vsip_chol_d*) NULL;

  chold->uplo      = uplo;
  chold->N         = N;

  /* check for allocation failure, 
     clean up and return NULL if found */
#ifdef VSIP_DEVELOPMENT_MODE
  if(chold->N < 1) {
	printf("Invalid system size -- returning NULL\n"); 
       vsip_chold_destroy_d(chold );
       return (vsip_chol_d*) NULL;
  } 
#endif /* VSIP_DEVELOPMENT_MODE */

  chold->CHOL = (vsip_mview_d*)malloc(sizeof(vsip_mview_d));
  if(chold->CHOL == NULL) return (vsip_chol_d *) NULL;

  return chold;
}
