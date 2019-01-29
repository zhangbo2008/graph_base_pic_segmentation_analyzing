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

/* convolution */

#ifndef CONVOLVE_H
#define CONVOLVE_H

#include <vector>
#include <algorithm>
#include <cmath>
#include "image.h"

/* convolve src with mask.  dst is flipped! */
static void convolve_even(image<float> *src, image<float> *dst, 
			  std::vector<float> &mask) {
  int width = src->width();
  int height = src->height();
  int len = mask.size();

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
    	
    	
      float sum = mask[0] * imRef(src, x, y);
      
      //下行就是kernal运算 就是深度学习里面的卷积.这里面mask是1维向量.所以卷积就是点积.
	  //是even的convolve,所以y是常数,让x和mask进行变化.形象化就是kernal是1*n的沿着水平方向
	  //对图像进行滑动来算卷积. 
      for (int i = 1; i < len; i++) {
	sum += mask[i] * 
	  (imRef(src, std::max(x-i,0), y) + 
	   imRef(src, std::min(x+i, width-1), y));
      }
      imRef(dst, y, x) = sum;
      
      
      
      
    }
  }
}

/* convolve src with mask.  dst is flipped! */
static void convolve_odd(image<float> *src, image<float> *dst, 
			 std::vector<float> &mask) {
  int width = src->width();
  int height = src->height();
  int len = mask.size();

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      float sum = mask[0] * imRef(src, x, y);
      for (int i = 1; i < len; i++) {
	sum += mask[i] * 
	  (imRef(src, std::max(x-i,0), y) - 
	   imRef(src, std::min(x+i, width-1), y));
      }
      imRef(dst, y, x) = sum;
    }
  }
}

#endif
