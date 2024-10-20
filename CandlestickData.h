#pragma once

#include "WeatherBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

// WROTE WITHOUT ASSISTANCE START
class CandlestickData
{
    public:
        CandlestickData() = default;
        // construct by reading a csv file
        CandlestickData(std::string filename);
        // function to get data according to country 
        std::vector<CandlestickData> getCountriesData(std::vector<WeatherBookEntry>& data);
        // function to get stats according to year
        std::vector<double> getYearlyStats(const std::vector<CandlestickData>& countriesData, const std::string& country, int year);
        // function to get timestamp and temp according to country
        std::vector<std::pair<std::string, double>> getCountryData(const std::string& country) const;
        // get raw data, returns a vector of WeatherBookEntry objects
        std::vector<WeatherBookEntry> getData() const;
        // function filter data by timestamp and country
        void getFilterData(const std::vector<CandlestickData>& countriesData, const std::string& country, std::string timestamp);
        // function to print entire weather data for a specific country
        void printData(const std::vector<CandlestickData>& countriesData, const std::string& country);
        // function to print specific year of data for a country
        void printYear(const std::vector<CandlestickData>& countriesData, const std::string& country, std::string yearInput);
        // function to print specific month from a year for a country
        void printMonth(const std::vector<CandlestickData>& countriesData, const std::string& country, std::string yearInput, std::string monthInput);
        // function to print specific day from a month and year for a specific country
        void printDay(const std::vector<CandlestickData>& countriesData, const std::string& country, std::string yearInput, std::string monthInput, std::string dayInput);

        // country specific data, containing a vector of timestamp and temperature
        std::vector<std::pair<std::string, double>> countryAT;
        std::vector<std::pair<std::string, double>> countryBE;
        std::vector<std::pair<std::string, double>> countryBG; 
        std::vector<std::pair<std::string, double>> countryCH; 
        std::vector<std::pair<std::string, double>> countryCZ; 
        std::vector<std::pair<std::string, double>> countryDE; 
        std::vector<std::pair<std::string, double>> countryDK; 
        std::vector<std::pair<std::string, double>> countryEE; 
        std::vector<std::pair<std::string, double>> countryES; 
        std::vector<std::pair<std::string, double>> countryFI; 
        std::vector<std::pair<std::string, double>> countryFR; 
        std::vector<std::pair<std::string, double>> countryGB; 
        std::vector<std::pair<std::string, double>> countryGR; 
        std::vector<std::pair<std::string, double>> countryHR; 
        std::vector<std::pair<std::string, double>> countryHU; 
        std::vector<std::pair<std::string, double>> countryIE; 
        std::vector<std::pair<std::string, double>> countryIT; 
        std::vector<std::pair<std::string, double>> countryLT; 
        std::vector<std::pair<std::string, double>> countryLU; 
        std::vector<std::pair<std::string, double>> countryLV; 
        std::vector<std::pair<std::string, double>> countryNL; 
        std::vector<std::pair<std::string, double>> countryNO; 
        std::vector<std::pair<std::string, double>> countryPL; 
        std::vector<std::pair<std::string, double>> countryPT; 
        std::vector<std::pair<std::string, double>> countryRO; 
        std::vector<std::pair<std::string, double>> countrySE; 
        std::vector<std::pair<std::string, double>> countrySI; 
        std::vector<std::pair<std::string, double>> countrySK;
    
    private:
        // declaration of vector for raw weather data entries
        std::vector<WeatherBookEntry> data;

        // map to store country-specific data vectors
        std::map<std::string, std::vector<std::pair<std::string, double>>> countryDataMap;
        // initialise the map for storing country-specific data vectors
        void initialiseCountryDataMap();
};
// WROTE WITHOUT ASSISTANCE END