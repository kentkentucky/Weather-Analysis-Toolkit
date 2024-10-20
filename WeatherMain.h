#pragma once

#include <vector>
#include "WeatherBookEntry.h"
#include "CandlestickData.h"
#include "WeatherPrediction.h"

class WeatherMain
{
    public:
        WeatherMain();
        /** call this to start the sim */
        void init();
        // constructor to hold csv file
        CandlestickData candlestickData{"weather_data_EU_1980-2019_temp_only.csv"};

    private:
        // function declaration
        void printMenu();
        void printHelp();
        // WROTE WITHOUT ASSISTANCE START
        // function to print stats
        void printCandlestickData();
        // function to draw candlestick plot
        void printCandlestickPlot();
        // function to filter and plot data
        void filterDataAndPlot();
        // prediction function
        void predictDataandPlot();
        int getUserOption();
        void processUserOption(int userOption);
        // print the list of country
        void printCountryOption();
        // function to get input
        std::string getCountryOption();
        // function to process input
        void processFilterOption(std::string countryOption);
        // function to check if timestamp is in csv file
        bool checkValidTimestamp (std::string timestamp);
        // function to predict temperature
        void processPredictionOption(std::string countryInput);
        // function to check if timestamp is not within csv
        bool checkPredictionTimestamp(std::string timestamp);
        // function to get dates from date range
        std::vector<std::string> getDatesBetween(std::string startRange, std::string endRange);
        // function to get date
        std::tm parseDate(std::string date);

        // data member to handle weather prediction
        WeatherPrediction weatherPrediction;
        // WROTE WITHOUT ASSISTANCE END
};