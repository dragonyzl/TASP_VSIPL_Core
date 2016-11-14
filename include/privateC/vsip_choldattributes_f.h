/* Created by RJudd April 19, 1998*/
/* SPAWARSYSCEN D881 */
/*
 *  vsip/CORE/include/private/vsip_choldattributes_f.h
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
 *  created:          july-17-98 (AP) 
 *                    modified from Randy Judd's vsip_ludattributes_f.h
 *  last update:      (date) (AP)
 *                    changed ...
 *
 * -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -   -
 */
#ifndef _vsip_choldattributes_f_h  
#define _vsip_choldattributes_f_h 1
#include<vsip.h>
#include<VI.h>
#include<vsip_mviewattributes_f.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_vviewattributes_vi.h>


struct vsip_choldattributes_f{
       	vsip_mview_f* CHOL; /* make up some workspace */
       	vsip_scalar_f singular;   /* define too small pivot */
      	vsip_mat_uplo uplo;    /* indicate which part of matrix is ref.*/ 
        vsip_length N;         /* num. of rows or cols in the matrix */ 
};

#endif /*_vsip_choldattributes_f_h */
