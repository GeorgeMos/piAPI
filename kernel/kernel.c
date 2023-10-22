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
        uart_hex(mmio_read(REGS_TIMER + TIMER_CLO));
        uart_writeText("\n");
        //uart_hex(gpio_read(4));
        //uart_writeText("\n");
        uart_update();
        //wait_msec(0x000000FF);
    }
}


void core0_main(void)
{
    gpio_function(12, 1);
    gpio_set(12, 1);
    unsigned int currTime = getTimer_32_lsb();
    unsigned int interval = 0x000FFFFF;
    unsigned int nextTime = currTime + interval;
    setTimer_compare_0(nextTime);
    unsigned int status = 1;
    while (1){
        if(getTimerStatus_match_0()){
            nextTime = getTimer_32_lsb() + interval;
            setTimer_compare_0(nextTime);
            if(status){
                gpio_clear(12, 1);
                status = 0;
            }
            else{
                gpio_set(12, 1);
                status = 1;
            }
        }
    }
}

void main(void)
{
    //start_core3(core3_main);      // Kick it off on core 3
    start_core1(core1_main);        // Kick it off on core 1

    core0_main();                 // Loop endlessly
}