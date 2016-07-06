cmake_minimum_required (VERSION 2.8)
project (dethgame)

# Check Oxygine path
if(NOT OXYGINE_PATH)
	# Fail if path to oxygine is not specified
	message(FATAL_ERROR "Path to Oxygine is not specified. Add -DOXYGINE_PATH=/path/to/oxygine/directory")
endif(NOT OXYGINE_PATH)


# Path to oxygene installation
add_subdirectory(${OXYGINE_PATH} oxygine-framework)

# Oxygine definitions and includes
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})
# Compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OXYGINE_CXX_FLAGS}")


# Project source code
aux_source_directory(./src SRC_FILES)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${OXYGINE_CORE_LIBS})

#disable console mode for VC++
if (WIN32) 
	set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif(WIN32)