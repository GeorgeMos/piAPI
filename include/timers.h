#ifndef REGS_HEADER
#include "regs.h"
#define REGS_HEADER
#endif

#include "io.h"


//Get the lower 32 bits of the system timer
unsigned int getTimer_32_lsb(){
    return mmio_read(REGS_TIMER + TIMER_CLO);
}

//Get the higher 32 bits of the system timer
unsigned int getTimer_32_msb(){
    return mmio_read(REGS_TIMER + TIMER_CHI);
}

//Set compare values for timers 0-3
void setTimer_compare_0(unsigned int value){
    mmio_write(REGS_TIMER + TIMER_C0, value);
}

void setTimer_compare_1(unsigned int value){
    mmio_write(REGS_TIMER + TIMER_C1, value);
}

void setTimer_compare_2(unsigned int value){
    mmio_write(REGS_TIMER + TIMER_C2, value);
}

void setTimer_compare_3(unsigned int value){
    mmio_write(REGS_TIMER + TIMER_C3, value);
}


//Get Match Results
unsigned int getTimerStatus_match_0(){
    unsigned int csStat = mmio_read(REGS_TIMER + TIMER_CS);
    //csStat >>= 0;
    csStat &= 0x1;
    return csStat;
}

unsigned int getTimerStatus_match_1(){
    unsigned int csStat = mmio_read(REGS_TIMER + TIMER_CS);
    csStat >>= 1;
    csStat &= 0x1;
    return csStat;
}

unsigned int getTimerStatus_match_2(){
    unsigned int csStat = mmio_read(REGS_TIMER + TIMER_CS);
    csStat >>= 2;
    csStat &= 0x1;
    return csStat;
}

unsigned int getTimerStatus_match_3(){
    unsigned int csStat = mmio_read(REGS_TIMER + TIMER_CS);
    csStat >>= 3;
    csStat &= 0x1;
    return csStat;
}