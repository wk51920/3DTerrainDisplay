#include "loadBmp.h"


#define STEP_SIZE 1            //���Ƶ�ļ����
#define HEIGHT_RATIO 0.8f      //���θ߶����ű�

GLfloat xRotate=0.0f;          //��X����תֵ
GLfloat yRotate=0.0f;          //��Y����תֵ
GLfloat zRotate=0.0f;          //��Z����תֵ

GLfloat xMove=0.0f;            //X�����ƶ�ֵ
GLfloat yMove=0.0f;            //Y�����ƶ�ֵ

class Display
{
private:
	LoadBmp load;
    BYTE   renderHeight[MAP_WIDTH_SIZE*MAP_HEIGHT_SIZE];    //���ڻ�ͼ�ĸ߶����飨��load.getTrueHeight()������
    GLint  rendMode;                                        //��Ⱦģʽ
    GLfloat scaleValue;                                     //��������ֵ
	GLint  height(BYTE *pHeightMap,int X,int Y);            //����(x,y)���ص�ĸ߶�ֵ
	GLvoid setVertexColor(BYTE*pHeightMap,int x,int y);     //����(x,y)���ص����ɫ
	GLvoid renderHeightMap(BYTE pHeightMap[]);              //���ݸ߶����飬����ͼ��
	int time,timebase,frame;                                //time:��ǰ�ĺ�����   timebase:�ӿ�ʼͳ�Ƶ����ڵ�ʱ��  frame:�ӿ�ʼͳ�Ƶ���ǰ��֡��
public :
	Display();                                              //���캯��
    GLvoid draw(void);                                      //���Ƶ���
    GLvoid reshape(int width, int height);                  //���ڴ��ڱ仯ʱ�����»��Ƶ���
	GLvoid setRendMode(GLint num);                          //������Ⱦģʽ
	GLint  getRendMode();                                   //�õ���Ⱦģʽ
	GLvoid setScaleValue(GLfloat num);                      //����ģ������ֵ
	GLfloat  getScaleValue();                               //�õ�ģ������ֵ
};
Display::Display()                                          //��ʼ��
{
	rendMode = 0;
	scaleValue = 1.2f;
	BYTE* temp=NULL;
	time=0;
	timebase=0;
	frame=0;

	load.loadBmp("Data/terrain.bmp");                       //����ͼ�񲢽�����õ��ĸ߶�ֵ��������
	int i;
	temp=load.getTrueHeight();                              //load�����еĸ߶����鸴�ƹ���
	for(i=0;i<MAP_WIDTH_SIZE*MAP_HEIGHT_SIZE;i++)           
	{
		renderHeight[i]=*temp;                             
		temp++;
	}
}

GLvoid Display::setRendMode(GLint num)
{
	rendMode = num;
}

GLint Display::getRendMode()
{
	return rendMode;
}
GLvoid Display::setScaleValue(GLfloat num)
{
	scaleValue = num;
}
GLfloat Display::getScaleValue()
{
	return scaleValue;
}
GLint Display::height(BYTE *pHeightMap,int X,int Y){ 
	int x = X % MAP_WIDTH_SIZE;
	int y = Y % MAP_HEIGHT_SIZE;

	if(!pHeightMap) return 0;
	return pHeightMap[x+(y*MAP_WIDTH_SIZE)];
}


GLvoid Display::reshape(int width, int height)		    // ���µ������ڴ�С������
{
	if (height==0)										// ��ֹ���ڸ߶�Ϊ0
		height=1;										

	glViewport(0,0,width,height);						// ���õ�ǰ�ӿ�

	glMatrixMode(GL_PROJECTION);						// ѡ������ͶӰ����
	glLoadIdentity();									// ����ͶӰ����

	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 500.0f); //����͸��ͶӰ
	//��һ������������Ұ����X-Zƽ���ϵĽǶȣ�0~180
	//�ڶ�����������ͶӰƽ��Ŀ�߱�
	//��������������Զ���ü�����Z���ᵽ�ӵ�ľ��룬������Ϊ��ֵ

	glMatrixMode(GL_MODELVIEW);							// ����ģ�;���
	glLoadIdentity();									// ����ģ�;���
}

