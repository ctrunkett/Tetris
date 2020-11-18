// Copyright (c) 2015-19, Joe Krachey
// All rights reserved.
//
// Redistribution and use in source or binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in source form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "project_hardware_init.h"
#include "main.h"

//*****************************************************************************
// GPIO Init
// This function is used to configure all of the GPIO pins used for HW3.  You 
// should initialize the pins for the LCD, PS2 Joystick, and SW1.
//*****************************************************************************
static void gpio_init(void)
{
	
	// PUSHBUTTON USES GPIOF
	SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_R5; // turn on clock for portF
  while ( !(SYSCTL->PRGPIO & SYSCTL_PRGPIO_R5 ) ) {} // wait for portF to be ready
		
	// only necessary on GPIOF and GPIOD of this microcontroller	
	GPIO_PORTF_LOCK_R = 0x4C4F434B; // change the lock
	GPIO_PORTF_CR_R = 0xFF;         // change the control reg
	
	GPIOF->DEN |=  SW1_M; // set pushbutton to be digital enable
	GPIOF->PUR |=  SW1_M; // set pull up resistor
  GPIOF->DIR &= ~SW1_M; // set as input
		
	// PS2 JOYSTICK USES GPIOE
	SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_R4; // turn on clock for portE
  while ( !(SYSCTL->PRGPIO & SYSCTL_PRGPIO_R4 ) ) {} // wait for portE to be ready
		
	GPIOE->DIR   &= ~(PS2_X_DIR_MASK|PS2_Y_DIR_MASK); // enable as input
	GPIOE->AMSEL |= PS2_X_DIR_MASK|PS2_Y_DIR_MASK;    // enable analog mode select
  GPIOE->AFSEL |= PS2_X_DIR_MASK|PS2_Y_DIR_MASK;	  // enable alternate function
	
}


//*****************************************************************************
// ADC0 Init
// This function is used to configure ADC0 based on the HW3 requirements.  
//
// DO NOT simply call the ADC0 initialization function from ICE-12.  That code
// configures the wrong sample sequencer and also does not use interrupts.
//*****************************************************************************
static void adc0_init(void)
{
	SYSCTL->RCGCADC |= SYSCTL_RCGCADC_R0; // turn on ADC clock
  
  // Wait for ADC0 to become ready
  while( (SYSCTL_PRADC_R0 & SYSCTL->PRADC) != SYSCTL_RCGCADC_R0){} 
    
  // disable sample sequencer #1 by writing a 0 to the 
  // corresponding ASENn bit in the ADCACTSS register 
	ADC0->ACTSS &= ~ADC_ACTSS_ASEN1;
		
	// Set the event multiplexer to trigger conversion on a processor trigger
  // for sample sequencer #1	
  ADC0->EMUX &= ~ADC_EMUX_EM1_M; // set trigger to processor (default) on SS1 can use the always macro too
  //myADC->EMUX |= ADC_EMUX_EM1_PROCESSOR; // doesnt do anything lmao but its explicit so whatever 
  
	
  
  //ADC0->SSCTL1 |= ADC_SSCTL1_IE0 | ADC_SSCTL1_IE1; // have both ps2x and ps2y channels generate interrupts (WRONG)
	
	// Set IE1 and END1 in SSCTL1
	ADC0->SSCTL1 |= ADC_SSCTL1_END1 | ADC_SSCTL1_IE1; // 2nd sample is end of sequence only generate raw interrupt after both x and y have been sampled
	
  
	ADC0->SSMUX1 |= PS2_X_ADC_CHANNEL; // set the first channel to read channel x (MUX0)
	ADC0->SSMUX1 |= (PS2_Y_ADC_CHANNEL << 4); // set the second channel to read channel y (MUX1)
	
	
	ADC0->SAC = 0x4; //set the Sample Averaging Control register to 16x hardware oversampling
	ADC0->ISC |= ADC_ISC_IN1; // clear interrupts on SS1
	
	//ADC0->IM |= ADC_IM_MASK1; // i think this should only be done after 16 reads and samples
	
	// enable interrupts and set priority
	NVIC_EnableIRQ(ADC0SS1_IRQn);
	NVIC_SetPriority(ADC_IM_MASK1, 2);
		
	ADC0->ACTSS |= ADC_ACTSS_ASEN1; // enable SS1
}

