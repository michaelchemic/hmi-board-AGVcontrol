#include <rtthread.h>
#include "hal_data.h"
#include <rtdevice.h>

#define LED_PIN    BSP_IO_PORT_02_PIN_09 /* Onboard LED pins */

 extern rt_int8_t motor_mode;
 extern rt_int8_t function_code;

#define SAMPLE_UART_NAME       "uart4"    /* 串口设备名称 */
static rt_device_t serial; /* 串口设备句柄 */

void send_packet(rt_int8_t mode,rt_int8_t code){

    rt_int8_t packet[4];
    packet[0] = 0xAA; // 起始字节
    packet[1] = mode; // 电机模式 01 点动，02 连续，03 停止。
    packet[2] = code; // 功能吗 01 前进，02 后退，03 左转，04右转。
    packet[3] = 0x55; // 结束字节

    // 发送数据包

    //while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); // 等待发送缓冲区为空
    rt_device_write(serial, 0, packet, (sizeof(packet) - 0));
    //USART_SendData(USART1, packet[i]); // 发送数据



}

void hal_entry(void)
{
    rt_kprintf("\nHello RT-Thread!\n");

    /* 查找串口设备 */
    serial = rt_device_find(SAMPLE_UART_NAME); //按照名字查找uart4 设备
    //打开uart4
    rt_device_open(serial, RT_DEVICE_FLAG_RX_NON_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING);
    // 串口设备使用模式为 (发送阻塞 接收非阻塞) 模式

    while (1)
    {

        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(10);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(10);

        if (motor_mode == 1)//点动模式
        {

            send_packet(motor_mode,function_code);
            /* 发送字符串 */

        }
        if (motor_mode == 2)//连续模式
           {

            send_packet(motor_mode,function_code);
               /* 发送字符串 */

           }
        if (motor_mode == 3)//停止模式
           {

            send_packet(motor_mode,function_code);
               /* 发送字符串 */

           }

        motor_mode = 0;
    }
}
