// Implement Dictionary methods.
#include "Dictionary.h"
#include <string>
using namespace std;


void Dictionary::bulkInsert(int n, string *keys) {
    srand(time(NULL));
    int counter = 0;
    checksum = false;
while(!checksum){
    counter++;
    generateH();
    insert_using_H(n,keys);
    checkSum();
    if(!checksum){
        this->Table_of_Second_Level.clear();
        this->Table_of_Second_Level.resize(number_of_buckets);
    }
}

    // Doing the Second Level Hashing
    for(int i = 0; i < Table_of_Second_Level.size();i++) {
        Table_of_Second_Level[i].check_collisions();
        if(Table_of_Second_Level[i].collision == true){
            SecondLevelCollisionResolution(Table_of_Second_Level[i]);
        }
    }
    cout << "First Level Hash Function: " << endl;
    for(int i = 0; i < H_matrix.size(); i++){
        for(int j = 0; j < 56; j++){
            cout << H_matrix[i][j];
        }
        cout << endl;
    }
    cout << "Sum of Squares mapped to every bin: " << check_final << endl;
    cout << "Number of trials needed to generate First Level Hash: " << counter << endl;

    for(int i = 0; i < Table_of_Second_Level.size(); i++){
        if(Table_of_Second_Level[i].SecondLevelHashTableLinkedList.size() > 1){
            cout << "Bucket number: " << i << endl;
            cout << "Number of iterations of H2 generater: " << Table_of_Second_Level[i].counter_of_H2 << endl;
                for(int j = 0; j < Table_of_Second_Level[i].H2_matrix.size(); j++) {
                    for (int x = 0; x < 56; x++) {
                        cout << Table_of_Second_Level[i].H2_matrix[j][x];
                    }
                    cout << endl;
                }

            }
        }
    }


void Dictionary::SecondLevelCollisionResolution(Dictionary::SecondLvlHashTable &s) {
bool col = s.check_collisions();
while(col == true){
        s.generateH2();
        s.counter_of_H2 += 1;
        s.insert_using_H2();
        s.check_collisions();
        col = s.check_collisions();
//        if(s.check_collisions() == true){
//            s.elements = 0;
//        }
    }
}

void Dictionary::SecondLvlHashTable::insert_using_H2() {
    vector<string> temp;
    vector<LL> ll;
    for (int i = 0; i < this->SecondLevelHashTableLinkedList.size();i++) {
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
        ll[index].vector_of_strings_on_second_level.push_back(temp[i]);
        }
    SecondLevelHashTableLinkedList = ll;
}

bool const Dictionary::SecondLvlHashTable::check_collisions() {
        for(int i = 0; i < this->SecondLevelHashTableLinkedList.size(); i++){
            if(this->SecondLevelHashTableLinkedList[i].vector_of_strings_on_second_level.size() > 1){
                return true;
            }
        }
        return false;
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
        for(int i = 0; i < pow(2,ceil(log2(elements))); i++){
            index += (result[0][i] % 2) * pow(2,double(i));
        }
    return index;
}

int Dictionary::SecondLvlHashTable::element_checker(){
    int counter = 0;
    for(int i = 0; i < SecondLevelHashTableLinkedList.size();i++){
        counter += SecondLevelHashTableLinkedList[i].vector_of_strings_on_second_level.size();
    }
    return counter;
}

void Dictionary::SecondLvlHashTable::generateH2() {
   //int elements = this->elements;
   int rows = 0;
   int element = element_checker();
   element = pow(element,2);
   element = ceil(log2(element));
   rows = element;

   for(int i = 0; i < rows; i++){
       vector<int> row;
       for(int j = 0; j < 56; j++){
           row.push_back(rand() %2 );
       }
       this->H2_matrix.push_back(row);
   }
}

void Dictionary::checkSum() {
    checksum = false;
    long long check = 0;
    for(int i = 0; i < Table_of_Second_Level.size(); i++){
        check += pow(Table_of_Second_Level[i].SecondLevelHashTableLinkedList.size(),2);
    }
    check_final = check;
    checksum = check < 4 * number_of_buckets;
}

