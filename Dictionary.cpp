// Implement Dictionary methods.
#include "Dictionary.h"
#include <string>
using namespace std;


void Dictionary::bulkInsert(int n, string *keys) {
checksum = false;
srand(time(NULL));
while(checksum == false){
    generateH(random());
    insert_using_H(keys);
    checkSum();
}
secondHash();
}

void Dictionary::generateH(int seed){
    
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
