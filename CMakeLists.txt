cmake_minimum_required(VERSION 3.22)
project(torture_fmt_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Try to find Catch2 provided by the system (e.g., Nix)
find_package(Catch2 3 REQUIRED)

if(NOT Catch2_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.4
    )
    FetchContent_MakeAvailable(catch2)
endif()

find_package(fmt REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(eigen-fmt REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(RBDyn REQUIRED)
find_package(SpaceVecAlg REQUIRED)

add_executable(torture-fmt test/torture_fmt.cpp)
target_include_directories(torture-fmt PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(
    torture-fmt
    PRIVATE fmt::fmt Boost::filesystem eigen-fmt::eigen-fmt Eigen3::Eigen
)

target_link_libraries(torture-fmt PRIVATE Catch2::Catch2WithMain)

enable_testing()
add_test(NAME torture-fmt COMMAND torture-fmt)
