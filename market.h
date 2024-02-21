#pragma once

#include<chrono>
#include<memory>
#include<string>
#include<unordered_map>

#include "stochastic.h"

struct Stock
{
    std::string ticker;
    std::shared_ptr<stochastic_process> price_process;
    Stock(std::string t, float d, float v, float ip) : 
        ticker(t), price_process(std::make_shared<stochastic_process> (d, v, ip)){}
    float price(float timestep);
};

class Market {

    std::vector<std::shared_ptr<Stock>> stock_market;
    float interest_rate;
    std::unordered_map<std::string, std::shared_ptr<Stock>> tickermap;
    void add_stock(std::string ticker);
    void add_stock(std::string ticker, float drift, float volatility, float init_price);

    public:
    std::vector<float> get_prices();
    float get_price(std::string ticker);

};
