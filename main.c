#include "init_pwm.h"
#include "init.h"
#define POWER_MAX 122
#define POWER_MIN 30

int main()
		{
	    TIM_conf();
	    ADC_conf();
	    uint16_t ADC_Val; //Stores the calculated ADC value
	    int power = POWER_MIN;
	    int period = TIM2->ARR;
		while(1)
					{
			ADC_Val = adc_convert();
			Delay(100000);
			power = 30 + ADC_Val*92/4096;
			TIM_SetCompare2(TIM2,power);
			Delay(100000);
			/*
			TIM_SetCompare2(TIM2,power);
			Delay(100000);
					}
					*/
		}
		}

int adc_convert(){
 ADC_SoftwareStartConv(ADC1);//Start the conversion
 while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));//Processing the conversion
 return ADC_GetConversionValue(ADC1); //Return the converted data
}
