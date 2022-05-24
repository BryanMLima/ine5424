// EPOS Segment Test Program

#include <memory.h>
#include <machine/flash.h>

using namespace EPOS;

const unsigned ES1_SIZE = 100;
const unsigned ES2_SIZE = 200;

int main()
{
    OStream cout;

    cout << "Flash test" << endl;

    cout << "My address space's page directory is located at " << reinterpret_cast<void *>(MMU::current()) << "" << endl;
    Address_Space self(MMU::current());

    cout << "Creating two extra flash segments:" << endl;
    Segment * es1 = new (FLASH) Segment(ES1_SIZE, Segment::Flags::SYS);
    Segment * es2 = new (FLASH) Segment(ES2_SIZE, Segment::Flags::SYS);
    cout << "  extra segment 1 => " << ES1_SIZE << " bytes, done!" << endl;
    cout << "  extra segment 2 => " << ES2_SIZE << " bytes, done!" << endl;

    cout << "Attaching flashes:" << endl;
    CPU::Log_Addr * extra1 = self.attach(es1);
    CPU::Log_Addr * extra2 = self.attach(es2);
    cout << "  extra flash 1 => " << extra1 << " done!" << endl;
    cout << "  extra flash 2 => " << extra2 << " done!" << endl;

    cout << "Clearing flashes:";
    memset(extra1, 0, ES1_SIZE);
    memset(extra2, 0, ES2_SIZE);
    cout << "  done!" << endl;

    cout << "Detaching flashes:";
    self.detach(es1);
    self.detach(es2);
    cout << "  done!" << endl;

    cout << "Deleting flashes:";
    delete es1;
    delete es2;
    cout << "  done!" << endl;

    cout << "I'm done, bye!" << endl;

    return 0;
}
