
add_executable(tradesim main.cpp stochastic.cpp market.cpp stock.cpp bank.cpp simulator.cpp trading_day.cpp)
add_executable(test test.cpp)
#target_link_libraries(tradesim PUBLIC matplot)