#include "tpl_os.h"
#include "servo.h"
#include "tpl_cortex_definitions.h"
#include "coroBoard.h"
#include "pinAccess.h"


void initServo()
{
  // Timer TIM7 INIT
  RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
  asm("nop");
  // mandatory reset
  RCC->APB1RSTR |= RCC_APB1RSTR_TIM7RST;
  RCC->APB1RSTR &= ~RCC_APB1RSTR_TIM7RST;
  asm("nop");
  TIM7->PSC = 64 - 1; /* tick@1us */
  TIM7->EGR |= TIM_EGR_UG; /* take into account PSC update */
  TIM7->CR1 |= TIM_CR1_OPM; /* One pulse mode */

  /* Init the NVIC */
  NVIC_InitTypeDef NVIC_InitDef;
  NVIC_InitDef.NVIC_IRQChannel = TIM7_IRQn;
  NVIC_InitDef.NVIC_IRQChannelPreemptionPriority =
        TIM7_IRQ_Priority;                                 /* Set priority             */
  NVIC_InitDef.NVIC_IRQChannelSubPriority = 0x00;          /* Set sub priority         */
  NVIC_InitDef.NVIC_IRQChannelCmd = ENABLE;                /* Enable interrupt         */
  NVIC_Init(&NVIC_InitDef);                                /* Add to NVIC              */

  /* Servo signal */
  pinMode(GPIOA, 4, OUTPUT);
}

void setServoPulse(uint16_t widthInMicroseconds)
{
  if (widthInMicroseconds > 2000) widthInMicroseconds = 2000;
  if (widthInMicroseconds < 1000) widthInMicroseconds = 1000;
  digitalWrite(GPIOA, 4, true);
  TIM7->CNT = 0;
  TIM7->ARR = widthInMicroseconds;
  TIM7->DIER = TIM_DIER_UIE;
  TIM7->CR1 |= TIM_CR1_CEN;
}

#define APP_ISR_isr_timer_7_START_SEC_CODE
#include "tpl_memmap.h"

ISR(isr_timer_7)
{
  digitalWrite(GPIOA, 4, false);	 // reset servo signal.
  digitalWrite(GPIOB, 0, false);	 // toggle green led.
}

extern "C" void TIM7_IRQ_ClearFlag()
{
  TIM7->SR = 0;
}

#define APP_ISR_isr_timer_7_STOP_SEC_CODE
#include "tpl_memmap.h"
