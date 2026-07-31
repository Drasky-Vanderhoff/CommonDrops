cmake_minimum_required(VERSION 3.28)

project(CommonDrops LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)

FetchContent_Declare(
    inipp
    GIT_REPOSITORY https://github.com/mcmtroffaes/inipp.git
    GIT_TAG develop
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(SFML)
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

target_compile_features(CommonDrops PRIVATE cxx_std_17)

target_link_libraries(CommonDrops PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
    inipp::inipp
)
