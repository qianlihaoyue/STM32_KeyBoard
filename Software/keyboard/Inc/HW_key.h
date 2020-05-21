#ifndef __HW_key_H__
#define __HW_key_H__

#include "main.h"

char KEY_SCAN(void);

#define KEY_C0_PORT GPIOA
#define KEY_C0_PIN  GPIO_PIN_1
#define KEY_C1_PORT GPIOA
#define KEY_C1_PIN  GPIO_PIN_2
#define KEY_C2_PORT GPIOA
#define KEY_C2_PIN  GPIO_PIN_3

#define KEY_R0_PORT GPIOA
#define KEY_R0_PIN  GPIO_PIN_4
#define KEY_R1_PORT GPIOA
#define KEY_R1_PIN  GPIO_PIN_5
#define KEY_R2_PORT GPIOA
#define KEY_R2_PIN  GPIO_PIN_6
#define KEY_R3_PORT GPIOA
#define KEY_R3_PIN  GPIO_PIN_7



#define KEY_C_NUM 3		//ÁÐ
#define KEY_R_NUM 4		//ÐÐ


typedef struct{
	char flag;
	uint8_t KEY[2];
}KEY_STRUCT;

extern KEY_STRUCT KEY_S;

#endif