GLvoid Display::setVertexColor(BYTE* pHeightMap,int x,int y){   //���ö�����ɫ
	if(!pHeightMap) return;								
    float rColor = (height(pHeightMap, x, y ) / 256.0f);
	glColor3f(rColor, 0, 1.0f-rColor);

}

GLvoid Display::renderHeightMap(BYTE pHeightMap[])		//���ƶ���			
{
	int X = 0, Y = 0;								
	int x, y, z;

	if(!pHeightMap) return;	
	switch(rendMode)                                    //ѡ����Ⱦģʽ
	{
	case 0:
		glBegin(GL_QUADS);
		break;
	case 1:
		glBegin(GL_POINTS);
		break;
	case 2:
		glBegin(GL_LINES);
		break;
	}			
	
	for ( X = 0; X < (MAP_WIDTH_SIZE-STEP_SIZE); X += STEP_SIZE )
		for ( Y = 0; Y < (MAP_HEIGHT_SIZE-STEP_SIZE); Y += STEP_SIZE )
		{
	
            x = X;							
			y = Y;
			z = height(pHeightMap, X, Y );							
			setVertexColor(pHeightMap, x, y);
            glVertex3f(x, y, z/5);
			x = X;										
			y = Y + STEP_SIZE;  
			z =   height(pHeightMap, X, Y + STEP_SIZE );							
			setVertexColor(pHeightMap, x, y);


			glVertex3f(x, y, z/5);


   			x = X + STEP_SIZE; 
			y = Y + STEP_SIZE; 
			z = height(pHeightMap, X + STEP_SIZE, Y + STEP_SIZE );

			setVertexColor(pHeightMap, x, y);
			   


			glVertex3f(x, y, z/5);
			x = X + STEP_SIZE; 

			y = Y; 
			z = height(pHeightMap, X + STEP_SIZE, Y );

			setVertexColor(pHeightMap, x, y);


			glVertex3f(x, y, z/5);

			frame++;
			time=glutGet(GLUT_ELAPSED_TIME);       //�������ε���glutGet(GLUT_ELAPSED_TIME)��ʱ����,��λΪ����
			if(time-timebase >1000)
			{
				printf("FPS:%4.2f\n",frame/(time-timebase)/10.0);
				timebase=time;
				frame=0;
			}
		
		}
	glEnd();
	glFlush();
}
 
GLvoid Display::draw(void){                                          //��ʼ����Ⱦ׼������������Ⱦ����

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	             //�����ɫ����������Ȼ�����
	glMatrixMode(GL_PROJECTION);                                     //����ͶӰ����
	glShadeModel(GL_SMOOTH);                                         //��Ϊƽ��ģʽ
	glLoadIdentity();                                                //����ͶӰ����
	glTranslatef(xMove-0.15f, yMove+0.5f, 0.0f);                     //����ǰ������x,yƽ����ƽ��
	glOrtho(-282*2,282*2,-190*2,190*2,-500,500);                     //���ÿ������򣬸������ֱ�Ϊ��
	//left��ʾ�Ӿ�����������꣬right��ʾ��������꣬bottom��ʾ����ģ�top��ʾ�����,�Լ�Զ����
	
	//��������Ƕ�
	glRotatef(-90, 0.0f, 0.0f, 1.0f);                                
	glRotatef(xRotate, 1.0f, 0.0f, 0.0f);
	glRotatef(yRotate,0.0f,1.0f,0.0f);
	glRotatef(zRotate, 0.0f, 0.0f, 1.0f);	

	glScalef(scaleValue, scaleValue, scaleValue * HEIGHT_RATIO);
	
	renderHeightMap(renderHeight);
}		