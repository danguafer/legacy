//!Complete

#include "ProcessManager.h"

using namespace Silexars;
using namespace System;
using namespace Managers;

ProcessManager::ProcessManager() {}

void ProcessManager::manage() {
    iterate(ProcessManager, this) {
        Process *p = *iterator;
        if (p->getStatus() == Process::RUNNING) p->run();
    }
}

ProcessManager::iterator ProcessManager::begin() { return processes.begin(); }
ProcessManager::iterator ProcessManager::end() { return processes.end(); }
uint32 ProcessManager::size() const { return processes.size(); }
