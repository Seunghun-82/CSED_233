#include "hash_function.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int HashFunction::hashing(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    int size_array = key_size * 2;
    int key_square = key * key;
    int* hash_array = new int[size_array];
    for (int i = size_array - 1; i >= 0; i--)
    {
        if (key_square == 0)
        {
            hash_array[i] = 0;
        }
        else
        {
            hash_array[i] = key_square % 2;
            key_square = key_square / 2;
        }
    }
    int key_value = 0;
    int multiplication = 1;
    for (int i = 0; i < index_size - 1; i++)
    {
        multiplication = multiplication * 2;
    }
    for (int i = 0; i < index_size; i++)
    {
        key_value = key_value + multiplication * hash_array[i + key_size - (index_size / 2)];
        multiplication = multiplication / 2;
    }

    return key_value;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////


///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
