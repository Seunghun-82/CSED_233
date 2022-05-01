#include "sort.h"
#include <iostream>
#include <fstream>
#include <string>


sortAlg::sortAlg() {
    arr_size = 0;
    arr = new int[100]; // Each test case will be less than 100 values
}

using namespace std;

void sortAlg::printArray(ofstream &fout) {
    string answer;
    for (int i = 0; i < arr_size - 1; i++)
        answer += to_string(arr[i]) + " ";
    answer += to_string(arr[arr_size - 1]);
    fout << answer << endl;
}


void sortAlg::bubbleSort(ofstream &fout) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////


    for (int i = 0; i < arr_size - 1; i++)
    {
        for (int j = arr_size - 1 ; j > i ; j--)
        {
            if (arr[j] < arr[j - 1])
            {
                int tempt;
                tempt = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = tempt;
            }
        }
        printArray(fout); // DO NOT ERASE THIS LINE
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void sortAlg::insertionSort(ofstream &fout) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    for (int i = 1; i < arr_size; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[j + 1] < arr[j])
            {
                int swap = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = swap;
            }
            else
            {
                break;
            }
        }

        printArray(fout);// DO NOT ERASE THIS LINE
    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

}


void sortAlg::merge(int left, int mid, int right) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    int left_index = mid - left + 1;
    int right_index = right - mid;
    int Left_list[left_index];
    int Right_list[right_index];

    for (int i = 0; i < left_index; i++)
    {
        Left_list[i] = arr[left + i];
    }
    for (int i = 0; i < right_index; i++)
    {
        Right_list[i] = arr[mid + 1 + i];
    }
    int left_seq = 0;
    int right_seq = 0;
    int arr_index = left;
    while (left_seq < left_index && right_seq < right_index)
    {
        if (Left_list[left_seq] > Right_list[right_seq])
        {
            arr[arr_index] = Right_list[right_seq];
            right_seq++;
        }
        else
        {
            arr[arr_index] = Left_list[left_seq];
            left_seq++;
        }
        arr_index++;
    }

    while (right_seq < right_index)
    {
        arr[arr_index] = Right_list[right_seq];
        right_seq++;
        arr_index++;
    }

    while (left_seq < left_index)
    {
        arr[arr_index] = Left_list[left_seq];
        left_seq++;
        arr_index++;
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void sortAlg::mergeSort(ofstream &fout, int left, int right) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    if (left < right) 
    {
        int mid = left + (right - left) / 2;
        mergeSort(fout, left, mid);
        mergeSort(fout, mid + 1, right);

        merge(left, mid, right);

        printArray(fout);// DO NOT ERASE THIS LINE

    }

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

}