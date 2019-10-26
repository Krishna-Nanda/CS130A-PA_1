// Implement Dictionary methods.
#include "Dictionary.h"
#include <string>
using namespace std;


void Dictionary::bulkInsert(int n, string *keys) {
checksum = false;
srand(time(nullptr));
while(!checksum){
    generateH(random());
    insert_using_H(n,keys);
    checkSum();
}
    // Doing the Second Level Hashing
    for(int i = 0; i < Table_of_Second_Level.size();i++) {
        if(Table_of_Second_Level[i].collision){
            SecondLevelCollisionResolution(Table_of_Second_Level[i]);
        }
    }
}

void Dictionary::generateH(int seed){
    mt19937 random(seed);
    matrix h;
    for(int i = 0; i < ceil(log2(elements)); i++){
        vector<int> row;
        for(int j = 0; j < 55; j++){
           row.push_back(random() % 2);
        }
        h.push_back(row);
    }
    H_matrix = h;
}

void Dictionary::insert_using_H(int n, string* keys){
    for(int i = 0; i < n; i++){
       int index = FirstHash(*(keys+i));
        if(Table_of_Second_Level[index].is_empty){ // If The Table is empty and therefore has no collisions
            Table_of_Second_Level[index].is_empty = false; // Updating the table is empty boolean
            LL linked_list; // Creating a LL object to push back
            linked_list.number_of_elements += 1; // updating the LL incrementer
            linked_list.vector_of_strings_on_second_level.push_back(*(keys+i)); // Adding the string to the LL object
            Table_of_Second_Level[index].SecondLevelHashTableLinkedList.push_back(linked_list); // Pushing the LL object
        }
        if(!Table_of_Second_Level[index].collision && !Table_of_Second_Level[index].is_empty){ // If the table has no collisions and is not empty
            Table_of_Second_Level[index].collision = true;
            LL linked_list;
            linked_list.number_of_elements += 1;
            linked_list.vector_of_strings_on_second_level.push_back(*(keys+i));
            Table_of_Second_Level[index].SecondLevelHashTableLinkedList.push_back(linked_list);
        }
        if(Table_of_Second_Level[index].collision){ // If the table has a collision and is therefore not empty
            LL linked_list;
            linked_list.number_of_elements += 1;
            linked_list.vector_of_strings_on_second_level.push_back(*(keys+i));
            Table_of_Second_Level[index].SecondLevelHashTableLinkedList.push_back(linked_list);
        }
    }
}

int Dictionary::FirstHash(string key) {
    while((int)key.size() < 8){
        key += key;
    }
    matrix key_in_binary;
    string Binary_Key;
    vector<int> temp_key;
    for(int i = key.size() - 1; i > key.size() - 9; i--){
        Binary_Key = bitset<7>(key[i]).to_string();
        for(int j = 0; j < 7; j++){
            temp_key.push_back(int(Binary_Key[j]));
        }
    }
    key_in_binary.push_back(temp_key);
}

void Dictionary::insert(string key) {
// TODO:: Write this.

}

void Dictionary::remove(string key) {
// TODO:: Write this.

}

bool Dictionary::find(string key) {
// TODO:: Write this.

    return false;
}
