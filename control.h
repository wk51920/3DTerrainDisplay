#include "display.h"

bool mouseLeftDown;          //�������Ƿ���
bool mouseRightDown;         //����Ҽ��Ƿ���
float mouseX, mouseY;        //��굱ǰ����ֵ



class Control
{
private:
public:
	Display display;                                            //ʵ����һ��display����
	GLvoid processNormalKeyboard(unsigned char key,int x,int y);//��ͨ�����¼�
	GLvoid processSpecialKeyboard(int key, int x, int y);       //���ⰴ���¼�
	void mouseCB(int button, int state, int x, int y);          //��갴���¼�
	void mouseMotionCB(int x, int y);                           //����ƶ��¼�

};

GLvoid Control::processNormalKeyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
	case 'e':
		display.setScaleValue(display.getScaleValue()+0.1f);           
		glutPostRedisplay();
		break;
	case 'd':
		display.setScaleValue(display.getScaleValue()-0.1f);
		glutPostRedisplay();
		break;
	}

}

GLvoid Control::processSpecialKeyboard(int key, int x, int y) 
{
	switch(key)
	{
	case GLUT_KEY_F1:
		display.getRendMode()<2?display.setRendMode(display.getRendMode()+1):display.setRendMode(0);
        glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		yRotate-=1.0f;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		yRotate+=1.0f;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		zRotate-=1.0f;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		zRotate+=1.0f;
		glutPostRedisplay();
		break;
	}
}

//����¼�
void Control::mouseCB(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if(state == GLUT_UP)
            mouseRightDown = false;
    }
}

void Control::mouseMotionCB(int x, int y)
{
    if(mouseLeftDown)
    {
        xMove += (x - mouseX)*0.01f;
        yMove -= (y - mouseY)*0.01f;
        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {
        display.setScaleValue( display.getScaleValue()+(y - mouseY)* 0.01f);
        mouseY = y;
    }

    glutPostRedisplay();
}