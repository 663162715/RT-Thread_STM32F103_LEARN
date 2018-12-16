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


#define THREAD_PRIORITY         25
#define THREAD_STACK_SIZE       512
#define THREAD_TIMESLICE        5

/* ָ���߳̿��ƿ��ָ�� */
static rt_thread_t tid1 = RT_NULL;

/* �߳���� */
static void print_th_entry(void* parameter)
{
    rt_uint32_t count = 0;
    rt_uint32_t no = (rt_uint32_t) parameter; /* ����̵߳���ڲ��� */

    while (1)
    {
        /* ��ӡ�̼߳���ֵ��� */
        rt_kprintf("thread%d count: %d\n", no, count ++);

        /* ����10��OS Tick */
        rt_thread_delay(100);
    }
}

/* �û�Ӧ����� */
int mine_rt_application_init()
{
    /* �����߳�1 */
    tid1 = rt_thread_create("print task",
        print_th_entry, (void*)1, /* �߳������thread_entry, ��ڲ�����1 */
        THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);
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
