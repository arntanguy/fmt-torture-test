cmake_minimum_required(VERSION 3.22)
project(torture_fmt_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(fmt REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem unit_test_framework)
find_package(eigen-fmt REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(RBDyn REQUIRED)
find_package(SpaceVecAlg REQUIRED)

add_executable(torture-fmt test/torture_fmt.cpp)
target_include_directories(torture-fmt PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(
    torture-fmt
    PRIVATE
        fmt::fmt
        Boost::filesystem
        Boost::unit_test_framework
        eigen-fmt::eigen-fmt
        Eigen3::Eigen
)

enable_testing()
add_test(NAME torture-fmt COMMAND torture-fmt)
