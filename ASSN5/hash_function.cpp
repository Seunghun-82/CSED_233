#include "hash_function.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;


int DivisionHashFunction::hashing(int key) {
    return key % this->table_size;
}

MidSquareHashFunction::MidSquareHashFunction(int key_size, int table_size)
:    key_size(key_size), table_size(table_size)
{
    this->index_size = 0;
    while (table_size > 1) {
        table_size = (table_size + 1) / 2;
        index_size += 1;
    }
    this->skip_bits = this->key_size - (this->index_size / 2);
}

int MidSquareHashFunction::hashing(int key) {
    int mask = ((1 << this->index_size) - 1);
    return ( ((key*key) >> this->skip_bits) & mask ) % this->table_size;
}

int StringFoldingHashFunction::hashing(string value) {
    /////////////////////////////////////////////////////////
    //////////    TODO: Implement From Here    //////////////
    int sum = 0;
    for (int i = 0; value[i] != '\0'; i++)
    {
        sum = sum + (int)value[i];
    }

    return sum;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*   Write your codes if you have additional classes   */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
