/* Created RJudd */
/* SPAWARSYSCEN D881 */
#ifndef _VI_functions_d_h
#define _VI_functions_d_h 1
vsip_vview_d* VI_vrealview_d(const vsip_cvview_d*, vsip_vview_d*);
vsip_mview_d* VI_mrealview_d(const vsip_cmview_d*, vsip_mview_d*);
vsip_vview_d* VI_vimagview_d(const vsip_cvview_d*, vsip_vview_d*);
vsip_mview_d* VI_mimagview_d(const vsip_cmview_d*, vsip_mview_d*);
vsip_cvview_d* VI_cmrowview_d(const vsip_cmview_d*,vsip_index,vsip_cvview_d*);
vsip_cvview_d* VI_cmcolview_d(const vsip_cmview_d*,vsip_index,vsip_cvview_d*);
vsip_vview_d* VI_mrowview_d(const vsip_mview_d*,vsip_index,vsip_vview_d*);
vsip_vview_d* VI_mcolview_d(const vsip_mview_d*,vsip_index,vsip_vview_d*);
void VI_rcvacosh_d(vsip_vview_d*,vsip_cvview_d*);
vsip_scalar_d VI_acosh_d(vsip_scalar_d);
void VI_cvcosh_d(vsip_cvview_d*,vsip_cvview_d*);
void VI_vfreqswap_d(vsip_vview_d*);
vsip_cscalar_d VI_cvjjdot_d(const vsip_cvview_d*,const vsip_cvview_d*);
vsip_cmview_d* VI_cmtransview_d(const vsip_cmview_d*,vsip_cmview_d*);
vsip_mview_d* VI_mtransview_d(const vsip_mview_d*,vsip_mview_d*);
#endif /* _VI_functions_d_h */
