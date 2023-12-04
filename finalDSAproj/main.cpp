#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <cmath>
#include <chrono>
#include <string>
#include <set>
#include <queue> // 2-person group, was told we can use a library function

//do we need to include queue, chono, or set?

#include "readcsv.h"
#include "menuMethods.h"
#include "mergesort.h"
#include "maxheap.h"


struct CompareGameNode {
    bool operator()(const GameNode& node1, const GameNode& node2) {
        return node1.similarity < node2.similarity;
    }
};
//priority queue needs this to work

int main() {

    setupMethods readCSV; //init
    menuMethods menu; //init



    std::string input;
    std::string name;
    std::string numOfInputs;
    bool quit = false;

    std::cout << "\n____GAME RECOMMENDATION SOFTWARE START____\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n.  .  .  .  .  .  .  .  .  .  .  .  .  . .\n" << std::endl;
    while(!quit)
    {

        std::cout << "Please Choose an Option:\n-----------------------\n[1] Search Game by Name and Find Similar (binary insertion)\n" <<
                  "[2] View a Game's Information\n" <<
                  "[3] Find Most Similar Games with Mergesort\n" <<
                  "[4] Find Most Similar Games with Max Heap\n" <<
                  "[5] Quit" << std::endl;
        std::getline(std::cin, input);

        if(input == "1")
        {
            menu.binaryInsertion(name, readCSV);
        }

        if(input == "2")
        {
            menu.displayInfo(name, readCSV);
        }

        if(input == "3")
        {
            menu.MergeSort(name, readCSV);
        }

        if(input == "4")
        {
            menu.HeapSort(name, readCSV);
        }

        if(input == "5")
        {
            std::cout << "\nThank you for using our program :)\n" << std::endl;
            quit = true;
            break;
        }


    }

    return 0;
}