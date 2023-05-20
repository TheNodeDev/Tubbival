if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR )
  message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the Portal Development Kit source code and call cmake from there")
endif()

cmake_minimum_required(VERSION 3.20)
project(Portal2_SDK VERSION 1.0.0)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CMAKE_CXX_STANDARD 23)  # required for MSVC
	set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Steam/steamapps/common/Portal 2/bin")

	if(CMAKE_SIZEOF_VOID_P EQUAL "8")
		message( FATAL_ERROR "Unsupported compiler platform: it is x64 instead of x86" )
	endif()
else()
	set(CMAKE_CXX_STANDARD 20)
	set(CMAKE_INSTALL_PREFIX "~/.local/share/Steam/steamapps/common/Portal 2/bin")
	add_compile_options(-m32)
	add_link_options(-m32)
	set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_definitions( _X86_ )
include_directories( include )

add_library(
		Portal2_SDK STATIC
		# --- headers ---
		#  -- engine --
		include/engine/vscript/VScript.hpp
		include/engine/vscript/Macros.hpp
		include/engine/vscript/ScriptVM.hpp
		include/engine/Client.hpp
		include/engine/Color.hpp
		include/engine/CommandLine.hpp
		include/engine/CUtl.hpp
		include/engine/CVar.hpp
		include/engine/Event.hpp
		include/engine/GameEvent.hpp
		include/engine/Interface.hpp
		include/engine/Math.hpp
		include/engine/Network.hpp
		include/engine/ParticleSystem.hpp
		include/engine/PluginInterface.hpp
		include/engine/RayTrace.hpp
		include/engine/Something.hpp
		include/engine/UserState.hpp
		#  -- game --
		include/game/Game.hpp
		include/game/Portal2.hpp
		include/game/Portal2Linux.hpp
		include/game/Portal2CommunityEdition.hpp
		#  -- hud --
		include/hud/Hud.hpp
		#  -- module --
		include/module/Client.hpp
		include/module/Console.hpp
		include/module/Engine.hpp
		include/module/Module.hpp
		include/module/Server.hpp
		include/module/Surface.hpp
		include/module/Tier1.hpp
		include/module/VGui.hpp
		include/module/VScript.hpp
		#  -- util --
		include/util/KeyValues.hpp
		include/util/Math.hpp
		include/util/Memory.hpp
		include/util/Platform.hpp
		#  -- root --
		include/Cheats.hpp
		include/Command.hpp
		include/Interface.hpp
		include/Offsets.hpp
		include/Plugin.hpp
		include/PluginBase.hpp
		include/Utils.hpp
		include/Variable.hpp
		# --- sources ---
		#  -- engine --
		src/engine/Interface.cpp
		#  -- game --
		src/game/Game.cpp
		src/game/Portal2.cpp
		src/game/Portal2Linux.cpp
		src/game/Portal2CommunityEdition.cpp
		#  -- hud --
		src/hud/Hud.cpp
		#  -- module --
		src/module/Client.cpp
		src/module/CommandLine.cpp
		src/module/Engine.cpp
		src/module/VScript.cpp
		src/module/Module.cpp
		src/module/Server.cpp
		src/module/Surface.cpp
		src/module/Tier1.cpp
		src/module/VGui.cpp
		#  -- util --
		src/util/Memory.cpp
		#  -- root --
		src/Cheats.cpp
		src/Command.cpp
		src/Interface.cpp
		src/Offsets.cpp
		src/Plugin.cpp
		src/PluginBase.cpp
		src/Variable.cpp
)

add_library(
	SamplePlugin SHARED
	# sources
	sample/DllMain.cpp
	sample/ExamplePlugin.cpp
	sample/ExamplePlugin.hpp
	sample/TubbivalHUD.cpp
	sample/TubbivalHUD.hpp
)
target_link_libraries( SamplePlugin PRIVATE Portal2_SDK )
set(P2DK_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
