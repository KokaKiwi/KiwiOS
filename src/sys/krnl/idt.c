#include <idt.h>
#include <string.h>
#include <stdio.h>
#include <sys/io.h>

idt_entry_t kidt[IDTSIZE];
idt_ptr_t kidtr;
interrupt_handler interrupt_handlers[IDTSIZE];

void init_idt()
{
    memset(&interrupt_handlers, 0, sizeof(interrupt_handler) * IDTSIZE);

    // Remap IRQ table
    // + Remap ICW1
    outb(0x20, 0x11);   // master
    outb(0xA0, 0x11);   // slave
    
    // + Remap ICW2
    outb(0x21, 0x20);   // master
    outb(0xA1, 0x70);   // slave

    // + Remap ICW3
    outb(0x21, 0x04);   // master
    outb(0xA1, 0x02);   // slave
    
    // + Remap ICW4
    outb(0x21, 0x01);   // master
    outb(0xA1, 0x01);   // slave
    
    // + Interrupt mask
    outb(0x21, 0x0);    // master
    outb(0xA1, 0x0);    // slave

    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(0), INTGATE, &kidt[0]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(1), INTGATE, &kidt[1]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(2), INTGATE, &kidt[2]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(3), INTGATE, &kidt[3]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(4), INTGATE, &kidt[4]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(5), INTGATE, &kidt[5]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(6), INTGATE, &kidt[6]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(7), INTGATE, &kidt[7]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(8), INTGATE, &kidt[8]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(9), INTGATE, &kidt[9]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(10), INTGATE, &kidt[10]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(11), INTGATE, &kidt[11]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(12), INTGATE, &kidt[12]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(13), INTGATE, &kidt[13]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(14), INTGATE, &kidt[14]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(15), INTGATE, &kidt[15]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(16), INTGATE, &kidt[16]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(17), INTGATE, &kidt[17]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(18), INTGATE, &kidt[18]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(19), INTGATE, &kidt[19]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(20), INTGATE, &kidt[20]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(21), INTGATE, &kidt[21]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(22), INTGATE, &kidt[22]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(23), INTGATE, &kidt[23]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(24), INTGATE, &kidt[24]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(25), INTGATE, &kidt[25]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(26), INTGATE, &kidt[26]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(27), INTGATE, &kidt[27]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(28), INTGATE, &kidt[28]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(29), INTGATE, &kidt[29]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(30), INTGATE, &kidt[30]);
    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(31), INTGATE, &kidt[31]);

    init_idt_entry(0x08, (uint32_t) IRQ_HANDLER(0), INTGATE, &kidt[IRQ(0)]);
    init_idt_entry(0x08, (uint32_t) IRQ_HANDLER(1), INTGATE, &kidt[IRQ(1)]);
    init_idt_entry(0x08, (uint32_t) IRQ_HANDLER(2), INTGATE, &kidt[IRQ(2)]);
    init_idt_entry(0x08, (uint32_t) IRQ_HANDLER(3), INTGATE, &kidt[IRQ(3)]);
    init_idt_entry(0x08, (uint32_t) IRQ_HANDLER(4), INTGATE, &kidt[IRQ(4)]);
    init_idt_entry(0x08, (uint32_t) IRQ_HANDLER(5), INTGATE, &kidt[IRQ(5)]);
    init_idt_entry(0x08, (uint32_t) IRQ_HANDLER(6), INTGATE, &kidt[IRQ(6)]);
    init_idt_entry(0x08, (uint32_t) IRQ_HANDLER(7), INTGATE, &kidt[IRQ(7)]);
    init_idt_entry(0x08, (uint32_t) IRQ_HANDLER(8), INTGATE, &kidt[IRQ(8)]);
    init_idt_entry(0x08, (uint32_t) IRQ_HANDLER(9), INTGATE, &kidt[IRQ(9)]);
    init_idt_entry(0x08, (uint32_t) IRQ_HANDLER(10), INTGATE, &kidt[IRQ(10)]);
    init_idt_entry(0x08, (uint32_t) IRQ_HANDLER(11), INTGATE, &kidt[IRQ(11)]);
    init_idt_entry(0x08, (uint32_t) IRQ_HANDLER(12), INTGATE, &kidt[IRQ(12)]);
    init_idt_entry(0x08, (uint32_t) IRQ_HANDLER(13), INTGATE, &kidt[IRQ(13)]);
    init_idt_entry(0x08, (uint32_t) IRQ_HANDLER(14), INTGATE, &kidt[IRQ(14)]);
    init_idt_entry(0x08, (uint32_t) IRQ_HANDLER(15), INTGATE, &kidt[IRQ(15)]);

    init_idt_entry(0x08, (uint32_t) ISR_HANDLER(255), INTGATE, &kidt[255]);

    kidtr.base = IDTBASE;
    kidtr.limit = IDTSIZE * sizeof(idt_entry_t);

    memcpy((void *) kidtr.base, (void *) kidt, kidtr.limit);

    asm("lidtl (kidtr)");
}

void init_idt_entry(uint16_t select, uint32_t base, uint16_t flags, idt_entry_t *entry)
{
    entry->base_0_15 = (base & 0xffff);
    entry->base_16_31 = (base & 0xffff0000) >> 16;

    entry->select = select;
    entry->flags = flags;
}

void register_interrupt_handler(uint8_t no, interrupt_handler handler)
{
    interrupt_handlers[no] = handler;
}

void isr_handler(registers_t *regs)
{
    if(interrupt_handlers[regs->int_no])
    {
        interrupt_handlers[regs->int_no] (regs);
    }
    else
    {
        // Unhandled interrupt
    }
}

void irq_handler(registers_t *regs)
{
    if(regs->int_no >= 40)
    {
        outb(0xa0, 0x20);   // Send EOI signal
    }

    outb(0x20, 0x20);       // Send reset signal

    if(interrupt_handlers[regs->int_no])
    {
        interrupt_handlers[regs->int_no] (regs);
    }
}
