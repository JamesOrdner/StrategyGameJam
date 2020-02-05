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
    src/Util/SDLMath.hpp
)

get_property("TARGET_SOURCE_FILES" TARGET StrategyGameJam PROPERTY SOURCES)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${TARGET_SOURCE_FILES})

# SuperBuild Dependencies

include(ExternalProject)
set(DEPENDENCIES_DIR ${PROJECT_SOURCE_DIR}/dependencies)
set(DEPENDENCY_CMAKE_ARGS
  -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
  -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
  -DCMAKE_BUILD_TYPE=Release
)

# SuperBuild Dependencies - SDL2

if (WIN32) # use precompiled binaries
  ExternalProject_Add(SDL2
    URL https://www.libsdl.org/release/SDL2-devel-2.0.10-VC.zip
    PREFIX ${DEPENDENCIES_DIR}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${DEPENDENCIES_DIR}/src/SDL2/lib/x64 ${DEPENDENCIES_DIR}/lib
      COMMAND ${CMAKE_COMMAND} -E copy_directory ${DEPENDENCIES_DIR}/src/SDL2/include ${DEPENDENCIES_DIR}/include/SDL2
  )
  target_link_libraries(StrategyGameJam PRIVATE ${DEPENDENCIES_DIR}/lib/SDL2.lib ${DEPENDENCIES_DIR}/lib/SDL2main.lib)
  add_custom_command(TARGET StrategyGameJam POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${DEPENDENCIES_DIR}/lib/SDL2.dll"
    $<TARGET_FILE_DIR:StrategyGameJam>
  )
else()
  set(SDL2_CACHE_ARGS
    -DSDL_STATIC:BOOL=FALSE
    -DSDL_SHARED:BOOL=TRUE
    -DSDL_Audio:BOOL=TRUE
    -DSDL_File:BOOL=FALSE
    -DSDL_Filesystem:BOOL=FALSE
    -DSDL_Threads:BOOL=FALSE
    -DSDL_Joystick:BOOL=FALSE
    -DSDL_Haptic:BOOL=FALSE
    -DSDL_Atomic:BOOL=FALSE
    -DSDL_Render:BOOL=TRUE
    -DSDL_Sensor:BOOL=FALSE
    -DDIRECTX:BOOL=FALSE
    -DVIDEO_VULKAN:BOOL=FALSE
  )

  ExternalProject_Add(SDL2
    URL http://www.libsdl.org/release/SDL2-2.0.10.tar.gz
    PREFIX ${DEPENDENCIES_DIR}
    CMAKE_ARGS ${DEPENDENCY_CMAKE_ARGS}
    CMAKE_CACHE_ARGS ${SDL2_CACHE_ARGS}
    INSTALL_COMMAND ${CMAKE_COMMAND} --build . --target install --config Release
  )

  if(XCODE)
    target_link_libraries(StrategyGameJam
      PRIVATE
        ${DEPENDENCIES_DIR}/lib/libSDL2.dylib
        ${DEPENDENCIES_DIR}/lib/libSDL2main.a
    )
  else()
    target_link_libraries(StrategyGameJam
      PRIVATE
        ${DEPENDENCIES_DIR}/lib/libSDL2.so
        ${DEPENDENCIES_DIR}/lib/libSDL2main.a
    )
  endif()
endif()
target_include_directories(StrategyGameJam PRIVATE ${DEPENDENCIES_DIR}/include/SDL2)

