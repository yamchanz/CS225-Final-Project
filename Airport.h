#pragma once

#include <string>
#include <vector>

using std::string;
//code is key
class Airport {
    public:
    Airport(string name, string city, string country, string code, double latitude, double longitude);
    ~Airport();
    Airport();

    string name_;
    string city_;
    string country_;
    string code_;
    double latitude_;
    double longitude_;
    private:
    
    
};












