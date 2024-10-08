#include<fstream>
#include<iostream>
#include<numeric>
#include<vector>

#include <boost/range/combine.hpp>
// #include<matplot/matplot.h>

//#include "bank.h"
#include "output.h"
#include "simulator.h"

void save_to_file(std::vector<float> & x_data, std::vector<float> & y_data, std::string filename){
    
    std::ofstream file;
    file.open(filename);
    float x, y;
    for (const auto & [x, y] : boost::combine(x_data, y_data)){
        file << x << " " << y << std::endl;
    };
    file.close();
}

int main(int argc, char *argv[]){
    // Read trading days, daily volume per stock and num stocks from stdin
    int trading_days, daily_volume_per_stock, num_stocks;

    trading_days = atoi(argv[1]);
    daily_volume_per_stock = atoi(argv[2]);
    num_stocks = atoi(argv[3]);
    

    auto sim = SimpleTimeBarDailySimulation(trading_days, daily_volume_per_stock, num_stocks);
    sim.run();
    sim.print();
    auto datafiles = format_as_gnuplot(sim.get_data());
    std::vector<std::string> outfiles = save(datafiles);
    
    std::cout << "Saved to: " << std::endl; 
    for (auto & file : outfiles){
        std::cout << file << std::endl;
    }
    plot(outfiles);
    std::cout << std::endl;

    return 0;
}