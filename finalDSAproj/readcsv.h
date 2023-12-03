#ifndef UNTITLED2_READCSV_H
#define UNTITLED2_READCSV_H
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <set> //as we are two people in a group we are allowed one data structure from a library





using std::cout;
using std::endl;
// Struct to represent a node
struct GameNode {
    std::string name;
    std::string platform;
    double releaseYear=0;
    double score=0;
    double userScore =0;
    std::string developer;
    std::string genre;
    std::string players;
    double critics = 0;
    double users = 0;

    std::vector<double> genreVec;



};

class setupMethods
{
    private:
        GameNode parseCSVRow();
        double cosineSimilarity(const std::vector<double>& vecA, const std::vector<double>& vecB);
    public:
        setupMethods();
        double getSimilarity(const GameNode& root, const GameNode& node);
        // Vector to store the GameNodes
        std::vector<GameNode> nodes;
        std::string row;

        std::unordered_map<std::string, GameNode> games;
        
        
};

setupMethods::setupMethods()
{
    std::ifstream inputFile("assets/games-data.csv");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the CSV file.\n";
        return;
    }

    std::string header;
    std::getline(inputFile, header);


    

    

    int asdf =0;
    while (std::getline(inputFile, row)) {
        GameNode node = parseCSVRow();
        games.insert(std::pair<std::string, GameNode>(node.name, node));
        nodes.push_back(node);
    }

    inputFile.close();
}

GameNode setupMethods::parseCSVRow() {
    std::istringstream iss(row);
    std::string token;

    GameNode node;

    //name
    if(iss.peek() != '"'){
        std::getline(iss, node.name, ',');
        //cout << node.name << " ";
    }
    else {
        // cout << "bruh" << endl;
        std::getline(iss, token, '\"');
        std::getline(iss, token, '\"');
        std::replace(token.begin(), token.end(), ',', ' ');
        node.name = token;
    }


    //platform
    std::getline(iss, node.platform, ',');

    //year
    std::getline(iss, token, ',');  // Read date
    std::getline(iss, token, ',');
    token.pop_back();
    try {
        node.releaseYear = std::stod(token);
    } catch (const std::invalid_argument& e) {
        // Handle the case where conversion to double fails (e.g., token is not a valid number)
        //std::cerr << "Error: score" << e.what() << std::endl;
        node.releaseYear = -1; // Set to -1 in case of an error
    }

    // metacritic
    std::getline(iss, token, ',');
    try {
        node.score = std::stod(token);
    } catch (const std::invalid_argument& e) {
        // Handle the case where conversion to double fails (e.g., token is not a valid number)
        //std::cerr << "Error: score" << e.what() << std::endl;
        node.score = -1; // Set to -1 in case of an error
    }

    //userScore
    std::getline(iss, token, ',');
    try {
        node.userScore = std::stod(token);
    } catch (const std::invalid_argument& e) {
        // Handle the case where conversion to double fails (e.g., token is not a valid number)
        //std::cerr << "Error: userscore" << e.what() << std::endl;
        node.userScore = -1; // Set to -1 in case of an error
    }



    //developer
    if(iss.peek() != '"'){
        std::getline(iss, node.developer, ',');
    }
    else {
       // cout << "bruh" << endl;
        std::getline(iss, token, '\"');
        std::getline(iss, token, '\"');
        std::replace(token.begin(), token.end(), ',', ' ');
        node.developer = token;
    }


    //genre
    std::getline(iss, token, '\"');
    std::getline(iss, token, '\"');
    std::replace(token.begin(), token.end(), ',', ' ');
    node.genre = token;
    iss.ignore();


    //players
    std::getline(iss, node.players, ',');

    //critics
    std::getline(iss, token, ',');
    try {
        node.critics = std::stod(token);
    } catch (const std::invalid_argument& e) {
        // Handle the case where conversion to double fails (e.g., token is not a valid number)
        //std::cerr << "Error: critics" << e.what() << std::endl;
        node.critics = -1; // Set to -1 in case of an error
    }


    //users
    std::getline(iss, token, ' ');
    try {
        node.users = std::stod(token);
    } catch (const std::invalid_argument& e) {
        // Handle the case where conversion to double fails (e.g., token is not a valid number)
        //std::cerr << "Error: users" << e.what() << std::endl;
        node.users = -1; // Set to -1 in case of an error
    }


    return node;
}

double setupMethods::cosineSimilarity(const std::vector<double>& vecA, const std::vector<double>& vecB)
{
    double dotProduct = 0.0;
    double magnitudeA = 0.0;
    double magnitudeB = 0.0;

    for (size_t i = 0; i < vecA.size(); ++i) {
        dotProduct += vecA[i] * vecB[i];
        magnitudeA += vecA[i] * vecA[i];
        magnitudeB += vecB[i] * vecB[i];
    }

    if (magnitudeA == 0.0 || magnitudeB == 0.0) {
        // Avoid division by zero
        return 0.0;
    }

    return dotProduct / (sqrt(magnitudeA) * sqrt(magnitudeB));
}

double setupMethods::getSimilarity(const GameNode& root, const GameNode& node)
{
    double similarity = 0;
    if(node.name == root.name){ //don't want same game dif platform
        similarity += -1;
    }
    if(node.platform == root.platform){
        similarity += .1;
    }
    if(node.developer == root.developer){
        similarity += .1;
    }
    if(node.players == root.players){
        similarity += .1;
    }
    similarity += cosineSimilarity(root.genreVec,node.genreVec) * .4;

    std::vector<double> nodeNums, rootNums;
    nodeNums.emplace_back(node.releaseYear/2023);
    nodeNums.emplace_back(node.score/100);
    nodeNums.emplace_back(node.userScore);
    nodeNums.emplace_back(node.critics/100);
    nodeNums.emplace_back(node.users/2000);


    rootNums.emplace_back(root.releaseYear/2023);
    rootNums.emplace_back(root.score/100);
    rootNums.emplace_back(root.userScore);
    rootNums.emplace_back(root.critics/100);
    rootNums.emplace_back(root.users/2000);

    similarity += cosineSimilarity(nodeNums,rootNums)*.3;




    return similarity;
}
#endif //UNTITLED2_READCSV_H
