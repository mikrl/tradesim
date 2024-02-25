#include "stock.h"

float Stock::price(float timestep){
    return price_process->next(timestep);
}
