cmake_minimum_required(VERSION 3.20)

project(design_pattern_labs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

function(add_lesson_test lesson_name source_file)
    # Each exercise is built on demand. Unfinished later lessons therefore do not
    # block the lesson currently being practiced.
    add_executable(${lesson_name}_test EXCLUDE_FROM_ALL ${source_file})
    target_include_directories(${lesson_name}_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_compile_options(${lesson_name}_test PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
    )
    add_test(NAME ${lesson_name} COMMAND ${lesson_name}_test)
endfunction()

add_lesson_test(strategy lessons/01_strategy/test.cpp)
add_lesson_test(factory lessons/02_factory/test.cpp)
add_lesson_test(observer lessons/03_observer/test.cpp)
add_lesson_test(decorator lessons/04_decorator/test.cpp)
add_lesson_test(adapter lessons/05_adapter/test.cpp)
add_lesson_test(template_method lessons/06_template_method/test.cpp)
add_lesson_test(state lessons/07_state/test.cpp)
add_lesson_test(command lessons/08_command/test.cpp)
add_lesson_test(singleton lessons/09_singleton/test.cpp)
add_lesson_test(facade lessons/10_facade/test.cpp)
