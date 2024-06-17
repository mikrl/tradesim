#include<cmath>
#include<random>
 
#include "stochastic.h"

struct BrownianRNG{
    std::random_device randgen{};
    std::normal_distribution<float> diffusion{0.0, 1.0};
};

float stochastic_process::get_current_value(){
    return current_value;
};

float stochastic_process::next(float timestep){
    BrownianRNG rng;
    auto randwalk = rng.diffusion(rng.randgen);
    float delta = current_value*(drift*timestep + volatility*randwalk*std::sqrt(timestep));
    current_value += delta;
    return current_value;
}

std::shared_ptr<std::vector<float>> stochastic_process::next_n(float timestep, int n){
    window->reserve(n);
    for (int i=0; i<n; i++){
        auto next = this->next(timestep);
        window->push_back(next);
    }
    return window;
}

void stochastic_process::update(float d, float v, float cv){
    drift = d;
    volatility = v;
    current_value = cv;
}