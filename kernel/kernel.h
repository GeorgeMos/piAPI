#ifndef REGS_HEADER
#include "../include/regs.h"
#define REGS_HEADER
#endif

void irq_init_vectors();
void irq_enable();
void irq_disable();
void enable_interrupt_controller();
void disable_interrupt_controller();

//System timer interupt handlers
void timer_0_interupt_handler();
void timer_1_interupt_handler();
void timer_2_interupt_handler();
void timer_3_interupt_handler();

void genericHandler();