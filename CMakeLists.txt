cmake_minimum_required(VERSION 3.23)
project(ece-city-3-e C)

file(GLOB_RECURSE SOURCES Jeu/*.c)
include_directories(include)

set(CMAKE_C_STANDARD 99)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies

set(RAYLIB_VERSION 4.2.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()
# Our Project
add_executable(ece-city-3-e ${SOURCES} Jeu/ECECity.c include/ECECity.h Jeu/initialisation.c include/initialisation.h Jeu/musique.c include/musique.h Jeu/temps.c include/temps.h Jeu/affichage.c include/affichage.h)
#set(raylib_VERBOSE 1)
target_link_libraries(ece-city-3-e raylib)
# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${ece-city-3-e} PROPERTIES SUFFIX ".html")
endif()
# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${ece-city-3-e} "-framework IOKit")
    target_link_libraries(${ece-city-3-e} "-framework Cocoa")
    target_link_libraries(${ece-city-3-e} "-framework OpenGL")
endif()