// Mirza Kazim Husain
// 6 - 1 - 2022
// Explained in header file

#include "HeaderFile.h"
#include <iostream>
#include <string>
using namespace std;

void DataEntry::setDate(string date)
{
    Date = date;
}

void DataEntry::setCountry(string country)
{
    Country = country;
}

void DataEntry::setCases(int cases)
{
    Cases = cases;
}

void DataEntry::setDeaths(int deaths)
{
    Deaths = deaths;
}

string DataEntry::getDate()
{
    return Date;
}

string DataEntry::getCountry()
{
    return Country;
}

int DataEntry::getCases()
{
    return Cases;
}

int DataEntry::getDeaths()
{
    return Deaths;
}

covidDB::covidDB(int m)
{
    newEntry = vector<vector<DataEntry>>(m);
    this->tableSize = m;
}

int covidDB::hash(string country)
{
    int ascii = 0;
    int size = country.size();
    for (int i = 1; i <= size; i++)
    {
        ascii += (i * int(country[i]));
    }
    return ascii % tableSize;
}

bool covidDB::add(DataEntry entry)
{
    if (inital == false)
    {
        newEntry[hash(entry.getCountry())].push_back(entry);
    }
    else
    {
        bool validCountry = false;
        int i = hash(entry.getCountry());
        int size = newEntry[i].size();
        string oldDate = "";
        int oldCases = 0, oldDeaths = 0; // Initially

        for (int j = 0; j < size; j++)
        {
            if (newEntry[i][j].getCountry() == entry.getCountry())
            {
                oldDate = newEntry[i][j].getDate();
                oldCases = newEntry[i][j].getCases();
                oldDeaths = newEntry[i][j].getDeaths();
                validCountry = true;
            }
        }

        if (!validCountry)
        {
            cout << "There is no country: " << entry.getCountry() << " in hash table!" << endl;
            return false;
        }

        vector<string> oldResult = split(oldDate, '/');
        int oldMonth = stoi(oldResult[0]);
        int oldDay = stoi(oldResult[1]);
        int oldYear = stoi(oldResult[2]);
        string newDate = entry.getDate();
        vector<string> newResult = split(newDate, '/');
        int newMonth = stoi(newResult[0]);
        int newDay = stoi(newResult[1]);
        int newYear = stoi(newResult[2]);

        if (oldYear > newYear)
        {
            cout << "Already up to date " << entry.getCountry() << " in hash table!" << endl;
            return false;
        }
        else if (oldYear == newYear)
        {
            if (oldMonth > newMonth)
            {
                cout << "Already up to date " << entry.getCountry() << " in hash table!" << endl;
                return false;
            }
            else if (oldMonth == newMonth)
            {
                if (oldDay >= newDay)
                {
                    cout << "Already up to date " << entry.getCountry() << " in hash table!" << endl;
                    return false;
                }
            }
        }

        int newCases = oldCases + entry.getCases();
        int newDeaths = oldDeaths + entry.getDeaths();

        for (int j = 0; j < size; j++)
        {
            if (newEntry[i][j].getCountry() == entry.getCountry())
            {
                newEntry[i][j].setDate(newDate);
                newEntry[i][j].setCases(newCases);
                newEntry[i][j].setDeaths(newDeaths);
            }
        }
        return true;
    }
    return true;
}

DataEntry covidDB::get(string country)
{
    DataEntry oneEntry;
    int i = hash(country);
    int size = newEntry[i].size();

    for (int j = 0; j < size; j++)
    {
        if (newEntry[i][j].getCountry() == country)
        {
            oneEntry.setDate(newEntry[i][j].getDate());
            oneEntry.setCountry(newEntry[i][j].getCountry());
            oneEntry.setCases(newEntry[i][j].getCases());
            oneEntry.setDeaths(newEntry[i][j].getDeaths());
        }
    }
    return oneEntry;
}

void covidDB::remove(string country)
{
    int i = hash(country);
    int size = newEntry[i].size();

    for (int j = 0; j < size; j++)
    {
        if (newEntry[i][j].getCountry() == country)
        {
            newEntry[i].erase(newEntry[i].begin() + j);
            cout << "The data entry of " << country << " is deleted!" << endl;
            return;
        }
    }
    cout << "There is no country: " << country << " in hash table!" << endl;
}

void covidDB::display()
{
    cout << "Hash Table" << endl;
    int size = newEntry.size();

    for (int i = 0; i < size; i++)
    {
        cout << i;
        int sizeV = newEntry[i].size();

        for (int j = 0; j < sizeV; j++)
        {
            cout << newEntry[i][j].getCountry() << endl;
            cout << "Cases: " << newEntry[i][j].getCases() << endl;
            cout << "Deaths: " << newEntry[i][j].getDeaths() << endl;
            cout << endl;
        }
    }
    cout << endl;
}

vector<string> covidDB::split(string str, char del)
{
    vector<string> result;
    string temp = "";

    for (int i = 0; i < (int)str.size(); i++)
    {
        if (str[i] != del)
        {
            temp += str[i];
        }
        else
        {
            result.push_back(temp);
            temp = "";
        }
    }
    result.push_back(temp);
    return result;
}
