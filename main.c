#include "stm32l4xx.h" 
#include "timer.h"

void config_clock(void){
	// Enable msi clock at 8mhz for sys clock
	RCC->CR |= (1);
	while(!(RCC->CR & (1 << 1)));
	// set msi range from cr itself
	RCC->CR |= (1 << 3);
	// set msi frequency 8
	RCC->CR |= (7 << 4);
	//SEt msi as sysclcksrc
	RCC->CFGR &= ~(3);
	SystemCoreClockUpdate();
}

int main(void){
	config_clock();
	config_tim2_pwm();
	while(1){
		for (int i =0; i <= 100; i++){
			TIM2->CCR1 = i;
			tim6_delay(50);			
		}
		
		for (int i = 100; i >= 0; i--){
			TIM2->CCR1 = i;
			tim6_delay(50);			
		}
	}
	return 0;
}
