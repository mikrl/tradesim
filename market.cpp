#include<chrono>
#include<memory>

#include "stochastic.h"
#include "market.h"

float Stock::price(float timestep){
    return price_process->next(timestep);
}