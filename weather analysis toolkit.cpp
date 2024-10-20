[ File: /Users/User/Desktop/OOP/Mid Term/weather/src/WeatherPrediction.cpp ]
-----
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
                std::cout << " *";
            }
            else
            {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }

    // print the x-axis labels
    std::cout << "       ";
    for (const auto& entry : predictions)
    {
        std::cout << "---";
    }
    std::cout << std::endl;

    std::cout << "       ";
    for (const auto& entry : predictions)
    {
        std::cout << entry.first.substr(8, 2) << " ";
    }
    std::cout << std::endl;
}
-----
[ File: /Users/User/Desktop/OOP/Mid Term/weather/src/CandlestickData.cpp ]
-----
#include "CandlestickData.h"
#include "CSVReader.h"
#include "CandlestickPlot.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <stdexcept>
#include <iomanip>

// WROTE WITHOUT ASSISTANCE START
// constructs CandleStickObject and intialise it by reading data from csv file
CandlestickData::CandlestickData(std::string filename)
{
    // read data from csv file and store it in data vector
    data = CSVReader::readCSV(filename);
    // WROTE WITHOUT ASSISTANCE END
    // intialise the map for storing country-specific data vectors
    initialiseCountryDataMap();
}

// get raw data
std::vector<WeatherBookEntry> CandlestickData::getData() const
{
    return data;
}

// get temperature data and timestamp from each country from weather data
std::vector<CandlestickData> CandlestickData::getCountriesData(std::vector<WeatherBookEntry>& data)
{
    // create vector to store data of all country
    std::vector<CandlestickData> countriesData;
    // map country name to timestamp and temperature
    std::map<std::string, std::vector<std::pair<std::string, double>>> tempDataMap;
    // iterate over data
    for (const auto& entry : data) 
    {
        // add temperature data and timestamp to temporary map
        tempDataMap["AT"].emplace_back(entry.timestamp, entry.at);
        tempDataMap["BE"].emplace_back(entry.timestamp, entry.be);
        tempDataMap["BG"].emplace_back(entry.timestamp, entry.bg);
        tempDataMap["CH"].emplace_back(entry.timestamp, entry.ch);
        tempDataMap["CZ"].emplace_back(entry.timestamp, entry.cz);
        tempDataMap["DE"].emplace_back(entry.timestamp, entry.de);
        tempDataMap["DK"].emplace_back(entry.timestamp, entry.dk);
        tempDataMap["EE"].emplace_back(entry.timestamp, entry.ee);
        tempDataMap["ES"].emplace_back(entry.timestamp, entry.es);
        tempDataMap["FI"].emplace_back(entry.timestamp, entry.fi);
        tempDataMap["FR"].emplace_back(entry.timestamp, entry.fr);
        tempDataMap["GB"].emplace_back(entry.timestamp, entry.gb);
        tempDataMap["GR"].emplace_back(entry.timestamp, entry.gr);
        tempDataMap["HR"].emplace_back(entry.timestamp, entry.hr);
        tempDataMap["HU"].emplace_back(entry.timestamp, entry.hu);
        tempDataMap["IE"].emplace_back(entry.timestamp, entry.ie);
        tempDataMap["IT"].emplace_back(entry.timestamp, entry.it);
        tempDataMap["LT"].emplace_back(entry.timestamp, entry.lt);
        tempDataMap["LU"].emplace_back(entry.timestamp, entry.lu);
        tempDataMap["LV"].emplace_back(entry.timestamp, entry.lv);
        tempDataMap["NL"].emplace_back(entry.timestamp, entry.nl);
        tempDataMap["NO"].emplace_back(entry.timestamp, entry.no);
        tempDataMap["PL"].emplace_back(entry.timestamp, entry.pl);
        tempDataMap["PT"].emplace_back(entry.timestamp, entry.pt);
        tempDataMap["RO"].emplace_back(entry.timestamp, entry.ro);
        tempDataMap["SE"].emplace_back(entry.timestamp, entry.se);
        tempDataMap["SI"].emplace_back(entry.timestamp, entry.si);
        tempDataMap["SK"].emplace_back(entry.timestamp, entry.sk);
    }

    // iterate temporary map
    for (auto it = tempDataMap.begin(); it != tempDataMap.end(); ++it) 
    {
        const std::string& country = it->first;
        const std::vector<std::pair<std::string, double>>& data = it->second;
        // transfer data to the country-specific vector
        CandlestickData candlestickData;
        candlestickData.countryDataMap[country] = data;
        countriesData.push_back(candlestickData);
    }

    return countriesData;
}

