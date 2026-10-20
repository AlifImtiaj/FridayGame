
cmake_minimum_required(VERSION 3.21)

project(Game LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Windows: statically link the MSVC C++ runtime.
# Release: /MT
# Debug:   /MTd
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY
        "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    )
endif()

# Source files
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(Game
    ${SOURCE_FILES}
)

# Your own headers
target_include_directories(Game PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Compiler warnings
if(MSVC)
    target_compile_options(Game PRIVATE /W4)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(Game PRIVATE -Wall -Wextra)
endif()

if(WIN32)
    # Original SDL Visual C++ development packages.
    set(SDL3_ROOT
        "C:/api/SDL3/SDL3-3.4.18"
    )
    set(SDL3_IMAGE_ROOT
        "C:/api/SDL3/SDL3_image-3.4.8"
    )
    set(SDL3_TTF_ROOT
        "C:/api/SDL3/SDL3_ttf-3.2.2"
    )
    set(SDL3_MIXER_ROOT
        "C:/api/SDL3/SDL3_mixer-3.2.4"
    )

    # Let CMake search the package configurations in these roots.
    list(PREPEND CMAKE_PREFIX_PATH
        "${SDL3_ROOT}"
        "${SDL3_IMAGE_ROOT}"
        "${SDL3_TTF_ROOT}"
        "${SDL3_MIXER_ROOT}"
    )

    find_package(SDL3 REQUIRED CONFIG)
    find_package(SDL3_image REQUIRED CONFIG)
    find_package(SDL3_ttf REQUIRED CONFIG)
    find_package(SDL3_mixer REQUIRED CONFIG)

elseif(UNIX)
    # Linux: use packages installed for the native Linux toolchain.
    find_package(SDL3 REQUIRED CONFIG)
    find_package(SDL3_image REQUIRED CONFIG)
    find_package(SDL3_ttf REQUIRED CONFIG)
    find_package(SDL3_mixer REQUIRED CONFIG)
    find_package(glm CONFIG REQUIRED)
endif()

target_link_libraries(Game PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_ttf::SDL3_ttf
    SDL3_mixer::SDL3_mixer
)

if(WIN32)
    target_include_directories(Game PRIVATE
        "C:/api/glm/include"
    )
elseif(UNIX)
    find_package(glm CONFIG REQUIRED)
    target_link_libraries(Game PRIVATE glm::glm)
endif()

# Copy runtime DLLs beside Game.exe on Windows.
if(WIN32)
    add_custom_command(TARGET Game POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy
            $<TARGET_RUNTIME_DLLS:Game>
            "$<TARGET_FILE_DIR:Game>"
        COMMAND_EXPAND_LISTS
    )
endif()
