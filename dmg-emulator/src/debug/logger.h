#pragma once

#include <stdlib.h>

#define DEBUG_ENABLED 0

void log_cpu_state(_In_z_ _Printf_format_string_ char const* const _Format, ...);