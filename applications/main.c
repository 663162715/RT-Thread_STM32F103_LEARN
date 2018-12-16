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
#include <led.h>

#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5

/* ָ���߳̿��ƿ��ָ�� */
static rt_thread_t tid1 = RT_NULL;

/* �߳���� */
static void led_th_entry(void* parameter)
{
   
	rt_pin_mode(LED0,PIN_MODE_OUTPUT);
    while (1)
    {
		rt_pin_write(LED0,PIN_LOW);
        rt_thread_delay(rt_tick_from_millisecond(500));
		rt_pin_write(LED0,PIN_HIGH);
       
        rt_thread_delay(rt_tick_from_millisecond(500));
    }
}



/* �û�Ӧ����� */
int mine_rt_application_init()
{
    /* �����߳�1 */
    tid1 =	rt_thread_create(
			"led task",//�߳�����
			led_th_entry, //��ں���
			(void*)1, //��ں�������
			THREAD_STACK_SIZE, //�߳�ջ��С����λ���ֽڣ���Ҫ�����ֽڵ�ַ���룩
			THREAD_PRIORITY,//���ȼ� 
			THREAD_TIMESLICE//�̵߳�ʱ��Ƭ��С
			);
    if (tid1 != RT_NULL)//�ɹ��󷵻��߳̾�������򷵻�RT_NULL
        rt_thread_startup(tid1);//��������ӵ������б���
    else
        return -1;
    return 0;
}

int main(void)
{
    /* user app entry */
	mine_rt_application_init();
    return 0;
}
