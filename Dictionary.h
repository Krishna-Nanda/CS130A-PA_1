#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <chrono>
#include <random>
#include <bitset>
#include <iostream>
using namespace std;
typedef vector<vector < int > > matrix;
class Dictionary {
public:

    Dictionary(int number_of_elements){
        elements = number_of_elements;
        number_of_buckets = pow(2,ceil(log2(elements)));
        this->Table_of_Second_Level.resize(pow(2.0,ceil(log2(elements))));
        for(int i = 0; i < pow(2.0,ceil(log2(elements)));i++){
            SecondLvlHashTable s;
            this->Table_of_Second_Level.push_back(s);
            LL ll;
            this->Table_of_Second_Level[i].SecondLevelHashTableLinkedList.push_back(ll);
        }
    }

    void Print();

    struct LL{
        vector<string> vector_of_strings_on_second_level;
        int number_of_elements = 0;
    };
    struct SecondLvlHashTable{
        vector<LL> SecondLevelHashTableLinkedList;
        matrix H2_matrix;
        bool collision = false;
        bool is_empty = true;
        int elements = 0;
        void generateH2(int seed);
        int secondHash(string key);
        void insert_using_H2();
        bool const check_collisions();

        int element_checker();
    };

    void generateH(int seed);

    int FirstHash(string key);

    void insert_using_H(int n, string* keys);

    void checkSum();

    void SecondLevelCollisionResolution(SecondLvlHashTable& s);




    // Insert an input set of n keys to the dictionary. This method should print out the following information:
    // 1. The hash functions comprising the perfect hash (both levels)
    // 2. The sum of squares of the number of keys mapped to each bin of the first level hash function, and
    // 3. The number of trials needed to generate each hash function.
    void bulkInsert(int n, string *keys);

    // Insert a key to the dictionary.
    // Print out whether the insertion caused a collision in the second level hash.
    // Handle collision with separate chaining.
    void insert(string key);

    // Remove a key from the dictionary, if it exists.
    void remove(string key);

    // Return whether a key is found in the dictionary.
    // Print the buckets (both first and second level) accessed during the operation.
    bool find(string key);

    static matrix multiply(const matrix& m1, const matrix &m2);

    private:
    vector<SecondLvlHashTable> Table_of_Second_Level;
    matrix H_matrix;
    bool checksum;
    int elements;
    int number_of_buckets;
};


