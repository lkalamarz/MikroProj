//#include "init_pwm.h"
#include "init.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include <misc.h>
#define POWER_MAX 122
#define POWER_MIN 30
#define MAX_STRLEN 4 // this is the maximum string length of our string in characters
//volatile char received_string[MAX_STRLEN+1]; // this will hold the recieved string
volatile uint8_t received_string[MAX_STRLEN+1];
volatile char chosen_data[MAX_STRLEN+1];// this will hold the recieved string
int power, power2;
int i=1;
int liczba_global;
volatile uint8_t data[8];
uint8_t Obtained;
long pasig, tamad = 0xBFFFF;
int manila;
int main()
{
	TIM_conf();
	RCC_Configuration();
	GPIO_Configuration();
	init_GPIO();
	USART3_Configuration();
	//setPA12_OUT_PP();


	while(1)
				{




		//GPIO_WriteBit(GPIOA, GPIO_Pin_0, 0);
		//Delay(5000000);

		//GPIO_WriteBit(GPIOA, GPIO_Pin_0, 1);

		/*Demultiplekser(5);
		GPIO_ResetBits(GPIOE,GPIO_Pin_3);
		GPIO_ResetBits(GPIOE,GPIO_Pin_5);

							PA_Set_Bit(7);*/
							//GPIO_ResetBits(GPIOE,GPIO_Pin_5);
	//	int g = 9;
	//	GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6);
		//power = usart_rec();
	/*power = USART_ReceiveData(USART3);
		if(power==106)
		{USART_puts(USART3,"zajebiscie");}
		else if (power==254)
		{USART_puts(USART3,"testowo");}
		else
			{}


		power = 0;*/
		//USART3_IRQHandler();
		//Delay(10000);

		/*ADC_Val = adc_convert();
		Delay(100000);
		power = 30 + ADC_Val*92/4096;
		power2 = 30 + ADC_Val*92/4096;
		TIM_SetCompare2(TIM2,power);
		TIM_SetCompare3(TIM2,power2);
		Delay(100000);*/
		/*
		TIM_SetCompare2(TIM2,power);
		Delay(100000);
				}
				*/
		//GPIO_SetBits(GPIOA, GPIO_Pin_1);
	}
}



/* This function is used to transmit a string of characters via
 * the USART specified in USARTx.
 *
 * It takes two arguments: USARTx --> can be any of the USARTs e.g. USART1, USART2 etc.
 * 						   (volatile) char *s is the string you want to send
 *
 * Note: The string has to be passed to the function as a pointer because
 * 		 the compiler doesn't know the 'string' data type. In standard
 * 		 C a string is just an array of characters
 *
 * Note 2: At the moment it takes a volatile char because the received_string variable
 * 		   declared as volatile char --> otherwise the compiler will spit out warnings
 * */


