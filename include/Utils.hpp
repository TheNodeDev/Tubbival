#pragma once

#include "util/Math.hpp"
#include "util/Memory.hpp"
#include "util/Platform.hpp"

#ifdef _WIN32
	#include <synchapi.h>
#endif
#ifndef _WIN32
    #include <unistd.h>
#endif

/**
 * return the engine name of this module
 * @param name non-engine name of the module
 */
#define MODULE(name) name MODULE_EXTENSION
#define GAME(x) GAME_PATH(x)

/**
 * Checks if a string ends with another one
 * @param str string to check
 * @param suffix string to search for
 */
static bool ends_with( const std::string& str, const std::string& suffix ) {
    return str.size() >= suffix.size() && !str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

/**
 * Redeclare a type
 */
#define REDECL(name) \
    decltype(name) name

/**
 * Safely delete a pointer (value?)
 */
#define SAFE_DELETE(ptr) \
    if (ptr) {           \
        delete ptr;      \
        ptr = nullptr;   \
    }

/**
 * Sleep for x milliseconds
 */
inline void GO_THE_FUCK_TO_SLEEP( unsigned long ms ) {
	#ifdef _WIN32
		Sleep(ms);
	#else
		usleep(ms * 1000);
	#endif
}
