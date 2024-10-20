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