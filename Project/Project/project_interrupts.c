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

#include "main.h"
#include "project_interrupts.h"
volatile int x_pos;
volatile int y_pos;
//*****************************************************************************
// TIMER4 ISR
//*****************************************************************************
volatile bool buttonPressed;
void TIMER4A_Handler(void)
{
	static uint8_t timer4_count = 0;
	
	if ( !(GPIOF->DATA & SW1_M) ) { // check if pushbutton pin is 0 aka pushed
	  timer4_count++;
	}
	else {
	  timer4_count = 0; // if not pushed, reset counter
	}
	
	//timer4_count = timer4_count%8; // 0,1,2,3,4,5,6,7,0 ...
	
	if (timer4_count >= 5) { // if pushbutton has been held down for 5 consecutive interrupts
	  buttonPressed = true;
	}
	else {
	  buttonPressed = false;
	}
	
	TIMER4->ICR |= TIMER_ICR_TATOCINT; // CLEAR INTERRUPT
	
}

//*****************************************************************************
// TIMER5 ISR
//*****************************************************************************
volatile bool AlertADC; 
volatile int wait; // wait counter for external wait method
void TIMER5A_Handler(void)
{
  AlertADC = true;
	ADC0->PSSI |= ADC_PSSI_SS1; // begin sampling on ACD0 SS1
	
	wait++; // increment wait timer for external wait method
	TIMER5->ICR |= TIMER_ICR_TATOCINT; // CLEAR INTERRUPT
}

//*****************************************************************************
// ADC0 SS1 ISR
//*****************************************************************************
volatile uint16_t avg_ps2x; // global x avg value
volatile uint16_t avg_ps2y; // global y avg value
volatile bool ADC_avg_ready;
void ADC0SS1_Handler(void)
{

	ADC_avg_ready = true;
	
	  avg_ps2x = ADC0->SSFIFO1 & 0x0FFF; // read x value
		avg_ps2y = ADC0->SSFIFO1 & 0x0FFF; // read y value
	
		ADC0->ISC |= ADC_ISC_IN1; // CLEAR INTERRUPT

}





