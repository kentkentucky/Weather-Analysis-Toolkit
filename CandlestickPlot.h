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