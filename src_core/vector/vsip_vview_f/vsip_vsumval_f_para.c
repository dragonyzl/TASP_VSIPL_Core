
/* $Id: vsip_vsumval_f.c,v 1.1 1999/12/02 19:09:06 judd Exp judd $ */
/* Modified RJudd January 2, 1999 */
/* to add rstride */
/* vsip_vsumval_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_vsumval_f function definition.
*/

#include <vsip.h>
#include <vsip_vviewattributes_f.h>
#include <omp.h>

extern void (vsip_vcheck_valid_f)(const char*,
  const vsip_vview_f*);

vsip_scalar_f (vsip_vsumval_f_para)(
  const vsip_vview_f* a) {/* a_0 + a_1 + ... + a_n-1	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_f("vsip_vsumval_f_para", a);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 


     /*define variables*/
      /* register */ vsip_length n = a->length;
      /* register */ vsip_stride ast = a->stride * a->block->rstride;
      vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride;

      vsip_scalar_f t = 0;
      vsip_length i;

      /* do sum */
#pragma omp parallel for reduction(+: t)
      for(i=0;i<n;i++){
         t += *(ap + i*ast);
      }

    /* return sum */
      return t;
   
  }
}
