#include <Veritas/Definitions/Definitions.h>
#ifdef UNIX
#include "Process.h"

using namespace Silexars::System;

#include <unistd.h>

bool Process::isAdmin() { return geteuid() == 0; }

#endif
