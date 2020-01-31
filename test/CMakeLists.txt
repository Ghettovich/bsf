project(BsfTest LANGUAGES CXX)

find_package(Qt5Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

enable_testing(true)

add_executable(BsfTest test_recipe.cpp test_recipe.h)
add_test(NAME BsfTest COMMAND BsfTest)

target_link_libraries(BsfTest PRIVATE Qt5::Test)