void setPA12_OUT_PP ( void ) {
      GPIO_InitTypeDef GPIO_InitStructure;
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
      GPIO_InitStructure.GPIO_Mode = GPIO_OType_OD; // GPIO_Mode_AF_PP for alternate function
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
      GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void RCC_Configuration(void)
{
  /* --------------------------- System Clocks Configuration -----------------*/
  /* USART3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

  /* GPIOB clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
}

/**************************************************************************************/

void GPIO_Configuration(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;

	  /*-------------------------- GPIO Configuration ----------------------------*/
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);

	  /* Connect USART pins to AF */
	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

	  /* Here the USART1 receive interrupt is enabled
	  	 * and the interrupt controller is configured
	  	 * to jump to the USART1_IRQHandler() function
	  	 * if the USART1 receive interrupt occurs
	  	 */
}

/**************************************************************************************/

void USART3_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
  /* USARTx configuration ------------------------------------------------------*/
  /* USARTx configured as follow:
        - BaudRate = 9600 baud
        - Word Length = 8 Bits
        - Two Stop Bit
        - Odd parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;






  USART_Init(USART3, &USART_InitStructure);

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); // enable the USART3 receive interrupt

	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;		 // we want to configure the USART3 interrupts
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;// this sets the priority group of the USART1 interrupts
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		 // this sets the subpriority inside the group
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			 // the USART1 interrupts are globally enabled
	NVIC_Init(&NVIC_InitStructure);							 // the properties are passed to the NVIC_Init function which takes care of the low level stuff

	// finally this enables the complete USART1 peripheral


  USART_Cmd(USART3, ENABLE);
}

/**************************************************************************************/
void USART_puts(USART_TypeDef* USARTx, volatile char *s){

        while(*s){
                // wait until data register is empty
                while( !(USARTx->SR & 0x00000040) );
                USART_SendData(USARTx, *s);
                *s++;
        }
}

void USART3_IRQHandler(void){


		uint8_t t = USART3->DR;
		static uint8_t u = 0;
		static uint8_t cnt = 0;

		if((cnt < MAX_STRLEN) )
		{
			received_string[cnt] = t;
			cnt++;
		}
		else
		{
			cnt = 0;
			t=0;
			if(received_string[0] == 48)
			{

				GPIO_SetBits(GPIOA,GPIO_Pin_7);
			Demultiplekser(received_string[1]-48);


			Delay(5000000);
				USART_SendData(USART3,PD_Status());
					GPIO_ResetBits(GPIOA,GPIO_Pin_7);



			}
			else if (received_string[0]==51)
			{
				if (received_string[3] == 255)
				{
					printf(received_string[3]);
					PA_Set_Bit(0);
					PA_Set_Bit(1);
					PA_Set_Bit(2);
					PA_Set_Bit(3);
					PA_Set_Bit(4);
					PA_Set_Bit(5);
					PA_Set_Bit(6);
					PA_Set_Bit(7);

				}
				GPIO_SetBits(GPIOA,GPIO_Pin_7);
				Demultiplekser(received_string[1]-48);
				Delay(5000000);
				USART_SendData(USART3,PA_Status());
				GPIO_ResetBits(GPIOA,GPIO_Pin_7);
			}
			else if (received_string[0] == 49) //& ((received_string[1] >=48 & received_string<=51)| received_string[1] ==53 | (received_string[1]==49 & (received_string[2]==48 | received_string[2]==49))))
			{
				GPIO_ResetBits(GPIOE,GPIO_Pin_3);
				Demultiplekser(received_string[1]-48);

				Delay(100000);
				if (received_string[3]==49)
				{PA_Set_Bit(received_string[2]-48);}
				else if (received_string[3] ==48)
				{PA_Reset_Bit(received_string[2]-48);}
								//USART_SendData(USART3,PA_Status());
				//Delay(500);

			//				USART_SendData(USART3,130);
				GPIO_SetBits(GPIOE,GPIO_Pin_3);
			}
			else
			{
			//	USART_SendData(USART3,0);
				//received_string = null;
			}
			}
		/*	if(received_string[0] == 48 && received_string[1] == 48 && received_string[2] == 52 )
			{//Demultiplekser(1);
				uint8_t gowno = M2_Status();
				USART_SendData(USART3,gowno);
			}
			else if (received_string[0] == 48 && received_string[1] == 48 && received_string[2] == 53 )
			{}
			else if (received_string[0] == 48 && received_string[1] == 48 && received_string[2] == 54 )
						{}
			else if (received_string[0] == 48 && received_string[1] == 48 && received_string[2] == 55 )
						{}
			else
			{
				uint8_t gowno = M1_Status();
				USART_SendData(USART3,gowno);
			}*/

			//USART_puts(USART3,t);
			//USART_puts(USART3, "]");
			//}
		/*}*/

	//}
	/*Delay(100000);
			USART3->DR = 0x0;
			for (u=0; u<MAX_STRLEN+1;u++)
			{received_string[u] = 0;*/
}

void PA_Set_Bit (int number)
{
	if(number==0)
		   GPIO_SetBits(GPIOA, GPIO_Pin_0);
		else if (number==1)
			GPIO_SetBits(GPIOA, GPIO_Pin_1);
		else if (number==2)
			GPIO_SetBits(GPIOA, GPIO_Pin_2) ;
		else if (number==3)
			GPIO_SetBits(GPIOA, GPIO_Pin_3) ;
		else if (number==4)
			GPIO_SetBits(GPIOC, GPIO_Pin_0) ;
		else if (number==5)
			GPIO_SetBits(GPIOC, GPIO_Pin_1);
		else if (number==6)
			GPIO_SetBits(GPIOC, GPIO_Pin_2) ;
		else if (number==7)
			GPIO_SetBits(GPIOC, GPIO_Pin_3);
		else
		{}
}

void PA_Reset_Bit (int number)
{
	if(number==0)
			   GPIO_ResetBits(GPIOA, GPIO_Pin_0);
			else if (number==1)
				GPIO_ResetBits(GPIOA, GPIO_Pin_1);
			else if (number==2)
				GPIO_ResetBits(GPIOA, GPIO_Pin_2) ;
			else if (number==3)
				GPIO_ResetBits(GPIOA, GPIO_Pin_3) ;
			else if (number==4)
				GPIO_ResetBits(GPIOC, GPIO_Pin_0) ;
			else if (number==5)
				GPIO_ResetBits(GPIOC, GPIO_Pin_1);
			else if (number==6)
				GPIO_ResetBits(GPIOC, GPIO_Pin_2) ;
			else if (number==7)
				GPIO_ResetBits(GPIOC, GPIO_Pin_3);
			else
			{}
}

int PD_Status ()
	  {


	int wynik =0;
	wynik = 1 * (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0) ? 1:0) + 2 * (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1) ? 1:0) + 4 * (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2) ? 1:0) + 8 *(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) ? 1:0) + 16 * (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4) ? 1:0) + 32 * (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10) ? 1:0) + 64 * (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11) ? 1:0) + 128 * (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12) ? 1:0);
	 return wynik;
	  }

