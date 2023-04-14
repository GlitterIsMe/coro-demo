#include <iostream>
#include <atomic>
#include "libgo/libgo.h"

std::atomic_bool trigger_task_1{false};
std::atomic_bool trigger_task_2{false};
int pending = 0;

void task1() {
    printf("process task 1\n");
    co_sleep(10);
    printf("finish task 1\n");
    pending--;
    trigger_task_1 = false;
}

void task2() {
    printf("process task 2\n");
    co_sleep(10);
    printf("finish task 2\n");
    pending--;
    trigger_task_2 = false;
}

void worker() {
    while(true) {
        if (trigger_task_1) {
            go task1;
            pending++;
        } else if (trigger_task_2) {
            go task2;
            pending++;
        }
        if (pending > 0) {
            co_yield;
        }
    }
}

void server() {
    go worker;
    co_sched.Start();
}

void client() {
    while(true) {
        sleep(1);
        if (!trigger_task_1) {
            printf("ask 1\n");
            trigger_task_1 = true;
        }
        sleep(1);
        if (!trigger_task_2) {
            printf("ask 2\n");
            trigger_task_2 = true;
        }
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::thread t1([] {
        server();
    });
    t1.detach();

    std::thread t2([] {
        client();
    });

    t2.join();
    return 0;
}
