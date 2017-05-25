#include <reg52.h>
#include "motor.h"

int flag = 0;

char Rec[];
//串口初始化程序
void UART_Init(void)
{
	SCON  = 0x40;//串口方式一
	PCON  = 0;//SOMD = 0
	REN  = 1;//允许接收
	TMOD = 0x20;//定时器1方式2
	TH1 = 0xfd;					//波特率9600，数据位8，停止位1
  TL1 = 0xfd;
	TR1  = 1;//开启定时器1
	ES  = 1;//打开UART中断
	EA  = 1;//打开总中断
}

void main(void)
{
	UART_Init();
	P0 = 0;//屏蔽干扰
	while(1)
	{
		if(RI)
		{
			switch(Rec[])
		{
			case "00"://前进
				Left_moto_go;
				Right_moto_go;
			break;
			case "01"://后退
				Left_moto_back;
				Right_moto_back;
			break;
			case ""://右转
				Left_moto_go;
				Right_moto_back;
			break;
			case ""://左转
				Left_moto_back;
				Right_moto_go;
			break;
			default:
				break;
			
		}
		}
		
	}
}

//串口服务中断子程序�
void Uart_Timer1(void) interrupt 4
{
	if(RI == 1)
	{
		RI = 0;
		if(flag < 2)
		{
			Rec[flag] = SBUF;
			flag++;
		}
		else
		{
			flag = 0;
		}
	}
}