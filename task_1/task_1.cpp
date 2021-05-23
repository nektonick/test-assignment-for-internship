#include <iostream>
#include <time.h>
#include <windows.h>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>
#include <string> 

#define READERS_COUNT 5
#define WRITERS_COUNT 3
#define REPEATS_COUNT 2

// Время в милисекундах
#define READER_TIME 230
#define WRITER_TIME 450

std::shared_mutex mutex_;

void printTimeStamp() {
    SYSTEMTIME timeStamp;
    GetLocalTime(&timeStamp);
    printf("%02d:%02d:%02d.%03d",
        timeStamp.wHour, timeStamp.wMinute,
        timeStamp.wSecond, timeStamp.wMilliseconds);
}

std::mutex cout_mutex;
void log(const std::string& msg) {
    std::lock_guard<std::mutex> guard(cout_mutex);
    printTimeStamp();  std::cout << msg;
}


void write(int writers_num) {
    log(std::string(" Писатель ") + std::to_string(writers_num) + std::string(" обратился к файлу\n"));
    std::unique_lock<std::shared_mutex> lock(mutex_);
    log(std::string(" Писатель ") + std::to_string(writers_num) + std::string(" получил доступ к файлу\n"));
    std::this_thread::sleep_for(std::chrono::milliseconds(WRITER_TIME));
    log(std::string(" Писатель ") + std::to_string(writers_num) + std::string(" завершил работу\n"));
}

void read(int readers_num) {
    log(std::string(" Читатель ") + std::to_string(readers_num) + std::string(" обратился к файлу\n"));
    std::shared_lock<std::shared_mutex> lock(mutex_);
    log(std::string(" Читатель ") + std::to_string(readers_num) + std::string(" получил доступ к файлу\n"));
    std::this_thread::sleep_for(std::chrono::milliseconds(READER_TIME));
    log(std::string(" Читатель ") + std::to_string(readers_num) + std::string(" завершил работу\n"));
}

int main() {
    setlocale(LC_ALL, "Russian");
    
    for (size_t i = 0; i < REPEATS_COUNT; ++i) {
        srand(i);
        log(std::string(" ") + std::to_string(i) + std::string(" повтор программы\n\n"));
        std::vector<std::thread> threads;

        size_t total_writers = 0, total_readers = 0;
        while (total_readers < READERS_COUNT || total_writers < WRITERS_COUNT) {
            if (rand() % 2 == 0 && total_writers < WRITERS_COUNT) {
                threads.emplace_back(write, total_writers);
                ++total_writers;
            }
            else if (total_readers < READERS_COUNT){
                threads.emplace_back(read, total_readers);
                ++total_readers;
            }
        }
        for (size_t n = 0; n < threads.size(); ++n) {
            threads[n].join();
        }
    }
}