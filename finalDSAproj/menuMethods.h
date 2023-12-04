#define UNTITLED2_READCSV_H
#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <map> //as we are two people in a group we are allowed a data structure from a library

#include "readcsv.h"
#include "mergesort.h"
#include "maxheap.h"

using namespace std;

class menuMethods
{
    public:
        menuMethods();
        void binaryInsertion(std::string name, setupMethods& readCSV); //option 1
        void displayInfo(std::string name, setupMethods& readCSV); //option 2
        void MergeSort(std::string name, setupMethods& readCSV); //option 3
        void HeapSort(std::string name, setupMethods& readCSV); //option 4
        

    private:
        std::string numOfInputs;
        
};

menuMethods::menuMethods()
{
}

void menuMethods::binaryInsertion(std::string name, setupMethods& readCSV)
{
    std::map<double, std::string, std::greater<double>> temp;
            int count = 0;
            std::cout << "\nWhat game would you like to search for?" << std::endl;
            std::getline(std::cin, name);
            std::cout << std::endl;
            if(readCSV.games.find(name) == readCSV.games.end())
            {
                std::cout << "Could not find game. Did you spell it correctly?\n" << std::endl;
                return;
            }
            else
            {
                std::cout << "How many similar games to " << name << " would you like to view?" << std::endl;
                std::getline(std::cin, numOfInputs);
                std::cout << std::endl;
            }
            auto start_time = std::chrono::high_resolution_clock::now();

            //binary search insertion
            for(const auto& node : readCSV.nodes) //insert nodes into temp
            {
                double simil = readCSV.getSimilarity(readCSV.games[name], node);
                if(name == node.name) // prevent same game from printing
                {
                    continue;
                }

                temp.insert(std::pair<double, std::string>(simil, node.name));


            }
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);


            int max = std::min(stoi(numOfInputs),int(readCSV.nodes.size()-1));
            for(std::map<double, std::string, std::greater<double>>::iterator it = temp.begin(); it!= temp.end(); it++)
            {
                if(count != max)
                {
                    std::cout << it->second << ": " << (it->first)*100 << std::endl; // print name and similarity
                    count ++;
                }
                else
                {
                    break;
                }

            }
            
            std::cout << "\nExecution time: " << duration.count() << " microseconds \n" << std::endl << endl;
}

void menuMethods::displayInfo(std::string name, setupMethods& readCSV)
{
    std::cout << "\nWhat game would you like to search for?" << std::endl;
            std::getline(std::cin, name);
            std::cout << std::endl;
            if(readCSV.games.find(name) == readCSV.games.end())
            {
                std::cout << "\nCould not find game. Did you spell it correctly?\n" << std::endl;
                return;
            }
            else
            {
                std::cout << readCSV.games[name].name << "\n" << std::string(name.size(), '=') << std::endl;
                std::cout << "Platform: " << readCSV.games[name].platform << std::endl;
                std::cout << "Release Year: " << readCSV.games[name].releaseYear << std::endl;
                std::cout << "Developer: " << readCSV.games[name].developer << std::endl;
                std::cout << "Genere: " << readCSV.games[name].genre << std::endl;
                std::cout << "Critic Score: " << (readCSV.games[name].score) << std::endl;
                std::cout << "User Score: " << (readCSV.games[name].userScore)*10 << std::endl;
                std::cout << std::endl;
            }
}

void menuMethods::MergeSort(std::string name, setupMethods& readCSV)
{
    auto mergesorted = readCSV.nodes;

            int count = 0;
            std::cout << "\nWhat game would you like to search for?" << std::endl;
            std::getline(std::cin, name);
            std::cout << std::endl;
            if(readCSV.games.find(name) == readCSV.games.end())
            {
                std::cout << "\nCould not find game. Did you spell it correctly?\n" << std::endl;
                return;
            }
            else
            {
                std::cout << "How many similar games to " << name << " would you like to view?" << std::endl;
                std::getline(std::cin, numOfInputs);
                std::cout << std::endl;
            }

            for(auto& node : mergesorted) //set similarity values and insert into mergesorted
            {

                node.similarity = readCSV.getSimilarity(readCSV.games[name], node);
                if(name == node.name)
                {
                    continue;
                }
            }


            auto start_time = std::chrono::high_resolution_clock::now();
            mergeSort(mergesorted, 0, mergesorted.size() - 1);


            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

            count = std::min(stoi(numOfInputs),int(readCSV.nodes.size()-1));
            for(int i = 0; i < count; ++i)
            {
                cout << mergesorted[i].name<< ": " << mergesorted[i].similarity*100 << std::endl;
            }

            std::cout << "\nExecution time: " << duration.count() << " microseconds \n" << std::endl << endl;

}

void menuMethods::HeapSort(std::string name, setupMethods& readCSV)
{
    auto temp = readCSV.nodes;
    MaxHeap maxheap;

    int count = 0;
    std::cout << "\nWhat game would you like to search for?" << std::endl;
    std::getline(std::cin, name);
    std::cout << std::endl;
    if(readCSV.games.find(name) == readCSV.games.end())
    {
        std::cout << "\nCould not find game. Did you spell it correctly?\n" << std::endl;
        return;
    }
    else
    {
        std::cout << "How many similar games to " << name << " would you like to view?" << std::endl;
        std::getline(std::cin, numOfInputs);
        std::cout << std::endl;
    }


    for(auto& node : temp) //set similarity values and insert heap
    {

        node.similarity = readCSV.getSimilarity(readCSV.games[name], node);
        if(name == node.name)
        {
            continue;
        }
    }


    auto start_time = std::chrono::high_resolution_clock::now();

    //std::priority_queue<GameNode, std::vector<GameNode>, CompareGameNode> maxheap(temp.begin(), temp.end());
    maxheap.pushVector(temp);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);


    //print
    count = std::min(stoi(numOfInputs),int(readCSV.nodes.size()-1));
    for(int i = 0; i < count; ++i)
    {
        cout << maxheap.top().name<< ": " << maxheap.top().similarity*100 << std::endl;
        maxheap.pop();
    }

    std::cout << "\nExecution time: " << duration.count() << " microseconds \n" << std::endl << endl;

}


