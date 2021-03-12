

cmake_minimum_required(VERSION 3.1)
project( BCISift )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#C++17 version

# External packages

## OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

## LSL
find_package(LSL)


## VL
find_package(VLFeat)
if(VLFEAT_FOUND)
	message("-- Using VLFeat: ${VLFEAT_INCLUDE_DIRS}")
	include_directories(${VLFEAT_INCLUDE_DIRS})
	SET(PROJECT_LIBS ${PROJECT_LIBS} ${VLFEAT_LIBRARIES})
else()
	message("-- VLFeat not found, set the VLFEAT_ROOT to the root folder of VLFeat ")
endif()



# Source files
include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/include
)

file(GLOB SOURCES
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )

link_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_SOURCE_DIR}/src/include)


# Build
add_executable( BCISift ${SOURCES})
target_link_libraries( BCISift ${OpenCV_LIBS} )
target_link_libraries(BCISift ${VLFEAT_LIBRARIES})
target_link_libraries(BCISift lsl)

# C++17 in order to use KFR
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

