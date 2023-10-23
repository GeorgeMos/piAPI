#ifndef REGS_HEADER
#include "regs.h"
#define REGS_HEADER
#endif


void mmio_write(long reg, unsigned int val);
unsigned int mmio_read(long reg);
void gpio_useAsAlt0(unsigned int pin_number);
void gpio_useAsAlt3(unsigned int pin_number);
void gpio_useAsAlt5(unsigned int pin_number);

unsigned int gpio_set     (unsigned int pin_number, unsigned int value);
unsigned int gpio_clear   (unsigned int pin_number, unsigned int value);
unsigned int gpio_pull    (unsigned int pin_number, unsigned int value);
unsigned int gpio_function(unsigned int pin_number, unsigned int value);
unsigned int gpio_read(unsigned int pin_number);
void gpio_setPin(unsigned int pin_number, unsigned int onOrOff);
void gpio_pwm0_set(unsigned int pin_number, unsigned int value);