#pragma once

#include <sstream>
#include <unordered_map>
#include <vector>

#include "trading_day.h"

void const print(std::unordered_map<std::string, std::vector<OHLCData>> trading_day_data);
std::stringstream  _construct_gnuplot_datafile(std::vector<OHLCData> trading_day_data);
std::vector<std::stringstream> const format_as_gnuplot(std::unordered_map<std::string, std::vector<OHLCData>> trading_day_data);

void const save(std::stringstream &file, std::string filename);
std::string const save(std::stringstream &file);
std::vector<std::string> const save(std::vector<std::stringstream> &files);

void const plot(std::vector<std::string> &files);