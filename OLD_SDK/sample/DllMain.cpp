//
// Created by ENDERZOMBI102 on 07/04/2022.
//

// Might fix potential deadlock
#ifdef _WIN32
	#include <minwindef.h>
	#include "ExamplePlugin.hpp"

	#pragma clang diagnostic push
	#pragma ide diagnostic ignored "UnusedParameter"
	BOOL WINAPI DllMain( HINSTANCE instance, DWORD reason, LPVOID reserved ) {
		if ( reason == DLL_PROCESS_DETACH )
			examplePlugin.Cleanup();
		return TRUE;
	}
	#pragma clang diagnostic pop
#endif
