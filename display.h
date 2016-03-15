#include "loadBmp.h"


#define STEP_SIZE 1            //绘制点的间隔数
#define HEIGHT_RATIO 0.8f      //地形高度缩放比

GLfloat xRotate=0.0f;          //绕X轴旋转值
GLfloat yRotate=0.0f;          //绕Y轴旋转值
GLfloat zRotate=0.0f;          //绕Z轴旋转值

GLfloat xMove=0.0f;            //X方向移动值
GLfloat yMove=0.0f;            //Y方向移动值

class Display
{
private:
	LoadBmp load;
    BYTE   renderHeight[MAP_WIDTH_SIZE*MAP_HEIGHT_SIZE];    //用于绘图的高度数组（从load.getTrueHeight()得来）
    GLint  rendMode;                                        //渲染模式
    GLfloat scaleValue;                                     //整体缩放值
	GLint  height(BYTE *pHeightMap,int X,int Y);            //返回(x,y)像素点的高度值
	GLvoid setVertexColor(BYTE*pHeightMap,int x,int y);     //设置(x,y)像素点的颜色
	GLvoid renderHeightMap(BYTE pHeightMap[]);              //根据高度数组，绘制图像
	int time,timebase,frame;                                //time:当前的毫秒数   timebase:从开始统计到现在的时间  frame:从开始统计到当前的帧数
public :
	Display();                                              //构造函数
    GLvoid draw(void);                                      //绘制地形
    GLvoid reshape(int width, int height);                  //用于窗口变化时，重新绘制地形
	GLvoid setRendMode(GLint num);                          //设置渲染模式
	GLint  getRendMode();                                   //得到渲染模式
	GLvoid setScaleValue(GLfloat num);                      //设置模型缩放值
	GLfloat  getScaleValue();                               //得到模型缩放值
};
Display::Display()                                          //初始化
{
	rendMode = 0;
	scaleValue = 1.2f;
	BYTE* temp=NULL;
	time=0;
	timebase=0;
	frame=0;

	load.loadBmp("Data/terrain.bmp");                       //载入图像并将计算得到的高度值存入数组
	int i;
	temp=load.getTrueHeight();                              //load对象中的高度数组复制过来
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


GLvoid Display::reshape(int width, int height)		    // 重新调整窗口大小及内容
{
	if (height==0)										// 防止窗口高度为0
		height=1;										

	glViewport(0,0,width,height);						// 重置当前视口

	glMatrixMode(GL_PROJECTION);						// 选择设置投影矩阵
	glLoadIdentity();									// 重置投影矩阵

	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 500.0f); //设置透视投影
	//第一个参数定义视野点在X-Z平面上的角度，0~180
	//第二个参数定义投影平面的宽高比
	//第三个参数定义远近裁剪面沿Z负轴到视点的距离，它们总为正值

	glMatrixMode(GL_MODELVIEW);							// 设置模型矩阵
	glLoadIdentity();									// 重置模型矩阵
}

GLvoid Display::setVertexColor(BYTE* pHeightMap,int x,int y){   //设置顶点颜色
	if(!pHeightMap) return;								
    float rColor = (height(pHeightMap, x, y ) / 256.0f);
	glColor3f(rColor, 0, 1.0f-rColor);

}

GLvoid Display::renderHeightMap(BYTE pHeightMap[])		//绘制顶点			
{
	int X = 0, Y = 0;								
	int x, y, z;

	if(!pHeightMap) return;	
	switch(rendMode)                                    //选择渲染模式
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
			time=glutGet(GLUT_ELAPSED_TIME);       //返回两次调用glutGet(GLUT_ELAPSED_TIME)的时间间隔,单位为毫秒
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
 
GLvoid Display::draw(void){                                          //初始化渲染准备，并调用渲染函数

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	             //清空颜色缓冲区和深度缓冲区
	glMatrixMode(GL_PROJECTION);                                     //设置投影矩阵
	glShadeModel(GL_SMOOTH);                                         //设为平滑模式
	glLoadIdentity();                                                //重置投影矩阵
	glTranslatef(xMove-0.15f, yMove+0.5f, 0.0f);                     //将当前矩阵在x,y平面上平移
	glOrtho(-282*2,282*2,-190*2,190*2,-500,500);                     //设置可视区域，各参数分别为：
	//left表示视景体左面的坐标，right表示右面的坐标，bottom表示下面的，top表示上面的,以及远近。
	
	//调整矩阵角度
	glRotatef(-90, 0.0f, 0.0f, 1.0f);                                
	glRotatef(xRotate, 1.0f, 0.0f, 0.0f);
	glRotatef(yRotate,0.0f,1.0f,0.0f);
	glRotatef(zRotate, 0.0f, 0.0f, 1.0f);	

	glScalef(scaleValue, scaleValue, scaleValue * HEIGHT_RATIO);
	
	renderHeightMap(renderHeight);
}		