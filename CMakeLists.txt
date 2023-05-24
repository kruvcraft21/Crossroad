cmake_minimum_required(VERSION 3.0.0)
project(Crossroad VERSION 0.1.0)

add_subdirectory(libs/raylib)

add_executable(Crossroad src/main.cpp
                        src/road.h
                        src/road.cpp
                        src/roadcontroller.h
                        src/roadcontroller.cpp
                        src/car.h
                        src/car.cpp)

target_link_libraries(Crossroad PUBLIC raylib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})