#include "WeatherPrediction.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

// WROTE WITHOUT ASSISTANCE START
// TASK 4
std::vector<std::pair<std::string, double>> WeatherPrediction::computeDailyMean(const std::vector<CandlestickData>& countriesData, const std::string& country, std::string date)
{
    // create vector for pair of string and double
    std::vector<std::pair<std::string, double>> meanData;
    // iterate over years
    for(int year = 1980; year <= 2019; ++year)
    {
        // initialise values
        double sum = 0;
        double count = 0;
        // iterate over countriesData vector
        for(const auto& data : countriesData)
        {
            // get specific country data
            auto countryEntries = data.getCountryData(country);
            // iterate over specific country data
            for(const auto & entry : countryEntries)
            {
                // convert string into int from timestamp
                int yearStr = std::stoi(entry.first.substr(0, 4));
                // compare for matching year
                if(year == yearStr)
                {
                    // get the month and day and convert it to a string
                    std::string monthDayStr = entry.first.substr(5, 5);
                    // check for match
                    if(monthDayStr == date)
                    {
                        // calculate sum and count
                        sum += entry.second;
                        count++;
                    }
                }
            }
        }
        if(count > 0)
        {
            // calculate mean
            double mean = sum / count;
            // get date by combining string
            std::string fullDate = std::to_string(year) + "-" + date;
            // push pair into vector
            meanData.emplace_back(fullDate, mean);
        }
    }
    // return vector
    return meanData;
}

std::vector<std::pair<std::string, double>> WeatherPrediction::predictFutureTemp(std::vector<std::pair<std::string, double>>& historicData,std::vector<std::string>& predictionDates)
{
    // create vector for pair of string and data
    std::vector<std::pair<std::string, double>> predictions;
    // iterate over mean data
    for (const auto& date : predictionDates)
    {
        // initialise sum and count to 0
        double sum = 0;
        double count = 0;
        // get month and date string
        std::string predictionMonthDay = date.substr(5, 5);

        // iterate over historicData
        for (const auto& data : historicData)
        {
            // get string if month and day
            std::string historyMonthDay = data.first.substr(5, 5);
            // get matches
            if (historyMonthDay == predictionMonthDay)
            {
                // get sum and count
                sum += data.second;
                count++;
            }
        }
        // calculate mean
        double mean = sum / count;
        // push mean and date in vector
        predictions.emplace_back(date, mean);
    }
    // return vector
    return predictions;
}
// WROTE WITHOUT ASSISTANCE END

void WeatherPrediction::printLineGraph(const std::vector<std::pair<std::string, double>>& predictions)
{
    // find the minimum and maximum temperatures for scaling the graph
    double minTemp = predictions.front().second;
    double maxTemp = predictions.front().second;
    for (const auto& entry : predictions)
    {
        if (entry.second < minTemp) minTemp = entry.second;
        if (entry.second > maxTemp) maxTemp = entry.second;
    }

    // scale factor for the graph height
    const int graphHeight = 20;
    double scale = (maxTemp - minTemp) / graphHeight;

    // print the graph
    for (int i = 0; i < graphHeight; ++i)
    {
        double currentLevel = maxTemp - i * scale;
        std::cout << std::setw(6) << std::fixed << std::setprecision(2) << currentLevel << " |";

        for (const auto& entry : predictions)
        {
            if (entry.second >= currentLevel && entry.second < currentLevel + scale)
            {
                std::cout << std::setw(3) << "*";
            }
            else
            {
                std::cout << std::setw(3) << "  ";
            }
        }
        std::cout << std::endl;
    }

    // print the x-axis labels
    std::cout << std::setw(6) << "       ";
    for (const auto& entry : predictions)
    {
        std::cout << "---";
    }
    std::cout << std::endl;

    std::cout << "       ";
    for (const auto& entry : predictions)
    {
        std::cout << entry.first.substr(8, 2) + " ";
    }
    std::cout << std::endl;
}