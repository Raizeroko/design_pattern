cmake_minimum_required(VERSION 3.20)

project(design_pattern_labs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_library(lab_test_framework INTERFACE)
target_include_directories(lab_test_framework INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

function(add_lesson_test lesson_name source_file)
    add_executable(${lesson_name}_test ${source_file})
    target_link_libraries(${lesson_name}_test PRIVATE lab_test_framework)
    target_compile_options(${lesson_name}_test PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
    )
    add_test(NAME ${lesson_name} COMMAND ${lesson_name}_test)
endfunction()

add_lesson_test(strategy lessons/01_strategy/tests/strategy_test.cpp)
add_lesson_test(factory lessons/02_factory/tests/factory_test.cpp)
add_lesson_test(observer lessons/03_observer/tests/observer_test.cpp)
add_lesson_test(decorator lessons/04_decorator/tests/decorator_test.cpp)
add_lesson_test(adapter lessons/05_adapter/tests/adapter_test.cpp)
add_lesson_test(template_method lessons/06_template_method/tests/template_method_test.cpp)
add_lesson_test(state lessons/07_state/tests/state_test.cpp)
add_lesson_test(command lessons/08_command/tests/command_test.cpp)
add_lesson_test(singleton lessons/09_singleton/tests/singleton_test.cpp)
add_lesson_test(facade lessons/10_facade/tests/facade_test.cpp)
