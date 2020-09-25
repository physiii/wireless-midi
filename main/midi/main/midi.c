/* UART Echo Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include <string.h>

/**
 * This is an example which echos any data it receives on UART1 back to the sender,
 * with hardware flow control turned off. It does not use UART driver event queue.
 *
 * - Port: UART1
 * - Receive (Rx) buffer: on
 * - Transmit (Tx) buffer: off
 * - Flow control: off
 * - Event queue: off
 * - Pin assignment: see defines below
 */

#define ECHO_TEST_TXD  (GPIO_NUM_23)
#define ECHO_TEST_RXD  (GPIO_NUM_22)
#define ECHO_TEST_RTS  (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS  (UART_PIN_NO_CHANGE)

#define ECHO_TEST_TXD_2  (GPIO_NUM_1)
#define ECHO_TEST_RXD_2  (GPIO_NUM_3)

#define BUF_SIZE (1024)

static void echo_task(void *arg)
{
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = 31250,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    uart_driver_install(UART_NUM_1, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS);

		uart_config_t uart_config_2 = {
				.baud_rate = 115200,
				.data_bits = UART_DATA_8_BITS,
				.parity    = UART_PARITY_DISABLE,
				.stop_bits = UART_STOP_BITS_1,
				.flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
				.source_clk = UART_SCLK_APB,
		};
		// uart_driver_install(UART_NUM_2, BUF_SIZE * 2, 0, 0, NULL, 0);
		// uart_param_config(UART_NUM_2, &uart_config_2);
		// uart_set_pin(UART_NUM_2, ECHO_TEST_TXD_2, ECHO_TEST_RXD_2, ECHO_TEST_RTS, ECHO_TEST_CTS);

    // Configure a temporary buffer for the incoming data
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);
		uint32_t old_val = 1;
		char * message[BUF_SIZE];

    while (1) {
        int len = uart_read_bytes(UART_NUM_1, data, BUF_SIZE, 1 / portTICK_RATE_MS);
				char * val = (const char *) data;

				// send to receiver

				// strcpy(message,val);
				// sprintf(message,"%s\n", val);
				uart_write_bytes(UART_NUM_2, val, len);
        // uart_write_bytes(UART_NUM_1, (const char *) data, len);
    }
}

void midi_main(void)
{
    // xTaskCreate(echo_task, "uart_echo_task", 1024, NULL, 10, NULL);
}
