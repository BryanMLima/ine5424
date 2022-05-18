// EPOS rv32 PMU Mediator Declarations

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
        typedef CPU::Reg64 Reg64;

    public:
        // Instruction Commit Events, mhpeventX[7:0] = 0
        enum {
            EXCEPTION_TAKEN                            = 1 << 8,
            INTEGER_LOAD_INSTRUCTION_RETIRED           = 1 << 9,
            INTEGER_STORE_INSTRUCTION_RETIRED          = 1 << 10,
            ATOMIC_MEMORY_OPERATION_RETIRED            = 1 << 11,
            SYSTEM_INSTRUCTION_RETIRED                 = 1 << 12,
            INTEGER_ARITHMETIC_INSTRUCTION_RETIRED     = 1 << 13,
            CONDITIONAL_BRANCH_RETIRED                 = 1 << 14,
            JAL_INSTRUCTION_RETIRED                    = 1 << 15,
            JALR_INSTRUCTION_RETIRED                   = 1 << 16,
            INTEGER_MULTIPLICATION_INSTRUCTION_RETIRED = 1 << 17,
            INTEGER_DIVISION_INSTRUCTION_RETIRED       = 1 << 18,
        };

        // Microarchitectural Events , mhpeventX[7:0] = 1
        enum {
            LOAD_USE_INTERLOCK                         = 1 << 8,
            LONG_LATENCY_INTERLOCK                     = 1 << 9,
            CSR_READ_INTERLOCK                         = 1 << 10,
            INSTRUCTION_CACHE_ITIM_BUSY                = 1 << 11,
            DATA_CACHE_DTIM_BUSY                       = 1 << 12,
            BRANCH_DIRECTION_MISPREDICTION             = 1 << 13,
            BRANCH_JUMP_TARGET_MISPREDICTION           = 1 << 14,
            PIPELINE_FLUSH_FROM_CSR_WRITE              = 1 << 15,
            PIPELINE_FLUSH_FROM_OTHER_EVENT            = 1 << 16,
            INTEGER_MULTIPLICATION_INTERLOCK           = 1 << 17,
        };
        
        // Memory System Events, mhpeventX[7:0] = 2
        enum {
            INSTRUCTION_CACHE_MISS                      = 1 << 8,
            MEMORY_MAPPED_IO_ACCESS                     = 1 << 9,
        };

        RV32_PMU_U() {}

        static void init();

        static Reg64 read_mcycle() {
            Reg64 lower = mcycle() & 0x0000ffff;
            Reg32 upper = mcycleh();
            return upper | lower;
        }

        static Reg64 read_minstret() {
            long lower = minstret() & 0x0000ffff;
            long upper = minstreth();
            return upper | lower;
        }

        static Reg64 read_mhpmcounter3() {
            long lower = mhpmcounter3() & 0x0000ffff;
            long upper = mhpmcounter3h();
            return upper | lower;
        }

        static Reg64 read_mhpmcounter4() {
            long lower = mhpmcounter4() & 0x0000ffff;
            long upper = mhpmcounter4h();
            return upper | lower;
        }

        static void write_mhpmcounter3(Reg64 value) {
            mhpmcounter3(value & 0x0000ffff);
            mhpmcounter3h(value & 0xffff0000);
        }

        static void write_mhpmcounter4(Reg64 value) {
            mhpmcounter4(value & 0x0000ffff);
            mhpmcounter4h(value & 0xffff0000);
        }

        static Reg32 read_mhpmevent3() {
            return mhpmevent3();
        }

        static Reg32 read_mhpmevent4() {
            return mhpmevent4();
        }

        static void write_mhpmevent3(Reg32 r) {
            mhpmevent3(r);
        }

        static void write_mhpmevent4(Reg32 r) {
            mhpmevent4(r);
        }

    private:
        static Reg64 mhpmcounter3() { Reg64 reg; ASM("csrr %0, mhpmcounter3\n\t" : "=r"(reg) : ); return reg; }
        static void mhpmcounter3(Reg64 r) {  ASM("csrw mhpmcounter3, %0" : : "r"(r) :); }

        static Reg32 mhpmcounter3h() { Reg32 reg; ASM("csrr %0, mhpmcounter3h\n\t" : "=r"(reg) : ); return reg; }
        static void mhpmcounter3h(Reg32 r) {  ASM("csrw mhpmcounter3h, %0" : : "r"(r) :); }

        static Reg64 mhpmcounter4() { Reg64 reg; ASM("csrr %0, mhpmcounter4\n\t" : "=r"(reg) : ); return reg; }
        static void mhpmcounter4(Reg64 r) {  ASM("csrw mhpmcounter4, %0" : : "r"(r) :); }

        static Reg32 mhpmcounter4h() { Reg32 reg; ASM("csrr %0, mhpmcounter4h\n\t" : "=r"(reg) : ); return reg; }
        static void mhpmcounter4h(Reg32 r) {  ASM("csrw mhpmcounter4h, %0" : : "r"(r) :); }

        static Reg32 mhpmevent3() { Reg32 reg; ASM("csrr %0, mhpmevent3\n\t" : "=r"(reg) : ); return reg; }
        static void mhpmevent3(Reg32 r) {  ASM("csrw mhpmevent3, %0" : : "r"(r) :); }

        static Reg32 mhpmevent4() { Reg32 reg; ASM("csrr %0, mhpmevent4\n\t" : "=r"(reg) : ); return reg; }
        static void mhpmevent4(Reg32 r) {  ASM("csrw mhpmevent4, %0" : : "r"(r) :); }

        static Reg64 minstret() { Reg64 reg; ASM("csrr %0, minstret\n\t" : "=r"(reg) : ); return reg; }
        static Reg32 minstreth() { Reg32 reg; ASM("csrr %0, minstreth\n\t" : "=r"(reg) : ); return reg; }

        static Reg64 mcycle() { Reg64 reg; ASM("csrr %0, mcycle\n\t" : "=r"(reg) : ); return reg; }
        static Reg32 mcycleh() { Reg32 reg; ASM("csrr %0, mcycleh\n\t" : "=r"(reg) : ); return reg; }
    };

__END_SYS

#endif