int PA_Status ()
	  {
	int wynik =0;
	wynik = 1 * (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) ? 1:0) + 2 * (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) ? 1:0) + 4 * (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) ? 1:0) + 8 *(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) ? 1:0) + 16 * (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) ? 1:0) + 32 * (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) ? 1:0) + 64 * (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2) ? 1:0) + 128 * (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) ? 1:0);
	 return wynik;
	  }


int M2_Status ()
	  {
	    return (GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_1) ? 1:0);
	  }

void init_GPIO(void){

	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	// PD0-7 - DO0-7
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1 | GPIO_Pin_2, GPIO_Pin_3 | GPIO_Pin_4 |  GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12| GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; 		// we want the pins to be an output
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 	// this sets the GPIO modules clock speed
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;   // this sets the pin type to push / pull (as opposed to open drain)
			GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; 	// this sets the pullup / pulldown resistors to be inactive
	GPIO_Init(GPIOD, &GPIO_InitStruct); 			// this finally passes all the values to the GPIO_Init function which takes care of setting the corresponding bits.


	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	// PA0-7 - DI0-7
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1 | GPIO_Pin_2, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10| GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;			  // we want to configure PA0
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; 	  // we want it to be an input
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//this sets the GPIO modules clock speed
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;  // this sets the pin type to push / pull (as opposed to open drain)
			GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;  // this enables the pulldown resistor --> we want to detect a high level
	GPIO_Init(GPIOA, &GPIO_InitStruct);			  // this passes the configuration to the Init function which takes care of the low level stuff


	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		// PA0-7 - DI0-7
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1 | GPIO_Pin_2, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10| GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;			  // we want to configure PA0
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; 	  // we want it to be an input
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//this sets the GPIO modules clock speed
		GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;     // this sets the pin type to push / pull (as opposed to open drain)
				GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;   // this enables the pulldown resistor --> we want to detect a high level
		GPIO_Init(GPIOC, &GPIO_InitStruct);			  // this passes the configuration to the Init function which takes care of the low level stuff


	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	//PE0, PE1 , PE2 - demultiplekser(wybor urzadzenia)
	//PE3 - AG
	//PE4 - ~RD
	//PE5 - ~WR
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;		  // we want to configure PA0
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN; 	  // we want it to be an input
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//this sets the GPIO modules clock speed
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   // this sets the pin type to push / pull (as opposed to open drain)
		GPIO_InitStruct.GPIO_PuPd =  GPIO_PuPd_UP;   // this enables the pulldown resistor --> we want to detect a high level
		GPIO_Init(GPIOE, &GPIO_InitStruct);

		GPIO_SetBits(GPIOE,GPIO_Pin_3);
						GPIO_ResetBits(GPIOE,GPIO_Pin_4);
						GPIO_ResetBits(GPIOE,GPIO_Pin_5);


						RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
						GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1|GPIO_Pin_2 | GPIO_Pin_3;
							GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; 	  // we want it to be an input
							GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//this sets the GPIO modules clock speed
							GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   // this sets the pin type to push / pull (as opposed to open drain)
							GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;   // this enables the pulldown resistor --> we want to detect a high level
							GPIO_Init(GPIOH, &GPIO_InitStruct);


		// B - PWM
		// C - Interupts



}