// initialise map for storing country-specific data vectors
void CandlestickData::initialiseCountryDataMap()
{
    countryDataMap["AT"] = {};
    countryDataMap["BE"] = {};
    countryDataMap["BG"] = {};
    countryDataMap["CH"] = {};
    countryDataMap["CZ"] = {};
    countryDataMap["DE"] = {};
    countryDataMap["DK"] = {};
    countryDataMap["EE"] = {};
    countryDataMap["ES"] = {};
    countryDataMap["FI"] = {};
    countryDataMap["FR"] = {};
    countryDataMap["GB"] = {};
    countryDataMap["GR"] = {};
    countryDataMap["HR"] = {};
    countryDataMap["HU"] = {};
    countryDataMap["IE"] = {};
    countryDataMap["IT"] = {};
    countryDataMap["LT"] = {};
    countryDataMap["LU"] = {};
    countryDataMap["LV"] = {};
    countryDataMap["NL"] = {};
    countryDataMap["NO"] = {};
    countryDataMap["PL"] = {};
    countryDataMap["PT"] = {};
    countryDataMap["RO"] = {};
    countryDataMap["SE"] = {};
    countryDataMap["SI"] = {};
    countryDataMap["SK"] = {};
}

// returns associated vector of timestamp-temperature pair for the input country
std::vector<std::pair<std::string, double>> CandlestickData::getCountryData(const std::string& country) const
{
    auto it = countryDataMap.find(country);
    if (it != countryDataMap.end()) 
    {
        return it->second;
    } 
    else
    {
        return {};
    }
}

// WROTE WITHOUT ASSISTANCE START
// TASK 1
// function to get yearly stats
std::vector<double> CandlestickData::getYearlyStats(const std::vector<CandlestickData>& countriesData, const std::string& country, int year) 
{
    // initialise stats 
    double open = 0,
           high = -100,
           low = 100,
           close = 0;
    double sumCurrYear = 0,
           sumPrevYear = 0;
    int countCurrYear = 0,
        countPrevYear = 0;
    // convert int year to str
    std::string yearStr = std::to_string(year);
    std::string prevYearStr = std::to_string(year - 1);

    // iterate countriesData
    for (const auto& data : countriesData) 
    {
        // get data for specific country
        auto countryEntries = data.getCountryData(country);

        // iterate over the data for that specific country
        for (const auto& entry : countryEntries) 
        {
            // create string and filter the year
            std::string entryYear = entry.first.substr(0, 4);
            // check for matching year
            if (entryYear == yearStr) 
            {
                // initialise value with first data/temp
                double value = entry.second;
                // compare value with high
                if(value > high)
                {
                    // intialise new high if temp is higher
                    high = value;
                }
                // compare temp with low
                if(value < low)
                {
                    // initialise new low if value is lower
                    low = value;
                }
                // add all temp to sum of current year
                sumCurrYear += entry.second;
                // increase count by 1
                countCurrYear++;
            }
            // check timestamp is same as previous year
            else if (entryYear == prevYearStr)
            {
                // add all temp in previous year
                sumPrevYear += entry.second;
                // increase count by 1
                countPrevYear++;
            }
        }
    }
    if (countPrevYear > 0) 
    {
        // calculate open
        open = sumPrevYear / countPrevYear;
    } 
    else 
    {
        open = 0;
    }

    if (countCurrYear > 0) 
    {
        // calculate close
        close = sumCurrYear / countCurrYear;
    } 
    else 
    {
        close = 0;
    }

    if (countCurrYear == 0 )
    {
        // no data found
        throw std::runtime_error("No data found for the specified country and year.");
    }

    // return stats
    return {open, high, low, close};
}

// TASK 3
// function to filter data according to timestamp
void CandlestickData::getFilterData(const std::vector<CandlestickData>& countriesData, const std::string& country, std::string timestamp)
{
    // get year from timestamp
    std::string yearInput = timestamp.substr(0, 4);
    // get month from timestamp
    std::string monthInput = timestamp.substr(5, 2);
    // get day from timestamp
    std::string dayInput = timestamp.substr(8, 2);
    // print entire data set of country
    if(yearInput == "0000")
    {
        printData(countriesData, country);
    }
    // print specific year of data
    if(monthInput == "00")
    {
        printYear(countriesData, country, yearInput);
    }
    // print specific month and year of data
    if(dayInput == "00")
    {
        printMonth(countriesData, country, yearInput, monthInput);
    }
    // print specifc day of data
    if(dayInput != "00")
    {
        printDay(countriesData, country, yearInput, monthInput, dayInput);
    }
}

