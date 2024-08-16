#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "market.h"
#include "trading_day.h"





struct StaticMarketInfo {
    float hours_per_trading_day;
    float total_volume;
};

struct ScenarioConfig {
    struct StaticMarketInfo market_configuration;
    int trading_days;
};

struct StockTrades{
    std::string ticker;
    TradingDay trades;
};

class StockMarketSimulation{
    protected:
    int trading_day = 0;
    const int trading_days;
    std::unique_ptr<Market> market;

    public:
    
    StockMarketSimulation(const int trading_days) : trading_days(trading_days), market(std::make_unique<Market>()){}
    StockMarketSimulation(const int trading_days, std::unique_ptr<Market> market) : trading_days(trading_days), market(std::move(market)){}
    StockMarketSimulation(int trading_days, int num_stocks) : StockMarketSimulation(trading_days){
        for (int i = 0; i < num_stocks; i++){
            market->add_stock("STOCK_" + std::to_string(i));
        }
    }
    StockMarketSimulation(int trading_days, std::vector<std::string> tickers) : StockMarketSimulation(trading_days){
        for (auto & ticker : tickers){
            market->add_stock(ticker);
        }
    }

    std::vector<std::string> get_tickers(){
        return market->get_tickers();
    }

    void run();
    virtual void handle(std::vector<StockTrades> &todays_data) = 0;
    virtual std::vector<StockTrades> advance() = 0;
};

class SimpleDailyStockSimulation : public StockMarketSimulation{
    /*
    Runs a simulation for a number of trading days with a fixed number of trades per minute.
    Generates a price history for each stock in the market in one operation.
    Outputs a mapping of stock tickers to price histories represented as vectors of OHLC data.
    */
    private:
    /* All member variables apply to every stock in the same way, eg volume, trades per minute etc*/
    const long int volume;
    float timestep;
    float HOURS_PER_TRADING_DAY = 6.5;
    int SECONDS_PER_TRADING_DAY = int(HOURS_PER_TRADING_DAY * 3600.0);


    protected:
    std::unordered_map<std::string, std::vector<OHLCData>> trading_day_data;

    public:
    using StockMarketSimulation::StockMarketSimulation;

    SimpleDailyStockSimulation(int trading_days, int volume, int num_stocks) : StockMarketSimulation(trading_days, num_stocks), volume(volume) {
        float avg_trades_per_second = float(volume) / float(SECONDS_PER_TRADING_DAY);
        timestep = float(SECONDS_PER_TRADING_DAY) / float(volume);
        for (auto & ticker : get_tickers()){
            auto time_bar_data = std::vector<OHLCData>();
            time_bar_data.reserve(trading_days);
            trading_day_data.insert({ticker, time_bar_data});
        }
    }

    SimpleDailyStockSimulation(int trading_days, int volume) : SimpleDailyStockSimulation(trading_days, volume, 1){}

    const std::unordered_map<std::string, std::vector<OHLCData>> get_data() const{
        return trading_day_data;
    }


    std::vector<StockTrades> advance() override;
    virtual void const print() const = 0;
};

class SimpleTimeBarDailySimulation : public SimpleDailyStockSimulation{
    public:
        SimpleTimeBarDailySimulation(int trading_days, int volume, int num_stocks) : SimpleDailyStockSimulation(trading_days, volume, num_stocks){}
        void handle(std::vector<StockTrades> &todays_data) override;
        void const print() const override;
};

class SimpleTickBarDailySimulation : public SimpleDailyStockSimulation{
    void handle(std::vector<StockTrades> &todays_data) override;

};

class SimpleVolumeBarDailySimulation : public SimpleDailyStockSimulation{
    void handle(std::vector<StockTrades> &todays_data) override;    
};
