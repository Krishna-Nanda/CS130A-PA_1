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
    cout << "before checksum" << endl;
    checkSum();
    if(!checksum){
        this->Table_of_Second_Level.clear();
        this->Table_of_Second_Level.resize(number_of_buckets);
    }
}
    // Doing the Second Level Hashing
    for(int i = 0; i < Table_of_Second_Level.size();i++) {
        if(Table_of_Second_Level[i].collision){
            SecondLevelCollisionResolution(Table_of_Second_Level[i]);
        }
    }
}

void Dictionary::SecondLevelCollisionResolution(Dictionary::SecondLvlHashTable &s) {
    mt19937 rand(time(NULL));
    while(s.collision){
        s.generateH2(rand());
        s.insert_using_H2();
        s.check_collisions();
        if(s.collision){
            s.elements = 0;
        }
    }
}

void Dictionary::SecondLvlHashTable::insert_using_H2() {
    vector<string> temp;
    vector<LL> ll;

    for (int i = 0; i < this->SecondLevelHashTableLinkedList.size() && !this->SecondLevelHashTableLinkedList[i].vector_of_strings_on_second_level.empty(); i++) {
        for(int j = 0; j < this->SecondLevelHashTableLinkedList[i].vector_of_strings_on_second_level.size(); j++) {
            temp.push_back(this->SecondLevelHashTableLinkedList[i].vector_of_strings_on_second_level[j]);
            elements+=1;
        }
    }

    int number_of_bucket = 0;
    number_of_bucket = elements;
    number_of_bucket = pow(number_of_bucket, 2);
    number_of_bucket = ceil(log2(number_of_bucket));
    int total_buckets = pow(2, number_of_bucket);
    ll.resize(total_buckets);


    for (int i = 0; i < temp.size(); i++) {
        int index = secondHash(temp[i]);
        if(index == 1){
            ll[0].vector_of_strings_on_second_level.push_back(temp[i]);
        }
        else{
        ll[index].vector_of_strings_on_second_level.push_back(temp[i]);
        }
    }
    SecondLevelHashTableLinkedList = ll;
}

void Dictionary::SecondLvlHashTable::check_collisions() {
    for(int i = 0; i < SecondLevelHashTableLinkedList.size(); i++){
        if(SecondLevelHashTableLinkedList[i].vector_of_strings_on_second_level.size() > 1){
            collision = true;
            return;
        }
    }
        collision = false;
        return;
}

int Dictionary::SecondLvlHashTable::secondHash(string key) {
    matrix key_in_binary;
    string Binary_Key;
    vector<int> temp_key;
    for(int i = key.size() - 1; i > key.size() - 9; i--){
        Binary_Key = bitset<7>(key[i]).to_string();
        for(int j = 0; j < 7; j++){
            temp_key.push_back(int(Binary_Key[j] - (int) '0'));
        }
    }
    key_in_binary.push_back(temp_key);
    matrix temp_H = H2_matrix;
    matrix result = multiply(key_in_binary,temp_H);
    int index = 0;
        for(int i = 0; i < SecondLevelHashTableLinkedList.size(); i++){
            index += (result[0][i] % 2) * pow(2,double(i));
        }
    cout << index;
    return index;
}

void Dictionary::SecondLvlHashTable::generateH2(int seed) {
    mt19937 random(seed);
    matrix h;
   int elements = this->SecondLevelHashTableLinkedList.size();
   int rows = 0;
   elements = pow(elements,2);
   elements = ceil(log2(elements));
   rows = pow(2,elements);

   for(int i = 0; i < rows; i++){
       vector<int> row;
       for(int j = 0; j < 55; j++){
           row.push_back(random() %2 );
       }
       h.push_back(row);
   }
   H2_matrix = h;
}

void Dictionary::checkSum() {
    long long check = 0;
    for(int i = 0; i < Table_of_Second_Level.size(); i++){
        check += pow(Table_of_Second_Level[i].SecondLevelHashTableLinkedList.size(),2);
    }
    checksum = check < 4 * number_of_buckets;
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
        else if(!Table_of_Second_Level[index].collision && !Table_of_Second_Level[index].is_empty){ // If the table has no collisions and is not empty
            Table_of_Second_Level[index].collision = true;
            LL linked_list;
            linked_list.number_of_elements += 1;
            linked_list.vector_of_strings_on_second_level.push_back(*(keys+i));
            Table_of_Second_Level[index].SecondLevelHashTableLinkedList.push_back(linked_list);
        }
       else if(Table_of_Second_Level[index].collision){ // If the table has a collision and is therefore not empty
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
    matrix temp_H = H_matrix;
    matrix result = multiply(key_in_binary,temp_H);
    int index = 0;
    for(int i = 0; i < result.size();i++){
        for(int j = 0; j < result[i].size(); j++){
            index = result[i][j] % 2;
        }
    }
return index;
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

matrix Dictionary::multiply(const matrix &m1, const matrix &m2) {
    matrix result(m1.size(), vector<int>(m2.at(0).size()));
    for(size_t row = 0; row < result.size(); ++row) {
        for(size_t col = 0; col < result.at(0).size(); ++col) {
            for(size_t inner = 0; inner < m2.size(); ++inner) {
                result.at(row).at(col) += m1.at(row).at(inner) * m2.at(inner).at(col);
            }
        }
    }
    return result;
}
void Dictionary::Print(){
    for(int i = 0; i < Table_of_Second_Level.size(); i++){
        for(int j = 0; j < Table_of_Second_Level[i].SecondLevelHashTableLinkedList.size(); j++){
            for(int x = 0; x < Table_of_Second_Level[i].SecondLevelHashTableLinkedList[j].vector_of_strings_on_second_level.size(); x++){
                cout << "Linked List" << x << endl;
                cout << Table_of_Second_Level[i].SecondLevelHashTableLinkedList[j].vector_of_strings_on_second_level[x] << endl;
            }
        }
    }
}
