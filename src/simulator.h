#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "market.h"

struct TradingDay{
    float open;
    float close;
    float high;
    float low;
};

struct SimulatorConfig{
    int trading_days;
    int trades_per_minute;
};


class StockMarketSimulation{
    protected:
    int trading_day = 0;
    std::unique_ptr<Market> market;
    std::unordered_map<std::string, std::vector<float>> raw_prices;

    public:
    SimulatorConfig config;
    StockMarketSimulation(int trading_days, int trades_per_minute) : config({trading_days, trades_per_minute}) , market(std::make_unique<Market>()){}
    StockMarketSimulation(int trading_days, int trades_per_minute, std::unique_ptr<Market> market) : config({trading_days, trades_per_minute}), market(std::move(market)){}
    StockMarketSimulation(int trading_days, int trades_per_minute, int num_stocks) : StockMarketSimulation(trading_days, trades_per_minute){
        for (int i = 0; i < num_stocks; i++){
            market->add_stock("STOCK_" + std::to_string(i));
        }
    }
    StockMarketSimulation(int trading_days, int trades_per_minute, std::vector<std::string> tickers) : StockMarketSimulation(trading_days, trades_per_minute){
        for (auto & ticker : tickers){
            market->add_stock(ticker);
        }
    }
    virtual void advance() = 0;
    const std::vector<TradingDay>& get_price_data() const;

};

class SimpleMultiStockSimulation : public StockMarketSimulation{
    public:
    void advance() override;
};