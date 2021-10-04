cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(PROJECT_NAME 3dModelMaker)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    src/main.cpp
	src/Renderer/ShaderProgram.cpp
	src/Renderer/ShaderProgram.h
	src/Camera/camera.h
	src/Object/LightSource.cpp
	src/Object/LightSource.h
	src/Renderer/Mesh.cpp
	src/Renderer/Mesh.h
	src/Renderer/Model.cpp
	src/Renderer/Model.h
	src/Object/Cube.cpp
	src/Object/Cube.h
	src/Object/ModelManager.cpp
	src/Object/ModelManager.h
	src/Events/EventsManager.cpp
	src/Events/EventsManager.h
	src/AlgGeometric/AlgGeometric.h
	src/Triangulation/Triangulation.cpp
	src/Triangulation/Triangulation.h
	src/Triangulation/List.cpp
	src/Triangulation/List.h
	src/Triangulation/TriangulationArray.cpp
	src/Triangulation/TriangulationArray.h
	src/Triangulation/TriangulationMonotone.cpp
	src/Triangulation/TriangulationMonotone.h)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

include_directories(external/glm)