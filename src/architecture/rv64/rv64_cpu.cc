// EPOS RISC-V 64 CPU Mediator Implementation

#include <architecture/rv64/rv64_cpu.h>
#include <system.h>

__BEGIN_SYS

unsigned int CPU::_cpu_clock;
unsigned int CPU::_bus_clock;

void CPU::Context::save() volatile
{
    ASM("       sd       x1,     0(a0)           \n");     // push RA as PC
    ASM("       csrr     x3,   mstatus           \n");
    ASM("       sd       x3,     8(sp)           \n");     // push ST
    ASM("       sd       x1,    16(sp)           \n");     // push RA
    ASM("       sd       x5,    24(sp)           \n");     // push x5-x31
    ASM("       sd       x6,    32(sp)           \n");
    ASM("       sd       x7,    40(sp)           \n");
    ASM("       sd       x8,    48(sp)           \n");
    ASM("       sd       x9,    56(sp)           \n");
    ASM("       sd      x10,    64(sp)           \n");
    ASM("       sd      x11,    72(sp)           \n");
    ASM("       sd      x12,    80(sp)           \n");
    ASM("       sd      x13,    88(sp)           \n");
    ASM("       sd      x14,    96(sp)           \n");
    ASM("       sd      x15,   104(sp)           \n");
    ASM("       sd      x16,   112(sp)           \n");
    ASM("       sd      x17,   120(sp)           \n");
    ASM("       sd      x18,   128(sp)           \n");
    ASM("       sd      x19,   136(sp)           \n");
    ASM("       sd      x20,   144(sp)           \n");
    ASM("       sd      x21,   152(sp)           \n");
    ASM("       sd      x22,   160(sp)           \n");
    ASM("       sd      x23,   168(sp)           \n");
    ASM("       sd      x24,   176(sp)           \n");
    ASM("       sd      x25,   184(sp)           \n");
    ASM("       sd      x26,   192(sp)           \n");
    ASM("       sd      x27,   200(sp)           \n");
    ASM("       sd      x28,   208(sp)           \n");
    ASM("       sd      x29,   216(sp)           \n");
    ASM("       sd      x30,   224(sp)           \n");
    ASM("       sd      x31,   232(sp)           \n");
    ASM("       ret                              \n");
}

// Context load does not verify if interrupts were previously enabled by the Context's constructor
// We are setting mstatus to MPP | MPIE, therefore, interrupts will be enabled only after mret
void CPU::Context::load() const volatile
{
    sp(Log_Addr(this));
    pop();
    iret();
}

void CPU::switch_context(Context ** o, Context * n)     // "o" is in a0 and "n" is in a1
{   
    // Push the context into the stack and update "o"
    Context::push();
    ASM("sd sp, 0(a0)");   // update Context * volatile * o, which is in a0

    // Set the stack pointer to "n" and pop the context from the stack
    ASM("mv sp, a1");   // "n" is in a1
    Context::pop();
    iret();
}

__END_SYS

