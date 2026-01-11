#include <iostream>
#include <thread>
// alle threads haben timeslots und wechseln sich ab
// bei timer interrupt, thread von running zu ready und zustand(PC) wird gespeichert und wird von scheduler verursacht
void kleinbuch() {
    for (char c = 'a'; c <= 'z'; ++c) { 
    std::cout << c << " ";
    }
}

void zahl() {
    for (int i = 0; i <= 32; ++i) {
    std::cout << i << " ";
    }
}

void großbuch() {
    for (char c = 'A'; c <= 'Z'; ++c) { 
    std::cout << c << " "; 
    }
}

int main() {
    std::thread t1(kleinbuch);
    std::thread t2(zahl);
    std::thread t3(großbuch);

    t1.join(); 
    t2.join(); 
    t3.join();

    std::cout << std::endl;
    return 0;
}