// TASK 3
void CandlestickData::printData(const std::vector<CandlestickData>& countriesData, const std::string& country)
{
    // create vector to store stats
    std::vector<CandlestickPlot> candlesticks;
    // print header
    std::cout << "Country " << country << std::endl;
    std::cout << std::left << std::setw(10) << "Date"
                << std::setw(10) << "Open"
                << std::setw(10) << "High"
                << std::setw(10) << "Low"
                << std::setw(10) << "Close" << std::endl;
    // iterate through every year
    for(int year = 1980; year <= 2019; ++year)
    {
        // initialise stats 
        double open = 0,
                high = -100,
                low = 100,
                close = 0;
        double sumCurrYear = 0,
                sumPrevYear = 0;
        int countCurrYear = 0,
            countPrevYear = 0;
        // convert int to str for comparison
        std::string yearStr = std::to_string(year);
        std::string prevYearStr = std::to_string(year - 1);
        // iterate through countriesData
        for (const auto& data : countriesData) 
        {
            // get specific country data
            auto countryEntries = data.getCountryData(country);

            // iterate through the specific country data
            for (const auto& entry : countryEntries) 
            {
                // get year from timestamp and convert into string
                std::string entryYear = entry.first.substr(0, 4);
                if (entryYear == yearStr) 
                {
                    // get high, low
                    double value = entry.second;
                    if(value > high)
                    {
                        high = value;
                    }
                    if(value < low)
                    {
                        low = value;
                    }
                    // get sum and entry count
                    sumCurrYear += entry.second;
                    countCurrYear++;
                }
                // get prev year data
                else if (entryYear == prevYearStr)
                {
                    sumPrevYear += entry.second;
                    countPrevYear++;
                }
            }
        }
        if (countPrevYear > 0) 
        {
            // calculate open
            open = sumPrevYear / countPrevYear;
        } 
        else 
        {
            open = 0;
        }

        if (countCurrYear > 0) 
        {
            // calculate close
            close = sumCurrYear / countCurrYear;
        } 
        else 
        {
            close = 0;
        }

        if (countCurrYear == 0 )
        {
            // no data
            throw std::runtime_error("No data found for the specified country and year.");
        }

        // print out the stats accordingly
        std::cout << std::left << std::setw(10) << year
                    << std::setw(10) << open
                    << std::setw(10) << high
                    << std::setw(10) << low
                    << std::setw(10) << close << std::endl;
        
        // convert year to string for display
        std::string date = std::to_string(year);
        // create candlestickplot object
        CandlestickPlot candlestick(date, open, high, low, close);
        // push object into vector
        candlesticks.push_back(candlestick);
    }
    // print candlestickplot
    CandlestickPlot::printCandlestickPlot(candlesticks, 0.25);
    exit(0);
}
// WROTE WITHOUT ASSISTANCE END

// TASK 3
// WROTE WITHOUT ASSISTANCE
void CandlestickData::printYear(const std::vector<CandlestickData>& countriesData, const std::string& country, std::string yearInput)
{
    // create vector for candletickplot object
    std::vector<CandlestickPlot> candlesticks;
    // print header
    std::cout << "Country " << country << std::endl;
    std::cout << "Year: " << yearInput << std::endl;
    std::cout << std::left << std::setw(10) << "Month"
                << std::setw(10) << "Open"
                << std::setw(10) << "High"
                << std::setw(10) << "Low"
                << std::setw(10) << "Close" << std::endl;
    // convert string to int
    int year = std::stoi(yearInput);
    // loop over the months
    for(int month = 1; month <= 12; ++month)
    {
        // initialise stats 
        double open = 0,
               high = -100,
               low = 100,
               close = 0;
        double sumCurrMonth = 0,
               sumPrevMonth = 0;
        int countCurrMonth = 0,
            countPrevMonth = 0;
        // WROTE WITHOUT ASSISTANCE END
        // create month string
        std::string monthStr = (month < 10) ? "0" + std::to_string(month) : std::to_string(month);
        // create a year + month string
        std::string yearMonthStr = yearInput + "-" + monthStr;
        std::string prevYearMonthStr = std::to_string((month == 1) ? year - 1 : year) + "-" + ((month == 1) ? "12" : (month < 11 ? "0" + std::to_string(month - 1) : std::to_string(month - 1)));
        // WROTE WITHOUT ASSISTANCE START
        // iterate countriesData
        for (const auto& data : countriesData) 
        {
            // get data from specific country
            auto countryEntries = data.getCountryData(country);

            // loop over country data
            for (const auto& entry : countryEntries) 
            {
                // get the year and month from timestamp
                std::string entryYearMonth = entry.first.substr(0, 7);
                // compare for match
                if (entryYearMonth == yearMonthStr) 
                {
                    // get high and low
                    double value = entry.second;
                    if(value > high)
                    {
                        high = value;
                    }
                    if(value < low)
                    {
                        low = value;
                    }
                    // get sum and count
                    sumCurrMonth += entry.second;
                    countCurrMonth++;
                }
                // get sum and count for prev month
                else if (entryYearMonth == prevYearMonthStr)
                {
                    sumPrevMonth += entry.second;
                    countPrevMonth++;
                }
            }
        }
        if (countPrevMonth > 0) 
        {
            // calculate open
            open = sumPrevMonth / countPrevMonth;
        } 
        else 
        {
            open = 0;
        }

        if (countCurrMonth > 0) 
        {
            // calculate close
            close = sumCurrMonth / countCurrMonth;
        } 
        else 
        {
            close = 0;
        }

        if (countCurrMonth == 0)
        {
            // no data
            throw std::runtime_error("No data found for the specified country and year.");
        }

        // print stats
        std::cout << std::left << std::setw(10) << month
                    << std::setw(10) << open
                    << std::setw(10) << high
                    << std::setw(10) << low
                    << std::setw(10) << close << std::endl;
        
        // convert int to string
        std::string date = std::to_string(month);
        // create candlestickplot object
        CandlestickPlot candlestick(date, open, high, low, close);
        // push into vector
        candlesticks.push_back(candlestick);
    } 
    // print candlestick plot
    CandlestickPlot::printCandlestickPlot(candlesticks, 0.25);
    exit(0);
}
// WROTE WITHOUT ASSISTANCE END

