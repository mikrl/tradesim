#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "simulator.h"


MarketTiming StockMarketSimulation::get_timing_config(){
    float hours_per_trading_day = 6.5; // 9:30am - 4:00pm
    float minutes_per_trading_day = hours_per_trading_day * 60;
    float total_trades_per_day = minutes_per_trading_day * config.trades_per_minute;
    float time_between_trades = 1.0 / config.trades_per_minute;

    return {
        hours_per_trading_day,
        minutes_per_trading_day,
        total_trades_per_day,
        time_between_trades
    };
}

void StockMarketSimulation::run(){
    for (int i = 0; i < config.trading_days; i++){
        advance();
    }
}

std::unique_ptr<std::unordered_map<std::string, TradingDay>> SimpleMultiStockSimulation::advance(){
    auto timing = get_timing_config();

    float timestep = timing.time_between_trades;
    float trades_per_day = timing.total_trades_per_day;

    auto raw_prices = market->get_n_prices(trades_per_day, timestep);

    std::unordered_map<std::string, TradingDay> _this_trading_day;

    for (auto & stock : market->get_tickers()){
        auto price_data = raw_prices->find(stock);
        auto & prices = *price_data->second;

        TradingDay trading_day = TradingDay(prices, config.trades_per_minute);
        std::pair<std::string, TradingDay> trading_day_pair = {stock, trading_day};
        _this_trading_day.insert(trading_day_pair);
    }

    trading_day_data->push_back(_this_trading_day);
    return std::make_unique<std::unordered_map<std::string, TradingDay>>(_this_trading_day);
}   



