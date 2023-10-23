/**
 * This header file provides addresses for all the memmory mapped io, CPU Peripheral bases and CPU registers
 * 
 */


#define PERIPHERAL_BASE 0xFE000000
#define LEGACY_BASE     0x7E000000
#define SAFE_ADDRESS    0x00400000 // Somewhere safe to store a lot of data

#define CLOCKHZ 1000000

#define REGS_TIMER  PERIPHERAL_BASE + 0x00003000

#define REGS_IRQ ((arm_irq_regs *)(PERIPHERAL_BASE + 0x0000B200))
#define AUX_MU_BAUD(baud) ((AUX_UART_CLOCK/(baud*8))-1)

//Interupt registters base addresses

//See BCM2711 Manual page 92
#define ARM_LOCAL 0x4c0000000

//See BCM2711 Manual page 100
#define ARMC 0x7e00b000

enum {
    GPFSEL0         = PERIPHERAL_BASE + 0x200000,
    GPSET0          = PERIPHERAL_BASE + 0x20001C,
    GPCLR0          = PERIPHERAL_BASE + 0x200028,
    GPPUPPDN0       = PERIPHERAL_BASE + 0x2000E4,
    GPLEV0          = PERIPHERAL_BASE + 0x200034,
    PWM0            = PERIPHERAL_BASE + 0x20C000,
};

enum {
    PWM_CTL         = 0x00, //pwm control
    PWM_STA         = 0x04, //pwm status
    PWM_RNG1        = 0x10, //pwm channel 1 range
    PWM_DAT1        = 0x14,
    PWM_FIF1        = 0x18
};

enum {
    GPIO_MAX_PIN       = 53,
    GPIO_FUNCTION_OUT  = 1,
    GPIO_FUNCTION_ALT5 = 2,
    GPIO_FUNCTION_ALT3 = 7,
    GPIO_FUNCTION_ALT0 = 4
};

enum {
    Pull_None = 0,
    Pull_Down = 2,
    Pull_Up = 1
};

// UART

enum {
    AUX_BASE        = PERIPHERAL_BASE + 0x215000,
    AUX_IRQ         = AUX_BASE,
    AUX_ENABLES     = AUX_BASE + 4,
    AUX_MU_IO_REG   = AUX_BASE + 64,
    AUX_MU_IER_REG  = AUX_BASE + 68,
    AUX_MU_IIR_REG  = AUX_BASE + 72,
    AUX_MU_LCR_REG  = AUX_BASE + 76,
    AUX_MU_MCR_REG  = AUX_BASE + 80,
    AUX_MU_LSR_REG  = AUX_BASE + 84,
    AUX_MU_MSR_REG  = AUX_BASE + 88,
    AUX_MU_SCRATCH  = AUX_BASE + 92,
    AUX_MU_CNTL_REG = AUX_BASE + 96,
    AUX_MU_STAT_REG = AUX_BASE + 100,
    AUX_MU_BAUD_REG = AUX_BASE + 104,
    AUX_UART_CLOCK  = 500000000,
    UART_MAX_QUEUE  = 16 * 1024
};


//System Timer Registers. BCM2711 manual page 142
enum {
    TIMER_CLO       = 0x04, //Lower 32 bits of the timer
    TIMER_CHI       = 0x08, //Higher 32 bits of the timer
    TIMER_CS        = 0x00, //Timer status register
    TIMER_C0        = 0x0C, //Timer compare 0
    TIMER_C1        = 0x10, //Timer compare 1
    TIMER_C2        = 0x14, //Timer compare 2
    TIMER_C3        = 0x18  //Timer compare 3
};

//TIMERS
struct timer_regs {
    volatile unsigned int control_status;
    volatile unsigned int counter_lo;
    volatile unsigned int counter_hi;
    volatile unsigned int compare[4];
};

struct arm_irq_regs_2711 {
    volatile unsigned int irq0_pending_0;
    volatile unsigned int irq0_pending_1;
    volatile unsigned int irq0_pending_2;
    volatile unsigned int res0;
    volatile unsigned int irq0_enable_0;
    volatile unsigned int irq0_enable_1;
    volatile unsigned int irq0_enable_2;
    volatile unsigned int res1;
    volatile unsigned int irq0_disable_0;
    volatile unsigned int irq0_disable_1;
    volatile unsigned int irq0_disable_2;
};

typedef struct arm_irq_regs_2711 arm_irq_regs;


enum vc_irqs {
    SYS_TIMER_IRQ_0 = 1,
    SYS_TIMER_IRQ_1 = 2,
    SYS_TIMER_IRQ_2 = 4,
    SYS_TIMER_IRQ_3 = 8,
    //AUX_IRQ = (1 << 29)
};

