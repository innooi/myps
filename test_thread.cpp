/*************************************************************************
	> File Name: test_thread.cpp
	> Author: 
	> Mail: 
	> Created Time: 二 10/27 17:07:39 2015
 ************************************************************************/

#include <iostream>
#include <thread>
#include <functional>
#include <memory>
using namespace std;

int main() {
    shared_ptr<int> sp;
    sp.reset();
    cout << sp.get();
    return 0;
}
