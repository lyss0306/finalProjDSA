#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <cmath>
#include <chrono>
#include <string>
#include <set> //as we are two people in a group we are allowed one data structure from a library

#include "tokens.h"
#include "readcsv.h"

/*
    - changed how the csv file is stored so it works on any computer. Held in project files "assets" folder
    - Now simply with the call "setupMethods" all parsing is completed and nodes vector is stored elsewhere
    - Moved similarity functions to readcsv.h as well
    - Created games map that works liked "nodes" but I can access by name now

    ToDO:
    - clean up functions jesus[~]
    - Create main function to take in user input by name (potentially by genre later)[]
    - sorts?? fuck me[]
        - make another map of similars (string, similarity) and use a sort to organize em

    - input name incorrect did you mean any of these?
    - How many similar games would you like to see?
    - What is the max similarity?? Bayonetta 2 and NieR should be very very similar


    I'd like to propose saving nodes by a map or set to have a key with the name and the value is the graph object
        - I kept both but my functions works off the "games" map so I may access names in constant time
*/



template <typename T>
void printVector(const std::vector<T>& vec) {
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}



int main() {
    
    setupMethods readCSV;

    /*this takes a few seconds to load up the map of genres, comment out chunk probably

    auto start = std::chrono::high_resolution_clock::now();
    auto genreMap = countVectorization(nodes);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;*/


    //std::cout << "NAME: " << readCSV.games["Bayonetta 2"].name << " USER SCORE: " << readCSV.games["Bayonetta 2"].userScore << std::endl;
    //std::cout << "NAME: " << readCSV.games["NieR: Automata - Game of the YoRHa Edition"].name << " USER SCORE: " << readCSV.games["NieR: Automata - Game of the YoRHa Edition"].userScore << std::endl;

    //double check = readCSV.getSimilarity(readCSV.games["Bayonetta 2"], readCSV.games["NieR: Automata - Game of the YoRHa Edition"]);

    //std::cout << "SIMILARITY: " << check << endl;
    std::string input = "";
    std::string name = "";
    std::string numOfInputs = "";
    bool quit = false;

    std::cout << "____WELCOME TO THE GAME SIMILARITY PROGRAM (name pending)____\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n.  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  " << std::endl;
    while(!quit)
    {
        std::cout << "What would you like to do?\n[1] Search for game by name\n[2] View a Game's Information\n[3] Quit" << std::endl;
        std::getline(std::cin, input);

        if(input == "1")
        {
            std::map<double, std::string, std::greater<double>> temp;
            int count = 0;
            std::cout << "What game would you like to search for?" << std::endl;
            std::getline(std::cin, name);
            std::cout << std::endl;
            if(readCSV.games.find(name) == readCSV.games.end())
            {
                std::cout << "Could not find game. Did you spell it correctly?" << std::endl;
                continue;
            }
            else
            {
                std::cout << "How many similar games to " << name << " would you like to view?" << std::endl;
                std::getline(std::cin, numOfInputs);
                std::cout << std::endl;
            }

            for(std::unordered_map<const std::string, GameNode>::iterator it = readCSV.games.begin(); it!=readCSV.games.end(); it++)
            {
                double simil = readCSV.getSimilarity(readCSV.games[name], it->second);
                if(name == it->second.name)
                {
                    continue;
                }
                temp.insert(std::pair<double, std::string>(simil, it->second.name));
                
            }
            for(std::map<double, std::string, std::greater<double>>::iterator it = temp.begin(); it!= temp.end(); it++)
            {
                if(count != stoi(numOfInputs))
                {
                    std::cout << it->second << ": " << (it->first)*100 << std::endl;
                    count ++;
                }
                else
                {
                    break;
                }

                
                
            }

            std::cout << std::endl;
            
        }

        if(input == "2")
        {
            std::cout << "What game would you like to search for?" << std::endl;
            std::getline(std::cin, name);
            std::cout << std::endl;
            if(readCSV.games.find(name) == readCSV.games.end())
            {
                std::cout << "Could not find game. Did you spell it correctly?" << std::endl;
                continue;
            }
            else
            {
                std::cout << readCSV.games[name].name << "\n" << std::string(name.size(), '=') << std::endl;
                std::cout << "Platform: " << readCSV.games[name].platform << std::endl;
                std::cout << "Release Year: " << readCSV.games[name].releaseYear << std::endl;
                std::cout << "Developer: " << readCSV.games[name].developer << std::endl;
                std::cout << "Genere: " << readCSV.games[name].genre << std::endl;
                std::cout << "Critic Score: " << (readCSV.games[name].score) << std::endl;
                std::cout << "User Score: " << (readCSV.games[name].userScore) << std::endl;
                std::cout << std::endl;
            }
           
        }

        if(input == "3")
        {
            std::cout << "Thank you for using our program :)" << std::endl;
            quit = true;
            break;
        }

        
    }
    
    return 0;
}
