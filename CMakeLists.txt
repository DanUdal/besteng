cmake_minimum_required(VERSION 2.6)
project(BESTENG)

string(TOLOWER "${CMAKE_CXX_COMPILER_ID}" COMP)
string(TOLOWER "${CMAKE_SYSTEM_NAME}" PLATFORM)
string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" ARCH)
message("${COMP}-${PLATFORM}-${ARCH}")

add_definitions(-DSDL_MAIN_HANDLED)

include_directories(
  src
  ${PROJECT_SOURCE_DIR}/contrib/${COMP}-${PLATFORM}-${ARCH}/include
)

link_directories(
  ${PROJECT_SOURCE_DIR}/contrib/${COMP}-${PLATFORM}-${ARCH}/lib
)

if(MINGW)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s -static")
  add_definitions(-DGLEW_STATIC)
  set(STATIC_LIBS imm32 iconv winmm ole32 gdi32 oleaut32 version)
  set(LIBGLEW glew32)
  set(LIBSDL2 SDL2)
elseif(MSVC)
  add_definitions(-DGLEW_STATIC)
  set(STATIC_LIBS imm32 winmm setupapi version)
  set(LIBGLEW glew32s)
  set(LIBSDL2 SDL2-static)
endif()

add_library(rend
  src/rend/Exception.cpp
  src/rend/Context.cpp
  src/rend/Texture.cpp
  src/rend/RenderTexture.cpp
  src/rend/Shader.cpp
  src/rend/Buffer.cpp
  src/rend/Mesh.cpp
  src/rend/Util.cpp

  src/rend/Buffer.h
  src/rend/Context.h
  src/rend/Exception.h
  src/rend/mathutil.h
  src/rend/Mesh.h
  src/rend/rend.h
  src/rend/RenderTexture.h
  src/rend/Shader.h
  src/rend/Texture.h
  src/rend/TextureAdapter.h
  src/rend/Util.h
)
if(MSVC OR MINGW)
  target_link_libraries(rend ${LIBGLEW} opengl32)
else()
  target_link_libraries(rend GLEW GL)
endif()

add_library(besteng
  src/besteng/core.cpp
  src/besteng/entity.cpp
  src/besteng/component.cpp
  src/besteng/environment.cpp
  src/besteng/Renderer.cpp
  src/besteng/transform.cpp
  src/besteng/resources.cpp
  src/besteng/screen.cpp
  src/besteng/inputManager.cpp
  src/besteng/collider.cpp
  src/besteng/mesh.cpp

  src/besteng/core.h
  src/besteng/entity.h
  src/besteng/component.h
  src/besteng/besteng.h
  src/besteng/environment.h
  src/besteng/Renderer.h
  src/besteng/transform.h
  src/besteng/resources.h
  src/besteng/screen.h
  src/besteng/inputManager.h
  src/besteng/collider.h
  src/besteng/mesh.h
)
target_link_libraries(besteng rend ${LIBSDL2} ${STATIC_LIBS})

add_executable(demo
  src/demo/main.cpp
)
target_link_libraries(demo besteng)
