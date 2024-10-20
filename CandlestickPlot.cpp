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