// TASK 3
// WROTE WITHOUT ASSISTANCE START
void CandlestickData::printMonth(const std::vector<CandlestickData>& countriesData, const std::string& country, std::string yearInput, std::string monthInput)
{
    // vector for candlestickplot object
    std::vector<CandlestickPlot> candlesticks;
    // print header
    std::cout << "Country " << country << std::endl;
    std::cout << "Timestamp: " << yearInput + "-" + monthInput << std::endl;
    std::cout << std::left << std::setw(10) << "Month"
              << std::setw(10) << "Open"
              << std::setw(10) << "High"
              << std::setw(10) << "Low"
              << std::setw(10) << "Close" << std::endl;
    int daysInMonth;
    // convert string to int 
    int month = std::stoi(monthInput);
    int year = std::stoi(yearInput);
    // WROTE WITHOUT ASSISTANCE END
    // get the number of days according to month input
    switch (month)
    {
        // case = month
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            daysInMonth = 31;
            break;
        case 4: case 6: case 9: case 11:
            daysInMonth = 30;
            break;
        case 2:
            daysInMonth = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
            break;
        default:
            // bad input
            std::cout << "Invalid month" << std::endl;
    }
    // WROTE WITHOUT ASSISTANCE START
    // iterate over the days in month
    for(int day = 1; day <= daysInMonth; ++day)
    {
        // initialise stats 
        double open = 0,
               high = -100,
               low = 100,
               close = 0;
        double sumCurrDay = 0,
               sumPrevDay = 0;
        int countCurrDay = 0,
            countPrevDay = 0;
        // WROTE WITHOUT ASSISTANCE END
        // convert int to strings
        std::string dayStr = (day < 10) ? "0" + std::to_string(day) : std::to_string(day);
        std::string yearMonthDayStr = std::to_string(year) + "-" + ((month < 10) ? "0" + std::to_string(month) : std::to_string(month)) + "-" + dayStr;
        std::string prevYearMonthDayStr = std::to_string((day == 1) ? ((month == 1) ? year - 1 : year) : year) + "-" +
                                          ((day == 1) ? ((month == 1) ? "12" : ((month < 11) ? "0" + std::to_string(month - 1) : std::to_string(month - 1))) : ((month < 10) ? "0" + std::to_string(month) : std::to_string(month))) + "-" +
                                          ((day == 1) ? ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) ? "31" : (month == 2 ? ((year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? "29" : "28") : "30")) : ((day < 11) ? "0" + std::to_string(day - 1) : std::to_string(day - 1)));
        // WROTE WITHOUT ASSISTANCE START
        // iterate over countries data
        for (const auto& data : countriesData) 
        {
            // get specific country data
            auto countryEntries = data.getCountryData(country);

            // iterate over specific country data
            for (const auto& entry : countryEntries) 
            {
                // get timestamp
                std::string entryYearMonthDay = entry.first.substr(0, 10);
                // compare timestamp
                if (entryYearMonthDay == yearMonthDayStr) 
                {
                    // get high and low stats
                    double value = entry.second;
                    if(value > high)
                    {
                        high = value;
                    }
                    if(value < low)
                    {
                        low = value;
                    }
                    // get sum and count
                    sumCurrDay += entry.second;
                    countCurrDay++;
                }
                else if (entryYearMonthDay == prevYearMonthDayStr)
                {
                    sumPrevDay += entry.second;
                    countPrevDay++;
                }
            }
        }
        if (countPrevDay > 0) 
        {
            // calculate open
            open = sumPrevDay / countPrevDay;
        } 
        else 
        {
            open = 0;
        }

        if (countCurrDay > 0) 
        {
            // calculate close
            close = sumCurrDay / countCurrDay;
        } 
        else 
        {
            close = 0;
        }

        if (countCurrDay == 0)
        {
            // no data
            throw std::runtime_error("No data found for the specified country and year.");
        }

        // print stats accordingly
        std::cout << std::left << std::setw(10) << day
                    << std::setw(10) << open
                    << std::setw(10) << high
                    << std::setw(10) << low
                    << std::setw(10) << close << std::endl;
        
        // convert date to string
        std::string date = std::to_string(day);
        // create candlestickplot object
        CandlestickPlot candlestick(date, open, high, low, close);
        // push object into vector
        candlesticks.push_back(candlestick);
    } 
    // print candlestick plot
    CandlestickPlot::printCandlestickPlot(candlesticks, 0.25);
}
// WROTE WITHOUT ASSISTANCE END

