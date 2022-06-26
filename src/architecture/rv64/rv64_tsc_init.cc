// EPOS ARMv7 Time-Stamp Counter Mediator Initialization

#include <machine/machine.h>
#include <machine/timer.h>

__BEGIN_SYS

void TSC::init()
{
    db<Init, TSC>(TRC) << "TSC::init()" << endl;

    if(CPU::id() == 0) {
        reg(MTIME) = 0;
    }
}

__END_SYS
