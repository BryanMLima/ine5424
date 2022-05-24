// EPOS Flash Memory Mediator Declarations

#ifndef __flash_h
#define __flash_h

#include <utility/heap.h>
#include <memory.h>

__BEGIN_SYS

// TODO: This design is a bit weird, since this is not a Common package (it's a base indeed). It could be refactored to have an "Engine" or to just leave ::init() to be implemented by each Machine
class Flash_Base
{
    friend class System;

    friend void * ::operator new(size_t, const EPOS::Flash_Allocator &);
    friend void * ::operator new[](size_t, const EPOS::Flash_Allocator &);

protected:
    Flash_Base() {}

public:
    static void * alloc(unsigned int bytes) { return _heap->alloc(bytes); }

public:
    static Segment * _segment;
    static Heap * _heap;
};

__END_SYS

#endif

#if defined(__FLASH_H) && !defined(__flash_common_only__)
#include __FLASH_H

inline void * operator new(size_t bytes, const EPOS::Flash_Allocator & allocator) {
    return _SYS::Flash::_heap->alloc(bytes);
}

inline void * operator new[](size_t bytes, const EPOS::Flash_Allocator & allocator) {
    return _SYS::Flash::_heap->alloc(bytes);
}

#endif

