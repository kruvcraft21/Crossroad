cmake_minimum_required(VERSION 3.0.0)
project(Crossroad VERSION 0.1.0)

add_subdirectory(libs/raylib)

file(GLOB src "src/*")

add_executable(Crossroad ${src})

target_link_libraries(Crossroad PUBLIC raylib)

set_target_properties(Crossroad PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

file(COPY "resources/" DESTINATION "Release/resources/")
file(COPY "resources/" DESTINATION "Debug/resources/")