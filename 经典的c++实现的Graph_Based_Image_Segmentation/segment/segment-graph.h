/*
Copyright (C) 2006 Pedro Felzenszwalb

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#ifndef SEGMENT_GRAPH
#define SEGMENT_GRAPH

#include <algorithm>
#include <cmath>
#include "disjoint-set.h"

// threshold function
#define THRESHOLD(size, c) (c/size)

typedef struct {
  float w;
  int a, b;
} edge;

bool operator<(const edge &a, const edge &b) {
  return a.w < b.w;
}

/*
 * Segment a graph
 *
 * Returns a disjoint-set forest representing the segmentation.
 *
 * num_vertices: number of vertices in graph.
 * num_edges: number of edges in graph
 * edges: array of edges.
 * c: constant for treshold function.
 */
universe *segment_graph(int num_vertices, int num_edges, edge *edges, 
			float c) { 
  // sort edges by weight
  std::sort(edges, edges + num_edges);//c++的函数都是直接在传进去的变量上直接修改.为了节省
  //空间和效率 ,第一个参数是数组的begin,第二个参数是数组的end.至于end的求法就是数组开始地址
  //+数组个数.(这个是指针加减运算的技巧) 

  // make a disjoint-set forest
  universe *u = new universe(num_vertices);
//整个算法的核心就在下面 
  // init thresholds
  float *threshold = new float[num_vertices];
  //对每一个vertx 给一个阈值.所以threshold就是一个数组 . 
  for (int i = 0; i < num_vertices; i++)
    threshold[i] = THRESHOLD(1,c);//这里面c是min_size:取的20. 

  // for each edge, in non-decreasing weight order...
  for (int i = 0; i < num_edges; i++) {
    edge *pedge = &edges[i];       //因为edges[i]是一歌对象,但是左边pedge是一个指针,所以右边需要&以下 
    
    // components conected by this edge
    int a = u->find(pedge->a);   //边的起点的祖宗节点 
    int b = u->find(pedge->b);//边的终点的祖宗节点 
    if (a!=b) {  
    
    //a!=b 是为了什么?如果不进行这个判断 ,那么就会把一个图的内部中的2个节点也进行了
	//下面的处理. 这样最后得到的图就是每一个像素是一类,显然不是我们要的!! 
    
      if ((pedge->w <= threshold[a]) &&
	  (pedge->w <= threshold[b])) {
	  	
	  	
	u->join(a, b);
	a = u->find(a);//把a的父节点,顶掉a,这样下面就用a来代表a所在的子树的祖先. 
	threshold[a] = pedge->w + THRESHOLD(u->size(a), c);//这行是一个更新策略.
	//其实上面行用其他更新策略也一样.比如 threshold[a] = pedge->w + THRESHOLD(u->size(a), c)*2;
	//比如这个策略后面写上*200那么,thereshold会突变非常大,直接上面的if都成立了,所以最后
	//得到的图片分类会非常少.反之如果策略后面写/200,那么分类后的类别会非常多! 
	
	
	
      }
      
      
      
      
    }
  }

  // free up
  delete threshold;
  return u;
}

#endif
