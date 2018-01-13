
#include <assert.h> // Assert macro
#include <math.h> // Math functions
#include <cstdint> // Standard fixed-width integer types
#include <cstdlib> // Basic stuff
#include <cstring> // String handling
#include <iostream> // Printing

#include "config.h"

#if CONFIG_VERBOSE
#define VERBOSE(code) code
#else
#define VERBOSE(code)
#endif
