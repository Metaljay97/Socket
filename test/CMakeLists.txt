INCLUDE("../component.cmake")

PROJECT(${TEST_NAME} CXX)
CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

# C++ version
SET(CMAKE_CXX_STANDARD 17)

# Compiler options
# Check if the current platform is Windows and set compiler flags accordingly
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
  SET(CMAKE_CXX_FLAGS_RELEASE ${WIN_RELEASE_FLAGS})
  SET(CMAKE_CXX_FLAGS_DEBUG ${WIN_DEBUG_FLAGS})
  SET(CMAKE_CXX_FLAGS_COVERAGE ${WIN_COVERAGE_FLAGS})
else()
  SET(CMAKE_CXX_FLAGS_RELEASE ${LINUX_RELEASE_FLAGS})
  SET(CMAKE_CXX_FLAGS_DEBUG ${LINUX_DEBUG_FLAGS})
  SET(CMAKE_CXX_FLAGS_COVERAGE ${LINUX_COVERAGE_FLAGS})
  SET(CMAKE_EXE_LINKER_FLAGS_COVERAGE "-fprofile-arcs -ftest-coverage")
endif()

# add googletest
add_subdirectory("googletest")

# add component
add_subdirectory(".." ${COMPONENT_NAME})

# generate test executable
file(GLOB src "*.cpp" "*.h" ".hpp")
add_executable(${TEST_NAME} "${src}")
target_compile_definitions(${TEST_NAME} PRIVATE SUPPORT)
target_include_directories(${TEST_NAME} PUBLIC "${dir}")
target_link_libraries(${TEST_NAME} PRIVATE gmock gtest ${COMPONENT_NAME})
install(TARGETS ${TEST_NAME})

# CPack
set(CPACK_GENERATOR "TGZ")