void Dictionary::generateH(){
    matrix h;
    for(int i = 0; i < ceil(log2(elements)); i++){
        vector<int> row;
        for(int j = 0; j < 56; j++){
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
            Table_of_Second_Level[index].SecondLevelHashTableLinkedList.push_back(linked_list);  // Pushing the LL object
        }
        else if(!Table_of_Second_Level[index].collision && Table_of_Second_Level[index].SecondLevelHashTableLinkedList.size() > 0){ // If the table has no collisions and is not empty
            Table_of_Second_Level[index].collision = true;
            Table_of_Second_Level[index].SecondLevelHashTableLinkedList[0].vector_of_strings_on_second_level.push_back(*(keys+i));
        }
       else if(Table_of_Second_Level[index].collision){ // If the table has a collision and is therefore not empty
            Table_of_Second_Level[index].SecondLevelHashTableLinkedList[0].vector_of_strings_on_second_level.push_back(*(keys+i));
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
            temp_key.push_back(int(Binary_Key[j]) - (int)'0');
        }
    }
    key_in_binary.push_back(temp_key);
    matrix temp_H = H_matrix;
    matrix result = multiply(key_in_binary,temp_H);
    int index = 0;
        for(int j = 0; j < result[0].size(); j++){
            index += (result[0][j] % 2) * pow(2,j);
        }
return index;
}

void Dictionary::insert(string key) {
int index = FirstHash(key);
int index_2 = Table_of_Second_Level[index].secondHash(key);
if(!Table_of_Second_Level[index].is_empty){
    Table_of_Second_Level[index].SecondLevelHashTableLinkedList[index_2].vector_of_strings_on_second_level.push_back(key);
    cout << "collision occured" << endl;
}
else{
    cout << "No collision occured inserted" << endl;
    LL ll;
    ll.vector_of_strings_on_second_level.push_back(key);
    Table_of_Second_Level[index].SecondLevelHashTableLinkedList.push_back(ll);
    Table_of_Second_Level[index].is_empty = false;
}
}
void Dictionary::remove(string key) {
    int index = FirstHash(key);
    int index_2 = Table_of_Second_Level[index].secondHash(key);
    if(Table_of_Second_Level[index].is_empty){
        cout << "Table Empty" << endl;
        return;
    }
    else{
        for(int i = 0; i < Table_of_Second_Level[index].SecondLevelHashTableLinkedList.size(); i++){
            for(int j = 0; j < Table_of_Second_Level[index].SecondLevelHashTableLinkedList[i].vector_of_strings_on_second_level.size(); j++)
            if(Table_of_Second_Level[index].SecondLevelHashTableLinkedList[i].vector_of_strings_on_second_level[j] == key){
                cout << "erased: " << key << endl;
                auto e = Table_of_Second_Level[index].SecondLevelHashTableLinkedList[i].vector_of_strings_on_second_level.begin();
                Table_of_Second_Level[index].SecondLevelHashTableLinkedList[i].vector_of_strings_on_second_level.erase(e+j);
            }
        }
    }
    return;
}

bool Dictionary::find(string key) {
// TODO:: Write this.
    int index = FirstHash(key);
    int index_2 = Table_of_Second_Level[index].secondHash(key);
    cout << "Indexed to First Bucket: " << index << " Indexed to Second Level Bucket: " << index_2 << endl;
    if (Table_of_Second_Level[index].is_empty || Table_of_Second_Level[index].SecondLevelHashTableLinkedList[index_2].vector_of_strings_on_second_level.size() == 0) {
        return false;
    };
    if ((Table_of_Second_Level[index].SecondLevelHashTableLinkedList[0].vector_of_strings_on_second_level[0]) == key) {
        return true;
    } else {
        for (int i = 0; i < Table_of_Second_Level[index].SecondLevelHashTableLinkedList[index_2].vector_of_strings_on_second_level.size(); i++) {
                if (Table_of_Second_Level[index].SecondLevelHashTableLinkedList[index_2].vector_of_strings_on_second_level[i] ==
                    key) {
                    return true;
                }
            }
        }

        return false;
    }

matrix Dictionary::multiply(const matrix &m1, const matrix &m2) {
    matrix result(m1.size(), vector<int>(m2.size()));
    for(size_t row = 0; row < m2.size(); row++) {
            for(size_t inner = 0; inner < m1.at(0).size(); inner++) {
                result.at(0).at(row) += m1.at(0).at(inner) * m2.at(row).at(inner);
            }
    }
    return result;
}
void Dictionary::Print(int index, int index_2) {



}
