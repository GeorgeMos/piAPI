#include "io.h"

// GPIO

void mmio_write(long reg, unsigned int val) { *(volatile unsigned int *)reg = val; }
unsigned int mmio_read(long reg) { return *(volatile unsigned int *)reg; }





//Functions I made
unsigned int gpio_read(unsigned int pin_number){
   unsigned int val = mmio_read(GPLEV0);
   val >>= pin_number;  //Shift val to the right (Target bis is now LSB)
   val &= 0x00000001;   //AND all the other bits with 0 except the target bit (Left with 0 or 1 as LSB)

   return val;
}

//PWM. See BCM2711 Manual page 128
//WIP
void gpio_pwm0_set(unsigned int pin_number, unsigned int value){
    mmio_write(PWM0+PWM_CTL, 0x0001);     //0000 0000 0000 0001
    mmio_write(PWM0 + PWM_RNG1, 0xFF);
    mmio_write(PWM0 + PWM_DAT1, 0x000000F);
    mmio_write(PWM0 + PWM_FIF1, 0x000000F);
}

//----------------


unsigned int gpio_call(unsigned int pin_number, unsigned int value, unsigned int base, unsigned int field_size, unsigned int field_max) {
    unsigned int field_mask = (1 << field_size) - 1;
  
    if (pin_number > field_max) return 0;
    if (value > field_mask) return 0; 

    unsigned int num_fields = 32 / field_size;
    unsigned int reg = base + ((pin_number / num_fields) * 4);
    unsigned int shift = (pin_number % num_fields) * field_size;

    unsigned int curval = mmio_read(reg);
    curval &= ~(field_mask << shift);
    curval |= value << shift;
    mmio_write(reg, curval);

    return 1;
}

unsigned int gpio_set     (unsigned int pin_number, unsigned int value) { return gpio_call(pin_number, value, GPSET0, 1, GPIO_MAX_PIN); }
unsigned int gpio_clear   (unsigned int pin_number, unsigned int value) { return gpio_call(pin_number, value, GPCLR0, 1, GPIO_MAX_PIN); }
unsigned int gpio_pull    (unsigned int pin_number, unsigned int value) { return gpio_call(pin_number, value, GPPUPPDN0, 2, GPIO_MAX_PIN); }
unsigned int gpio_function(unsigned int pin_number, unsigned int value) { return gpio_call(pin_number, value, GPFSEL0, 3, GPIO_MAX_PIN); }

void gpio_useAsAlt0(unsigned int pin_number) {
    gpio_pull(pin_number, Pull_None);
    gpio_function(pin_number, GPIO_FUNCTION_ALT0);
}

void gpio_useAsAlt3(unsigned int pin_number) {
    gpio_pull(pin_number, Pull_None);
    gpio_function(pin_number, GPIO_FUNCTION_ALT3);
}

void gpio_useAsAlt5(unsigned int pin_number) {
    gpio_pull(pin_number, Pull_None);
    gpio_function(pin_number, GPIO_FUNCTION_ALT5);
}

void gpio_initOutputPinWithPullNone(unsigned int pin_number) {
    gpio_pull(pin_number, Pull_None);
    gpio_function(pin_number, GPIO_FUNCTION_OUT);
}

void gpio_setPin(unsigned int pin_number, unsigned int onOrOff) {
    if (onOrOff) {
        gpio_set(pin_number, 1);
    } else {
        gpio_clear(pin_number, 1);
    }
}