// EPOS RISC V Initialization

#include <machine.h>

__BEGIN_SYS

void Machine::pre_init(System_Info * si)
{
    db<Init, Machine>(TRC) << "Machine::pre_init()" << endl;
    if(Traits<System>::multicore && (CPU::id() == 0))
        smp_barrier_init(Traits<Build>::CPUS);

    if(CPU::id() == 0)
        Display::init();

    db<Init, Machine>(TRC) << "Machine::pre_init() finished" << endl;
}

void Machine::init()
{
    db<Init, Machine>(TRC) << "Machine::init()" << endl;

    if(Traits<IC>::enabled)
        IC::init();

    if(Traits<Timer>::enabled)
        Timer::init();
}

__END_SYS
