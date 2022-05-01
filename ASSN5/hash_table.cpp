#include <iostream>
#include <fstream>
#include <string>
#include "hash_function.h"
#include "hash_table.h"

using namespace std;


HashTable::HashTable(int table_size,
                     StringFoldingHashFunction *hf)
:    table_size(table_size)
{
    this->bloom_filter = nullptr;
    /////////////////////////////////////////////////////////
    //////////    TODO: Implement From Here    //////////////
    this->hf = hf;
    this->table = new Node * [table_size];
    this->is_it_filled = new bool[table_size];

    for (int i = 0; i < table_size; i++)
    {
        is_it_filled[i] = false;
    }
    /*             Write your codes if you need            */
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

HashTable::HashTable(int table_size,
                     StringFoldingHashFunction *hf,
                     BloomFilter *bloom_filter)
:    table_size(table_size)
{
    this->bloom_filter = bloom_filter;
    /////////////////////////////////////////////////////////
    //////////    TODO: Implement From Here    //////////////
    this->hf = hf;
    this->table = new Node* [table_size];
    this->is_it_filled = new bool[table_size];

    for (int i = 0; i < table_size; i++)
    {
        is_it_filled[i] = false;
    }
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

HashTable::~HashTable() {
    /////////////////////////////////////////////////////////
    //////////    TODO: Implement From Here    //////////////
    delete[] table;
    delete[] is_it_filled;
    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string HashTable::lookup_bloom_filter(string value) {
    int key;
    /////////////////////////////////////////////////////////
    //////////    TODO: Implement From Here    //////////////
    key = hf->hashing(value);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
    return this->bloom_filter->search(key);
}

void HashTable::print_table(ostream &out) {
    for (int i=0; i < this->table_size; i++) {
        out << i << ": [";
        /////////////////////////////////////////////////////
        /////////   TODO: Implement From Here     ///////////
        if (is_it_filled[i] == true)
        {
            Node* tempt = table[i];
            while (tempt != NULL)
            {
                if (tempt == table[i])
                {
                    out << "'" << tempt->value << "'";
                }
                else
                {
                    out << " ";
                    out << "'" << tempt->value << "'";
                }
                tempt = tempt->next;
            }
        }
        /////////      End of Implementation      ///////////
        /////////////////////////////////////////////////////
        out << "]" << endl;
    }
}

void HashTable::insert(string value) {
    int key;
    /////////////////////////////////////////////////////////
    ///////////   TODO: Implement From Here     /////////////
    int store_original;
    store_original = hf->hashing(value);
    key = store_original % table_size;
    Node* node = new Node;
    node->value = value;
    node->next = NULL;
    if (is_it_filled[key] == false)
    {
        is_it_filled[key] = true;
        table[key] = node;
    }
    else
    {
        Node* tempt = table[key];
        while (true)
        {
            if (tempt->next == NULL)
            {
                break;
            }
            tempt = tempt->next;
        }
        tempt->next = node;
    }
    key = store_original;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
    if (this->bloom_filter != nullptr)
        this->bloom_filter->insert(key);
}

string HashTable::search(string value) {
    /////////////////////////////////////////////////////////
    ///////////    TODO: Implement From Here    /////////////
    int key = hf->hashing(value) % table_size;
    Node* tempt = table[key];
    while (tempt != NULL)
    {
        if (tempt->value == value)
        {
            return "hit";
        }
        tempt = tempt->next;
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
