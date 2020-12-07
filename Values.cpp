#include "Values.h"
#include "iostream"
using std::string;

Values::Values(string name, string city, string country, string code, long double latitude, long double longitude)
 : name_(name), city_(city), country_(country), code_(code), latitude_(latitude), longitude_(longitude)
{}

Values::Values() {

}
string Values::to_string() {
    return name_ + "," + city_ + "," + country_ + "," + code_ + "," + std::to_string(latitude_) + "," + std::to_string(longitude_);
}
bool Values::operator==(const Values &rhs) const{
    return (
    (this->name_ == rhs.name_) &&
    (this->city_ == rhs.city_) &&
    (this->country_ == rhs.country_) &&
    (this->code_ == rhs.code_) && 
    ((int)this->latitude_ == (int)rhs.latitude_) &&
    ((int)this->longitude_ == (int)rhs.longitude_));
}