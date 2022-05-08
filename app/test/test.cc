#include <utility/ostream.h>
#include <machine/riscv/riscv_uart.h>

using namespace EPOS;

OStream cout;

int main()
{

    char p = 'h';
    init();
    put(p);
    p++;
    put(p);

    return 0;
}
