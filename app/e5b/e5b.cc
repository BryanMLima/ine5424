#include <utility/ostream.h>
#include <architecture/rv32/rv32_pmu.h>
#include <architecture/cpu.h>


using namespace EPOS;

OStream cout;

int main()
{
    CPU_Common::Reg64 teste = 0x00000000;

    RV32_PMU_U::write_mhpmevent3((RV32_PMU_U::read_mhpmevent3() & 0x00) | RV32_PMU_U::SYSTEM_INSTRUCTION_RETIRED);


    cout << "  mcycle value: " << RV32_PMU_U::read_mcycle() << endl;
    cout << "minstret value: " << RV32_PMU_U::read_minstret() << endl;

    for (size_t i = 0; i < 100; i++)
    {
        RV32_PMU_U::read_mcycle();
    }
    
    cout << "mhpmcounter3: " << RV32_PMU_U::read_mhpmcounter3() << endl;
    cout << "mhpmevent3: " << RV32_PMU_U::read_mhpmevent3() << endl;
    // As we tested with multiple values, we can only assume it is "hard wired" to zero, as the manual mentions it. By that, we mean QEMU didn't implemented.

    return 0;
}