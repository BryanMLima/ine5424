// EPOS Flash Memory Implementation

#include <utility/heap.h>
#include <memory.h>
#include <machine/flash.h>

__BEGIN_SYS

Segment * Flash_Base::_segment;
Heap * Flash_Base::_heap;

__END_SYS
