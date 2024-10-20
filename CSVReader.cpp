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