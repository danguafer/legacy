//!Clean

#include "Process.h"
#include "Managers/Manager.h"
#include <cstdlib>

using namespace Silexars;
using namespace System;
using namespace Managers;

Process::Process() : status(RUNNING) {
    Manager* manager = Manager::getManager();
    ProcessManager* pm = manager->getProcessManager();
    pm->processes.push_back(this);
}

Process::~Process() {
    Manager* manager = Manager::getManager();
    ProcessManager* pm = manager->getProcessManager();
    pm->processes.remove(this);
}

void Process::run() {}

void Process::suspend() {
    status = SUSPENDED;
    onSuspend();
}

void Process::resume() {
    status = RUNNING;
    onResume();
}

void Process::onResume() {}
void Process::onSuspend() {}

uint8 Process::getStatus() const { return status; }

uint32 Process::getArgc() const { return argc; }
const char** Process::getArgv() const { return (const char**) argv; }

Process *p = 0;
void deleteProcess() { delete p; }

Manager* manager = 0;
WindowManager *wm = 0;

void mainLoop() {
    if (wm->size()) manager->manage();
    else exit(0);
}

#ifdef OSX
#include <GLUT/glut.h>

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    manager = Manager::getManager();
    p = EntryPoint(argc, argv);
    wm = manager->getWindowManager();

    manager->manage();
    atexit(deleteProcess);

    glutDisplayFunc(mainLoop);
    glutMainLoop();
    return 0;
}
#else

extern "C" {
    struct android_app;
    void android_main(struct android_app* state);
}

int main(int argc, char **argv) {
    #ifdef ANDROID
    android_main(0);
    #endif

    manager = Manager::getManager();
    p = EntryPoint(argc, argv);
    wm = manager->getWindowManager();

    manager->manage();
    atexit(deleteProcess);
    while (1) mainLoop();
    return 0;
}

#endif
