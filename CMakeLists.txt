cmake_minimum_required(VERSION 3.20)

project(design_pattern_labs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

function(add_lesson_test lesson_name source_file)
    add_executable(${lesson_name}_test ${source_file})
    target_include_directories(${lesson_name}_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_compile_options(${lesson_name}_test PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
    )
    add_test(NAME ${lesson_name} COMMAND ${lesson_name}_test)
endfunction()

add_lesson_test(strategy_before lessons/01_strategy/before_test.cpp)
add_lesson_test(strategy_after lessons/01_strategy/after_test.cpp)
add_lesson_test(factory_before lessons/02_factory/before_test.cpp)
add_lesson_test(factory_after lessons/02_factory/after_test.cpp)
add_lesson_test(observer_before lessons/03_observer/before_test.cpp)
add_lesson_test(observer_after lessons/03_observer/after_test.cpp)
add_lesson_test(decorator_before lessons/04_decorator/before_test.cpp)
add_lesson_test(decorator_after lessons/04_decorator/after_test.cpp)
add_lesson_test(adapter_before lessons/05_adapter/before_test.cpp)
add_lesson_test(adapter_after lessons/05_adapter/after_test.cpp)
add_lesson_test(template_method_before lessons/06_template_method/before_test.cpp)
add_lesson_test(template_method_after lessons/06_template_method/after_test.cpp)
add_lesson_test(state_before lessons/07_state/before_test.cpp)
add_lesson_test(state_after lessons/07_state/after_test.cpp)
add_lesson_test(command_before lessons/08_command/before_test.cpp)
add_lesson_test(command_after lessons/08_command/after_test.cpp)
add_lesson_test(singleton_before lessons/09_singleton/before_test.cpp)
add_lesson_test(singleton_after lessons/09_singleton/after_test.cpp)
add_lesson_test(facade_before lessons/10_facade/before_test.cpp)
add_lesson_test(facade_after lessons/10_facade/after_test.cpp)
