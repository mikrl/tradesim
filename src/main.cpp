#include<fstream>
#include<iostream>
#include<numeric>
#include<vector>

#include <boost/range/combine.hpp>
// #include<matplot/matplot.h>

#include "bank.h"
#include "market.h"
#include "simulator.h"
#include "stochastic.h"

// namespace plt = matplot;

void save_to_file(std::vector<float> & x_data, std::vector<float> & y_data, std::string filename){
    
    std::ofstream file;
    file.open(filename);
    float x, y;
    for (const auto & [x, y] : boost::combine(x_data, y_data)){
        file << x << " " << y << std::endl;
    };
    file.close();
}

int main(){
    int trading_days = 1;
    int trades_per_minute = 10;
    int num_stocks = 3;

    auto sim = SimpleMultiStockSimulation(trading_days, trades_per_minute, num_stocks);
    sim.run();

    return 0;
}