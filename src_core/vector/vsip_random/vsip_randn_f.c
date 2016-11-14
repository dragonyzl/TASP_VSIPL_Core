/* Created RJudd */
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
/* $Id: vsip_randn_f.c,v 1.1 1999/12/02 19:04:27 judd Exp judd $ */
#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_randobject.h>

vsip_scalar_f vsip_randn_f(
     vsip_randstate *state)
{
   vsip_index i;
   vsip_scalar_f rp;
   if(state->type)
   { /* nonportable generator */
      vsip_scalar_ue32 a = state->a,
                      c = state->c,
                      X = state->X;
      rp = 0;
      for(i=0; i<12; i++){
          X    = a * X + c;
          rp  += (vsip_scalar_f)X/(vsip_scalar_f)4294967296.0;
      }
      state->X = X;
      rp -= 6.0;
   } else { /* portable generator */
      vsip_scalar_ue32 itemp;
      rp = 0;
      for(i=0; i<12; i++){
         state->X  = state->X * state->a + state->c;
         state->X1 = state->X1 * state->a1 + state->c1;
         itemp     = state->X - state->X1;
         if(state->X1 == state->X2){
            state->X1++;
            state->X2++;
         }
         itemp = (itemp>>8) | 0x00000001;
         rp  += (vsip_scalar_f)itemp/(vsip_scalar_f)16777216.0;
      }
      rp = (vsip_scalar_f)6.0 - rp;
   }
   return rp;
}
