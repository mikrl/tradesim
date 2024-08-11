#pragma once

#include<memory>
#include<string>
#include<unordered_map>

#include "stock.h"

using PriceMap = std::unordered_map<std::string, float>;
/* Don't be smart, rewrite nPriceMap to just map a string to a vector*/
using nPriceMap = std::unordered_map<std::string, std::unique_ptr<std::vector<float>>>; 

class Market {

    std::vector<std::shared_ptr<Stock>> stock_market;
    std::unordered_map<std::string, std::shared_ptr<Stock>> tickermap;

    public:
    std::vector<std::string> get_tickers();
    std::unique_ptr<PriceMap> get_prices(float timestep);
    std::unique_ptr<nPriceMap> get_next_n_prices(int num_timesteps, float timestep);
    float get_price(const std::string &ticker, float timestep);
    void add_stock(const std::string &ticker);
    void add_stock(const std::string &ticker, float drift, float volatility, float init_price);
    void update_stock(const std::string &ticker, float drift, float volatility, float price);

};
