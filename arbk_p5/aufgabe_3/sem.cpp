#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Semaphore {
private:
    int count; // Anzahl der verfügbaren Ressourcen
    std::mutex mtx; // Mutex zum Schutz des Zählers
    std::condition_variable cv; // Bedingungsvariable zum Warten und Signalisieren

public:

    Semaphore(int m) : count(m) {}

    void warte() { 
        std::unique_lock<std::mutex> lock(mtx); // template für klasse mutex mit der lock objekt und den konstruktoraufruf durch mtx
        while (count == 0) {
            cv.wait(lock); // lock hat intern zeiger und zeigt im ram die adresse des mutex an
        }
        --count;
        }

    void los() { 
        std::lock_guard<std::mutex> lock(mtx);
        count++;
        cv.notify_one(); // Weckt einen wartenden Thread auf 
    }
};

Semaphore s(1); 

void kleinbuch() {
    s.warte();
    for (char c = 'a'; c <= 'z'; ++c) { std::cout << c << " "; }
    std::cout << std::endl;
    s.los();
}

void zahl() {
    s.warte();
    for (int i = 0; i <= 32; ++i) { std::cout << i << " "; }
    std::cout << std::endl;
    s.los();
}

void großbuch() {
    s.warte();
    for (char c = 'A'; c <= 'Z'; ++c) { std::cout << c << " "; }
    std::cout << std::endl;
    s.los();
}

int main() {
    std::thread t1(kleinbuch);
    std::thread t2(zahl);
    std::thread t3(großbuch);

    t1.join();
    t2.join(); 
    t3.join();

    return 0;
}