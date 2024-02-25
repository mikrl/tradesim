#pragma once

#include<memory>
#include<string>
#include<unordered_map>

#include "stochastic.h"
#include "stock.h"

class Market {

    std::vector<std::shared_ptr<Stock>> stock_market;
    float interest_rate;
    std::unordered_map<std::string, std::shared_ptr<Stock>> tickermap;

    public:
    std::vector<float> get_prices(float timestep);
    float get_price(std::string ticker, float timestep);
    void add_stock(std::string ticker);
    void add_stock(std::string ticker, float drift, float volatility, float init_price);

};
