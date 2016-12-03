/* $Id: vsip_vdot_f.c,v 1.1 1999/12/02 19:08:36 judd Exp judd $ */
/* Modified RJudd January 2, 1999 */
/* to add rstride */

#include <vsip.h>
#include <vsip_vviewattributes_f.h>
#include <omp.h>

extern void (vsip_vcheck_valid_f)(const char*,
  const vsip_vview_f*);
extern void (vsip_vcheck_lengths_f)(const char*,
  int, const vsip_vview_f*,
  int, const vsip_vview_f*);

vsip_scalar_f (vsip_vdot_f_para)(
  const vsip_vview_f* a,
  const vsip_vview_f* b) {
			/* a_0*b_0 + a_1*b_1 + ... + a_n-1*b_n-1	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_f("vsip_vdot_f_para", a);
    vsip_vcheck_valid_f("vsip_vdot_f_para", b);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_vcheck_lengths_f("vsip_vdot_f_para", 1, a, 2, b);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
     /*define variables*/
      /* register */ vsip_length n = a->length;
      /* register */ vsip_stride ast = a->stride * a->block->rstride,
                                 bst = b->stride * b->block->rstride;
      vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride,
                    *bp = (b->block->array) + b->offset * b->block->rstride;
      vsip_scalar_f t = 0;

      vsip_length i;
      /* do sum */
#pragma omp parallel for reduction(+: t)
      for(i=0;i<n;i++){
         t += (*(ap + i*ast) * *(bp + i*bst));
      }

     /* return dot sum */
      return t;
   }
}
