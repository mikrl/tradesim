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
        virtual float next(float timestep);
        std::shared_ptr<std::vector<float>> next_n(float timestep, int n);
        void update(float d, float v, float cv);
};     

class stock_process : public stochastic_process {
    private:
        bool hit_zero = false;
    public:
        stock_process(float d, float v, float cv = 1.0) : stochastic_process(d, v, cv) {}
        stock_process() = delete;
        stock_process(const stock_process& sp) : stochastic_process(sp) {}
        float next(float timestep) override;
};