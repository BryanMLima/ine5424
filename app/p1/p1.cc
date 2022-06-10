// EPOS Scheduler Test Program

#include <machine/display.h>
#include <time.h>
#include <synchronizer.h>
#include <process.h>

using namespace EPOS;

const int iterations = 10;

Mutex table;

Thread * phil[2];

OStream cout;

int func1();
int func2();

int main()
{
    // table.lock();
    _print("teste");

    cout << "P1:" << endl;

    phil[0] = new Thread(&func1);
    phil[1] = new Thread(&func2);

    cout << "The dinner is served ..." << endl;
    // table.unlock();

    for(int i = 0; i < 2; i++) {
        phil[i]->join();
        // table.lock();
        cout << " Thread " << phil[i] << "Finished" << endl;
        // table.unlock();
    }

    for(int i = 0; i < 2; i++)
        delete phil[i];

    cout << "The end!" << endl;

    return 0;
}

int func2()
{
    for (size_t i = 0; i < 10000; i++)
    {
        // table.lock();
        _print("Func 2\n");
        // table.unlock();
    }
    return 0;
}

int func1()
{
    int a = 0;
    for (size_t i = 0; i < 10000; i++)
    {
        // table.lock();
        a++;
        a--;
        // _print("Func 1");
        // table.unlock();
    }
    return 0;
}
