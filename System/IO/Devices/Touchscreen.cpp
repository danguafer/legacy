#include "Touchscreen.h"

using namespace Silexars;
using namespace System;
using namespace IO;
using namespace Devices;

Touchscreen::List Touchscreen::touches;

Touchscreen::iterator Touchscreen::begin() { return touches.begin(); }
Touchscreen::iterator Touchscreen::end() { return touches.end(); }
uint32 Touchscreen::size() { return touches.size(); }
