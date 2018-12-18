/*
 * File      : main.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-07-29     Arda.Fu      first implementation
 */
#include <rtthread.h>
#include <finsh.h>
#include <led.h>
#include <stm32f103xe.h>

#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5

/* 指向线程控制块的指针 */
static rt_thread_t tid1 = RT_NULL;

/* 线程入口 */
static void led_th_entry(void* parameter)
{
   
	rt_pin_mode(LED0,PIN_MODE_OUTPUT);
	GPIOA->ODR |= 1 << 8;
    while (1)
    {
		//user handler
        rt_thread_delay(rt_tick_from_millisecond(500));
    }
}



/* 用户应用入口 */
int mine_rt_application_init()
{
    /* 创建线程1 */
    tid1 =	rt_thread_create(
			"led task",//线程名称
			led_th_entry, //入口函数
			(void*)1, //入口函数参数
			THREAD_STACK_SIZE, //线程栈大小，单位：字节（需要向四字节地址对齐）
			THREAD_PRIORITY,//优先级 
			THREAD_TIMESLICE//线程的时间片大小
			);
    if (tid1 != RT_NULL)//成功后返回线程句柄；否则返回RT_NULL
        rt_thread_startup(tid1);//将任务添加到就绪列表中
    else
        return -1;
    return 0;
}

//控制台LED指令
int led_switch(void)
{
	if(rt_pin_read(LED0)==1)
	{
		rt_kprintf("led on!\n");
		rt_pin_write(LED0,PIN_LOW);
	}
	else
	{
		rt_kprintf("led off!\n");
		rt_pin_write(LED0,PIN_HIGH);
	}
    
    return 0;
}
MSH_CMD_EXPORT(led_switch, my command test);

int main(void)
{
    /* user app entry */
	mine_rt_application_init();
    return 0;
}


