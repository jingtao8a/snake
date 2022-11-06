cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
project("snake")

# add_executable(print tests/print.cpp)
# target_link_libraries(print ncurses)

# add_executable(print1 tests/print1.cpp)
# target_link_libraries(print1 ncurses)

# add_executable(print2 tests/print2.cpp)
# target_link_libraries(print2 ncurses)

add_executable(print3 tests/print3.cpp)
target_link_libraries(print3 ncurses)

add_executable(test1 tests/test1.cpp src/gamewindow.cpp src/snake.cpp src/food.cpp)
target_link_libraries(test1 ncurses yxtwebcpp dl pthread yaml-cpp)



# add_executable(splice tests/splice.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)