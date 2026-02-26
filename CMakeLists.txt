# CMakeList.txt : CMake project for NIM, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.25)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (NIM C CXX)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(CURRENT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# Add source to this project's executable.
add_executable (NIM "main.cpp")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT NIM)

#3rd party
add_subdirectory(vendor)
add_dependencies(NIM raylib)


target_link_libraries(NIM PRIVATE raylib)

#end 3rd party

target_sources(NIM 
	PUBLIC
		FILE_SET nim_headers
			TYPE HEADERS
			BASE_DIRS "include"
			FILES
				"include/nim.h"


	PRIVATE
		"src/nim.cpp"

)

target_compile_definitions(NIM PUBLIC NIM_DIR="${CURRENT_PATH}")
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET NIM PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
