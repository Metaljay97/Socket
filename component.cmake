# component variables

SET(COMPONENT_NAME support)
SET(TEST_NAME supportTests)
SET(SUBCOMPONENTS config exceptions events log utils)
SET(3RD_PARTY spdlog)
SET(LINUX_RELEASE_FLAGS "-O2 -Wall -Werror")
SET(LINUX_DEBUG_FLAGS "-O2 -g -Wall -Werror")
SET(LINUX_COVERAGE_FLAGS "-O0 -g -Wall -Werror -fprofile-arcs -ftest-coverage")
SET(WIN_RELEASE_FLAGS "/O2 /W3 /MT")
SET(WIN_DEBUG_FLAGS "/Od /Zi /D_DEBUG /MTd /W3")
SET(WIN_COVERAGE_FLAGS "/Od /Zi /D_DEBUG /MTd /W3") # TODO: code coverage on Windows
SET(FILE_PATHS "inc/*" "src/*")
