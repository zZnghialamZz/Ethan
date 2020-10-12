#ifndef ETHAN_UTILS_H_
#define ETHAN_UTILS_H_

namespace Ethan {}

// NOTE(Nghia Lam): This needs to be included first before using any shorten
// types or general macros
#include "utils/misc/macros.h"
#include "utils/misc/types.h"
#include "utils/misc/funcs.h"

// Main include
#include "utils/console/console.h"
#include "utils/ds/queue.h"
#include "utils/ds/stack.h"
#include "utils/helper/pointer_ext.h"
#include "utils/helper/string_ext.h"
#include "utils/os/file_system.h"
#include "utils/time/timer.h"

#endif  // ETHAN_UTILS_H_
