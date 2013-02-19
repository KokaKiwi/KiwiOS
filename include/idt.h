#ifndef IDT_H_
#define IDT_H_

#include "stdint.h"

#define IDTBASE                 0x0800
#define IDTSIZE                 256

#define INTGATE                 0x8e00
#define TRAPGATE                0xef00

#define IRQ(num)                (32+(num))
#define IRQ_HANDLER(num)        irq ## num
#define ISR_HANDLER(num)        isr ## num

#define PAGEFAULT_ISR           14

#define CLOCK_IRQ               IRQ(0)
#define KEYBOARD_IRQ            IRQ(1)

typedef struct _idt_entry_t idt_entry_t;
struct _idt_entry_t
{
    uint16_t base_0_15;
    uint16_t select;
    uint16_t flags;
    uint16_t base_16_31;
}__attribute__ ((packed));

typedef struct _idt_ptr_t idt_ptr_t;
struct _idt_ptr_t
{
    uint16_t limit;
    uint32_t base;
}__attribute__ ((packed));

typedef struct _registers_t registers_t;
struct _registers_t
{
    uint32_t ds;                                        // Data Segment
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;    // Pushed by pusha
    uint32_t int_no, err_code;                          // INT number and error code
    uint32_t eip, cs, eflags, useresp, ss;              // Pushed by processor
};

typedef void (*interrupt_handler)(registers_t *);

void init_idt(void);
void init_idt_entry(uint16_t, uint32_t, uint16_t, idt_entry_t *);
void register_interrupt_handler(uint8_t, interrupt_handler);

extern idt_entry_t kidt[];
extern idt_ptr_t kidtr;

extern void ISR_HANDLER(0)(void);
extern void ISR_HANDLER(1)(void);
extern void ISR_HANDLER(2)(void);
extern void ISR_HANDLER(3)(void);
extern void ISR_HANDLER(4)(void);
extern void ISR_HANDLER(5)(void);
extern void ISR_HANDLER(6)(void);
extern void ISR_HANDLER(7)(void);
extern void ISR_HANDLER(8)(void);
extern void ISR_HANDLER(9)(void);
extern void ISR_HANDLER(10)(void);
extern void ISR_HANDLER(11)(void);
extern void ISR_HANDLER(12)(void);
extern void ISR_HANDLER(13)(void);
extern void ISR_HANDLER(14)(void);
extern void ISR_HANDLER(15)(void);
extern void ISR_HANDLER(16)(void);
extern void ISR_HANDLER(17)(void);
extern void ISR_HANDLER(18)(void);
extern void ISR_HANDLER(19)(void);
extern void ISR_HANDLER(20)(void);
extern void ISR_HANDLER(21)(void);
extern void ISR_HANDLER(22)(void);
extern void ISR_HANDLER(23)(void);
extern void ISR_HANDLER(24)(void);
extern void ISR_HANDLER(25)(void);
extern void ISR_HANDLER(26)(void);
extern void ISR_HANDLER(27)(void);
extern void ISR_HANDLER(28)(void);
extern void ISR_HANDLER(29)(void);
extern void ISR_HANDLER(30)(void);
extern void ISR_HANDLER(31)(void);

extern void ISR_HANDLER(255)(void);

extern void IRQ_HANDLER(0)(void);
extern void IRQ_HANDLER(1)(void);
extern void IRQ_HANDLER(2)(void);
extern void IRQ_HANDLER(3)(void);
extern void IRQ_HANDLER(4)(void);
extern void IRQ_HANDLER(5)(void);
extern void IRQ_HANDLER(6)(void);
extern void IRQ_HANDLER(7)(void);
extern void IRQ_HANDLER(8)(void);
extern void IRQ_HANDLER(9)(void);
extern void IRQ_HANDLER(10)(void);
extern void IRQ_HANDLER(11)(void);
extern void IRQ_HANDLER(12)(void);
extern void IRQ_HANDLER(13)(void);
extern void IRQ_HANDLER(14)(void);
extern void IRQ_HANDLER(15)(void);

#endif
