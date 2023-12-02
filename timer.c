#include "stm32l4xx.h" 

void config_tim2_pwm(void){
	
	//From datasheet PA5(pin for device led) is connected to tim2 channel 1 with AF0
	//Step 1: initialize gpio for led (set clock and modes)
	//Initializing clock for GPIO-A
	RCC->AHB2ENR |= 1ul;
	
	// Unsetting Mode at port GPIOA-5
	GPIOA->MODER &= ~(3ul << 10); // 
	// Setting Mode to alternate function i.e, 10 
	//(00 is input(reset), 10 is alternate function, 11 is analog mode)
	GPIOA->MODER |= (2ul << 10);
	GPIOA->AFR[0] |= (1 << 20);
	
	//Enable clock for timer 2
	RCC->APB1ENR1 |= 1ul;
	
	//set mode 1 for pwm 
	TIM2->CCMR1 |= (6ul << 4);
	//Capture compare output enable
	TIM2->CCER |= 1;
	//Frquency of the signal
	TIM2->ARR = 100; 
	//Enable counter
	TIM2->CR1 |= 1;
}

void tim6_delay(uint32_t delay){
	
	// Initialize clock for TIM6 set RCC_APB1ENR1_TIM6EN 
	RCC->APB1ENR1 |= (1ul << 4);
	
	// Setting our prescaler value since clock speed is 4mhz  by default 8mhz/(61) ~= 1 event per sec (not very accurate?) 
	// Calculation is for uint16 bit counter ..counter value can be set by TIM6->ARR
	TIM6->PSC = (8000-1);
	
	// Enable update interrupt set TIM_DIER_UIE
	TIM6->DIER |= (1ul);
	
	TIM6->ARR = delay;
	TIM6->CNT = 0;
	
	// Setting Control register of timer
	// Enable bit 0 to enable counter TIM_CR1_CEN
	// Enable bit 2 to only send interrupt when overflow/underflow TIM_CR1_URS
	TIM6->CR1 |= ((1ul) | (1ul << 2));
	
	//wait for pending interrupt flag set
	while(!(TIM6->SR & (1ul)));
	//unset the flag
	TIM6->SR &= ~(1ul);
}