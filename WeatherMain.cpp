#include "WeatherMain.h"
#include "WeatherBookEntry.h"
#include "CSVReader.h"
#include "CandlestickData.h"
#include "CandlestickPlot.h"
#include "WeatherPrediction.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>
#include <chrono>

// WROTE WITHOUT ASSISTANCE START
WeatherMain::WeatherMain()
{

}

void WeatherMain::init()
{
    int input;

    while(true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void WeatherMain::printMenu()
{
     // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print candlestick data
    std::cout << "2: Print candlestick data " << std::endl;
    // 3 print candlestick plot
    std::cout << "3: Print candlestick plot " << std::endl;
    // 4 print filter data and plotting
    std::cout << "4: Filter data and plotting " << std::endl;
    // 5 print predicting data and plotting
    std::cout << "5: Predicting data and plotting " << std::endl;

    std::cout << "=============================== " << std::endl;
}

void WeatherMain::printHelp()
{
    std::cout << "Help - the goal of this assignment is to develop a technical analysis toolkit for visualising and predicting weather data." << std::endl;
}

// TASK 1
void WeatherMain::printCandlestickData()
{
    // retrieve data from csv
    std::vector<WeatherBookEntry> entries = candlestickData.getData();
    // process entries to get data according to each country
    std::vector<CandlestickData> countriesData = candlestickData.getCountriesData(entries);
    // intialise country code
    std::string country = "GB";

    // print header 
    // std::setw to assign width to each header
    std::cout << "Country " << country << std::endl;
    std::cout << std::left << std::setw(10) << "Date"
              << std::setw(10) << "Open"
              << std::setw(10) << "High"
              << std::setw(10) << "Low"
              << std::setw(10) << "Close" << std::endl;

    // loop through each year of csv to retrieve and display stats
    for (int year = 1980; year <= 2019; ++year) 
    {
        // convert year to string
        std::string date = std::to_string(year);
        // get yearly stats for specified country and year
        std::vector<double> stats = candlestickData.getYearlyStats(countriesData, country, year);
        
        // print the date and stats accordingly (open, high, low, close)
        std::cout << std::left << std::setw(10) << date
                  << std::setw(10) << stats[0]
                  << std::setw(10) << stats[1]
                  << std::setw(10) << stats[2]
                  << std::setw(10) << stats[3] << std::endl;
    }
}

// TASK 2
void WeatherMain::printCandlestickPlot() 
{
    // retrieve data from csv
    std::vector<WeatherBookEntry> entries = candlestickData.getData();
    // process entries to get data according to each country
    std::vector<CandlestickData> countriesData = candlestickData.getCountriesData(entries);
    // intialise country code
    std::string country = "AT";

    // print country name
    std::cout << "Country " << country << std::endl;

    // declare vector to hold candlestick data
    std::vector<CandlestickPlot> candlesticks;
    // loop through every year
    for (int year = 1980; year <= 2019; ++year) 
    {
        // convert year to string
        std::string date = std::to_string(year);
        // hold yearly stats for specified country and year in vector
        std::vector<double> stats = candlestickData.getYearlyStats(countriesData, country, year);
        
        // create candlestick object from retrieved stats
        CandlestickPlot candlestick(date, stats[0], stats[1], stats[2], stats[3]);
        // add candlestick object into vector
        candlesticks.push_back(candlestick);
    }
    // print candlestick plot passing in step size for y axis
    CandlestickPlot::printCandlestickPlot(candlesticks, 0.25);
}

// TASK 3
void WeatherMain::filterDataAndPlot()
{
    // create string for country input
    std::string countryInput;
    // print instruction to user
    std::cout << "Type in the country you want to filter" << std::endl;
    // call function
    printCountryOption();
    // get input
    countryInput = getCountryOption();
    // process input accordingly
    processFilterOption(countryInput);
}

// TASK 4
void WeatherMain::predictDataandPlot()
{
    // create string for country input
    std::string countryInput;
    // print instruction for user
    std::cout << "Type in country you want to see predictions for" << std::endl;
    // print list of country
    printCountryOption();
    // get input from user
    countryInput = getCountryOption();
    // process input
    processPredictionOption(countryInput);
}

void WeatherMain::printCountryOption()
{
    // list of countries
    std::cout << "AT" << std::endl;
    std::cout << "BE" << std::endl;
    std::cout << "BG" << std::endl;
    std::cout << "CH" << std::endl;
    std::cout << "CZ" << std::endl;
    std::cout << "DE" << std::endl;
    std::cout << "DK" << std::endl;
    std::cout << "EE" << std::endl;
    std::cout << "ES" << std::endl;
    std::cout << "FI" << std::endl;
    std::cout << "FR" << std::endl;
    std::cout << "GB" << std::endl;
    std::cout << "GR" << std::endl;
    std::cout << "HR" << std::endl;
    std::cout << "HU" << std::endl;
    std::cout << "IE" << std::endl;
    std::cout << "IT" << std::endl;
    std::cout << "LT" << std::endl;
    std::cout << "LU" << std::endl;
    std::cout << "LV" << std::endl;
    std::cout << "NL" << std::endl;
    std::cout << "NO" << std::endl;
    std::cout << "PL" << std::endl;
    std::cout << "PT" << std::endl;
    std::cout << "RO" << std::endl;
    std::cout << "SE" << std::endl;
    std::cout << "SI" << std::endl;
    std::cout << "SK" << std::endl;
}

std::string WeatherMain::getCountryOption()
{
    // create string for input
    std::string line;
    // print instructions
    std::cout << "Type in the country" << std::endl;
    std::cout << "e.g GB" << std::endl;
    // get user input
    std::getline(std::cin, line);
    // display user input
    std::cout << "You choose: " << line << std::endl;
    // return user input
    return line;
}

int WeatherMain::getUserOption()
{
    // intialise input to 0
    int userOption = 0;
    // create string for input
    std::string line;
    // print instruction
    std::cout << "Type in 1-5" << std::endl;
    // get user input
    std::getline(std::cin, line);
    try
    {
        // convert string to int
        userOption = std::stoi(line);
    }
    catch(const std::exception& e)
    {
        //
    }
    // display input
    std::cout << "You choose: " << userOption << std::endl;
    // return input
    return userOption;
}

void WeatherMain::processUserOption(int userOption)
{
    if (userOption == 0)
    {
        // bad input
        std::cout << "Invalid choice. Choose 1-5" << std::endl;
    }
    if (userOption == 1) 
    {
        printHelp();
    }
    if (userOption == 2) 
    {
        printCandlestickData();
    }
    if (userOption == 3) 
    {
        printCandlestickPlot();
    }
    if (userOption == 4) 
    {
        filterDataAndPlot();
    }
    if (userOption == 5) 
    {
        predictDataandPlot();
    }
}

void WeatherMain::processFilterOption(std::string countryOption)
{
    // create string for timestamp input
    std::string timestampInput;
    // check for correct inputs
    if (countryOption == "AT" || countryOption == "BE" || countryOption == "BG" || countryOption == "CH" || countryOption == "CZ" || countryOption == "DE"
        || countryOption == "DK" || countryOption == "EE" || countryOption == "ES" || countryOption == "FI" || countryOption == "FR" || countryOption == "GB" 
        || countryOption == "GR" || countryOption == "HR" || countryOption == "HU" || countryOption == "IE" || countryOption == "IT" || countryOption == "LT" 
        || countryOption == "LU" || countryOption == "LV" || countryOption == "NL" || countryOption == "NO" || countryOption == "PL" || countryOption == "PT" 
        || countryOption == "RO" || countryOption == "SE" || countryOption == "SI" || countryOption == "SK")
    {
        // print instructions for user
        std::cout << "Type in the year, month and day you want to filter out" << std::endl;
        std::cout << "Timestamp: YYYY-MM-DD" << std::endl;
        std::cout << "If you want to view data and plot according to country e.g 0000-00-00" << std::endl;
        std::cout << "If you want to view data and plot according to country and year e.g 2000-00-00" << std::endl;
        std::cout << "If you want to view data and plot according to country, year and month e.g 2000-05-00" << std::endl;
        std::cout << "If you want to view data and plot according to country, year, month and day e.g 2000-05-01" << std::endl;
        // get timestamp
        std::getline(std::cin, timestampInput);
        // check for valid timestamp-within csv
        if(!checkValidTimestamp(timestampInput))
        {
            // print instruction for invalid timestamp
            std::cout << "Invalid timestamp. Please enter a valid date, within 1980 - 2019." << std::endl;
        }
        else
        {
            // retrieve data from csv
            std::vector<WeatherBookEntry> entries = candlestickData.getData();
            // process entries to get data according to each country
            std::vector<CandlestickData> countriesData = candlestickData.getCountriesData(entries);
            // call function to filter data according to timestamp
            candlestickData.getFilterData(countriesData, countryOption, timestampInput);
        }
    }
    else
    {
        // bad input
        std::cout << "Invalid input. Type in valid country." << std::endl;
    }
}
// WROTE WITHOUT ASSISTANCE END

bool WeatherMain::checkValidTimestamp(std::string timestamp)
{
    // check the format of the timestamp
    if (timestamp.length() != 10 || timestamp[4] != '-' || timestamp[7] != '-') 
    {
        return false;
    }
    // return true if timestamp is 0000-00-00
    if (timestamp == "0000-00-00")
    {
        return true;
    }

    // extract year, month, and day
    std::string yearStr = timestamp.substr(0, 4);
    std::string monthStr = timestamp.substr(5, 2);
    std::string dayStr = timestamp.substr(8, 2);

    // convert year, month, and day to integers
    int year = std::stoi(yearStr);
    int month = std::stoi(monthStr);
    int day = std::stoi(dayStr);

    // check if year is within the valid range
    if (year < 1980 || year > 2019) 
    {
        return false;
    }

    // check if month is within the valid range
    if (month < 0 || month > 12) 
    {
        return false;
    }

    // check if day is within the valid range
    if (day < 0 || day > 31) 
    {
        return false;
    }

    // additional check for specific days in each month
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) 
    {
        return false;
    }

    // check for feb
    if (month == 2) 
    {
        // check for leap year
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeapYear && day > 29) 
        {
            return false;
        } 
        else if (!isLeapYear && day > 28) 
        {
            return false;
        }
    }

    return true;
}

