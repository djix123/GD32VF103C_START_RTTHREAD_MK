/*!
    \file  main.c
    \brief running led
    
    \version 2019-6-5, V1.0.0, firmware for GD32VF103
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "gd32vf103.h"
#include <stdio.h>

//#define __GD32VF103C_START__
//#define __SIPEED_LONGAN_NANO__

/* Built-in LED of GD32VF103C_START Boards is PA7 */
#ifdef __GD32VF103C_START__
#define LED_PIN GPIO_PIN_7
#define LED_GPIO_PORT GPIOA
#define LED_GPIO_CLK RCU_GPIOA
#endif

#ifdef __SIPEED_LONGAN_NANO__
#define LED_PIN GPIO_PIN_13
#define LED_GPIO_PORT GPIOC
#define LED_GPIO_CLK RCU_GPIOC

#define __LED_INVERT__
#endif



void delay_1ms(uint32_t count);
void led_on(void);
void led_off(void);

void led_init()
{
    /* enable the led clock */
    rcu_periph_clock_enable(LED_GPIO_CLK);
    /* configure led GPIO port */ 
    gpio_init(LED_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_PIN);
    /* Turn led off */
    led_off();
}

void led_off()
{
#ifndef __LED_INVERT__
    GPIO_BC(LED_GPIO_PORT) = LED_PIN;
#else
    GPIO_BOP(LED_GPIO_PORT) = LED_PIN;
#endif
}

void led_on()
{
#ifndef __LED_INVERT__
    GPIO_BOP(LED_GPIO_PORT) = LED_PIN;
#else
    GPIO_BC(LED_GPIO_PORT) = LED_PIN;
#endif
}
/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
int main(void)
{
    led_init();

    while(1)
    {
        /* turn on builtin led */
        led_on();
        delay_1ms(50);
        /* turn off uiltin led */
        led_off();
        delay_1ms(500);
    }
}


void delay_1ms(uint32_t count)
{
    uint64_t start_mtime, delta_mtime;
    uint64_t scaled_count = (SystemCoreClock / 4000) * count;

    // Don't start measuruing until we see an mtime tick
    uint64_t tmp = get_timer_value();
    do
    {
        start_mtime = get_timer_value();
    }
    while (start_mtime == tmp);

    do
    {
        delta_mtime = get_timer_value() - start_mtime;
    }
    while(delta_mtime < scaled_count);
}
