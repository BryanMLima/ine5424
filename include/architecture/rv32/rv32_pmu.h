// EPOS IA32 PMU Mediator Declarations

#ifndef __rv32_pmu_h
#define __rv32_pmu_h

#include <architecture/cpu.h>
#include <architecture/pmu.h>
#include <machine/ic.h>
#include <utility/handler.h>

__BEGIN_SYS

class RV32_PMU_U: public PMU_Common
{
    private:
        typedef CPU::Reg32 Reg32;

    protected:
        static const unsigned int EVENTS = 93; // 54 if A53

    public:
        // Useful bits in the PMCR register
        enum {                      // Description                          Type    Value after reset
            PMCR_E = 1 << 0,        // Enable all counters                  r/w
            PMCR_P = 1 << 1,        // Reset event counters                 r/w
            PMCR_C = 1 << 2,        // Cycle counter reset                  r/w
            PMCR_D = 1 << 3,        // Enable cycle counter prescale (1/64) r/w
            PMCR_X = 1 << 4,        // Export events                        r/w
        };

    public:
        RV32_PMU_U() {}

        static void init();

    private:
        static const Event _events[EVENTS];
    };


    class PMU: private RV32_PMU_U
    {
        friend class CPU;

    private:
        typedef RV32_PMU_U Engine;

    public:
        using Engine::EVENTS;

        using Engine::Event;
        using Engine::Count;
        using Engine::Channel;

    public:
        PMU() {}

    private:
        static void init() { Engine::init(); }
};

__END_SYS

#endif
