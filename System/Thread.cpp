#include "Thread.h"

#include <pthread.h>
#include <signal.h>
#include <time.h>

using namespace Silexars::System;

Thread::Thread(void* (*f)(void *data), void *data) {
    pthread_t tid;
    pthread_create(&tid, 0, f, data);
    id = (Handle) tid;
}

void* Thread::join() {
    void *ret;
    pthread_join((pthread_t) id, &ret);
    return ret;
}

void Thread::sleep(uint64 ms) {
    timespec ts;
    ts.tv_nsec = ms * 1000000L;
    ts.tv_sec = 0;
    nanosleep(&ts, 0);
}
