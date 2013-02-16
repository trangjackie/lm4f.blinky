/*
 * blinky.c
 *
 *  Created on: Feb 16, 2013
 *      Author: trang
 */
#include <stdio.h>
#include <math.h>
#include "inc/lm4f120h5qr.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/fpu.h"
#include "driverlib/rom.h"
#include "driverlib/gpio.h"

//*****************************************************************************
//
//!
//! A very simple example that blinks the on-board LED using direct register
//! access.
//
//*****************************************************************************

//*****************************************************************************
//
// Define pin to LED color mapping.
//
//*****************************************************************************

#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3

//*****************************************************************************
//
// Blink the on-board LED.
//
//*****************************************************************************
int
main(void)
{
    volatile unsigned long ulLoop;
    float x = 3.141529684;
    unsigned long y = 0x49249249;
    //
    // Setup the system clock to run at 50 Mhz from PLL with crystal reference
    //
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //
    // Enable and configure the GPIO port for the LED operation.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED);
    // FPU
    ROM_FPULazyStackingEnable();
    ROM_FPUEnable();
    //
    // Loop forever.
    //
    while(1)
    {
        //
        // Turn on the LED.
        //
    	y = y>>1;
        ROM_GPIOPinWrite(GPIO_PORTF_BASE,RED_LED|BLUE_LED|GREEN_LED,y);

        //
        // Delay for a bit.
        //
        for(ulLoop = 0; ulLoop < 200000; ulLoop++)
        {
        	x = x*x*x*x;
        }

        //
        // Turn off the LED.
        //
        ROM_GPIOPinWrite(GPIO_PORTF_BASE,RED_LED|BLUE_LED|GREEN_LED,~y);

        //
        // Delay for a bit.
        //
        for(ulLoop = 0; ulLoop < 200000; ulLoop++)
        {
        	x = x*x*x*x;
        }
        if (y==0) y = 0x49249249;
    }
}


