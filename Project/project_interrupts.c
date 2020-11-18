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

extern volatile uint16_t linesCleared;

volatile bool buttonPressed;
volatile bool leftButtonPressed;
volatile bool rightButtonPressed;
volatile bool upButtonPressed;
volatile bool downButtonPressed;

volatile bool timerDone;
volatile uint8_t random;
void TIMER4A_Handler(void)
{
	
	static uint8_t timer4_count = 0;
	static uint8_t leftButton_count = 0;
	static uint8_t rightButton_count = 0;
	static uint8_t upButton_count = 0;
	static uint8_t downButton_count = 0;
	
	
	//static uint8_t fall_count = 0;
	if ( !(GPIOF->DATA & SW1_M) ) { // check if pushbutton pin is 0 aka pushed
	  timer4_count++;
	}
	else {
	  timer4_count = 0; // if not pushed, reset counter
	}
	if ( !(io_expander_read_button_poll(DIR_BTN_UP_PIN)) ) { // check if pushbutton pin is 0 aka pushed
	  upButton_count++;
	}
	else {
	  upButton_count = 0; // if not pushed, reset counter
	}
	if ( !(io_expander_read_button_poll(DIR_BTN_DOWN_PIN)) ) { // check if pushbutton pin is 0 aka pushed
	  downButton_count++;
	}
	else {
	  downButton_count = 0; // if not pushed, reset counter
	}
	if ( !(io_expander_read_button_poll(DIR_BTN_LEFT_PIN)) ) { // check if pushbutton pin is 0 aka pushed
	  leftButton_count++;
	}
	else {
	  leftButton_count = 0; // if not pushed, reset counter
	}
	if ( !(io_expander_read_button_poll(DIR_BTN_RIGHT_PIN)) ) { // check if pushbutton pin is 0 aka pushed
	  rightButton_count++;
	}
	else {
	  rightButton_count = 0; // if not pushed, reset counter
	}
	
	//timer4_count = timer4_count%8; // 0,1,2,3,4,5,6,7,0 ...
	
	if (timer4_count >= 5) { // if pushbutton has been held down for 5 consecutive interrupts
	  buttonPressed = true;
	}
	else {
	  buttonPressed = false;
	}
	
	if (upButton_count >= 5) { // if pushbutton has been held down for 5 consecutive interrupts
	  upButtonPressed = true;
	}
	else {
	  upButtonPressed = false;
	}	
	
	if (downButton_count >= 5) { // if pushbutton has been held down for 5 consecutive interrupts
	  downButtonPressed = true;
	}
	else {
	  downButtonPressed = false;
	}
	if (leftButton_count >= 5) { // if pushbutton has been held down for 5 consecutive interrupts
	  leftButtonPressed = true;
	}
	else {
	  leftButtonPressed = false;
	}
	if (rightButton_count >= 5) { // if pushbutton has been held down for 5 consecutive interrupts
	  rightButtonPressed = true;
	}
	else {
	  rightButtonPressed = false;
	}
	
//	if (linesCleared < 5) {
//		if (fall_count == (10-linesCleared)) { // if pushbutton has been held down for 5 consecutive interrupts
//			timerDone = true;
//		}
//		else {
//			timerDone = false;
//		}
//		fall_count= (fall_count+1)%(11-linesCleared);
//	} else {
//		if (fall_count == 5) { // if pushbutton has been held down for 5 consecutive interrupts
//			timerDone = true;
//		}
//		else {
//			timerDone = false;
//		}
//		fall_count= (fall_count+1)%6;
//	}
	random++;
	TIMER4->ICR |= TIMER_ICR_TATOCINT; // CLEAR INTERRUPT
	
	
	
}

//*****************************************************************************
// TIMER5 ISR
//*****************************************************************************
volatile bool AlertADC;
volatile int wait; // wait counter for external wait method

void TIMER5A_Handler(void)
{
	
	static uint16_t fall_count = 0;
//	TIMER0_Type *gp_timer;
//	ADC0_Type  *myADC;
//	myADC = (ADC0_Type *)ADC0_BASE;
//	gp_timer = (TIMER0_Type *)TIMER5_BASE;

//	
//	//If the interrupt happened the countdown has happened
//	myADC->PSSI = ADC_PSSI_SS1;
	
	//Clear the interrupt
	//second_wait++;
		//gp_timer->ICR |= TIMER_ICR_TATOCINT;
  AlertADC = true;
	ADC0->PSSI |= ADC_PSSI_SS1; // begin sampling on ACD0 SS1
	
	if (linesCleared < 5) {
		if (fall_count == (10-linesCleared)) { // if pushbutton has been held down for 5 consecutive interrupts
			timerDone = true;
		}
		else {
			timerDone = false;
		}
		fall_count= (fall_count+1)%(11-linesCleared);
	} else {
		if (fall_count == 5) { // if pushbutton has been held down for 5 consecutive interrupts
			timerDone = true;
		}
		else {
			timerDone = false;
		}
		fall_count= (fall_count+1)%6;
	}
//	
	wait++; // increment wait timer for external wait method
	random++;
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
	ADC0_Type  *myADC;
	myADC = (ADC0_Type *)ADC0_BASE;
	//Do two calls to get both positions
	avg_ps2x = myADC->SSFIFO1 & 0xFFF;
	avg_ps2y = myADC->SSFIFO1 & 0xFFF;
	
//	  avg_ps2x = ADC0->SSFIFO1 & 0x0FFF; // read x value
//		avg_ps2y = ADC0->SSFIFO1 & 0x0FFF; // read y value
	
		ADC0->ISC |= ADC_ISC_IN1; // CLEAR INTERRUPT
		ADC_avg_ready = true;

}


//*****************************************************************************
// ADC0 SS1 ISR
//*****************************************************************************
//void ADC0SS1_Handler(void)
//{
//	static int count = 0;
//	static bool moved = false;
//	//Set up the ADC to read data and clear interrupts
//	ADC0_Type  *myADC;
//	uint32_t x;
//	uint32_t y;
//	myADC = (ADC0_Type *)ADC0_BASE;
//	
//	
//	
//	//Do two calls to get both positions
//	x = myADC->SSFIFO1 & 0xFFF;
//	y = myADC->SSFIFO1 & 0xFFF;
//	
//	/*
//	* The next section handles doing left and right movement before up and down
//	* movement. It does this by clearing the interrupt and return once an if 
//	* statement has been entered.
//	*
//	* might want to move somewhere else (main)
//	*/
//	
//	//If the x reading is greater than 2.8 V
//	changed = true;
//	if(x > 3475){
//		if(x_pos != 0 && !moved){
//			x_pos--;
//			moved = true;
//		}
//		myADC->ISC = ADC_ISC_IN1;
//		return;
//	}	
//	//If the x reading is less than .6 V
//	else if(x < 744){
//		if(x_pos != 2 && !moved){
//				x_pos++;
//				moved = true;
//		}
//		myADC->ISC = ADC_ISC_IN1;
//		return;
//	}
//	//If the y reading is less than .6 V
//	else if(y < 744){
//		if(y_pos !=2 && !moved){
//				y_pos++;
//				moved = true;
//		}
//	
//		myADC->ISC = ADC_ISC_IN1;
//		return;
//	}
//	//Otherwise, in the center, don't move
//	else {
//		changed = false;
//		myADC->ISC = ADC_ISC_IN1;
//		moved = false;
//		return;
//	}
//	
//	
//	
//}




