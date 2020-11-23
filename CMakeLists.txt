cmake_minimum_required(VERSION 3.17)

set(META_PROJECT_AUTHOR integer-overflown)
set(META_PROJECT_NAME chi-internship-labs)

set(CMAKE_CXX_STANDARD 20)

include(cmake-utils/AddAssetsDirectory.cmake)

project(
        ${META_PROJECT_NAME}
        VERSION 1
        HOMEPAGE_URL https://github.com/${META_PROJECT_AUTHOR}/${META_PROJECT_NAME}
        LANGUAGES CXX
)

add_subdirectory(solutions)

