#include "kernel.h"


//Old code. To be replaced.
void enable_interrupt_controller() {
    REGS_IRQ->irq0_enable_0 = SYS_TIMER_IRQ_1 | SYS_TIMER_IRQ_3;
}

void disable_interrupt_controller() {
    REGS_IRQ->irq0_enable_0 = 0;
}

/**
 * @brief This function runs on interupt detection. Stops kernel execution, runs and resumes kernel execution. See irqentry.S L: 154
 * 
 */
void handle_irq() {
    //genericHandler();
    //unsigned int irq = REGS_IRQ->irq0_pending_0;

    //while(irq) {
        //if (irq & SYS_TIMER_IRQ_1) {
            //irq &= ~SYS_TIMER_IRQ_1;

            //handle_timer_1();
        //}
    //}
}
