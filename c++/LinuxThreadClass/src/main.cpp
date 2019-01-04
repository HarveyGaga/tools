//============================================================================
// Name        : thread.cpp
// Author      : Harvey
// Version     :
// Copyright   : copyright@Harvey.Ltd
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unistd.h>
#include "common/thread.hpp"
using namespace std;

class MyThread: public Thread {
private:
    void Run() {
        for (int i = 0; i < 1; i++) {
            for (int j = 0; j < 500000000; j++) {
            }
            cout << "run:" << i << endl;
        }
    }

};

int main() {
    cout << "app start" << endl;

    MyThread t;
    t.Start();
    cout << t.GetState() << endl;
    sleep(1);
    cout << t.GetState() << endl;
    sleep(1);
    cout << t.GetState() << endl;
    t.Join();

    cout << "app exit" << endl;
    return 0;
}
