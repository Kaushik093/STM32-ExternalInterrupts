
#include <exti.h>

#define GPIOCEN		(1U<<2)
#define SYSCFG_EN	(1U<<14)

#define UMSK_13		(1U<<13)
#define FTRG_EN		(1U<<13)

void pc13_exti_init(void){

	//Disable global interrupts
//	__disable_irq();

	//Enable clock for GPIOC
	RCC->AHB1ENR |= GPIOCEN;

	//Set PC13 as input (input is default)
	GPIOC->MODER &= ~(1U<<26);
	GPIOC->MODER &= ~(1U<<27);

	//Enable clock for SYSCFG (EXTI)
	RCC->APB2ENR |= SYSCFG_EN;

	//Select PORTC for EXT13
	SYSCFG->EXTICR[3] |= (1U<<5);

	//Un-mask EXT13
	EXTI->IMR |= UMSK_13;

	//Select falling edge trigger
	EXTI->FTSR |= FTRG_EN;

	//Enable IRQ for EXT13 in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);	//Pins 10-15 share the same IRQ in NVIC

	//Enable global interrupts
	__enable_irq();
}
