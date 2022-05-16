// EPOS IA32 PMU Mediator Declarations

#ifndef __rv32_hpm_h
#define __rv32_hpm_h

#include <architecture/cpu.h>
#include <architecture/pmu.h>
#include <machine/ic.h>
#include <utility/handler.h>

__BEGIN_SYS

class RV32_HPM_U: public PMU_Common
{
    private:
        typedef CPU::Reg32 Reg32;

    protected:
        static const unsigned int CHANNELS = 6;
        static const unsigned int FIXED = 0;
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

        // Useful bits in the PMCNTENSET register
        enum {                      // Description                          Type    Value after reset
            PMCNTENSET_C = 1 << 31, // Cycle counter enable                 r/w
        };

        // Useful bits in the PMOVSR register
        enum {                      // Description                          Type    Value after reset
            PMOVSR_C = 1 << 31,     // Cycle counter overflow clear         r/w
        };

        // Predefined architectural performance events
        enum {
            // Event
            L1I_REFILL                            = 0x01,
            L1I_TLB_REFILL                        = 0x02,
            L1D_REFILL                            = 0x03,
            L1D_ACCESS                            = 0x04,
            L1D_TLB_REFILL                        = 0x05,
        };

    public:
        RV32_HPM_U() {}

        static void config(Channel channel, const Event event, Flags flags = NONE) {
            assert((static_cast<unsigned int>(channel) < CHANNELS) && (static_cast<unsigned int>(event) < EVENTS));
            db<PMU>(TRC) << "PMU::config(c=" << channel << ",e=" << event << ",f=" << flags << ")" << endl;
            pmselr(channel);
            pmxevtyper(_events[event]);
            start(channel);
        }

        static Count read(Channel channel) {
            db<PMU>(TRC) << "PMU::read(c=" << channel << ")" << endl;
            pmselr(channel);
            return pmxevcntr();
        }

        static void write(Channel channel, Count count) {
            db<PMU>(TRC) << "PMU::write(ch=" << channel << ",ct=" << count << ")" << endl;
            pmselr(channel);
            pmxevcntr(count);
        }

        static void start(Channel channel) {
            db<PMU>(TRC) << "PMU::start(c=" << channel << ")" << endl;
            pmcntenset(pmcntenset() | (1 << channel));
        }

        static void stop(Channel channel) {
            db<PMU>(TRC) << "PMU::stop(c=" << channel << ")" << endl;
            pmcntenclr(pmcntenclr() | (1 << channel));
        }

        static void reset(Channel channel) {
            db<PMU>(TRC) << "PMU::reset(c=" << channel << ")" << endl;
            write(channel, 0);
        }

        static void init();

    private:
        static void pmcr(Reg32 reg) { ASM("mcr p15, 0, %0, c9, c12, 0\n\t" : : "r"(reg)); }
        static Reg32 pmcr() { Reg32 reg; ASM("mrc p15, 0, %0, c9, c12, 0\n\t" : "=r"(reg) : ); return reg; }

        static void pmcntenset(Reg32 reg) { ASM("mcr p15, 0, %0, c9, c12, 1\n\t" : : "r"(reg)); }
        static Reg32 pmcntenset() { Reg32 reg; ASM("mrc p15, 0, %0, c9, c12, 1\n\t" : "=r"(reg) : ); return reg; }

        static void pmcntenclr(Reg32 reg) { ASM("mcr p15, 0, %0, c9, c12, 2\n\t" : : "r"(reg)); }
        static Reg32 pmcntenclr() { Reg32 reg; ASM("mrc p15, 0, %0, c9, c12, 2\n\t" : "=r"(reg) : ); return reg; }

        static void pmovsr(Reg32 reg) { ASM("mcr p15, 0, %0, c9, c12, 3\n\t" : : "r"(reg)); }
        static Reg32 pmovsr() { Reg32 reg; ASM("mrc p15, 0, %0, c9, c12, 3\n\t" : "=r"(reg) : ); return reg; }

        static void pmselr(Reg32 reg) { ASM("mcr p15, 0, %0, c9, c12, 5\n\t" : : "r"(reg)); }
        static Reg32 pmselr() { Reg32 reg; ASM("mrc p15, 0, %0, c9, c12, 5\n\t" : "=r"(reg) : ); return reg; }

        static void pmxevtyper(const Reg32 reg) { ASM("mcr p15, 0, %0, c9, c13, 1\n\t" : : "r"(reg)); }
        static Reg32 pmxevtyper() { Reg32 reg; ASM("mrc p15, 0, %0, c9, c13, 1\n\t" : "=r"(reg) : ); return reg; }

        static void pmxevcntr(Reg32 reg) { ASM("mcr p15, 0, %0, c9, c13, 2\n\t" : : "r"(reg)); }
        static Reg32 pmxevcntr() { Reg32 reg; ASM("mrc p15, 0, %0, c9, c13, 2\n\t" : "=r"(reg) : ); return reg; }

    private:
        static const Event _events[EVENTS];
    };


    class PMU: private RV32_HPM_U
    {
        friend class CPU;

    private:
        typedef RV32_HPM_U Engine;

    public:
        using Engine::CHANNELS;
        using Engine::FIXED;
        using Engine::EVENTS;

        using Engine::Event;
        using Engine::Count;
        using Engine::Channel;

    public:
        PMU() {}

        using Engine::config;
        using Engine::read;
        using Engine::write;
        using Engine::start;
        using Engine::stop;
        using Engine::reset;

    private:
        static void init() { Engine::init(); }
};

__END_SYS

#endif