void ResetDemultip()
{
	Delay(5000000);
}
void Demultiplekser (int number)
{

	//Wybranie odpowiedniego ukladu do odczytu/zapisu danych
	if (number ==0)
	{

		GPIO_WriteBit(GPIOE,GPIO_Pin_0,0);
		GPIO_ResetBits(GPIOE,GPIO_Pin_1);
		GPIO_ResetBits(GPIOE,GPIO_Pin_2);
		ResetDemultip();
	}
	else if (number ==1)
	{
				GPIO_SetBits(GPIOE,GPIO_Pin_0);
				GPIO_ResetBits(GPIOE,GPIO_Pin_1);
				GPIO_ResetBits(GPIOE,GPIO_Pin_2);
				ResetDemultip();
	}
	else if (number==2)
	{
		GPIO_ResetBits(GPIOE,GPIO_Pin_0);
						GPIO_SetBits(GPIOE,GPIO_Pin_1);
						GPIO_ResetBits(GPIOE,GPIO_Pin_2);
						ResetDemultip();
	}

	else if (number==3)
	{

		GPIO_SetBits(GPIOE,GPIO_Pin_0);
						GPIO_SetBits(GPIOE,GPIO_Pin_1);
						GPIO_ResetBits(GPIOE,GPIO_Pin_2);
						ResetDemultip();
	}

	else if (number ==4)
	{

						GPIO_SetBits(GPIOE,GPIO_Pin_0);
												GPIO_ResetBits(GPIOE,GPIO_Pin_1);
												GPIO_SetBits(GPIOE,GPIO_Pin_2);

	}

	else if (number ==5)
	{
		GPIO_SetBits(GPIOE,GPIO_Pin_0);
						GPIO_ResetBits(GPIOE,GPIO_Pin_1);
						GPIO_SetBits(GPIOE,GPIO_Pin_2);
						ResetDemultip();
	}
	else
	{}
}

void SaveDataFrom(GPIO_TypeDef* GPIOx, int number, int value)
{
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
	 // assert_param(IS_GPIO_PIN(GPIO_Pin));
	//ustawienie danej
	GPIO_SetBits(GPIOA,GPIO_Pin_7);
	if(number==3)
	{
	if (value ==48)
	{
		GPIO_ResetBits(GPIOx,GPIO_Pin_3);
	}
	else if (value ==49)
	{

		GPIO_SetBits(GPIOx,GPIO_Pin_3);
	}
	else if (value ==0)
		{
			GPIO_ResetBits(GPIOx,GPIO_Pin_3);
		}
		else if (value ==1)
		{

			GPIO_SetBits(GPIOx,GPIO_Pin_3);
		}
	else
	{}
	}
		Delay(100000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
}

void ReadDataFrom(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	//odczytanie danej
	GPIO_SetBits(GPIOE,GPIO_Pin_4);
	//Delay(1000);
	//Int2Str(chosen_data,GPIO_ReadOutputDataBit(GPIOx,GPIO_Pin));
	Obtained = GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_0);
	//USART_puts(USART3,GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_1));
	//USART_puts(USART3,GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_0));
	USART_SendData(USART3,(GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_1) ? 1:0));
//USART_puts(USART3,(GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_1) ? 1:0));
	//GPIO_SetBits(GPIOE,GPIO_Pin_0);
					//GPIO_ResetBits(GPIOE,GPIO_Pin_1);
	Delay(1000);
	GPIO_ResetBits(GPIOE,GPIO_Pin_4);

}

void Int2Str(char *str, u32 intnum)

{

u32 Div = 1000000000;

int i, j = 0, Status = 0;

for (i = 0; i < 10; i++)

{

str[j++] = (intnum / Div) + 48;

intnum = intnum % Div;

Div /= 10;



if ((str[j-1] == '0') & (Status == 0))

{

str[j] = '\0';

j = 0;

}

else

{

str[j] = '\0';

Status++;

}



}

}