// TASK 3
// WROTE WITHOUT ASSISTANCE START
void CandlestickData::printDay(const std::vector<CandlestickData>& countriesData, const std::string& country, std::string yearInput, std::string monthInput, std::string dayInput)
{
    // print header
    std::cout << "Country " << country << std::endl;
    std::cout << "Timestamp: " << yearInput + "-" + monthInput + "-" + dayInput<< std::endl;
    std::cout << std::left << std::setw(10) << "Hour"
              << std::setw(10) << "Open"
              << std::setw(10) << "High"
              << std::setw(10) << "Low"
              << std::setw(10) << "Close" << std::endl;
    // convert string to int 
    int month = std::stoi(monthInput);
    int year = std::stoi(yearInput);
    int day = std::stoi(dayInput);
    // iterate over hours
    for(int hour = 0; hour < 24; ++hour)
    {
        // initialise stats 
        double open = 0,
               high = -100,
               low = 100,
               close = 0;
        double sumCurrHour = 0,
               sumPrevHour = 0;
        int countCurrHour = 0,
            countPrevHour = 0;
        // WROTE WITHOUT ASSISTANCE END
        // get string of hour
        std::string hourStr = (hour < 10) ? "0" + std::to_string(hour) : std::to_string(hour);
        std::string yearMonthDayHourStr = std::to_string(year) + "-" + ((month < 10) ? "0" + std::to_string(month) : std::to_string(month)) + "-" +
                                        ((day < 10) ? "0" + std::to_string(day) : std::to_string(day)) + "T" + hourStr + ":00:00Z";
        std::string prevYearMonthDayHourStr = std::to_string(year) + "-" + ((month < 10) ? "0" + std::to_string(month) : std::to_string(month)) + "-" +
                                            ((day < 10) ? "0" + std::to_string(day) : std::to_string(day)) + "T" + ((hour == 0) ? "23" : (hour < 11) ? "0" + std::to_string(hour - 1) : std::to_string(hour - 1)) + ":00:00Z";
        // WROTE WITHOUT ASSISTANCE START
        // iterate over countries data
        for (const auto& data : countriesData) 
        {
            // get specific country data
            auto countryEntries = data.getCountryData(country);

            // iterate over country data
            for (const auto& entry : countryEntries) 
            {
                // get timestamp
                std::string entryYearMonthDayHour = entry.first.substr(0, 13);
                // comapre timestamp
                if (entryYearMonthDayHour == yearMonthDayHourStr.substr(0, 13)) 
                {
                    // calculate high and low
                    double value = entry.second;
                    if(value > high)
                    {
                        high = value;
                    }
                    if(value < low)
                    {
                        low = value;
                    }
                    // get sum and count
                    sumCurrHour += entry.second;
                    countCurrHour++;
                }
                else if (entryYearMonthDayHour == prevYearMonthDayHourStr.substr(0, 13))
                {
                    sumPrevHour += entry.second;
                    countPrevHour++;
                }
            }
        }
        if (countPrevHour > 0) 
        {
            // calculate open
            open = sumPrevHour / countPrevHour;
        } 
        else 
        {
            open = 0;
        }

        if (countCurrHour > 0) 
        {
            // calculate close
            close = sumCurrHour / countCurrHour;
        } 
        else 
        {
            close = 0;
        }

        if (countCurrHour == 0)
        {
            // no data
            throw std::runtime_error("No data found for the specified country and year.");
        }

        // print stats according to header
        std::cout << std::left << std::setw(10) << hour
                    << std::setw(10) << open
                    << std::setw(10) << high
                    << std::setw(10) << low
                    << std::setw(10) << close << std::endl;
    }
}
// WROTE WITHOUT ASSISTANCE END


=====================================================================================================
-----
[ File: /Users/User/Desktop/OOP/Mid Term/weather/src/CandlestickData.h ]
-----
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


=====================================================================================================
-----
[ File: /Users/User/Desktop/OOP/Mid Term/weather/src/CandlestickPlot.cpp ]
-----
#include "CandlestickPlot.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

// WROTE WITHOUT ASSISTANCE START
// TASK 2
// initialise new instance of candlestickplot class
CandlestickPlot::CandlestickPlot(const std::string& date, double open, double high, double low, double close)
: date(date), 
    open(open), 
    high(high), 
    low(low), 
    close(close) 
{ 

}

