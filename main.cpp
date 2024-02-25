#include<iostream>
#include<vector>

#include<matplot/matplot.h>

#include "bank.h"
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
    
    Market market = Market{};
    market.add_stock("SNEED", drift, volatility, price);
    market.add_stock("CHUCK", drift*0.1, volatility*1.05, price*10);

    BankAccount bank_acc = BankAccount(0.04, 10); 

    std::vector<float> prices_1;
    std::vector<float> prices_2;
    std::vector<float> bank;

    prices_1.reserve(steps.size());
    prices_2.reserve(steps.size());
    bank.reserve(steps.size());

    for (auto const & _ : steps){
        auto prices = market.get_prices(timestep);
        prices_1.push_back(prices[0]);
        prices_2.push_back(prices[1]);
        bank.push_back(bank_acc.get_balance());
        bank_acc.apply_interest(timestep);
    }
    const auto & s = steps;

    
    auto plt1 = plt::plot(prices_1, "r");
    plt1->display_name("SNEED");

    plt::hold(plt::on);
    plt::title("Market");
    plt::xlabel("Time");
    plt::ylabel("Price ($)");
    auto plt2 = plt::plot(prices_2, "b");
    plt2->display_name("CHUCK");

    auto plt3 = plt::plot(bank, "g");
    plt3->display_name("BANK");

    plt::legend();
   
    plt::show();

    return 0;
}
