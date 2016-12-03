/* $Id: vsip_vmul_f_para.c,v 1.1 1999/12/02 19:08:56 judd Exp judd $ */
/* Modified RJudd January 2, 1999 */
/* to add rstride */
/* vsip_vmul_f_para.c Version 0.000 February 28, 1997*/


#include <vsip.h>
#include <vsip_vviewattributes_f.h>
#include <omp.h>

extern void (vsip_vcheck_valid_f)(const char*,
  const vsip_vview_f*);
extern void (vsip_vcheck_lengths_f)(const char*,
  int, const vsip_vview_f*, int, const vsip_vview_f*);
extern void (vsip_vcheck_clobber_f)(const char*,
  const vsip_vview_f*, const vsip_vview_f*);

void (vsip_vmul_f_para)(
  const vsip_vview_f *a,
  const vsip_vview_f *b,
  const vsip_vview_f *r) {	/* r_j = a_j*b_j	*/
#ifdef VSIP_DEVELOPMENT_MODE
  if (vsip_check_error(vsip_invalid_structure_object)) {
    vsip_vcheck_valid_f("vsip_vmul_f_para", a);
    vsip_vcheck_valid_f("vsip_vmul_f_para", b);
    vsip_vcheck_valid_f("vsip_vmul_f_para", r);
    }
  if (vsip_check_error(vsip_nonconformal_view_lengths)) {
    vsip_vcheck_lengths_f("vsip_vmul_f_para", 1, a, 3, r);
    vsip_vcheck_lengths_f("vsip_vmul_f_para", 2, b, 3, r);
    }
  if (vsip_check_error(vsip_clobbered_source_operand)) {
    vsip_vcheck_clobber_f("vsip_vmul_f_para", a, r);
    vsip_vcheck_clobber_f("vsip_vmul_f_para", b, r);
    }
#endif /* VSIP_DEVELOPMENT_MODE */
  { 
      /*define variables*/
      /* register */ vsip_length n = r->length;
      /* register */ vsip_stride ast = a->stride * a->block->rstride,
                                 bst = b->stride * b->block->rstride,
                                 rst = r->stride * r->block->rstride;
      vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride,
                    *bp = (b->block->array) + b->offset * b->block->rstride,
                    *rp = (r->block->array) + r->offset * r->block->rstride;
      /*end define*/

      vsip_length i;
#pragma omp parallel for
      for(i=0;i<n;i++){
        *(rp + i*rst) = *(ap + i*ast) * *(bp + i*bst);
      }

   }
}
