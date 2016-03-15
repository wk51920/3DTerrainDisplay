#include "control.h"
//�����޷�ֱ�ӽ���Щֵ��������Func����������ڴ˼�ӵ���
void myDraw(void);
void myReshape(int width, int height);
void myProcessNormalKeyboard(unsigned char key,int x,int y);
void myProcessSpecialKeyboard(int key, int x, int y);
void myMouseCB(int button, int state, int x, int y);
void myMouseMotionCB(int x, int y);

Control control;
int main(int argc,char *argv[])
{
	
	glutInit(&argc,argv);                         //��ʼ��GLUT 
	glutInitDisplayMode(GLUT_RGB |  GLUT_SINGLE); //��ʼ����ʾģʽΪ��RGB,��ͨ��
	glutInitWindowPosition(0,0);                  //��ʼ������λ��
	glutInitWindowSize(300,300);                  //��ʼ�����ڴ�С
	glutCreateWindow("3D_Terrain_Display");       //���ڱ���
	 
	glutDisplayFunc(&myDraw);                     //���û��ƺ���
	glutReshapeFunc(&myReshape);                  //���õ�������

	glutKeyboardFunc(&myProcessNormalKeyboard);   //������ͨ�����¼�
	glutSpecialFunc(&myProcessSpecialKeyboard);   //�������ⰴ���¼�

	glutMouseFunc(myMouseCB);                     //������갴���¼�
    glutMotionFunc(myMouseMotionCB);              //��������ƶ��¼�
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
