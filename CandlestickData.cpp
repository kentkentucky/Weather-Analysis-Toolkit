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