#pragma once

#include <memory>
#include <vector>

struct OHLCData{
    float open;
    float close;
    float high;
    float low;
};

class TradingDay {
    
    
    float trades_per_minute;
    OHLCData daily_data;
    std::unique_ptr<std::vector<OHLCData>> hourly_data;

    OHLCData _generate_OHLC_from_price_history(const std::vector<float> &ph);
    std::unique_ptr<std::vector<OHLCData>> _generate_hourly_data(const std::vector<float> &ph);

    public:
  
    TradingDay() = delete;
    TradingDay(std::vector<float> ph, float tpm) : trades_per_minute(tpm), daily_data(_generate_OHLC_from_price_history(ph)), hourly_data(_generate_hourly_data(ph)) {}
    TradingDay(OHLCData dd, std::unique_ptr<std::vector<OHLCData>> hd, float tpm) : daily_data(dd), hourly_data(std::move(hd)), trades_per_minute(tpm){}
    
    OHLCData get_daily_data() const;
    std::vector<OHLCData> get_hourly_data() const;

};