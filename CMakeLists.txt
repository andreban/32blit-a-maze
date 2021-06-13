# Basic parameters; check that these match your project / environment
cmake_minimum_required(VERSION 3.9)

project(amaze)

set(PROJECT_SOURCE
        amaze.cpp
        amaze.hpp
        mazegen/Cell.h
        mazegen/Cell.cpp
        mazegen/Direction.h
        mazegen/Direction.cpp
        mazegen/Distances.h
        mazegen/Distances.cpp
        mazegen/Maze.h
        mazegen/Maze.cpp
        mazegen/MazeGen.h
        mazegen/MazeGen.cpp
        gamemap/Tile.h
        gamemap/Tile.cpp
        gamemap/GameMap.cpp
        gamemap/GameMap.h
        entities/Bomb.h
        entities/Bomb.cpp
        entities/Player.h
        entities/Player.cpp
        entities/Viewport.h
        entities/Viewport.cpp
        states/Game.h
        states/Game.cpp
        states/MainMenu.h
        states/MainMenu.cpp
        states/GameOver.h
        states/GameOver.cpp
)

# ... and any other files you want in the release here
set(PROJECT_DISTRIBS LICENSE README.md)

# Build configuration; approach this with caution!
if(MSVC)
  add_compile_options("/W4" "/wd4244" "/wd4324" "/wd4458" "/wd4100")
else()
  add_compile_options("-Wall" "-Wextra" "-Wdouble-promotion" "-Wno-unused-parameter")
endif()

find_package (32BLIT CONFIG REQUIRED PATHS ../../32blit-beta)

blit_executable (${PROJECT_NAME} ${PROJECT_SOURCE})
blit_assets_yaml (${PROJECT_NAME} assets.yml)
blit_metadata (${PROJECT_NAME} metadata.yml)
add_custom_target (flash DEPENDS ${PROJECT_NAME}.flash)

# setup release packages
install (FILES ${PROJECT_DISTRIBS} DESTINATION .)
set (CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set (CPACK_GENERATOR "ZIP" "TGZ")
include (CPack)
