cmake_minimum_required(VERSION 3.16)

project(CommonDrops LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

find_package(
    SFML 2.5
    COMPONENTS graphics window system audio
    REQUIRED
)

FetchContent_Declare(
    inipp
    GIT_REPOSITORY https://github.com/mcmtroffaes/inipp.git
    GIT_TAG develop
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(inipp)

add_executable(CommonDrops
    Animatable.cpp
    CommonDrops.cpp
    Crystal.cpp
    CrystalMatrix.cpp
    Map.cpp
    Player.cpp
    Renderable.cpp
)

target_link_libraries(CommonDrops PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    inipp::inipp
)
