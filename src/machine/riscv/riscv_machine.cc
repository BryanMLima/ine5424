// EPOS RISC-V Mediator Implementation

#include <machine/machine.h>
#include <machine/display.h>

__BEGIN_SYS

void Machine::panic()
{
    CPU::int_disable();

    if(Traits<Display>::enabled)
        Display::puts("PANIC!\n");

    if(Traits<System>::reboot)
        reboot();
    else
        poweroff();
}

void Machine::reboot()
{
    if(Traits<System>::reboot) {
        db<Machine>(WRN) << "Machine::reboot()" << endl;

        CPU::Reg * reset = reinterpret_cast<CPU::Reg *>(Memory_Map::AON_BASE);
        reset[0] = 0x5555;

        while(true);
    } else {
        poweroff();
    }
}

void Machine::poweroff()
{
    db<Machine>(WRN) << "Machine::poweroff()" << endl;

        CPU::Reg * reset = reinterpret_cast<CPU::Reg *>(Memory_Map::AON_BASE);
        reset[0] = 0x5555;

    while(true);
}

__END_SYS
