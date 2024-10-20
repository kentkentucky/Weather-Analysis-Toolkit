#pragma once

#include <iostream>
#include <vector>
#include "CandlestickData.h"

// WROTE WITHOUT ASSISTANCE START
class WeatherPrediction
{
    public:
        // compute daily mean according to year
        std::vector<std::pair<std::string, double>> computeDailyMean(const std::vector<CandlestickData>& countriesData, const std::string& country, std::string date);
        // predict temperature value by calculating mean of year
        std::vector<std::pair<std::string, double>> predictFutureTemp(std::vector<std::pair<std::string, double>>& historicData,std::vector<std::string>& predictionDates);
        // WROTE WITHOUT ASSISTANCE END
        // print a graph according to predicted values
        void printLineGraph(const std::vector<std::pair<std::string, double>>& predictions);
};