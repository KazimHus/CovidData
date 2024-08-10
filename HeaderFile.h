// Mirza Kazim Husain 
// 06 - 01 - 2022
 #ifndef HeaderFile_H
 #define HEaderFile_H
 #include <iostream>
 #include <vector> 
using namespace std;
 class DataEntry
 {
    private:
        string Date; // Newest Date
        string Country; // Name of Country
        int Cases; // Number of cases, up to date
        int Deaths; // Number of deaths, up to date
    public: 
        void setDate(string);
        void setCountry(string);
        void setCases(int);
        void setDeaths(int);
        string getDate();
        string getCountry();
        int getCases();
        int getDeaths();
 };  
class covidDB
 {
    private:
        int tableSize;
        vector<vector<DataEntry>> newEntry; // Double vector
    public:
        covidDB(int m); 
        bool inital;
        int hash(string country); 
        int getIndex(string country); 
        bool add(DataEntry entry); // addding new cases and deaths
        DataEntry get(string country);
        void remove(string country); // removing a country
        void display(); // displaying all data
        vector<string> split(string str, char del); 
};
 #endif