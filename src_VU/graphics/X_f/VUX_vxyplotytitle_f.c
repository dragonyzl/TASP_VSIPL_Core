/* Created RJudd May 18, 1999 */
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

void VUX_vxyplotytitle_f(
         VUX_graph_f* graph,
         float xpos,
         float ypos,
         char *title)
{
/*         strcpy(graph->title, title); */
         graph->ytitle = title;
         if(xpos < 1.0){
             graph->ytitle_xloc = (int)((float)graph->xpixels * xpos);
         }else{
             graph->ytitle_xloc = (int)xpos;
         }
         if(ypos < 1.0){
             graph->ytitle_yloc = (int)((float)graph->ypixels * ypos);
         }else{
             graph->ytitle_yloc = (int)ypos;
         }
         graph->ytitle_yn = VSIP_TRUE;
         return;
}
