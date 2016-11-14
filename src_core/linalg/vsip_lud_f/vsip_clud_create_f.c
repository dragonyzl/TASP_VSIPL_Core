/* Created By RJudd April 19, 1998 */
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
/* $Id: vsip_clud_create_f.c,v 1.1 1999/12/02 17:22:30 judd Exp judd $ */
#include<vsip.h>
#include<vsip_cludattributes_f.h>

vsip_clu_f* (vsip_clud_create_f)(
             vsip_length N)
{
  vsip_clu_f *clud = (vsip_clu_f*) malloc(sizeof(vsip_clu_f));
  if(clud == NULL) return (vsip_clu_f*) NULL;
  clud->N = N;
  clud->P = (vsip_index*)malloc(N * sizeof(vsip_index));
  /* check for allocation failure, 
     clean up and return NULL if found */
  if((clud->N      == (vsip_length)0) |
     (clud->P      == NULL) ){ 
       vsip_clud_destroy_f(clud);
       return (vsip_clu_f*) NULL;
  }
  return clud;
}
