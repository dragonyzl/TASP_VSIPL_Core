/* Created RJudd May 20, 1999 */
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
/* $Id$ */
#include<stdio.h>
#include<string.h>
#include<vsip.h>
#include<VUX.h>

void VUX_mgramxtitle_f(
         VUX_gram_f* gram,
         float xpos,
         float ypos,
         char *title)
{
/*         strcpy(gram->title, title); */
         gram->xtitle = title;
         if(xpos < 1.0){
             gram->xtitle_xloc = (int)((float)gram->xpixels * xpos);
         }else{
             gram->xtitle_xloc = (int)xpos;
         }
         if(ypos < 1.0){
             gram->xtitle_yloc = (int)((float)gram->ypixels * ypos);
         }else{
             gram->xtitle_yloc = (int)ypos;
         }
         gram->xtitle_yn = VSIP_TRUE;
         return;
}
