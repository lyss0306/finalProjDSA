#ifndef UNTITLED2_MERGESORT_H
#define UNTITLED2_MERGESORT_H
#pragma once
#include "readcsv.h"


void merge(std::vector<GameNode>& mergesorted, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors to hold the two halves
    std::vector<GameNode> left_half(n1);
    std::vector<GameNode> right_half(n2);

    // Copy data to temporary vectors left_half[] and right_half[]
    for (int i = 0; i < n1; i++)
        left_half[i] = mergesorted[left + i];
    for (int j = 0; j < n2; j++)
        right_half[j] = mergesorted[mid + 1 + j];

    // Merge the temporary vectors back into mergesorted[left...right]
    int i = 0; // Initial index of first subvector
    int j = 0; // Initial index of second subvector
    int k = left; // Initial index of merged subvector
    while (i < n1 && j < n2) {
        if (left_half[i].similarity >= right_half[j].similarity) {
            mergesorted[k] = left_half[i];
            i++;
        } else {
            mergesorted[k] = right_half[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of left_half[], if there are any
    while (i < n1) {
        mergesorted[k] = left_half[i];
        i++;
        k++;
    }

    // Copy the remaining elements of right_half[], if there are any
    while (j < n2) {
        mergesorted[k] = right_half[j];
        j++;
        k++;
    }
}

// Merge sort function
void mergeSort(std::vector<GameNode>& mergesorted, int left, int right) {
    if (left < right) {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(mergesorted, left, mid);
        mergeSort(mergesorted, mid + 1, right);

        // Merge the sorted halves
        merge(mergesorted, left, mid, right);
    }
}



#endif //UNTITLED2_MERGESORT_H
