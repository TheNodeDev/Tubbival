#pragma once

#define _GAME_PATH(x) #x

#ifdef _WIN32
	#define MODULE_EXTENSION ".dll"
	// clang-format off
	#define GAME_PATH(x) _GAME_PATH(Games/Windows/##x.hpp)
	// clang-format on
	#define __funccc __thiscall

	/**
	 * mark something to be exported from the plugin's dll
	 */
	#define DLL_EXPORT extern "C" __declspec(dllexport)

	/**
	 * https://github.com/Krzyhau/SourceAutoRecord/blob/master/doc/contributing.md#hooking
	 */
	#define DECL_DETOUR(name, ...)                                  \
	    using _##name = int(__funccc*)(void* thisptr, __VA_ARGS__); \
	    static _##name name;                                        \
	    static int __fastcall name##_Hook(void* thisptr, int edx, __VA_ARGS__);
	/**
	 * https://github.com/Krzyhau/SourceAutoRecord/blob/master/doc/contributing.md#hooking
	 */
	#define DECL_DETOUR_T(type, name, ...)                           \
	    using _##name = type(__funccc*)(void* thisptr, __VA_ARGS__); \
	    static _##name name;                                         \
	    static type __fastcall name##_Hook(void* thisptr, int edx, __VA_ARGS__);
	/**
	 *  https://github.com/Krzyhau/SourceAutoRecord/blob/master/doc/contributing.md#hooking
	 */
	#define DECL_DETOUR_B(name, ...)                                \
	    using _##name = int(__funccc*)(void* thisptr, __VA_ARGS__); \
	    static _##name name;                                        \
	    static _##name name##Base;                                  \
	    static int __fastcall name##_Hook(void* thisptr, int edx, __VA_ARGS__);

	/**
	 *  https://github.com/Krzyhau/SourceAutoRecord/blob/master/doc/contributing.md#hooking
	 */
	#define DETOUR(name, ...) \
	    int __fastcall name##_Hook(void* thisptr, int edx, __VA_ARGS__)
	/**
	 *  https://github.com/Krzyhau/SourceAutoRecord/blob/master/doc/contributing.md#hooking
	 */
	#define DETOUR_T(type, name, ...) \
	    type __fastcall name##_Hook(void* thisptr, int edx, __VA_ARGS__)
	/**
	 *  https://github.com/Krzyhau/SourceAutoRecord/blob/master/doc/contributing.md#hooking
	 */
	#define DETOUR_B(name, ...) \
	    int __fastcall name##_Hook(void* thisptr, int edx, __VA_ARGS__)

	#define THIS_CALL(func, thisptr, ...) func( __VA_ARGS__ )
#else
	#define MODULE_EXTENSION ".so"
	// clang-format off
	#define GAME_PATH(x) _GAME_PATH(Games/Linux/x.hpp)
	// clang-format on
	#define __funccc __attribute__((__cdecl__))
	#define __cdecl __attribute__((__cdecl__))
	#define __stdcall __attribute__((__stdcall__))
	#define __fastcall __attribute__((__fastcall__))
	/**
	 * mark something to be exported from the plugin's dll
	 */
	#define DLL_EXPORT extern "C" __attribute__((visibility("default")))

	/**
	 *  https://github.com/Krzyhau/SourceAutoRecord/blob/master/doc/contributing.md#hooking
	 */
	#define DECL_DETOUR(name, ...)                                  \
	    using _##name = int(__funccc*)(void* thisptr, __VA_ARGS__); \
	    static _##name name;                                        \
	    static int __funccc name##_Hook(void* thisptr, __VA_ARGS__);
	/**
	 *  https://github.com/Krzyhau/SourceAutoRecord/blob/master/doc/contributing.md#hooking
	 */
	#define DECL_DETOUR_T(type, name, ...)                           \
	    using _##name = type(__funccc*)(void* thisptr, __VA_ARGS__); \
	    static _##name name;                                         \
	    static type __funccc name##_Hook(void* thisptr, __VA_ARGS__);
	/**
	 *  https://github.com/Krzyhau/SourceAutoRecord/blob/master/doc/contributing.md#hooking
	 */
	#define DECL_DETOUR_B(name, ...)                                \
	    using _##name = int(__funccc*)(void* thisptr, __VA_ARGS__); \
	    static _##name name;                                        \
	    static _##name name##Base;                                  \
	    static int __funccc name##_Hook(void* thisptr, __VA_ARGS__);

	/**
	 *  https://github.com/Krzyhau/SourceAutoRecord/blob/master/doc/contributing.md#hooking
	 */
	#define DETOUR(name, ...) \
	    int __funccc name##_Hook(void* thisptr, __VA_ARGS__)
	/**
	 *  https://github.com/Krzyhau/SourceAutoRecord/blob/master/doc/contributing.md#hooking
	 */
	#define DETOUR_T(type, name, ...) \
	    type __funccc name##_Hook(void* thisptr, __VA_ARGS__)
	/**
	 *  https://github.com/Krzyhau/SourceAutoRecord/blob/master/doc/contributing.md#hooking
	 */
	#define DETOUR_B(name, ...) \
	    int __funccc name##_Hook(void* thisptr, __VA_ARGS__)

	#define THIS_CALL(func, thisptr, ...) func( thisptr, __VA_ARGS__ )
#endif

/**
 *  https://github.com/Krzyhau/SourceAutoRecord/blob/master/doc/contributing.md#hooking
 */
#define DECL_DETOUR_STD(type, name, ...)             \
    using _##name = type(__stdcall*)( __VA_ARGS__ ); \
    static _##name name;                             \
    static type __stdcall name##_Hook( __VA_ARGS__ );

/**
 *  https://github.com/Krzyhau/SourceAutoRecord/blob/master/doc/contributing.md#hooking
 *  Detour a __stdcall function
 */
#define DETOUR_STD(type, name, ...) \
    type __stdcall name##_Hook( __VA_ARGS__ )

#define SAFE_UNLOAD(ptr) \
    if (ptr) {           \
        delete ptr;      \
        ptr = nullptr;   \
    }