// print candlestick plot
void CandlestickPlot::printCandlestickPlot(const std::vector<CandlestickPlot>& candlesticks, double stepSize)
{
    double minValue = 1000;
    double maxValue = -1000;

    // determine min and max values for normalization
    for (const auto& candle : candlesticks) 
    {
        minValue = std::min({minValue, candle.low});
        maxValue = std::max({maxValue, candle.high});
    }

    int maxCol = 24; // max column for plot
    int startIndex = 0; 
    int numCandlesticks = candlesticks.size();
    int plotWidth = 6; // adjust for better spacing

    while(startIndex < numCandlesticks)
    {
        // calculate endIndex
        int endIndex = std::min(startIndex + maxCol, numCandlesticks);
        std::cout << std::left << std::setw(8) << "Temp" << std::endl;
        // iterate over plot
        for(double temp = maxValue; temp >= minValue; temp -= stepSize) 
        {
            // print y axis
            std::cout << "\033[37m" << std::left << std::setw(8) << std::fixed << std::setprecision(4) << temp << "|"; // print temperature scale

            // iterate over index
            for(int i = startIndex; i < endIndex; ++i) 
            {
                const auto& candle = candlesticks[i];
                // if open is larger than close
                if(candle.open > candle.close)
                {
                    // fill red
                    std::string colour = "\033[32m";
                    // check if candle value are with y axis
                    if (temp <= candle.high && temp >= candle.low) 
                    {
                        // for open and close
                        if (temp <= candle.open && temp >= candle.close) 
                        {
                            std::cout << colour << std::setw(plotWidth) << "-----";
                        }
                        // for high and low
                        else 
                        {
                            std::cout << colour << std::setw(plotWidth) << "  |";
                        }
                    } 
                    else 
                    {
                        // print black spaces
                        std::cout << std::setw(plotWidth) << " ";
                    }
                }
                // close id higher than open
                else if (candle.close > candle.open)
                {
                    // fill green
                    std::string colour = "\033[31m";
                    // check if candle stats and y axis
                    if (temp <= candle.high && temp >= candle.low) 
                    {
                        // print close and open
                        if (temp >= candle.open && temp <= candle.close) 
                        {
                            std::cout << colour << std::setw(plotWidth) << "-----";
                        }
                        else 
                        {
                            // print high and low
                            std::cout << colour << std::setw(plotWidth) << "  |";
                        }
                    } 
                    else 
                    {
                        // print empty space
                        std::cout << std::setw(plotWidth) << " ";
                    }
                }
            }
            std::cout << std::endl;
        }

        // print the date labels for the current range of candlesticks / x axis
        std::cout << std::left << std::setw(9) << "  ";
        for(int i = startIndex; i < endIndex; ++i) 
        {
            std::cout << "\033[37m" << std::setw(plotWidth) << candlesticks[i].date;
        }
        std::cout << std::endl;

        // move to the next range of candlesticks
        startIndex = endIndex;
    }
}
// WROTE WITHOUT ASSISTANCE END


==========================================================================================================
-----
[ File: /Users/User/Desktop/OOP/Mid Term/weather/src/CandlestickPlot.h ]
-----
#pragma once
#include <string>
#include <vector>

// WROTE WITHOUT ASSISTANCE START
class CandlestickPlot 
{
    public:
        // construct candlestickplot object
        CandlestickPlot(const std::string& date, double open, double high, double low, double close);

        // print candlestick plot by inputing vector and stepsize for y axis
        static void printCandlestickPlot(const std::vector<CandlestickPlot>& candlesticks, double stepSize);

    private:
        // date for x axis
        std::string date;
        // initialise stats;
        double open;
        double high;
        double low;
        double close;
};
// WROTE WITHOUT ASSISTANCE END


========================================================================================================
-----
[ File: /Users/User/Desktop/OOP/Mid Term/weather/src/CSVReader.cpp ]
-----
#include "CSVReader.h"

#include <iostream>
#include <fstream>

CSVReader::CSVReader()
{

}

std::vector<WeatherBookEntry> CSVReader::readCSV(std::string csvFilename)
{
    // create vector for entries
    std::vector<WeatherBookEntry> entries;
    std::ifstream csvFile{csvFilename};
    // create string for each line
    std::string line;

    if(csvFile.is_open())
    {
        // skip the header line
        std::getline(csvFile, line);
        // read each line of csv
        while(std::getline(csvFile, line))
        {
            try
            {
                //convert each line to a WeatherBookEntry object and add it to the entries vector
                WeatherBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            }
            catch(const std::exception& e)
            {
                // bad line
                std::cout << "CSVReader::read CSV bad data" << std::endl;
            }
        }
    }
    // print number of entries
    std::cout << "CSVReader::readCSV read " << entries.size() << " entries" << std::endl;
    return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
    // create vector to hold strings
    std::vector<std::string> tokens;
    signed int start, end;
    // create string for tokenised string
    std::string token;
    start = csvLine.find_first_not_of(separator, 0);
    // parse data
    do{
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end) break;
        if (end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
        // push token into vector
        tokens.push_back(token);
    start = end + 1;
    }while(end > 0);

    // return tokenised values
   return tokens; 
}

