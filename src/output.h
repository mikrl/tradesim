#pragma once

#include <fstream>
#include <unordered_map>
#include <vector>

#include "trading_day.h"

void const print(std::unordered_map<std::string, std::vector<OHLCData>> trading_day_data);
std::vector<std::ofstream> const format_as_gnuplot(std::unordered_map<std::string, std::vector<OHLCData>> trading_day_data);

void const save(std::ofstream &file, std::string filename);
std::string const save(std::ofstream &file);
std::vector<std::string> const save(std::vector<std::ofstream> &files);