bool WeatherMain::checkPredictionTimestamp(std::string timestamp)
{
    // Check the format of the timestamp
    if (timestamp.length() != 10 || timestamp[4] != '-' || timestamp[7] != '-') 
    {
        return false;
    }

    // extract year, month, and day
    std::string yearStr = timestamp.substr(0, 4);
    std::string monthStr = timestamp.substr(5, 2);
    std::string dayStr = timestamp.substr(8, 2);

    // convert year, month, and day to integers
    int year = std::stoi(yearStr);
    int month = std::stoi(monthStr);
    int day = std::stoi(dayStr);

    // decline years that are below 2019
    if (year < 2019) 
    {
        return false;
    }

    // check if month is within the valid range
    if (month < 0 || month > 12) 
    {
        return false;
    }

    // check if day is within the valid range
    if (day < 0 || day > 31) 
    {
        return false;
    }

    // additional check for specific days in each month
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) 
    {
        return false;
    }

    // check for feb
    if (month == 2) 
    {
        // check leap year
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeapYear && day > 29) 
        {
            return false;
        } 
        else if (!isLeapYear && day > 28) 
        {
            return false;
        }
    }

    return true;
}

// WROTE WITHOUT ASSISTANCE START
void WeatherMain::processPredictionOption(std::string countryInput)
{
    // create strings to get date range
    std::string startRange;
    std::string endRange;
    // check for correct input
    if (countryInput == "AT" || countryInput == "BE" || countryInput == "BG" || countryInput == "CH" || countryInput == "CZ" || countryInput == "DE"
        || countryInput == "DK" || countryInput == "EE" || countryInput == "ES" || countryInput == "FI" || countryInput == "FR" || countryInput == "GB" 
        || countryInput == "GR" || countryInput == "HR" || countryInput == "HU" || countryInput == "IE" || countryInput == "IT" || countryInput == "LT" 
        || countryInput == "LU" || countryInput == "LV" || countryInput == "NL" || countryInput == "NO" || countryInput == "PL" || countryInput == "PT" 
        || countryInput == "RO" || countryInput == "SE" || countryInput == "SI" || countryInput == "SK")
    {
        // print instruction
        std::cout << "Type in the start of prediction date range in YYYY-MM-DD format" << std::endl;
        // get start date
        std::getline(std::cin, startRange);
        // check if date is valid
        if(!checkPredictionTimestamp(startRange))
        {
            // bad input
            std::cout << "Invalid timestamp. Please enter a valid date, 2019 onwards" << std::endl;
        }
        else
        {
            // print instructions
            std::cout << "Type in the end of prediction date range in YYYY-MM-DD format" << std::endl;
            // get end date
            std::getline(std::cin, endRange);
            // check valid date
            if(!checkPredictionTimestamp(endRange))
            {
                // bad input
                std::cout << "Invalid timestamp. Please enter a valid date, 2019 onwards" << std::endl;
            }
            else
            {
                // get the days between the date range input
                std::vector<std::string> dates = getDatesBetween(startRange, endRange);
                // retrieve data from csv
                std::vector<WeatherBookEntry> entries = candlestickData.getData();
                // process entries to get data according to country
                std::vector<CandlestickData> countriesData = candlestickData.getCountriesData(entries);
                // create vector that accepts a pair of string and double
                std::vector<std::pair<std::string, double>> historicData;
                // loop through date range
                for(const auto& date : dates)
                {
                    // create string to contain month and day of date
                    std::string monthDay = date.substr(5, 5);
                    // create vector to store string and double for date and mean value
                    std::vector<std::pair<std::string, double>> meanData = weatherPrediction.computeDailyMean(countriesData, countryInput, monthDay);
                    // append computed mean data to historicData vector
                    historicData.insert(historicData.end(), meanData.begin(), meanData.end());
                }
                // predict future temperature based on historical data and specified date range
                std::vector<std::pair<std::string, double>> predictions = weatherPrediction.predictFutureTemp(historicData, dates);
                // loop through predictions
                for (const auto& prediction : predictions)
                {
                    // print predicted temperature and dates
                    std::cout << "Date: " << prediction.first << ", Predicted Temperature: " << prediction.second << std::endl;
                }
                // plot a graph according to predicted values
                weatherPrediction.printLineGraph(predictions);
            }
        }
    }
    else
    {
        // bad input
        std::cout << "Invalid input. Type in valid country." << std::endl;
    }
}
// WROTE WITHOUT ASSISTANCE END

