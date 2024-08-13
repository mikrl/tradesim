#include<memory>
#include<string>
#include<vector>

#include "market.h"

std::vector<std::string> Market::get_tickers(){
    std::vector<std::string> tickers;
    tickers.reserve(stock_market.size());
    for (auto & stock : stock_market){
        tickers.push_back(stock->ticker);
    }
    return tickers;
}

float Market::get_price(const std::string &t, float ts){
    auto stock = tickermap.find(t);
    float price = stock->second->price(ts);
    return price;
}

std::unique_ptr<PriceMap> Market::get_prices(float ts){
    auto prices = std::make_unique<PriceMap>();
    prices->reserve(stock_market.size());
    for (auto & stock : stock_market){
        prices->insert({stock->ticker, stock->price(ts)});
    }
    return prices;
}

std::unique_ptr<nPriceMap> Market::get_next_n_prices(int n, float ts){
    /*
    For every entry in the get_prices map, we want to add it to prices, the nPriceMap.
    Essentially, for every stock that we received prices for, append it to the vector in prices it is keyed on, n times.
    */
    auto prices = std::unique_ptr<nPriceMap>(new nPriceMap());

    prices->reserve(stock_market.size());


    for (auto & stock : get_tickers()){
        auto vec = std::vector<float>();
        vec.reserve(n);
        prices->insert({stock, vec});
    }
    
    for (int i = 0; i < n; i++){
        auto price_map = get_prices(ts);
        for (auto & stock : get_tickers()){
            auto stock_price = price_map->at(stock);
            prices->at(stock).push_back(stock_price);
        }
    }
    
    return prices;
}

void Market::add_stock(const std::string &t, float d, float v, float ip){
    auto new_stock = std::make_shared<Stock>(t, d, v, ip);
    tickermap.insert({t, new_stock});
    stock_market.push_back(new_stock);
}

void Market::add_stock(const std::string &t){
    // Since we are not given any parameters, we can just call the other add_stock function with default parameters.
    // Choosing the volatility to be 1% per day, averaged over each second
    add_stock(t, 0.1/86400, 10.0/86400, 30.0);
}

void Market::update_stock(const std::string &t, float d, float v, float p){
    auto stock = tickermap.find(t);
    stock->second->update(d, v, p);
}