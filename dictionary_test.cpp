#include "Dictionary.h"
#include <iostream>
#include <boost_1_71_0/boost/algorithm/string/classification.hpp>
#include "csv.h"
#include "boost_1_71_0/boost/algorithm/string.hpp"

using namespace std;

// Driver program
//int main()
//{
//    // Initialize the dictionary.
//    Dictionary dict(9);
//
//    // BulkInsert the keys into the dictionary.
//    string strs[] = {"Fred Astaire", "Lauren Bacall", "Brigitte Bardot", "John Belushi", "Ingmar Bergman","Humphrey Bogart","James Cagney","Bette Davis","Henry Fonda"};
//    int n = 9;
//    dict.bulkInsert(n, strs);
//    dict.Print();
//
//    // Insert "Humphrey Bogart" into the dictionary.
////    dict.insert("Humphrey Bogart");
////
////    // Remove "Lauren Bacall" from the dictionary.
////    dict.remove("Lauren Bacall");
////
////    // Find "Fred Astaire" in the dictionary.
////    cout << dict.find("Fred Astaire") << endl;
////
////    // Find "Lauren Bacall" in the dictionary.
////    cout << dict.find("Lauren Bacall") << endl;
//
//    return 0;
//}
int main() {
    Dictionary Dic(1000);
    io::LineReader in("name.basics.tsv");
    vector<string> data;
    int counter = 0;
    int index = 0;
    string *t = new string[1000];
    while (char *line = in.next_line()) {
        string a = line;
        //boost::erase_all(a, " ");
        split(data, a, boost::is_any_of("\t"));
        string w = data[1];
        a += "\n";
        t[index] = w;
        //cout << t[index] << endl;
        index++;
        counter++;
        if (counter == 1000) {
            break;
        }
    }
    Dic.bulkInsert(1000, t);
    //Dic.Print();
    cout << "--------------" << endl;
    Dic.insert("Krishna Nanda");
    Dic.remove("Albert Yuan");
    Dic.find("Megan Fox");
    //Dic.print();
    return 0;
}