// function to parse a date string in the format of MMMM-YY-DD
std::tm WeatherMain::parseDate(std::string date) 
{
    std::tm tm = {};
    std::istringstream ss(date);
    // parse the date string into the std::tm struct
    ss >> std::get_time(&tm, "%Y-%m-%d");
    if (ss.fail()) 
    {
        // error if parsing failed
        throw std::runtime_error("Failed to parse date: " + date);
    }
    return tm;
}

// function to get all dates between startRange and endRange
std::vector<std::string> WeatherMain::getDatesBetween(std::string startRange, std::string endRange) 
{
    // create vector of string to store dates
    std::vector<std::string> dates;

    // parse the start and end date strings
    std::tm startTm = parseDate(startRange);
    std::tm endTm = parseDate(endRange);

    // convert the std::tm structs to time points
    std::chrono::system_clock::time_point start = std::chrono::system_clock::from_time_t(std::mktime(&startTm));
    std::chrono::system_clock::time_point end = std::chrono::system_clock::from_time_t(std::mktime(&endTm));

    // iterate over each day from start to end and add the date string to the dates vector
    for (std::chrono::system_clock::time_point current = start; current <= end; current += std::chrono::hours(24)) 
    {
        std::time_t currentTime = std::chrono::system_clock::to_time_t(current);
        // covert time point 
        std::tm* currentTm = std::localtime(&currentTime);

        //convert date string into YYYY-MM-DD format and push in to vector
        std::ostringstream ss;
        ss << std::put_time(currentTm, "%Y-%m-%d");
        dates.push_back(ss.str());
    }

    return dates;
}