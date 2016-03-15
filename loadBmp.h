#include <iostream>
#include <windows.h>								
#include <stdio.h>																	
#include <GL/glaux.h>	
#include <GL/glut.h>
#include <malloc.h>
using namespace std;

//bmp文件的宽度和高度值
#define MAP_HEIGHT_SIZE 190
#define MAP_WIDTH_SIZE  282
//自定义数据类型
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;


class LoadBmp
{
private:	
	GLint readBmp(const char* szFileName);         //读入原始BMP图像
	GLint getDIBColor(int X, int Y, BYTE *r, BYTE *g, BYTE *b);  //得到原始BMP图像每个像素的RGB值
	BYTE  trueHeight[MAP_WIDTH_SIZE*MAP_HEIGHT_SIZE];             //存储高度值的数组
	
	BITMAPINFOHEADER bih;       //位图信息头
	BYTE *Buffer ;              //缓冲区指针
	long LineByteWidth;         //图片一行像素所占的大小
public:
	LoadBmp();                        //构造函数
	GLvoid loadBmp(char* szfilename); //将读入的像素值存入数组
	BYTE*  getTrueHeight();           //返回一个高度数组
		
};
LoadBmp::LoadBmp()
{
	Buffer=NULL;
}

//读取BMP文件
GLint LoadBmp::readBmp(const char* szFileName)
{
FILE *file;
WORD bfh[7];
long dpixeladd;

if (NULL == (file = fopen(szFileName, "rb")))
{
   return 0;
}


fread(&bfh, sizeof(WORD), 7, file);         
if (bfh[0] != (WORD)(((WORD)'B')|('M'<<8)))
{
   fclose(file);
   return 0;
}

fread(&bih, sizeof(BITMAPINFOHEADER), 1, file);     //读入位图的信息头结构

if (bih.biBitCount < 24)
{
   fclose(file);
   return 0;
}

dpixeladd = bih.biBitCount / 8;                   //将一个像素所占用的大小转化为字节
LineByteWidth = bih.biWidth * (dpixeladd);
if ((LineByteWidth % 4) != 0)
LineByteWidth += 4 - (LineByteWidth % 4);

if ((Buffer = (BYTE*)malloc(sizeof(BYTE)* LineByteWidth * bih.biHeight)) != NULL)
{
   fread(Buffer, LineByteWidth * bih.biHeight, 1, file);

   fclose(file);
   return 1;
}

fclose(file);
return 0;
}

GLint LoadBmp::getDIBColor(int X, int Y, BYTE *r, BYTE *g, BYTE *b)       //参数分别为：图片中某像素的位置(x,y)以及读取的RGB值
{
int dpixeladd;
BYTE *ptr;
if (X < 0 || X >= bih.biWidth || Y < 0 || Y >= bih.biHeight)
{
   return 0;
}

dpixeladd = bih.biBitCount / 8;
ptr = Buffer + X * dpixeladd + (bih.biHeight - 1 - Y) * LineByteWidth;

*b = *ptr;
*g = *(ptr + 1);
*r = *(ptr + 2);

return 1;
}

GLvoid LoadBmp::loadBmp(char* szfilename){              //参数为文件名
	int x, y;
	BYTE r, g, b;
	int count=0;

	if (readBmp(szfilename) == 0)
	{
	printf("failure to read file %s", szfilename);
	return ;
	}

	int i,j;
   for(i=0;i<bih.biHeight;i++)
	   for(j=0;j<bih.biWidth;j++){

		   if (getDIBColor(j, i, &r, &g, &b) == 1){
				trueHeight[count++] = r * 0.3 + g * 0.59 + b * 0.11;     //直接算出灰度值作为该位置的高度值
		   }
   else
    printf("input error.\n");
	   }

free(Buffer);
}

BYTE* LoadBmp::getTrueHeight()             //返回一个指向数组的指针
{
	BYTE* temp=NULL;
	temp=trueHeight;
	return temp;

}
