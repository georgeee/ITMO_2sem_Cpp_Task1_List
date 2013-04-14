/* 
 * File:   main.cpp
 * Author: georgeee
 *
 * Created on 7 Апрель 2013 г., 15:16
 */

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cassert>
#include "../list.hpp"

using namespace std;

#define COUNT (int)(1e5)

int main() {
    srand(time(0));
    rand();
    for(int i=0; i<10; i++){
        List<int> l;
        for(int i=0; i<rand()%COUNT+COUNT/2; i++){
            l.push_back(i);
        }00
        for(int i=0; i<rand()%(l.size()/2-5)+l.size()/2; i++)
            assert(i==l.pop_front());
    }
    return 0;
}
