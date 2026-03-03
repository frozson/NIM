# CMakeList.txt : CMake project for NIM, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.25)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (NIM LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/src")

#FILE(GLOB cpp "${CMAKE_CURRENT_SOURCE_DIR}/src/engine/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/util/*.cpp")

add_subdirectory(vendor)

# Add source to this project's executable.
add_executable (NIM "main.cpp")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT NIM)

add_dependencies(NIM opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui)

#3rd party
target_include_directories(NIM PRIVATE ${CMAKE_CURRENT_BINARY_DIR} vendor/opencv/include vendor/opencv/modules/core/include vendor/opencv/modules/imgproc/include vendor/opencv/modules/imgcodecs/include vendor/opencv/modules/highgui/include)
target_link_libraries(NIM PRIVATE opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui )

#end 3rd party

target_sources(NIM 
	PUBLIC
		FILE_SET nim_headers
			TYPE HEADERS
			BASE_DIRS "include"
			FILES
				"include/nim.h"
				"include/stb_image.h"
				"include/stb_image_write.h"

	PRIVATE
		"src/nim.cpp"
		#${cpp}

)

if(MSVC)
    target_compile_options(NIM PRIVATE "/MP")
endif()
target_compile_definitions(NIM PUBLIC NIM_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET NIM PROPERTY CXX_STANDARD 23)
endif()

# TODO: Add tests and install targets if needed.
