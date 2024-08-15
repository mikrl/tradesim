# Tradesim
A simple stock market simulator.

## Building
`mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && make`

## Running
`./tradesim [num days] [total volume] [num stocks]`
eg
```
./tradesim 10 100 1                                                                                                                              
Running simulation for 10 trading days.
Day 0
Day 1
Day 2
Day 3
Day 4
Day 5
Day 6
Day 7
Day 8
Day 9
Ticker: STOCK_0
Open: 30.0439 Close: 32.1692 High: 32.1692 Low: 30.0439 Volume: 100
Open: 32.1479 Close: 32.5461 High: 32.5461 Low: 31.8117 Volume: 100
Open: 32.5619 Close: 34.2683 High: 34.4253 Low: 32.5461 Volume: 100
Open: 34.2691 Close: 33.8046 High: 34.5995 Low: 33.7158 Volume: 100
Open: 33.6732 Close: 35.3491 High: 35.3491 Low: 33.6732 Volume: 100
Open: 35.3813 Close: 35.4434 High: 35.8289 Low: 35.1355 Volume: 100
Open: 35.4709 Close: 35.2721 High: 35.9522 Low: 35.0006 Volume: 100
Open: 35.2954 Close: 34.8599 High: 35.6496 Low: 34.8338 Volume: 100
Open: 34.8303 Close: 35.3745 High: 35.3745 Low: 34.528 Volume: 100
Open: 35.3569 Close: 36.7404 High: 36.9984 Low: 35.3285 Volume: 100
                                                                                                                                                
```