#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <misc.h>
#include <stm32f4xx_tim.h>
#include <stm32f4xx_usart.h>

void LED_init();
void USART2_init(void);
void init();
void Delay(__IO uint32_t nCount);
