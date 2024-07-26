#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "market.h"
#include "trading_day.h"



struct SimulatorConfig{
    int trading_days;
    int trades_per_minute;
};

struct MarketTiming {
    float hours_per_trading_day;
    float minutes_per_trading_day;
    float total_trades_per_day;
    float time_between_trades;
};

class StockMarketSimulation{
    protected:
    int trading_day = 0;
    std::unique_ptr<Market> market;
    std::shared_ptr<std::vector<std::unordered_map<std::string, TradingDay>>> trading_day_data;

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

    MarketTiming get_timing_config();

    void run();
    virtual std::unique_ptr<std::unordered_map<std::string, TradingDay>> advance() = 0;
};

class SimpleMultiStockSimulation : public StockMarketSimulation{
    /*
    Runs a simulation for a number of trading days with a fixed number of trades per minute.
    Generates a price history for each stock in the market in one operation.
    Outputs a mappikng of stock tickers to price histories represented as vectors of OHLC data.
    */
    public:
    using StockMarketSimulation::StockMarketSimulation;
    std::unique_ptr<std::unordered_map<std::string, TradingDay>> advance() override;
};