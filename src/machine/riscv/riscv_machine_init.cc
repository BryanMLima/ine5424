// EPOS RISC V Initialization

#include <machine.h>

__BEGIN_SYS

void Machine::pre_init(System_Info * si)
{
    Display::init();

    db<Init, Machine>(TRC) << "Machine::pre_init()" << endl;
}


void Machine::init()
{
    db<Init, Machine>(TRC) << "Machine::init()" << endl;

    if(Traits<IC>::enabled)
        IC::init();

    if(Traits<Timer>::enabled)
        Timer::init();
#ifdef __FLASH_H
    if(Traits<Flash>::enabled)
        Flash::init();
#endif
}

__END_SYS
