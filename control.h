#include "display.h"

bool mouseLeftDown;          //鼠标左键是否按下
bool mouseRightDown;         //鼠标右键是否按下
float mouseX, mouseY;        //鼠标当前坐标值



class Control
{
private:
public:
	Display display;                                            //实例化一个display对象
	GLvoid processNormalKeyboard(unsigned char key,int x,int y);//普通按键事件
	GLvoid processSpecialKeyboard(int key, int x, int y);       //特殊按键事件
	void mouseCB(int button, int state, int x, int y);          //鼠标按键事件
	void mouseMotionCB(int x, int y);                           //鼠标移动事件

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

//鼠标事件
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