cmake_minimum_required(VERSION 3.22)

project(oroe LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.2
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(raylib)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/entities/player/player.cpp
    src/entities/enemies/enemy.cpp
    src/shared/base.cpp
    src/shared/creature.cpp
    src/shared/weapon.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

function(enableProjectWarnings targetName)
    # Header bên thứ ba không thuộc phạm vi warning policy của mã dự án.
    target_include_directories(${targetName} SYSTEM PRIVATE $<TARGET_PROPERTY:raylib,INTERFACE_INCLUDE_DIRECTORIES>)
    if(MSVC)
        target_compile_options(${targetName} PRIVATE /W4 /WX /we4062)
    else()
        target_compile_options(${targetName} PRIVATE -Wall -Wextra -Wpedantic -Werror -Werror=switch -Wswitch-enum)
    endif()
endfunction()

enableProjectWarnings(${PROJECT_NAME})

include(CTest)
if(BUILD_TESTING)
    add_executable(player_test
        tests/player_test.cpp
        src/entities/player/player.cpp
        src/entities/enemies/enemy.cpp
        src/shared/base.cpp
        src/shared/creature.cpp
        src/shared/weapon.cpp
    )
    add_executable(weapon_mastery_test
        tests/weapon_mastery_test.cpp
        src/shared/base.cpp
        src/shared/creature.cpp
        src/shared/weapon.cpp
    )
    foreach(testTarget IN ITEMS player_test weapon_mastery_test)
        target_include_directories(${testTarget} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
        target_link_libraries(${testTarget} PRIVATE raylib)
        enableProjectWarnings(${testTarget})
        if(MSVC)
            target_compile_options(${testTarget} PRIVATE /UNDEBUG)
        else()
            target_compile_options(${testTarget} PRIVATE -UNDEBUG)
        endif()
        add_test(NAME ${testTarget} COMMAND ${testTarget})
    endforeach()
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)
