cmake_minimum_required(VERSION 3.10)
project(tradesim)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_subdirectory(matplotplusplus)
find_package(Boost COMPONENTS REQUIRED)

add_executable(tradesim src/main.cpp src/stochastic.cpp src/market.cpp src/stock.cpp src/bank.cpp src/simulator.cpp src/trading_day.cpp)
#target_link_libraries(tradesim PUBLIC matplot)