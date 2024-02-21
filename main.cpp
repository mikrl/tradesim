#include<iostream>
#include<vector>

#include<matplot/matplot.h>

#include "market.h"
#include "stochastic.h"

namespace plt = matplot;

int main(){

    float volatility = 0.05;
    
    float timestep = 0.001;
    float drift = 0.1;

    float price = 1.0;
    

    int NUM_STEPS = 10000;

    std::vector<int> steps(NUM_STEPS);
    std::iota(steps.begin(), steps.end(), 1);
    
    auto stock_1 = Stock("SNEED", drift, volatility, price); 
    auto stock_2 = Stock("CHUCK", drift*0.1, volatility*1.05, price*10);

    std::vector<float> prices_1;
    std::vector<float> prices_2;

    prices_1.reserve(steps.size());
    prices_2.reserve(steps.size());

    for (auto const & _ : steps){
        float p1 = stock_1.price(timestep);
        float p2 = stock_2.price(timestep);
        prices_1.push_back(p1);
        prices_2.push_back(p2);
    }
    const auto & s = steps;
    plt::hold(plt::on);
    auto plt1 = plt::plot(prices_1, "r");
    plt1->display_name(stock_1.ticker);
    auto plt2 = plt::plot(prices_2, "b");
    plt2->display_name(stock_2.ticker);
    plt::legend();
    plt::title("Market");
    plt::xlabel("Time");
    plt::ylabel("Price ($)");
    plt::show();

    return 0;
}
