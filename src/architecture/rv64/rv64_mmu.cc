// EPOS RISC-V 32 MMU Mediator Implementation

#include <architecture/rv64/rv64_mmu.h>

__BEGIN_SYS

RV64S_MMU::List RV64S_MMU::_free[colorful * COLORS + 1];
RV64S_MMU::Page_Directory * RV64S_MMU::_master;

__END_SYS