// convert vector of string into WeatherBookEntry object
WeatherBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    // create double to hold temp, each variable for each country
    double at, be, bg, ch, cz, de, dk, ee, es, fi, fr, gb, gr, hr, hu, ie, it, lt, lu, lv, nl, no, pl, pt, ro, se, si, sk;

    if (tokens.size() != 29) 
    {
        // bad
        std::cout << "Bad line " << std::endl;
        throw std::exception{};
    }
    // we have 29 tokens
    try
    {
         at = std::stod(tokens[1]);
         be = std::stod(tokens[2]);
         bg = std::stod(tokens[3]);
         ch = std::stod(tokens[4]);
         cz = std::stod(tokens[5]);
         de = std::stod(tokens[6]);
         dk = std::stod(tokens[7]);
         ee = std::stod(tokens[8]);
         es = std::stod(tokens[9]);
         fi = std::stod(tokens[10]);
         fr = std::stod(tokens[11]);
         gb = std::stod(tokens[12]);
         gr = std::stod(tokens[13]);
         hr = std::stod(tokens[14]);
         hu = std::stod(tokens[15]);
         ie = std::stod(tokens[16]);
         it = std::stod(tokens[17]);
         lt = std::stod(tokens[18]);
         lu = std::stod(tokens[19]);
         lv = std::stod(tokens[20]);
         nl = std::stod(tokens[21]);
         no = std::stod(tokens[22]);
         pl = std::stod(tokens[23]);
         pt = std::stod(tokens[24]);
         ro = std::stod(tokens[25]);
         se = std::stod(tokens[26]);
         si = std::stod(tokens[27]);
         sk = std::stod(tokens[28]);
    }
    catch(const std::exception& e)
    {
        // bad input
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[1]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[2]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[3]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[4]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[5]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[6]<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[7]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[8]<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[9]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[10]<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[11]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[12]<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[13]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[14]<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[15]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[16]<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[17]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[18]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[19]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[20]<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[21]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[22]<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[23]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[24]<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[25]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[26]<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[27]<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[28]<< std::endl;  
        throw;        
    }

    // convert individual string values into WeatherBookEntry object
    WeatherBookEntry obe{tokens[0],
                         at,
                         be, 
                         bg, 
                         ch, 
                         cz, 
                         de, 
                         dk, 
                         ee, 
                         es, 
                         fi, 
                         fr, 
                         gb, 
                         gr, 
                         hr, 
                         hu, 
                         ie, 
                         it, 
                         lt, 
                         lu, 
                         lv, 
                         nl, 
                         no, 
                         pl, 
                         pt, 
                         ro, 
                         se, 
                         si, 
                         sk};

    return obe; 
}

WeatherBookEntry CSVReader::stringsToOBE(std::string timestamp,
                                         std::string stringat,
                                         std::string stringbe,
                                         std::string stringbg,
                                         std::string stringch,
                                         std::string stringcz,
                                         std::string stringde,
                                         std::string stringdk,
                                         std::string stringee,
                                         std::string stringes,
                                         std::string stringfi,
                                         std::string stringfr,
                                         std::string stringgb,
                                         std::string stringgr,
                                         std::string stringhr,
                                         std::string stringhu,
                                         std::string stringie,
                                         std::string stringit,
                                         std::string stringlt,
                                         std::string stringlu,
                                         std::string stringlv,
                                         std::string stringnl,
                                         std::string stringno,
                                         std::string stringpl,
                                         std::string stringpt,
                                         std::string stringro,
                                         std::string stringse,
                                         std::string stringsi,
                                         std::string stringsk)
{
    double at, be, bg, ch, cz, de, dk, ee, es, fi, fr, gb, gr, hr, hu, ie, it, lt, lu, lv, nl, no, pl, pt, ro, se, si, sk;

    try
    {
         at = std::stod(stringat);
         be = std::stod(stringbe);
         bg = std::stod(stringbg);
         ch = std::stod(stringch);
         cz = std::stod(stringcz);
         de = std::stod(stringde);
         dk = std::stod(stringdk);
         ee = std::stod(stringee);
         es = std::stod(stringes);
         fi = std::stod(stringfi);
         fr = std::stod(stringfr);
         gb = std::stod(stringgb);
         gr = std::stod(stringgr);
         hr = std::stod(stringhr);
         hu = std::stod(stringhu);
         ie = std::stod(stringie);
         it = std::stod(stringit);
         lt = std::stod(stringlt);
         lu = std::stod(stringlu);
         lv = std::stod(stringlv);
         nl = std::stod(stringnl);
         no = std::stod(stringno);
         pl = std::stod(stringpl);
         pt = std::stod(stringpt);
         ro = std::stod(stringro);
         se = std::stod(stringse);
         si = std::stod(stringsi);
         sk = std::stod(stringsk);
    }
    catch(const std::exception& e)
    {
        // bad input
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringat<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringbe<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringbg<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringch<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringcz<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringde<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringdk<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringee<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringes<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringfi<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringfr<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringgb<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringgr<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringhr<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringhu<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringie<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringit<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringlt<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringlu<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringlv<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringnl<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringno<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringpl<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringpt<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringro<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringse<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringsi<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << stringsk<< std::endl;  
        throw;        
    }
    WeatherBookEntry obe{timestamp,
                         at,
                         be, 
                         bg, 
                         ch, 
                         cz, 
                         de, 
                         dk, 
                         ee, 
                         es, 
                         fi, 
                         fr, 
                         gb, 
                         gr, 
                         hr, 
                         hu, 
                         ie, 
                         it, 
                         lt, 
                         lu, 
                         lv, 
                         nl, 
                         no, 
                         pl, 
                         pt, 
                         ro, 
                         se, 
                         si, 
                         sk};

    return obe;
}


============================================================================================================
-----
[ File: /Users/User/Desktop/OOP/Mid Term/weather/src/CSVReader.h ]
-----
#pragma once

#include "WeatherBookEntry.h"
#include <vector>
#include <string>

class CSVReader
{
    public:
        // default constructor for CSVReader
        CSVReader();

