#include <rtthread.h>
#include "hal_data.h"
#include <rtdevice.h>

#define LED_PIN    BSP_IO_PORT_02_PIN_09 /* Onboard LED pins */

 extern rt_int8_t motor_mode;
 extern rt_int8_t function_code;

#define SAMPLE_UART_NAME       "uart4"    /* �����豸���� */
static rt_device_t serial; /* �����豸��� */

void send_packet(rt_int8_t mode,rt_int8_t code){

    rt_int8_t packet[4];
    packet[0] = 0xAA; // ��ʼ�ֽ�
    packet[1] = mode; // ���ģʽ 01 �㶯��02 ������03 ֹͣ��
    packet[2] = code; // ������ 01 ǰ����02 ���ˣ�03 ��ת��04��ת��
    packet[3] = 0x55; // �����ֽ�

    // �������ݰ�

    //while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); // �ȴ����ͻ�����Ϊ��
    rt_device_write(serial, 0, packet, (sizeof(packet) - 0));
    //USART_SendData(USART1, packet[i]); // ��������



}

void hal_entry(void)
{
    rt_kprintf("\nHello RT-Thread!\n");

    /* ���Ҵ����豸 */
    serial = rt_device_find(SAMPLE_UART_NAME); //�������ֲ���uart4 �豸
    //��uart4
    rt_device_open(serial, RT_DEVICE_FLAG_RX_NON_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING);
    // �����豸ʹ��ģʽΪ (�������� ���շ�����) ģʽ

    while (1)
    {

        rt_pin_write(LED_PIN, PIN_HIGH);
        rt_thread_mdelay(10);
        rt_pin_write(LED_PIN, PIN_LOW);
        rt_thread_mdelay(10);

        if (motor_mode == 1)//�㶯ģʽ
        {

            send_packet(motor_mode,function_code);
            /* �����ַ��� */

        }
        if (motor_mode == 2)//����ģʽ
           {

            send_packet(motor_mode,function_code);
               /* �����ַ��� */

           }
        if (motor_mode == 3)//ֹͣģʽ
           {

            send_packet(motor_mode,function_code);
               /* �����ַ��� */

           }

        motor_mode = 0;
    }
}
