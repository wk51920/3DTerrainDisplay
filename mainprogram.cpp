#include "control.h"
//由于无法直接将这些值传给各个Func函数，因此在此间接调用
void myDraw(void);
void myReshape(int width, int height);
void myProcessNormalKeyboard(unsigned char key,int x,int y);
void myProcessSpecialKeyboard(int key, int x, int y);
void myMouseCB(int button, int state, int x, int y);
void myMouseMotionCB(int x, int y);

Control control;
int main(int argc,char *argv[])
{
	
	glutInit(&argc,argv);                         //初始化GLUT 
	glutInitDisplayMode(GLUT_RGB |  GLUT_SINGLE); //初始化显示模式为：RGB,单通道
	glutInitWindowPosition(0,0);                  //初始化窗口位置
	glutInitWindowSize(300,300);                  //初始化窗口大小
	glutCreateWindow("3D_Terrain_Display");       //窗口标题
	 
	glutDisplayFunc(&myDraw);                     //调用绘制函数
	glutReshapeFunc(&myReshape);                  //调用调整函数

	glutKeyboardFunc(&myProcessNormalKeyboard);   //调用普通按键事件
	glutSpecialFunc(&myProcessSpecialKeyboard);   //调用特殊按键事件

	glutMouseFunc(myMouseCB);                     //调用鼠标按键事件
    glutMotionFunc(myMouseMotionCB);              //调用鼠标移动事件
	glutMainLoop();  
	return 0;

}

void myDraw(void)
{
	control.display.draw();
}

void myReshape(int width, int height)
{
	control.display.reshape(width,height);
}

void myProcessNormalKeyboard(unsigned char key,int x,int y)
{
	control.processNormalKeyboard(key,x,y);
}

void myProcessSpecialKeyboard(int key, int x, int y)
{
	control.processSpecialKeyboard(key,x,y);
}

void myMouseCB(int button, int state, int x, int y)
{
	control.mouseCB(button,state,x,y);
}
void myMouseMotionCB(int x, int y)
{
	control.mouseMotionCB(x,y);
}
