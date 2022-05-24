// EPOS PC Flash Memory Initialization

#include <machine/flash.h>
#include <system.h>
#include <memory.h>

__BEGIN_SYS

void Flash::init()
{
    db<Init, Flash>(TRC) << "Flash::init(a=" << CPU::Phy_Addr(ADDRESS) << ",s=" << SIZE << ")" << endl;

    _segment = new (SYSTEM) Segment(CPU::Phy_Addr(ADDRESS), SIZE, MMU::Flags::FLASH);
    _heap = new (SYSTEM) Heap(Address_Space(MMU::current()).attach(_segment, ADDRESS), _segment->size());
}

__END_SYS