//*****************************************************************************
// TIMER4 Init
// This function is used to configure TIMER4 based on the HW3 requirements
//*****************************************************************************
static void timer4_init(void)
{
	SYSCTL->RCGCTIMER |= SYSCTL_RCGCTIMER_R4; // turn on timer 4 clock
	
	while (! (SYSCTL->PRTIMER |= SYSCTL_PRTIMER_R4) ) {} // wait for timer 4 to be ready
	
	TIMER4->CTL &= (TIMER_CTL_TAEN | TIMER_CTL_TBEN); // turn off timerA and timerB
	
	TIMER4->CFG |= TIMER_CFG_32_BIT_TIMER; // configure to be 32-bit
		
	TIMER4->TAMR &= ~TIMER_TAMR_TAMR_M; // clear any mode it got going on
	TIMER4->TAMR |= TIMER_TAMR_TAMR_PERIOD; // configure to be periodic/free-running
	TIMER4->TAMR &= ~TIMER_TAMR_TACDIR; // configure to count-down
	
	TIMER4->TAILR = 1000000; // oh shit alright gotta figure this one out
	
	TIMER4->IMR |= TIMER_IMR_TATOIM; // enable timerA time-out interrupt
		
	
	
	TIMER4->ICR |= TIMER_ICR_TATOCINT; // clear any interrupts it got going on rn
	
	// enable interrupts and set priority
	NVIC_EnableIRQ(TIMER4A_IRQn);
	NVIC_SetPriority(TIMER4A_IRQn, 0);
	
	TIMER4->CTL |= TIMER_CTL_TAEN; // turn on timerA idk
	
}

//*****************************************************************************
// TIMER5 Init
// This function is used to configure TIMER5 based on the HW3 requirements
//*****************************************************************************
static void timer5_init(void)
{
	SYSCTL->RCGCTIMER |= SYSCTL_RCGCTIMER_R5; // turn on timer 5 clock
	
	while (! (SYSCTL->PRTIMER |= SYSCTL_PRTIMER_R5) ) {} // wait for timer 5 to be ready
	
	TIMER5->CTL &= (TIMER_CTL_TAEN | TIMER_CTL_TBEN); // turn off timerA and timerB
	
	TIMER5->CFG |= TIMER_CFG_32_BIT_TIMER; // configure to be 32-bit
		
	TIMER5->TAMR &= ~TIMER_TAMR_TAMR_M; // clear any mode it got going on
	TIMER5->TAMR |= TIMER_TAMR_TAMR_PERIOD; // configure to be periodic/free-running
	TIMER5->TAMR &= ~TIMER_TAMR_TACDIR; // configure to count-down
	
	TIMER5->TAILR = 50000; // oh shit alright gotta figure this one out
	
	TIMER5->IMR |= TIMER_IMR_TATOIM; // enable timerA time-out interrupt
	
	TIMER5->ICR |= TIMER_ICR_TATOCINT; // clear any interrupts it got going on rn
	
	// enable interrupts and set priority
	NVIC_EnableIRQ(TIMER5A_IRQn);
	NVIC_SetPriority(TIMER5A_IRQn, 1);
	
	TIMER5->CTL |= TIMER_CTL_TAEN; // turn on timerA idk
}

//*****************************************************************************
// This function calls all of the routines used to configure the hardware
// for HW3.
//*****************************************************************************
void initialize_hardware(void)
{
    gpio_init();
    adc0_init();
    timer4_init();
    timer5_init();
}
