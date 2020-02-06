cmake_minimum_required(VERSION 3.16)

project(StrategyGameJam)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(StrategyGameJam)

target_sources(StrategyGameJam
  PRIVATE
    src/main.cpp
    src/AI/AI.cpp
    src/AI/AI.hpp
    src/AI/AIComponent.cpp
    src/AI/AIComponent.hpp
    src/Engine/Engine.cpp
    src/Engine/Engine.hpp
    src/Engine/GameState.cpp
    src/Engine/GameState.hpp
    src/Engine/GameSystem.hpp
    src/Engine/GameObject.cpp
    src/Engine/GameObject.hpp
    src/Engine/GameObjectComponent.cpp
    src/Engine/GameObjectComponent.hpp
    src/Engine/Types.hpp
    src/Engine/World.cpp
    src/Engine/World.hpp
    src/Engine/WorldLoader.cpp
    src/Engine/WorldLoader.hpp
    src/Graphics/Graphics.cpp
    src/Graphics/Graphics.hpp
    src/Graphics/GraphicsComponent.cpp
    src/Graphics/GraphicsComponent.hpp
    src/Graphics/Renderer.cpp
    src/Graphics/Renderer.hpp
    src/Graphics/Sprite.cpp
    src/Graphics/Sprite.hpp
    src/Input/Input.cpp
    src/Input/Input.hpp
    src/Input/InputComponent.cpp
    src/Input/InputComponent.hpp
    src/Input/InputTypes.hpp
    src/Objects/Actor.cpp
    src/Objects/Actor.hpp
    src/Objects/Camera.cpp
    src/Objects/Camera.hpp
    src/Objects/DrawableObject.cpp
    src/Objects/DrawableObject.hpp
    src/Physics/Physics.cpp
    src/Physics/Physics.hpp
    src/Physics/PhysicsComponent.cpp
    src/Physics/PhysicsComponent.hpp
    src/UI/UI.cpp
    src/UI/UI.hpp
    src/UI/UIComponent.cpp
    src/UI/UIComponent.hpp
    src/UI/UIObject.hpp
    src/Util/SDLMath.hpp
)

get_property("TARGET_SOURCE_FILES" TARGET StrategyGameJam PROPERTY SOURCES)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${TARGET_SOURCE_FILES})

# Dependencies

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
target_include_directories(StrategyGameJam PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(StrategyGameJam ${SDL2_LIBRARIES})

find_package(SDL2TTF REQUIRED)
target_include_directories(StrategyGameJam PRIVATE ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(StrategyGameJam ${SDL2TTF_LIBRARIES})

# Copy resources

if(WIN32)
  add_custom_command(TARGET StrategyGameJam POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/res
    ${CMAKE_BINARY_DIR}/res
  )
else()
  add_custom_command(TARGET StrategyGameJam POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/res
    $<TARGET_FILE_DIR:StrategyGameJam>/res
  )
endif()