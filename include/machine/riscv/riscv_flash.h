// EPOS PC Flash Memory Mediator Declarations

#ifndef __riscv_flash_h
#define __riscv_flash_h

#define __flash_common_only__
#include <machine/flash.h>
#undef __flash_common_only__

__BEGIN_SYS

class Flash: public Flash_Base
{
    friend class Machine;

private:
    static const unsigned int ADDRESS = Traits<Flash>::ADDRESS;
    static const unsigned int SIZE = Traits<Flash>::SIZE;

public:
    Flash() {}

private:
    static void init();
};

__END_SYS

#endif
