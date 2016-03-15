#include <iostream>
#include <windows.h>								
#include <stdio.h>																	
#include <GL/glaux.h>	
#include <GL/glut.h>
#include <malloc.h>
using namespace std;

//bmp�ļ��Ŀ�Ⱥ͸߶�ֵ
#define MAP_HEIGHT_SIZE 190
#define MAP_WIDTH_SIZE  282
//�Զ�����������
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;


class LoadBmp
{
private:	
	GLint readBmp(const char* szFileName);         //����ԭʼBMPͼ��
	GLint getDIBColor(int X, int Y, BYTE *r, BYTE *g, BYTE *b);  //�õ�ԭʼBMPͼ��ÿ�����ص�RGBֵ
	BYTE  trueHeight[MAP_WIDTH_SIZE*MAP_HEIGHT_SIZE];             //�洢�߶�ֵ������
	
	BITMAPINFOHEADER bih;       //λͼ��Ϣͷ
	BYTE *Buffer ;              //������ָ��
	long LineByteWidth;         //ͼƬһ��������ռ�Ĵ�С
public:
	LoadBmp();                        //���캯��
	GLvoid loadBmp(char* szfilename); //�����������ֵ��������
	BYTE*  getTrueHeight();           //����һ���߶�����
		
};
LoadBmp::LoadBmp()
{
	Buffer=NULL;
}

//��ȡBMP�ļ�
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

fread(&bih, sizeof(BITMAPINFOHEADER), 1, file);     //����λͼ����Ϣͷ�ṹ

if (bih.biBitCount < 24)
{
   fclose(file);
   return 0;
}

dpixeladd = bih.biBitCount / 8;                   //��һ��������ռ�õĴ�Сת��Ϊ�ֽ�
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

GLint LoadBmp::getDIBColor(int X, int Y, BYTE *r, BYTE *g, BYTE *b)       //�����ֱ�Ϊ��ͼƬ��ĳ���ص�λ��(x,y)�Լ���ȡ��RGBֵ
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

GLvoid LoadBmp::loadBmp(char* szfilename){              //����Ϊ�ļ���
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
				trueHeight[count++] = r * 0.3 + g * 0.59 + b * 0.11;     //ֱ������Ҷ�ֵ��Ϊ��λ�õĸ߶�ֵ
		   }
   else
    printf("input error.\n");
	   }

free(Buffer);
}

BYTE* LoadBmp::getTrueHeight()             //����һ��ָ�������ָ��
{
	BYTE* temp=NULL;
	temp=trueHeight;
	return temp;

}
