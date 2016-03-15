#include <stdio.h>
#include <iostream>
using namespace std;

class Test
{
private:
	int i;
public :
	Test();
	int getNum();
	void setNum(int num);
	
};

int main()
{
	Test test;
	test.setNum(2);
	cout << test.getNum()<<endl;
	return 0;
}

Test::Test()
{
	i=0;
}
int Test::getNum()
{
   return i;
}
void Test::setNum(int num)
{
	i = num;
}