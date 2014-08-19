#include "Arduino.h"
#include "CTS.h"
CTS::CTS() {}

int CTS::xcoord(int num)
{
	int Byte=0;
	int data=0;
	int center=120;
	Byte='p'+(num-1)*10;
	Serial3.write(Byte);
	delay(10);
	if(Serial3.available())
	{
		data=Serial3.read();
		if(data==0)	{ return 200;}
		return data-center;
	}
	return 200;
}

int CTS::size(int num)
{
	int Byte=0;
	int data=0;
	Byte='o'+(num-1)*10;
	Serial3.write(Byte);
	delay(10);
	if(Serial3.available())
	{
		data=Serial3.read();
		return data;
	}
	return 200;
}


int CTS::location()
{
	int x1=CTS::xcoord(1);
	int x2=CTS::xcoord(2);
	if(x1==200)
	{
		return x2;
	}
	else
	{
		if(x2==200)
			return x1;
		else return (x1+x2)/2;
	}
	/* using color1 : 1-3 , color2 : 4-6, color3 : 7-9
		//3k+1�� u, v�� ���� ����, 3k+2�� 3k+3�� ���� �а�
	int x[9];
	for(int i=0; i<9; i++)
		x[i]=CTS::xcoord(i+1);
	...?
	3k+1�� �������� ��� ������ ������ 3k+2,3�� �̿�
	*/

	//�ѹ� ��ġ�� ������ ����-�ʷ����� �ʷ�-���������� ����ϴ� bit�� �ѱ�?
	//ex. ����-�ʷ��϶� ������ ������ ������ �߽���ǥ + ������ ��/2 = ������ �ʷ��� �߰�
}