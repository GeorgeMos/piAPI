#include "../include/io.h"
#include "../include/multicore.h"
#include "kernel.h"
#include "../include/timers.h"
#include "../include/miniuart.h"

void wait_msec(unsigned int n)
{
    register unsigned long f, t, r;

    // Get the current counter frequency
    asm volatile ("mrs %0, cntfrq_el0" : "=r"(f));
    // Read the current counter
    asm volatile ("mrs %0, cntpct_el0" : "=r"(t));
    // Calculate expire value for counter
    t+=((f/1000)*n)/1000;
    do{asm volatile ("mrs %0, cntpct_el0" : "=r"(r));}while(r<t);
}

void core3_main(void)
{
    clear_core3();                // Only run once

    while (1) {
       
    }
}

void core2_main(void)
{
    clear_core2();                // Only run once
    while (1) {
       
    }

}

void core1_main(void)
{
    clear_core1();                // Only run once

    uart_init();
    
    //uart_hex(mmio_read(REGS_TIMER + TIMER_CLO));

    while (1) {
        uart_writeText("Timer Reg: ");
        uart_hex(mmio_read(REGS_TIMER + TIMER_CLO));
        uart_writeText("\tInterupt 0 Reg: ");
        uart_hex(mmio_read(ARMC_BASE + IRQ0_STATUS0));
        uart_writeText("\n");
        //uart_hex(gpio_read(4));
        //uart_writeText("\n");
        uart_update();
        //wait_msec(0x000000FF);
    }
}


void core0_main(void)
{
    //gpio_function(12, GPIO_FUNCTION_ALT0);  //Set pin 12 as pwm output (pin 12 has alt0 function PWM0 channel, BCM2711 Manual page 128)
    //gpio_set(12, 1);
    //gpio_pwm0_set(12, 100);
    setTimer_compare_0(0x00FFFFFF);
    while (1){
        if(getTimerStatus_match_0()){
            gpio_function(12, GPIO_FUNCTION_OUT);
            gpio_set(12, 1);
        }
    }
}

void main(void)
{
    //start_core3(core3_main);      // Kick it off on core 3
    start_core1(core1_main);        // Kick it off on core 1
    core0_main();                 // Loop endlessly
}