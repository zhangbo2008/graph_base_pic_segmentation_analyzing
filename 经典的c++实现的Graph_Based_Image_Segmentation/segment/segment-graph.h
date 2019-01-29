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
  std::sort(edges, edges + num_edges);//c++�ĺ�������ֱ���ڴ���ȥ�ı�����ֱ���޸�.Ϊ�˽�ʡ
  //�ռ��Ч�� ,��һ�������������begin,�ڶ��������������end.����end���󷨾������鿪ʼ��ַ
  //+�������.(�����ָ��Ӽ�����ļ���) 

  // make a disjoint-set forest
  universe *u = new universe(num_vertices);
//�����㷨�ĺ��ľ������� 
  // init thresholds
  float *threshold = new float[num_vertices];
  //��ÿһ��vertx ��һ����ֵ.����threshold����һ������ . 
  for (int i = 0; i < num_vertices; i++)
    threshold[i] = THRESHOLD(1,c);//������c��min_size:ȡ��20. 

  // for each edge, in non-decreasing weight order...
  for (int i = 0; i < num_edges; i++) {
    edge *pedge = &edges[i];       //��Ϊedges[i]��һ�����,�������pedge��һ��ָ��,�����ұ���Ҫ&���� 
    
    // components conected by this edge
    int a = u->find(pedge->a);   //�ߵ��������ڽڵ� 
    int b = u->find(pedge->b);//�ߵ��յ�����ڽڵ� 
    if (a!=b) {  
    
    //a!=b ��Ϊ��ʲô?�������������ж� ,��ô�ͻ��һ��ͼ���ڲ��е�2���ڵ�Ҳ������
	//����Ĵ���. �������õ���ͼ����ÿһ��������һ��,��Ȼ��������Ҫ��!! 
    
      if ((pedge->w <= threshold[a]) &&
	  (pedge->w <= threshold[b])) {
	  	
	  	
	u->join(a, b);
	a = u->find(a);//��a�ĸ��ڵ�,����a,�����������a������a���ڵ�����������. 
	threshold[a] = pedge->w + THRESHOLD(u->size(a), c);//������һ�����²���.
	//��ʵ���������������²���Ҳһ��.���� threshold[a] = pedge->w + THRESHOLD(u->size(a), c)*2;
	//����������Ժ���д��*200��ô,thereshold��ͻ��ǳ���,ֱ�������if��������,�������
	//�õ���ͼƬ�����ǳ���.��֮������Ժ���д/200,��ô����������ǳ���! 
	
	
	
      }
      
      
      
      
    }
  }

  // free up
  delete threshold;
  return u;
}

#endif
