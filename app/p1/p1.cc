// EPOS Scheduler Test Program

#include <machine/display.h>
#include <time.h>
#include <synchronizer.h>
#include <process.h>

using namespace EPOS;

Thread * thread[6];

OStream cout;

int cpuBoundFunc();
int ioBoundFunc();

int main()
{
    cout << "Scheduler test" << endl;

    thread[0] = new Thread(&cpuBoundFunc);
    thread[1] = new Thread(&ioBoundFunc);
    thread[2] = new Thread(&cpuBoundFunc);
    thread[3] = new Thread(&ioBoundFunc);
    thread[4] = new Thread(&cpuBoundFunc);
    thread[5] = new Thread(&ioBoundFunc);

    cout << "Threads created..." << endl;

    for(int i = 0; i < 6; i++) {
        thread[i]->join();

        if (i % 2 == 1)
            cout << "IO Bound Thread " << thread[i] << " finished with priority: " << thread[i]->priority()<< endl;
        else 
            cout << "CPU Bound Thread " << thread[i] << " finished with priority: " << thread[i]->priority()<< endl;
    }

    for(int i = 0; i < 2; i++)
        delete thread[i];

    cout << "The end!" << endl;

    return 0;
}

int cpuBoundFunc()
{
    int n1 = 0, n2 = 1, result;
    for (size_t i = 0; i < 30000; i++)
    {
        if (i <= 1)
            result = i;
        else {
            result = n1 + n2;
            n1 = n2;
            n2 = result;
        }
    }

    cout << "Fibonacci of " << 10 << " is " << result << endl;
    return 0;
}

int ioBoundFunc()
{
    for (size_t i = 0; i < 4; i++)
    {
        cout << "IO bound process | Getting data from disk... " << endl;

        Alarm::delay(10000);

        cout << "IO bound process | Done getting data. " << endl;
    }

    return 0;
}
