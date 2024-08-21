#include <cstdio>
#include <fstream>
#include <sstream>
#include <ios>
#include <iostream>
#include <unordered_map>

#include "output.h"
#include "trading_day.h"



void const print(std::unordered_map<std::string, std::vector<OHLCData>> trading_day_data) {
    for (auto & [ticker, daily_data] : trading_day_data){
        std::cout << "Ticker: " << ticker << std::endl;
        for (auto & data : daily_data){
            std::cout << "Open: " << data.open << " Close: " << data.close << " High: " << data.high << " Low: " << data.low << " Volume: " << data.volume << std::endl;
        }
    }
}

std::stringstream  _construct_gnuplot_datafile(std::vector<OHLCData> trading_day_data) {
    std::stringstream data;
    int idx = 0;
    for (auto & market_data : trading_day_data){
        data << idx++ << " " << market_data.open << " " << market_data.low << " " << market_data.high << " " << market_data.close << std::endl;
    }
    return data;
}

std::vector<std::stringstream> const format_as_gnuplot(const std::unordered_map<std::string, std::vector<OHLCData>> trading_day_data) {
    auto output = std::vector<std::stringstream>();
    output.reserve(trading_day_data.size());
    for (auto & [ticker, daily_data] : trading_day_data){
        output.push_back(_construct_gnuplot_datafile(daily_data));
    }
    return output;
    // gnuplot> plot '/tmp/tmpfileXXXXXX' using 1:2:3:4:5 with candlesticks  
}

inline void const save(std::stringstream &data, std::string filename){
    std::ofstream outfile(filename, std::ios::out);
    if (!outfile) {
        throw std::runtime_error("Failed to open temporary file.");
    }

    data.seekp(0, std::ios::beg);
    outfile << data.rdbuf();

    outfile.close();
}

std::string const save(std::stringstream &file){
    char template_name[] = "/tmp/tmpfileXXXXXX";
    int fd = mkstemp(template_name);
    if (fd == -1) {
        // Handle error...
        throw std::runtime_error("Failed to create temporary file.");
    }

    save(file, template_name);
    return std::string(template_name);
}

std::vector<std::string> const save(std::vector<std::stringstream> &files){
    auto output = std::vector<std::string>();
    output.reserve(files.size());
    for (auto & file : files){
        output.push_back(save(file));
    }
    return output;
}

void const plot(std::vector<std::string> &files){
    std::string command = "gnuplot -p -e \"";
    command += "plot ";
    for (auto & file : files){
        command += "'" + file + "' using 1:2:3:4:5 with candlesticks, ";
    }
    command = command.substr(0, command.size() - 2); // remove the last 3 characters
    command += "\"";
    system(command.c_str());
}