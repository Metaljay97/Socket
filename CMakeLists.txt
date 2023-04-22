INCLUDE("component.cmake")

PROJECT(${COMPONENT_NAME})
CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

# add the subcomponents
foreach(component ${SUBCOMPONENTS})
  add_subdirectory("${component}")
endforeach()

# CPack
set(CPACK_GENERATOR "TGZ")

