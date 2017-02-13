/*
 * LAB06_RTOS.c
 *
 * Created: 09/02/2017 08:12:04
 * Author : KasperSK
 */ 

#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "switch.h"
#include "uart.h"
#include "semphr.h"
#include "queue.h"

xSemaphoreHandle xSemaphoreButton = NULL;
xSemaphoreHandle xSemaphoreCount = NULL;
unsigned char count = 0;
xQueueHandle xQueue1 = NULL;
	
void vLEDFlashTask1( void *pvParameters )
{
	portTickType xLastWakeTime;
	xLastWakeTime=xTaskGetTickCount();
	while(1)
	{
		toggleLED(0);
		vTaskDelayUntil(&xLastWakeTime,5000);
	}
}

void vLEDFlashTask2( void *pvParameters )
{
	portTickType xLastWakeTime;
	xLastWakeTime=xTaskGetTickCount();
	while(1)
	{
		toggleLED(1);
		vTaskDelayUntil(&xLastWakeTime,1500);
	}
}

void vLEDFlashTask7( void *pvParameters )
{
	portTickType xLastWakeTime;
	xLastWakeTime=xTaskGetTickCount();
	static unsigned char blinks = 8;
	while(1)
	{
		if(blinks != 8)
		{
			toggleLED(7);
			++blinks;
			vTaskDelayUntil(&xLastWakeTime,500);
		}

		if(xSemaphoreTake(xSemaphoreButton, ( portTickType ) 10) == pdTRUE)
		{
			blinks = 0;
		}
		vTaskDelayUntil(&xLastWakeTime,1000);
	}
}

void vSwitchTask(void *pvParameters)
{
	portTickType xLastWakeTime;
	xLastWakeTime=xTaskGetTickCount();
	
	while(1) {
		if(switchOn(0))
			xSemaphoreGive(xSemaphoreButton);
		
		vTaskDelayUntil(&xLastWakeTime,50);			
	}
}

void vIncrementCount(void *pvParameters)
{
	while(1)
	{
		if(switchOn(0))
		{
			if(xSemaphoreTake(xSemaphoreCount, portMAX_DELAY) == pdTRUE)
			{
				++count;
				xQueueSend(xQueue1, &count, ( portTickType ) 0);
				xSemaphoreGive(xSemaphoreCount);
			}
		}
		vTaskDelay(100);	
	}
}

void vDecrementCount(void *pvParameters)
{
	while(1)
	{
		if(switchOn(1))
		{
			if(xSemaphoreTake(xSemaphoreCount, portMAX_DELAY) == pdTRUE)
			{
				--count;
				xQueueSend(xQueue1, &count, ( portTickType ) 0);
				xSemaphoreGive(xSemaphoreCount);
			}
		}
		vTaskDelay(100);
	}
}

void vIShowStuff(void *pvParameters)
{
	unsigned char inQ;
	while(1)
	{
		if(xQueueReceive(xQueue1, &(inQ), portMAX_DELAY) == pdTRUE)
		{
			writeAllLEDs(inQ);
			SendInteger(inQ);
			SendChar('\r');
			SendChar('\n');
		}
		vTaskDelay(100);
	}
}

int main(void)
{
	initLEDport();
	initSwitchPort();
	InitUART(115200,8);
	
	vSemaphoreCreateBinary(xSemaphoreButton);
	xSemaphoreTake(xSemaphoreButton, 10);
	vSemaphoreCreateBinary(xSemaphoreCount);
	xQueue1 = xQueueCreate(10, sizeof(unsigned char));


	xTaskCreate(vLEDFlashTask1, (signed char * ) "LED1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(vLEDFlashTask2, (signed char * ) "LED2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(vSwitchTask, (signed char * ) "SW1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(vLEDFlashTask7, (signed char * ) "LED7", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	
	xTaskCreate(vIncrementCount, (signed char * ) "Inc", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(vDecrementCount, (signed char * ) "Dec", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(vIShowStuff, (signed char * ) "Handle", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	vTaskStartScheduler();
    while (1) 
    {}
}

