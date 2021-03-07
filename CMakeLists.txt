cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME studyopengl)
project(${PROJECT_NAME})

set (SOURCE_EXE src/main.cpp 
                src/appl/appl.cpp 
                src/mainwindow.cpp 
                src/render/renderer.cpp 
                src/render/vertexbufferlayout.cpp 
                src/render/vertexbuffers.cpp 
                src/render/shaderprogramm.cpp 
                src/render/indexbuffers.cpp 
                src/render/vertexarray.cpp 
                src/render/texture2D.cpp 
                src/render/sprite.cpp 
                src/appl/menu.cpp 
                src/appl/resourcemanager.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_EXE}) 

message ("Now composing [${SOURCE_EXE}]")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

include_directories(inc external/glm external/rapidjson/include/)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
