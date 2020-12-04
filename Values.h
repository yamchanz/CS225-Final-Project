#pragma once
#include <string>
using std::string;


class Values {
    public:
    Values(string name, string city, string country, string code, long double latitude, long double longitude);
    Values();
    string to_string();
    string name_;
    string city_;
    string country_;
    string code_;
    long double latitude_;
    long double longitude_;
    private:

};