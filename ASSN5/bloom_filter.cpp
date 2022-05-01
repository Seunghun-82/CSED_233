#include <iostream>
#include <fstream>
#include <string>
#include "hash_function.h"
#include "bloom_filter.h"

using namespace std;


BloomFilter::BloomFilter(int key_size,
                         int vector_size)
:    key_size(key_size), vector_size(vector_size)
{
    this->bit_vector = new bool[this->vector_size];
    /////////////////////////////////////////////////////////
    //////////    TODO: Implement From Here    //////////////
    this->hf1 = new DivisionHashFunction(vector_size);
    this->hf2 = new MidSquareHashFunction(key_size, vector_size);
    for (int i = 0; i < vector_size; i++)
    {
        bit_vector[i] = false;
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

BloomFilter::~BloomFilter() {
    /////////////////////////////////////////////////////////
    //////////    TODO: Implement From Here    //////////////
    
    delete hf1;
    delete hf2;
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
    delete[] this->bit_vector;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BloomFilter::print_vector(ostream &out) {
    for (int i=0; i < this->vector_size; i++) {
        out << this->bit_vector[i];
    }
    out << endl;
}

void BloomFilter::insert(int key) {
    /////////////////////////////////////////////////////////
    ///////////   TODO: Implement From Here     /////////////
    int key1 = hf1->hashing(key);
    int key2 = hf2->hashing(key);
    bit_vector[key1] = true;
    bit_vector[key2] = true;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string BloomFilter::search(int key) {
    /////////////////////////////////////////////////////////
    ///////////    TODO: Implement From Here    /////////////
    int key1 = hf1->hashing(key);
    int key2 = hf2->hashing(key);
    if ((bit_vector[key1] == true) && (bit_vector[key2] == true))
    {
        return "hit";
    }
    return "miss";

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
