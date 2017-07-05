#pragma once

#include "Architecture.h"
#include "OS.h"
#include "Atoms.h"
// Use template instead:
#define iterate(T,x) for (T::iterator iterator = (x)->begin(); iterator != (x)->end(); iterator++)
