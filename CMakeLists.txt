cmake_minimum_required (VERSION 2.8)
project (dethgame)

# Path to oxygene installation
add_subdirectory(./oxygine-framework)

# Oxygine definitions and includes
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})
# Compile flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OXYGINE_CXX_FLAGS}")


# Project source code
#aux_source_directory(./src _SRC_FILES)
file(GLOB_RECURSE SRC_FILES "./src/*.cpp")
#message(STATUS "Cpps: ${SRC_FILES}")


add_executable(${PROJECT_NAME} ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} ${OXYGINE_CORE_LIBS})

# Copy dlls to output dir
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/data"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)


#disable console mode for VC++
if (WIN32) 
	set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif(WIN32)


