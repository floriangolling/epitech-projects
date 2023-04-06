cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 20)
project(bomberman)

find_package(raylib 3.0 QUIET)

# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)

  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/master.tar.gz
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

  endif()

endif()

add_executable(${PROJECT_NAME}
        src/core/main.cpp
        src/core/LoadScene.cpp
        src/core/Core.cpp
        src/core/Clock.cpp
        src/ecs/Entity.cpp
        src/ecs/Component.cpp
        src/ecs/Manager.cpp
        src/ecs/Scene.cpp
        src/graphicalLib/graphical.cpp
        src/graphicalLib/Init_raylib.cpp
        src/graphicalLib/RaylibCamera.cpp
        src/graphicalLib/RaylibTexture.cpp
        src/graphicalLib/RaylibAnimation.cpp
        src/graphicalLib/Raylib3DPerso.cpp
        src/graphicalLib/RaylibMap.cpp
        src/ecs/ComponentsList/PositionComponent.cpp
        src/ecs/ComponentsList/TextureComponent.cpp
        src/ecs/ComponentsList/ButtonComponent.cpp
        src/ecs/ComponentsList/StatsComponent.cpp
        src/ecs/ComponentsList/BombComponent.cpp
        src/ecs/ComponentsList/BonusComponent.cpp
        src/ecs/ComponentsList/IA.cpp
        src/ecs/ComponentsList/RectangleComponent.cpp
        src/ecs/ComponentsList/KeyboardEventComponent.cpp
        src/ecs/ComponentsList/MouseEventComponent.cpp
        src/ecs/ComponentsList/DestructibleComponent.cpp
        src/ecs/ComponentsList/TextComponent.cpp
        src/ecs/ComponentsList/CameraComponent.cpp
        src/ecs/ComponentsList/Perso3DComponent.cpp
        src/ecs/ComponentsList/AnimationComponent.cpp
        src/ecs/ComponentsList/MapComponent.cpp
        src/ecs/ComponentsList/PauseComponent.cpp
        src/core/SceneManager.cpp
        src/core/EventManager.cpp
        src/utils/jsonParser.cpp
        src/utils/GenerateImages.cpp
        src/jsoncpp/jsoncpp.cpp
        src/lodepng/lodepng.cpp)

target_link_libraries(${PROJECT_NAME} raylib)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()