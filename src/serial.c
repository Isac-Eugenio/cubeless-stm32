// #include "cubeless/serial.h"

// /* =========================
//  * UART CONFIG
//  * ========================= */
// UartConfig_t uart2_config = {

//     .instance = USART2,

//     .baudrate = 115200,

//     .word_length = UART_WORDLENGTH_8B,

//     .stop_bits = UART_STOPBITS_1,

//     .parity = UART_PARITY_NONE,

//     .mode = UART_MODE_TX_RX,

//     .hw_flow_ctl = UART_HWCONTROL_NONE,

//     .oversampling = UART_OVERSAMPLING_16,

//     .tx = {
//         .port = GPIOA,
//         .pin = GPIO_PIN_2,
//         .alternate = GPIO_AF7_USART2,
//         .pull = GPIO_NOPULL,
//         .speed = GPIO_SPEED_FREQ_VERY_HIGH
//     },

//     .rx = {
//         .port = GPIOA,
//         .pin = GPIO_PIN_3,
//         .alternate = GPIO_AF7_USART2,
//         .pull = GPIO_NOPULL,
//         .speed = GPIO_SPEED_FREQ_VERY_HIGH
//     }
// };


// /* =========================
//  * DMA CONFIG
//  * ========================= */
// DmaConfig_t uart2_tx_dma_conf = {

//     .channel =
//         DMA1_Channel2,

//     .request =
//         DMA_REQUEST_USART2_TX,

//     .direction =
//         DMA_MEMORY_TO_PERIPH,

//     .periph_inc =
//         DMA_PINC_DISABLE,

//     .mem_inc =
//         DMA_MINC_ENABLE,

//     .periph_alignment =
//         DMA_PDATAALIGN_BYTE,

//     .mem_alignment =
//         DMA_MDATAALIGN_BYTE,

//     .mode =
//         DMA_NORMAL,

//     .priority =
//         DMA_PRIORITY_LOW
// };
// /* =========================
//  * UART HANDLE
//  * ========================= */
// Uart_t uart2;

// /* =========================
//  * DMA HANDLE
//  * ========================= */
// Dma_t uart2_tx_dma;


// int _write(
//     int file,
//     char *ptr,
//     int len
// )
// {
//     while (HAL_UART_GetState(&uart2.handle)
//            != HAL_UART_STATE_READY);

//     HAL_UART_Transmit_DMA(
//         &uart2.handle,
//         (uint8_t*)ptr,
//         len
//     );

//     return len;
// }


// void serial_init(void){
//      dma_init(&uart2_tx_dma, &uart2_tx_dma_conf);

//     __HAL_LINKDMA(
//         &uart2.handle,
//         hdmatx,
//         uart2_tx_dma.handle
//     );

//     uart_init(&uart2, &uart2_config);

//      /* =========================
//     * DMA IRQ
//     * ========================= */
//     HAL_NVIC_SetPriority(
//         DMA1_Channel2_IRQn,
//         0,
//         0
//     );

//     HAL_NVIC_EnableIRQ(
//         DMA1_Channel2_IRQn
//     );

//     /* =========================
//     * USART IRQ
//     * ========================= */
//     HAL_NVIC_SetPriority(
//         USART2_IRQn,
//         0,
//         0
//     );

//     HAL_NVIC_EnableIRQ(
//         USART2_IRQn
//     );

// }

//  /* =========================
//  * DMA IRQ HANDLER
//  * ========================= */
// void DMA1_Channel2_IRQHandler(void)
// {
//     HAL_DMA_IRQHandler(
//         &uart2_tx_dma.handle
//     );
// }

// void USART2_IRQHandler(void)
// {
//     HAL_UART_IRQHandler(
//         &uart2.handle
//     );
// }
