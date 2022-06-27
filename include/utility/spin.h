// EPOS Spin Lock Utility Declarations

#ifndef __spin_h
#define __spin_h

#include <architecture.h>

__BEGIN_UTIL

// Forwarder to the running thread id
class This_Thread
{
public:
    static volatile CPU::Reg id();
    static void not_booting() { _not_booting = true; }

private:
    static bool _not_booting;
};

// Recursive Spin Lock
class Spin
{
public:
    Spin(): _level(0), _owner(0) {}

    void acquire() {
        unsigned int me = This_Thread::id();

        while(CPU::cas(_owner, 0U, me) != me);
        _level++;

        db<Spin>(TRC) << "Spin::acquire[this=" << this << ",id=" << hex << me << "]() => {owner=" << _owner << dec << ",level=" << _level << "}" << endl;
    }

    void release() {
        db<Spin>(TRC) << "Spin::release[this=" << this << "]() => {owner=" << hex << _owner << dec << ",level=" << _level << "}" << endl;

        if(--_level <= 0) {
    	    _level = 0;
            _owner = 0;
    	}
    }

    volatile bool taken() const { return (_owner != 0); }

private:
    volatile int _level;
    volatile unsigned int _owner;
    // volatile unsigned int __attribute__((aligned(8))) _owner;
};

// Flat Spin Lock
class Simple_Spin
{
public:
    Simple_Spin(): _locked(false) {}

    void acquire() {
        while(CPU::tsl(_locked));

        db<Spin>(TRC) << "Spin::acquire[SPIN=" << this << "]()" << endl;
    }

    void release() {
        _locked = 0;

        db<Spin>(TRC) << "Spin::release[SPIN=" << this << "]()}" << endl;
    }

private:
    // volatile bool _locked;
    volatile bool __attribute__((aligned(4))) _locked;
};

class Atomic_Spin
{
public:
    Atomic_Spin(): _locked(false) {}

    void acquire() {
        ASM("       li             t0, 1          \n");
        ASM("again: ld             t1, (%0)       \n" :: "r"(&_locked));
        ASM("       bnez           t1, again      \n");
        ASM("       amoswap.d.aq   t1, t0, (%0)   \n" :: "r"(&_locked));
        ASM("       bnez           t1, again      \n");

        db<Spin>(TRC) << "Spin::acquire[SPIN=" << this << "]()" << endl;
    }

    void release() {
        ASM("amoswap.d.rl x0, x0, (%0) \n" :: "r"(&_locked));

        db<Spin>(TRC) << "Spin::release[SPIN=" << this << "]()}" << endl;
    }

private:
    volatile bool _locked;
};

__END_UTIL

#endif
