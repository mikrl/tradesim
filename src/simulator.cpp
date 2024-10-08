#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "simulator.h"
#include "trading_day.h"


void StockMarketSimulation::run(){
    std::cerr << "Running simulation for " << trading_days << " trading days." << std::endl;
    for (; trading_day < trading_days; trading_day++){
        std::cerr << "Day " << trading_day << std::endl;
        auto todays_data = advance();
        handle(todays_data);
    }

}


std::vector<StockTrades> SimpleDailyStockSimulation::advance(){
    /* Advances by 1 trading day*/
    int daily_volume_per_stock = volume;
    auto raw_prices = market->get_next_n_prices(daily_volume_per_stock, timestep);

    auto tickers = market->get_tickers();

    std::vector<StockTrades> todays_data = {};
    std::chrono::time_point<std::chrono::system_clock> start_time = std::chrono::system_clock::now();
    for (auto & stock_ticker : tickers){
        auto& prices = raw_prices->at(stock_ticker);
        TradingDay trading_day;
        for (auto price : prices){
            auto delta = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::duration<float>(timestep));
            long tick = trading_day.get_tick();
            trading_day.add_transaction(price, 1, start_time + tick * delta);
        }
        todays_data.push_back({stock_ticker, trading_day});
    }

    return todays_data;
}   

void SimpleTimeBarDailySimulation::handle(std::vector<StockTrades> &todays_data){
    /* Handles the data generated by the simulation for a single trading day.*/
    for (auto & stock_history : todays_data){
        auto & ticker = stock_history.ticker;
        auto & trades = stock_history.trades;
        auto daily_bar = trades.get_daily_data();
        trading_day_data.at(ticker).push_back(daily_bar);
    }

}

void SimpleTickBarDailySimulation::handle(std::vector<StockTrades> &todays_data){
    /* Handles the data generated by the simulation for a single trading day.*/
    for (auto & stock_history : todays_data){
        auto & ticker = stock_history.ticker;
        auto & trades = stock_history.trades;
        auto daily_bar = trades.get_daily_data();
        trading_day_data.at(ticker).push_back(daily_bar);
    }

}


void const SimpleTimeBarDailySimulation::print() const{
    for (auto & [ticker, daily_data] : trading_day_data){
        std::cout << "Ticker: " << ticker << std::endl;
        for (auto & data : daily_data){
            std::cout << "Open: " << data.open << " Close: " << data.close << " High: " << data.high << " Low: " << data.low << " Volume: " << data.volume << std::endl;
        }
    }
}

