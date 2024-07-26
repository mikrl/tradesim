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
    int trading_days = 260;
    int trades_per_minute = 1000;
    int num_stocks = 10;

    auto sim = SimpleMultiStockSimulation(trading_days, trades_per_minute, num_stocks);
    sim.run();

    return 0;
}


// int main(){

//     float volatility = 0.05;
    
//     float timestep = 0.001;
//     float drift = 0.1;

//     float price = 1.0;
    

//     int NUM_STEPS = 10000;

//     std::vector<float> steps(NUM_STEPS);
//     std::iota(steps.begin(), steps.end(), 1);
    
//     Market market = Market{};
//     market.add_stock("SNEED", drift, volatility, price);
//     market.add_stock("CHUCK", drift*0.1, volatility*1.05, price*10);

//     BankAccount bank_acc = BankAccount(0.04, 10); 

//     std::vector<float> prices_1;
//     std::vector<float> prices_2;
//     std::vector<float> bank;

//     prices_1.reserve(steps.size());
//     prices_2.reserve(steps.size());
//     bank.reserve(steps.size());

//     for (auto const & _ : steps){
//         auto prices = market.get_prices(timestep);
//         prices_1.push_back(prices->at("SNEED"));
//         prices_2.push_back(prices->at("CHUCK"));
//         bank.push_back(bank_acc.get_balance());
//         bank_acc.apply_interest(timestep);
//     }
//     auto & s = steps;

//     save_to_file(s, prices_1, "sneed.txt");
//     save_to_file(s, prices_2, "chuck.txt");
//     save_to_file(s, bank, "bank.txt");
//     // auto plt1 = plt::plot(prices_1, "r");
//     // plt1->display_name("SNEED");

//     // plt::hold(plt::on);
//     // plt::title("Market");
//     // plt::xlabel("Time");
//     // plt::ylabel("Price ($)");
//     // auto plt2 = plt::plot(prices_2, "b");
//     // plt2->display_name("CHUCK");

//     // auto plt3 = plt::plot(bank, "g");
//     // plt3->display_name("BANK");

//     // plt::legend();
   
//     // plt::show();

//     return 0;
// }
