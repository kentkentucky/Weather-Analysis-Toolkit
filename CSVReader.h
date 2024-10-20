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