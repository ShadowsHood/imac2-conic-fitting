cmake_minimum_required(VERSION 3.20)

project(conic_fitting LANGUAGES C CXX)

# Download the sil library
include(FetchContent)
FetchContent_Declare(
    sil
    GIT_REPOSITORY https://github.com/JulesFouchy/Simple-Image-Lib
    GIT_TAG 89bd175cd55fb6daa9e99b218e869c3d516043f4
)
FetchContent_MakeAvailable(sil)

function(add_exercise FOLDER)
    add_executable(${FOLDER})

    # include Eigen
    find_package(Eigen3)
    if(${EIGEN3_FOUND})
        message(STATUS "lib EIGEN3 found")
        message(STATUS "  version " ${EIGEN3_VERSION_STRING})
        message(STATUS "  include " ${EIGEN3_INCLUDE_DIR})
    else()
        set(EIGEN3_INCLUDE_DIR "C:/Users/elvin/Documents/IMAC/Projets/eigen-3.4.0")  #Path to the Eigen library
        message(STATUS "  include " ${EIGEN3_INCLUDE_DIR})
        #message(FATAL_ERROR "lib EIGEN3 not found")
    endif()

    # C++ version
    target_compile_features(${FOLDER} PRIVATE cxx_std_17)

    # Prevents compiler-specific extensions to C++ because they might allow code to compile on your machine but not on other people's machine
    set_target_properties(${FOLDER} PROPERTIES
        CXX_EXTENSIONS OFF)

    # Add all the source files
    file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/${FOLDER}/* lib/*)
    target_sources(${FOLDER} PRIVATE ${SOURCES})
    target_include_directories(${FOLDER} PRIVATE src/${FOLDER} lib)

    

    # lib include path
    target_link_libraries(${FOLDER} PRIVATE sil)
    target_include_directories(${FOLDER} PRIVATE "${EIGEN3_INCLUDE_DIR}")

endfunction(add_exercise)

add_exercise(conic_fitting)
add_exercise(fractale)
add_exercise(rosace)