cmake_minimum_required(VERSION 3.10)
project(tradesim)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(matplotplusplus)
find_package(Boost COMPONENTS REQUIRED)

add_executable(tradesim main.cpp stochastic.cpp market.cpp stock.cpp bank.cpp)
target_link_libraries(tradesim PUBLIC matplot)