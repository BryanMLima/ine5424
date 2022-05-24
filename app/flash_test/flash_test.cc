// EPOS Segment Test Program

#include <memory.h>
#include <machine/flash.h>

using namespace EPOS;

int main()
{
    OStream cout;

    cout << "          Flash test" << endl;
    cout << "Flash base address: " << CPU::Phy_Addr(Traits<Flash>::ADDRESS) << endl;
    cout << "        Flash size: " << CPU::Phy_Addr(Traits<Flash>::SIZE) << " -> " << Traits<Flash>::SIZE << " bytes" << endl;

    int *array = new (FLASH) int[3] {1, 2, 3};

    cout << "         Array addr " << array << endl;
    cout << "      Array[0] addr " << &array[0] << endl;
    cout << "      Array[1] addr " << &array[1] << endl;
    cout << "      Array[2] addr " << &array[2] << endl;

    cout << " Finished, bye!" << endl;

    return 0;
}