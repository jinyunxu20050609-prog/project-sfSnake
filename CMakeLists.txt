cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SFML_DIR "C:\\360Downloads\\SFML-2.6.2\\lib\\cmake\\SFML")
find_package(SFML 2.6 COMPONENTS graphics audio system window network REQUIRED)

set(EXECUTABLE_NAME sfSnake)
set(SOURCE_FILES
    sfSnake-master/main.cpp
    sfSnake-master/Game.cpp
    sfSnake-master/Screen.cpp
    sfSnake-master/Fruit.cpp
    sfSnake-master/GameOverScreen.cpp
    sfSnake-master/GameScreen.cpp
    sfSnake-master/MenuScreen.cpp
    sfSnake-master/Snake.cpp
    sfSnake-master/SnakeNode.cpp
    sfSnake-master/Grid.cpp
)

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

target_link_libraries(${EXECUTABLE_NAME} PRIVATE
    sfml-graphics
    sfml-audio
    sfml-system
    sfml-window
    sfml-network
)

target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_17)

file(COPY
    Fonts/
    Music/
    pics/
    Sounds/
    DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug
)

add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "C:\\360Downloads\\SFML-2.6.2\\bin"
    $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
)