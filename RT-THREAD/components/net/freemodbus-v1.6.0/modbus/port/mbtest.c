/***************************2012-2013, NJUT, Edu.****************************** 
  FileName: mbtest.c 
  Author:  孙冬梅       Version :  1.0        Date: 2012.12.9
  Description:    freemodbus测试  
  Version:         1.0 
  Function List:    
    1. 
    2.
  History:         
      <author>  <time>   <version >   <desc> 
      Sundm    13/08/08     1.0     文件格式修订   
******************************************************************************/ 
#include <rtthread.h>
#include "stm32f10x.h"
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- Defines ------------------------------------------*/
#define REG_INPUT_START 1000
#define REG_INPUT_NREGS 4

/* ----------------------- Static variables ---------------------------------*/
static USHORT   usRegInputStart = REG_INPUT_START;
static USHORT   usRegInputBuf[REG_INPUT_NREGS];

void rt_init_freemodbus_entry(void* parameter)
{
    eMBErrorCode    eStatus;

    eStatus = eMBInit( MB_RTU, 0x01, 2, 19200, MB_PAR_EVEN );

    /* Enable the Modbus Protocol Stack. */
    eStatus = eMBEnable(  );

    for( ;; )
    {
        ( void )eMBPoll(  );

        /* Here we simply count the number of poll cycles. */
        usRegInputBuf[0]++;
    }  
}
void freemodbus()
{
     rt_thread_t init_thread;

    init_thread = rt_thread_create("freemodbus",
                                   rt_init_freemodbus_entry, RT_NULL,
                                   2048, 9, 20);

    if (init_thread != RT_NULL)
        rt_thread_startup(init_thread);
}

#ifdef  RT_USING_FINSH 
#include  <finsh.h> 
/*  输出testmodbus函数到finsh  shell中 */ 
FINSH_FUNCTION_EXPORT (freemodbus, freemodbus RTU模式 从机地址为1 Uart2 9600 偶校验 测试e.g.:freemodbus()); 

#endif 
  
