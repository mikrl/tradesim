#include <algorithm>
#include <cmath>
#include <vector>

#include "trading_day.h"

OHLCData TradingDay::_generate_OHLC_from_price_history(const std::vector<float> &ph){
    /* Turns a vector of floats representing stock prices for some period into a vector of OHLC data.*/
    float open = ph.front();
    float close = ph.back();
    float high = *std::max_element(ph.begin(), ph.end());
    float low = *std::min_element(ph.begin(), ph.end());
    return {open, close, high, low};
}

std::unique_ptr<std::vector<OHLCData>> TradingDay::_generate_hourly_data(const std::vector<float> &ph){
    /* Returns a vector of OHLC data for each hour of the trading day.*/
    float hours_per_trading_day = 6.5; // 9:30am - 4:00pm
    float trades_per_trading_day = ph.size();
    float trades_per_hour = trades_per_trading_day / hours_per_trading_day;

    std::unique_ptr<std::vector<OHLCData>> hourly_data = std::make_unique<std::vector<OHLCData>>();
    
    hourly_data->reserve(std::ceil(hours_per_trading_day));

    int trades_this_hour = std::floor(trades_per_hour);
    for (int processed_trades = 0; processed_trades < trades_per_trading_day; processed_trades += trades_this_hour){
        std::vector<float> hourly_window;

        if (processed_trades + trades_this_hour > trades_per_trading_day){
            /* If the last hour of trading is not a full hour, we need to handle this case.*/
            hourly_window = std::vector<float>(ph.begin() + processed_trades, ph.end());
        } else {
            hourly_window = std::vector<float>(ph.begin() + processed_trades, ph.begin() + processed_trades + trades_this_hour);
        }
        
        auto start = ph.begin() + processed_trades;
        auto end = ph.begin() + processed_trades + trades_this_hour;
        std::vector<float> prices_this_hour(start, end);
        hourly_data->push_back(_generate_OHLC_from_price_history(prices_this_hour));
    }


    return hourly_data;
}