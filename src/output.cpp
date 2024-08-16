#include <cstdio>
#include <fstream>
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

std::vector<std::ofstream> const format_as_gnuplot(std::unordered_map<std::string, std::vector<OHLCData>> trading_day_data) {
    auto output = std::vector<std::ofstream>();
    output.reserve(trading_day_data.size());
    int idx = 0;
    for (auto & [ticker, daily_data] : trading_day_data){
        std::ofstream file;
        for (auto & data : daily_data){
            file << idx << "\t" << data.open << "\t" << data.high << "\t" << data.low << "\t" << data.close << std::endl;
        }
        file << std::endl;
        output.push_back(std::move(file));
        idx++;
    }
    return output;
}

void const save(std::ofstream &file, std::string filename){
    std::ofstream outfile(filename, std::ios::out);
    if (!outfile) {
        throw std::runtime_error("Failed to open temporary file.");
    }

    file.seekp(0, std::ios::beg);
    outfile << file.rdbuf();

    outfile.close();
}

std::string const save(std::ofstream &file){
    char tempname[L_tmpnam];
    std::tmpnam(tempname);
    save(file, tempname);
    return std::string(tempname);
}

std::vector<std::string> const save(std::vector<std::ofstream> &files){
    auto output = std::vector<std::string>();
    output.reserve(files.size());
    for (auto & file : files){
        output.push_back(save(file));
    }
    return output;
}
