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

/* basic image I/O */

#ifndef PNM_FILE_H
#define PNM_FILE_H

#include <cstdlib>
#include <climits>
#include <cstring>
#include <fstream>
#include "image.h"
#include "misc.h"

#define BUF_SIZE 256

class pnm_error { };

static void read_packed(unsigned char *data, int size, std::ifstream &f) {
  unsigned char c = 0;
  
  int bitshift = -1;
  for (int pos = 0; pos < size; pos++) {
    if (bitshift == -1) {
      c = f.get();
      bitshift = 7;
    }
    data[pos] = (c >> bitshift) & 1;
    bitshift--;
    }
}

static void write_packed(unsigned char *data, int size, std::ofstream &f) {
  unsigned char c = 0;
  
  int bitshift = 7;
  for (int pos = 0; pos < size; pos++) {
      c = c | (data[pos] << bitshift);
      bitshift--;
      if ((bitshift == -1) || (pos == size-1)) {
	f.put(c);
	bitshift = 7;
	c = 0;
      }
  }
}

/* read PNM field, skipping comments */ 
static void pnm_read(std::ifstream &file, char *buf) {
/*	������ &file   Ȼ�����ݸ��ַ���buf*/
  char doc[BUF_SIZE];
  char c;
  
  file >> c;
  while (c == '#') {
    file.getline(doc, BUF_SIZE);
    file >> c;
  }
/*  ÿ�ζ�һ�� */
  
  
  
  file.putback(c);
 
  file.width(BUF_SIZE);
  file >> buf;
  file.ignore();
   /* ����������������������n���ַ�����������ָ������ֹ�ַ�ʱ��ǰ��������ʱ����������ֹ�ַ����ڵ������ַ�����*/
 
}

static image<uchar> *loadPBM(const char *name) {
  char buf[BUF_SIZE];
  
  /* read header */
  std::ifstream file(name, std::ios::in | std::ios::binary);
  pnm_read(file, buf);
  if (strncmp(buf, "P4", 2))
    throw pnm_error();
    
  pnm_read(file, buf);
  int width = atoi(buf);
  pnm_read(file, buf);
  int height = atoi(buf);
  
  /* read data */
  image<uchar> *im = new image<uchar>(width, height);
  for (int i = 0; i < height; i++)
    read_packed(imPtr(im, 0, i), width, file);
  
  return im;
}

static void savePBM(image<uchar> *im, const char *name) {
  int width = im->width();
  int height = im->height();
  std::ofstream file(name, std::ios::out | std::ios::binary);

  file << "P4\n" << width << " " << height << "\n";
  for (int i = 0; i < height; i++)
    write_packed(imPtr(im, 0, i), width, file);
}

static image<uchar> *loadPGM(const char *name) {
  char buf[BUF_SIZE];
  
  /* read header */
  std::ifstream file(name, std::ios::in | std::ios::binary);
  pnm_read(file, buf);
  if (strncmp(buf, "P5", 2))
    throw pnm_error();

  pnm_read(file, buf);
  int width = atoi(buf);
  pnm_read(file, buf);
  int height = atoi(buf);

  pnm_read(file, buf);
  if (atoi(buf) > UCHAR_MAX)
    throw pnm_error();

  /* read data */
  image<uchar> *im = new image<uchar>(width, height);
  file.read((char *)imPtr(im, 0, 0), width * height * sizeof(uchar));

  return im;
}

static void savePGM(image<uchar> *im, const char *name) {
  int width = im->width();
  int height = im->height();
  std::ofstream file(name, std::ios::out | std::ios::binary);

  file << "P5\n" << width << " " << height << "\n" << UCHAR_MAX << "\n";
  file.write((char *)imPtr(im, 0, 0), width * height * sizeof(uchar));
}
#include <iostream>
using namespace std;
static image<rgb> *loadPPM(const char *name) {  /*char *name ��һ���ַ��� */


/*

Ϊʲôͷ�ļ�����ĺ�����д��static. ������кô���. 

��̬�����ᱻ�Զ�������һ��һֱʹ�õĴ洢����ֱ���˳�Ӧ�ó���ʵ���������˵��ú���ʱѹջ��ջ
���ٶȿ�ܶࡣ
�ؼ��֡�static����������ľ��ǡ���̬�ġ��������ڲ������ֳƾ�̬���������˴���static���ĺ���
����ָ�洢��ʽ������ָ�Ժ�����������������ڱ��ļ��� ʹ���ڲ������ĺô��ǣ���ͬ���˱�д��
ͬ�ĺ���ʱ�����õ����Լ�����ĺ������Ƿ���������ļ��еĺ���ͬ������Ϊͬ��Ҳû�й�ϵ��*/




  char buf[BUF_SIZE], doc[BUF_SIZE];
  cout<<"%c.............\n"<<buf<<"******"<<endl; 
  /* read header */
  std::ifstream file(name, std::ios::in | std::ios::binary);
  /*��in����binary��ʽ ��ȡ�ļ�name  ������name����a.pnm*/
  
  
  cout<<"%c.............\n"<<buf<<endl; 
  pnm_read(file, buf);
  
  cout<<"%c.............\n"<<buf<<endl; 
  cout<<"%c size_of buff\n"<<sizeof(buf)<<endl; 
  
  
  
  /*�������if��ë��,���ƻ��ǲ���������,����ͼƬ������
  ��ʵbuf��pnm��ɫͼƬ�ĸ�ʽ,��P3��P6,��Ϊc�����������0������,���������б�ʾ�����ʽ����P6�ͱ���*/
  if (strncmp(buf, "P6", 2))
    throw pnm_error();

  pnm_read(file, buf);
  int width = atoi(buf);
  pnm_read(file, buf);
  int height = atoi(buf);

  pnm_read(file, buf);
  if (atoi(buf) > UCHAR_MAX)
    throw pnm_error();

  /* read data */
  image<rgb> *im = new image<rgb>(width, height);
  file.read((char *)imPtr(im, 0, 0), width * height * sizeof(rgb));

  return im;
}

static void savePPM(image<rgb> *im, const char *name) {
  int width = im->width();
  int height = im->height();
  std::ofstream file(name, std::ios::out | std::ios::binary);

  file << "P6\n" << width << " " << height << "\n" << UCHAR_MAX << "\n";
  file.write((char *)imPtr(im, 0, 0), width * height * sizeof(rgb));
}

template <class T>
void load_image(image<T> **im, const char *name) {
  char buf[BUF_SIZE];
  
  /* read header */
  std::ifstream file(name, std::ios::in | std::ios::binary);
  pnm_read(file, buf);
  if (strncmp(buf, "VLIB", 9))
    throw pnm_error();

  pnm_read(file, buf);
  int width = atoi(buf);
  pnm_read(file, buf);
  int height = atoi(buf);

  /* read data */
  *im = new image<T>(width, height);
  file.read((char *)imPtr((*im), 0, 0), width * height * sizeof(T));
}

template <class T>
void save_image(image<T> *im, const char *name) {
  int width = im->width();
  int height = im->height();
  std::ofstream file(name, std::ios::out | std::ios::binary);

  file << "VLIB\n" << width << " " << height << "\n";
  file.write((char *)imPtr(im, 0, 0), width * height * sizeof(T));
}

#endif
