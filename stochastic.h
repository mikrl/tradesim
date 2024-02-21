#pragma once

#include<memory>
#include<vector>

class stochastic_process {
    float current_value;
    float drift;
    float volatility;
    std::shared_ptr<std::vector<float>> window = std::make_shared<std::vector<float>>();

    public:
        stochastic_process(float d, float v, float cv = 1.0) {current_value = cv; drift = d; volatility = v;}
        stochastic_process() = delete;
        stochastic_process(const stochastic_process& sp) {current_value = sp.current_value; drift = sp.drift; volatility = sp.volatility;}
        float get_current_value();
        float next(float timestep);
        std::shared_ptr<std::vector<float>> get_n(float timestep, int n);
};     