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
 
 ����Ĵ�����Ҫ�ڱ����������Э�� -std=c++11����.
 
 
 
 ���в���: 0.5 500 20 a.pnm b.pnm
 
 �������ǳ��ǳ���
 
 ����Ҳûд.����żȻ����������˵ֻ��ʶ��.pnm��ͼƬ ,�������Թ�Ȼһ�¾ͺ�ʹ��!!!!!!!!!!!!! 
 https://blog.csdn.net/abc15766228491/article/details/82261298     ����������д�� 
 
 ��� ��Ч������a.jpg ��b.jpg ��Ϊû��pnm�������������ת��jpg�� 
 
 
  
 
 
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
	//argc:��ʾ�����ܵ���Ŀ,Ҳ����������������Ĳ�������+1 
  fprintf(stderr, "usage: %s sigma k min input(ppm) output(ppm)\n", argv[0]);
  cout<<argc<<endl;
  if (argc != 6) {
    fprintf(stderr, "usage: %s sigma k min input(ppm) output(ppm)\n", argv[0]);  /*arg��ȥ�Ĳ�������char���͵�*/ 
    return 1;
  }
  
  
/*  c����������ַ���: 

 ��Ϊ����һ���ؼ�����C�������ַ��������ı��ʱ�ʾ��ʵ��һ����ַ����������ѧ�߱Ƚ����������⡣����

          ������

          char  *s ;

          s = "China";
		  
		  �ַ��������ı��ʱ����Ǵ������ĵ�һ���ַ��ĵ�ַ
		  
		  ��һ�仰������������ char *s ֻ��һ�������ַ����׵�ַ��ָ������� char a[ ] ������������ڴ浥Ԫ����Ԫ�е�Ԫ��Ϊchar ��֮������ char *�ܴﵽ

 char a  [ ] ��Ч���������ַ����ı��ʣ���ַ��������һ���ַ�����ַ����������������Ĳ������������ǣ�char* �� char a[ ] �ı��������ǲ�һ���ġ���
		  
		  
		  
		  */
          
  
  
  
  
  
  
  
  
  
  float sigma = atof(argv[1]);      /*  �ַ���תfloat        char to float*/ 
  float k = atof(argv[2]);
  int min_size = atoi(argv[3]);    /*  �ַ���תint        char to int*/ 
	
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

