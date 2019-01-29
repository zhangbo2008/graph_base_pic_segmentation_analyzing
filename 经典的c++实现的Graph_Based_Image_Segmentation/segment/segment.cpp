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


32	2	C:\Program Files (x86)\Dev-Cpp\MinGW64\lib\gcc\x86_64-w64-mingw32\4.9.2\include\c++\bits\c++0x_warning.h	[Erro
r] #error This file requires compiler and library support for the ISO C++ 2011
 standard. This support is currently experimental, and must be enabled with the -std=c++11 or -std=gnu++11 compiler options.
 
 上面的错误需要在编译参数里面协商 -std=c++11即可.
 
 
 
 运行参数: 0.5 500 20 a.pnm b.pnm
 
 这个代码非常非常坑
 
 官网也没写.后来偶然看到博客上说只能识别.pnm的图片 ,经过尝试果然一下就好使了!!!!!!!!!!!!! 
 https://blog.csdn.net/abc15766228491/article/details/82261298     就是这里面写的 
 
 最后 的效果就是a.jpg 和b.jpg 因为没有pnm的浏览器所以又转回jpg了 
 
 
  
 
 
*/

#include <cstdio>
#include <cstdlib>
#include "image.h"
#include "misc.h" 
#include "pnmfile.h" 
#include "segment-image.h"
#include <iostream>
using namespace std;
int main(int argc, char **argv) {
	//argc:表示参数总的数目,也等于命令行中输入的参数个数+1 
  fprintf(stderr, "usage: %s sigma k min input(ppm) output(ppm)\n", argv[0]);
  cout<<argc<<endl;
  if (argc != 6) {
    fprintf(stderr, "usage: %s sigma k min input(ppm) output(ppm)\n", argv[0]);  /*arg进去的参数都是char类型的*/ 
    return 1;
  }
  
  
/*  c语言里面的字符串: 

 因为还有一个关键，在C语言中字符串常量的本质表示其实是一个地址，这是许多初学者比较难理解的问题。。。

          举例：

          char  *s ;

          s = "China";
		  
		  字符串常量的本质表现是代表它的第一个字符的地址
		  
		  用一句话来概括，就是 char *s 只是一个保存字符串首地址的指针变量， char a[ ] 是许多连续的内存单元，单元中的元素为char ，之所以用 char *能达到

 char a  [ ] 的效果，还是字符串的本质，地址，即给你一个字符串地址，便可以随心所欲的操所他。。但是，char* 和 char a[ ] 的本质属性是不一样的。。
		  
		  
		  
		  */
          
  
  
  
  
  
  
  
  
  
  float sigma = atof(argv[1]);      /*  字符串转float        char to float*/ 
  float k = atof(argv[2]);
  int min_size = atoi(argv[3]);    /*  字符串转int        char to int*/ 
	
  printf("loading input image.\n");
  image<rgb> *input = loadPPM(argv[4]);
	
  printf("processing\n");
  int num_ccs; 
  image<rgb> *seg = segment_image(input, sigma, k, min_size, &num_ccs); 
  savePPM(seg, argv[5]);

  printf("got %d components\n", num_ccs);
  printf("done! uff...thats hard work.\n");

  return 0;
}

