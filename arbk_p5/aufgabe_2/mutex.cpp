#include <iostream>
#include <thread>
#include <mutex>

std::mutex m;
void kleinbuch() {
    m.lock(); 
    for (char c = 'a'; c <= 'z'; ++c) { std::cout << c << " "; }
    std::cout << std::endl;
    m.unlock(); // Gibt den Weg für den nächsten Thread frei (Zustand: ready)
}

void zahl() {
    m.lock();// thread warten bis mutex frei ist (Zustand: blocked)
    for (int i = 0; i <= 32; ++i) { std::cout << i << " "; }
    std::cout << std::endl;
    m.unlock();
}

void großbuch() {
    m.lock();
    for (char c = 'A'; c <= 'Z'; ++c) { std::cout << c << " "; }
    std::cout << std::endl;
    m.unlock();
}

int main() {
    // Ein TCB Steckbrief mit der Startadresse wird erstellt
    // Der Thread wechselt von 'nicht existent' zu 'Ready'.
    std::thread t1(kleinbuch); 
    // Auch angereiht im ready-queue
    // Er wartet dort auf eine freie CPU (Zustand: Ready)
    std::thread t2(zahl);
    std::thread t3(großbuch);
    // Scheduler sieht ready-queue und nimmt eine adresse (zb. von t1)
    // und schreibt sie in den PC (Program Counter) eines Kerns.
    // wechselt der Thread zu 'Running'.


    t1.join(); // Wartet bis der Thread fertig ist
    t2.join(); 
    t3.join();

    return 0;
}