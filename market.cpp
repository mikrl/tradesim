#include<memory>
#include<vector>

#include "market.h"


float Market::get_price(std::string ticker, float timestep){
    auto stock = tickermap.find(ticker);
    float price = stock->second->price(timestep);
    return price;
}

std::vector<float> Market::get_prices(float timestep){
    std::vector<float> prices;
    prices.reserve(stock_market.size());
    for (auto & stock : stock_market){
        prices.push_back(stock->price(timestep));
    }
    return prices;
}

void Market::add_stock(std::string t, float d, float v, float ip){
    auto new_stock = std::make_shared<Stock>(t, d, v, ip);
    tickermap.insert({t, new_stock});
    stock_market.push_back(new_stock);
}

void Market::add_stock(std::string t){
    add_stock(t, 0.5, 0.1, 1.0);
}