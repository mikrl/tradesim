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

std::unique_ptr<std::unordered_map<std::string, float>> Market::get_prices(float ts){
    auto prices = std::make_unique<std::unordered_map<std::string, float>> ();
    prices->reserve(stock_market.size());
    for (auto & stock : stock_market){
        prices->insert({stock->ticker, stock->price(ts)});
    }
    return prices;
}

std::unique_ptr<std::unordered_map<std::string, std::unique_ptr<std::vector<float>>>> Market::get_n_prices(int n, float ts){
    auto prices = std::unique_ptr<
                    std::unordered_map<std::string, std::unique_ptr<std::vector<float>>>>
                    (new std::unordered_map<std::string, std::unique_ptr<std::vector<float>>>());
    
    prices->reserve(stock_market.size());
    for (auto & stock : stock_market){
        auto price_data = std::make_unique<std::vector<float>>();
        price_data->reserve(n);
        for (int i = 0; i < n; i++){
            price_data->push_back(stock->price(ts));
        }
        prices->insert({stock->ticker, std::move(price_data)});
    }
    return prices;
}

void Market::add_stock(const std::string &t, float d, float v, float ip){
    auto new_stock = std::make_shared<Stock>(t, d, v, ip);
    tickermap.insert({t, new_stock});
    stock_market.push_back(new_stock);
}

void Market::add_stock(const std::string &t){
    add_stock(t, 0.5, 0.1, 1.0);
}

void Market::update_stock(const std::string &t, float d, float v, float p){
    auto stock = tickermap.find(t);
    stock->second->update(d, v, p);
}