        // reads a csv file and converts its content into a vector of WeatherBookEntry
        static std::vector<WeatherBookEntry> readCSV(std::string csvFile);
        // tokenise a csv line into individual strings based on the separator
        static std::vector<std::string> tokenise(std::string csvLine, char separator);

        // converts individual string values into a WeatherBookEntry object
        static WeatherBookEntry stringsToOBE(std::string timestamp,
                                             std::string at,
                                             std::string be,
                                             std::string bg,
                                             std::string ch,
                                             std::string cz,
                                             std::string de,
                                             std::string dk,
                                             std::string ee,
                                             std::string es,
                                             std::string fi,
                                             std::string fr,
                                             std::string gb,
                                             std::string gr,
                                             std::string hr,
                                             std::string hu,
                                             std::string ie,
                                             std::string it,
                                             std::string lt,
                                             std::string lu,
                                             std::string lv,
                                             std::string nl,
                                             std::string no,
                                             std::string pl,
                                             std::string pt,
                                             std::string ro,
                                             std::string se,
                                             std::string si,
                                             std::string sk);

    private:
        // convert vector of strings into a WeatherBookEntry object
        static WeatherBookEntry stringsToOBE(std::vector<std::string> strings);
};


==================================================================================================
-----
[ File: /Users/User/Desktop/OOP/Mid Term/weather/src/main.cpp ]
-----
#include "WeatherMain.h"
#include <iostream>

int main()
{
    WeatherMain app{};
    app.init();
}
-----
[ File: /Users/User/Desktop/OOP/Mid Term/weather/src/WeatherBookEntry.cpp ]
-----
#include "WeatherBookEntry.h"

// WROTE WITHOUT ASSISTANCE START
// constructor to initialise WeatherBookEntry object
// string to hold timestamp for weather data entry
// double to hold temperature data
// each variable for each country
WeatherBookEntry::WeatherBookEntry(std::string _timestamp,
                                   double _at,
                                   double _be,
                                   double _bg,
                                   double _ch,
                                   double _cz,
                                   double _de,
                                   double _dk,
                                   double _ee,
                                   double _es,
                                   double _fi,
                                   double _fr,
                                   double _gb,
                                   double _gr,
                                   double _hr,
                                   double _hu,
                                   double _ie,
                                   double _it,
                                   double _lt,
                                   double _lu,
                                   double _lv,
                                   double _nl,
                                   double _no,
                                   double _pl,
                                   double _pt,
                                   double _ro,
                                   double _se,
                                   double _si,
                                   double _sk)
: timestamp(_timestamp),
  at(_at),
  be(_be),
  bg(_bg),
  ch(_ch),
  cz(_cz),
  de(_de),
  dk(_dk),
  ee(_ee),
  es(_es),
  fi(_fi),
  fr(_fr),
  gb(_gb),
  gr(_gr),
  hr(_hr),
  hu(_hu),
  ie(_ie),
  it(_it),
  lt(_lt),
  lu(_lu),
  lv(_lv),
  nl(_nl),
  no(_no),
  pl(_pl),
  pt(_pt),
  ro(_ro),
  se(_se),
  si(_si),
  sk(_sk)
{

}
// WROTE WITHOUT ASSISTANCE END


====================================================================================================
-----
[ File: /Users/User/Desktop/OOP/Mid Term/weather/src/WeatherBookEntry.h ]
-----
#pragma once

#include <string>

// WROTE WITHOUT ASSISTANCE START
class WeatherBookEntry
{
    public:
        // constructor to initialise WeatherBookEntry object
        // string to hold timestamp for weather data entry
        // double to hold temperature data
        // each variable for each country
        WeatherBookEntry(std::string _timestamp,
                         double _at,
                         double _be,
                         double _bg,
                         double _ch,
                         double _cz,
                         double _de,
                         double _dk,
                         double _ee,
                         double _es,
                         double _fi,
                         double _fr,
                         double _gb,
                         double _gr,
                         double _hr,
                         double _hu,
                         double _ie,
                         double _it,
                         double _lt,
                         double _lu,
                         double _lv,
                         double _nl,
                         double _no,
                         double _pl,
                         double _pt,
                         double _ro,
                         double _se,
                         double _si,
                         double _sk);

    std::string timestamp;
    double at;
    double be;
    double bg;
    double ch;
    double cz;
    double de;
    double dk;
    double ee;
    double es;
    double fi;
    double fr;
    double gb;
    double gr;
    double hr;
    double hu;
    double ie;
    double it;
    double lt;
    double lu;
    double lv;
    double nl;
    double no;
    double pl;
    double pt;
    double ro;
    double se;
    double si;
    double sk;
};
// WROTE WITHOUT ASSISTANCE END


=============================================================================================
-----
[ File: /Users/User/Desktop/OOP/Mid Term/weather/src/WeatherMain.cpp ]
-----
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


======================================================================================================
-----
[ File: /Users/User/Desktop/OOP/Mid Term/weather/src/WeatherMain.h ]
-----
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


============================================================================================================================
-----
[ File: /Users/User/Desktop/OOP/Mid Term/weather/src/WeatherPrediction.h ]
-----
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