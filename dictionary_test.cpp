#include "Dictionary.h"
#include <iostream>
using namespace std;

// Driver program
int main()
{
    // Initialize the dictionary.
    Dictionary dict(52);

    // BulkInsert the keys into the dictionary.
    string strs[] = {"Fred AstairQe", "Lauren Bacall", "Brigitte BaVrdot", "John BeluEshi", "Ingmar BergRman", "Akeel StubbFs", "Jenna CraGig", 
        "Ella-Grace Henderson", "Hebe Lara", "Gurpreet Woodley", "Angus Shepherd", "Violet Kline", "Caitlan Simmons", "Gred AstaiYrz", "Lauren BacaYlz", "Brigitte BYardoz", "John BeluYshz", "Ingmar BergYmaz"
        , "Akeel Stubbz", "Jenna Craiz", 
        "Ella-Grace Hendersoz", "Hebe Laraz", "Gurpreet Woodlez", "Angus Shepherz", "Violet Klinz", "Caitlan Simmonz",
        "Fred Astaire", "Lauren Bacallzd", "Brigitte Barhdbdot", "John BelushFi", "Ingmar Bergmanqze", "Akeel Stubbs", "Jenna Craig", 
        "Ella-Grace HendersonHq", "Hebe LaraDq", "Gurpreet WooQdleyq", "Angus ShephWerdq", "Violet 1Klinqe", "Caitlan Si3mmonsq", "Gred Astairzq", "Lauren Bac7alzq", "Brigitte Bardozq", "John Belushzq", "Ingmar Bergmazq"
        , "Akeel StubbFHz", "Jenna CrFHaiz", 
        "Ella-Grace HendersoHzq", "Hebe LarHazq", "Gurpreet WoodlezVq", "Angus Shdepherzq", "Violet Klsinqz", "Caitlan Simmsonzq"};

    int n = 52;
    dict.bulkInsert(n, strs);
    cout << "Here 1" << endl;

    // Insert "Humphrey Bogart" into the dictionary.
    dict.insert("Humphrey Bogart");
    cout << "Here 2" << endl;

    // Remove "Lauren Bacall" from the dictionary.
    //dict.remove("Lauren Bacall");
    cout << "Here 3" << endl;
    // Find "Fred Astaire" in the dictionary.
    cout << dict.find("Fred Astaire") << endl;
    cout << "Here 4" << endl;
    // Find "Lauren Bacall" in the dictionary.
    cout << dict.find("Lauren Bacall") << endl;
    cout << "Here 5" << endl;
    cout << dict.find("Humphrey Bogart") << endl;
    cout << "Here 6" << endl;
    dict.remove("Humphrey Bogart");
    cout << dict.find("Humphrey Bogart") << endl;
    cout << "Here 7" << endl;
    return 0;
}