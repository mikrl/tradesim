#pragma once

#include <memory>
#include <string>

#include "stochastic.h"

struct Stock
{
    const std::string ticker;
    std::shared_ptr<stochastic_process> price_process;
    Stock(std::string t, float d, float v, float ip) : 
        ticker(t), price_process(std::make_shared<stochastic_process> (d, v, ip)){}
    float price(float timestep);
    void update(float drift, float volatility, float price);
};
