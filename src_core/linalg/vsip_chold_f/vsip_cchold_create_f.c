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
/* $Id: vsip_cchold_create_f.c,v 1.2 1999/12/02 18:41:03 judd Exp judd $ */

/*
 *  vsip/CORE/src/linalg/vsip_chold_f/vsip_cchold_create_f.c
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
 *  created:          august-25-98 (AP) (modified from AP's version for
 *                                       real chold_create)
 *
 *                    february-19-99 (AP)
 *                    made the attribute structure public, hence its not
 *                    necessary to create it here.
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -   -
 */

#include<vsip_ccholdattributes_f.h>


vsip_cchol_f* (vsip_cchold_create_f)(
              const vsip_mat_uplo uplo,  
              vsip_length N)
{
  vsip_cchol_f *cchold = (vsip_cchol_f*) malloc(sizeof(vsip_cchol_f));
  if(cchold == NULL) return (vsip_cchol_f*) NULL;

  cchold->CHOL = (vsip_cmview_f*)malloc(sizeof(vsip_cmview_f));
  if(cchold->CHOL == NULL) return (vsip_cchol_f *) NULL;

  cchold->uplo      = uplo;
  cchold->N         = N;

  /* check for allocation failure, 
     clean up and return NULL if found */
#ifdef VSIP_DEVELOPMENT_MODE
  if(cchold->N   < 1){
       printf("Invalid system size -- returning NULL\n");
       vsip_cchold_destroy_f(cchold );
       return (vsip_cchol_f*) NULL;
  } 
#endif /* VSIP_DEVELOPMENT_MODE */
  return cchold;
}
