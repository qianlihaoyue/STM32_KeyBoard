#include "HW_key.h"

//储存多个按键


KEY_STRUCT KEY_S={
	0,
	{0x00,0x00}
};

void KEY_SETBIT(char CH,char mode)
{
	switch (CH)
	{
		case 0:	HAL_GPIO_WritePin(KEY_C0_PORT,KEY_C0_PIN,mode); break;
		case 1:	HAL_GPIO_WritePin(KEY_C1_PORT,KEY_C1_PIN,mode); break;	
		case 2:	HAL_GPIO_WritePin(KEY_C2_PORT,KEY_C2_PIN,mode); break;
		default:break;
	}
}

char KEY_READBIT(char CH)
{
	switch (CH)
	{
		case 0:	return HAL_GPIO_ReadPin(KEY_R0_PORT,KEY_R0_PIN); break;
		case 1:	return HAL_GPIO_ReadPin(KEY_R1_PORT,KEY_R1_PIN); break;
		case 2:	return HAL_GPIO_ReadPin(KEY_R2_PORT,KEY_R2_PIN); break;
		case 3:	return HAL_GPIO_ReadPin(KEY_R3_PORT,KEY_R3_PIN); break;
		default:break;
	}	
}
//以4*4为例
//v1.0 扫描式
//读取IO 16次
//设置IO 16次



char KEY_SCAN(void)
{   
	int i,j;
	uint8_t Key[2]={0x00,0x00};   
	for(i=0;i<KEY_C_NUM;i++)
	{
		for(j=0;j<KEY_C_NUM;j++)
		{
			if(j==i) KEY_SETBIT(j,1);
			else KEY_SETBIT(j,0);
		}
		for(j=0;j<KEY_R_NUM;j++)
		{
			if(KEY_READBIT(j))
			{
				return j*KEY_C_NUM+i+1;
			}
		}
	}
	return 0;
}


