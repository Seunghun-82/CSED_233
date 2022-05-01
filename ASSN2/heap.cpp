#include "heap.h"
#include <iostream>
#include <string>

using namespace std;


MinHeap::MinHeap() {
    heap_size = 0;
    heap_arr = new int[100]; // Default array of size 100
}

string MinHeap::printHeap(){
    string answer;
    for (int i = 0; i < heap_size; i++)
        answer += to_string(heap_arr[i]) + " ";
    return answer;
}

void MinHeap::insertKey(int k) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
   
    int current_index = heap_size;
    heap_size++;
    int root_index = (current_index - 1) / 2;
    heap_arr[current_index] = k;
    while (heap_arr[root_index] > heap_arr[current_index])
    {
        int tempt = heap_arr[root_index];
        heap_arr[root_index] = heap_arr[current_index];
        heap_arr[current_index] = tempt;

        current_index = root_index;
        root_index = (root_index - 1) / 2;
    }

    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void MinHeap::deleteMin() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    heap_arr[0] = heap_arr[heap_size - 1];
    heap_size--;
    minHeapProp(0);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void MinHeap::minHeapProp(int i) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int store_pres_max = i;
    int max_index = i;
    int left_index = 2 * i + 1;
    int right_index = 2 * i + 2;

    if (left_index < heap_size && heap_arr[max_index] > heap_arr[left_index])
    {
        max_index = left_index;
    }
    if (right_index < heap_size && heap_arr[max_index] > heap_arr[right_index])
    {
        max_index = right_index;
    }

    if (max_index != store_pres_max)
    {
        int tempt = heap_arr[max_index];
        heap_arr[max_index] = heap_arr[store_pres_max];
        heap_arr[store_pres_max] = tempt;
        minHeapProp(max_index);
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}