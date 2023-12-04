#ifndef UNTITLED2_READCSV_H
#define UNTITLED2_READCSV_H
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <set>





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

    double similarity; //for sorts


};

class setupMethods
{
    private:
        GameNode parseCSVRow();
        template <typename T> void printVector(const std::vector<T>& vec);
        static double cosineSimilarity(const std::vector<double>& vecA, const std::vector<double>& vecB);
    public:
        setupMethods();
        static double getSimilarity(const GameNode& root, const GameNode& node);
        // Vector to store the GameNodes
        std::vector<GameNode> nodes;
        std::string row;

        std::unordered_map<std::string, GameNode> games;
        
        
};

std::vector<std::string> tokenize(const std::string& text) {
    std::vector<std::string> tokens;
    std::unordered_set<std::string> uniqueTokens;

    std::regex wordRegex(R"([^[:space:]]+)"); // Keep only alphanumeric and exclude whitespace

    for (std::sregex_iterator it(text.begin(), text.end(), wordRegex), end; it != end; ++it) {
        std::string token = it->str();

        std::transform(token.begin(), token.end(), token.begin(), ::tolower);

        // Check if the lowercase token is already in the set
        if (uniqueTokens.insert(token).second) {
            // If not found (insert successful), add it to the vector
            tokens.push_back(token);
        }
    }

    return tokens; // Return vector of unique words that were separated by spaces
}
void countVectorization(std::vector<GameNode>& nodes) {
    // Create a vocabulary
    std::unordered_set <std::string> vocabulary;
    for (const auto& node : nodes) {
        auto tokens = tokenize(node.genre);
        vocabulary.insert(tokens.begin(), tokens.end());
    }


    // Initialize a dictionary to store word counts for each node.genre
    std::unordered_map<std::string, std::unordered_map<std::string, double>> countMatrix;
    for (const auto& node : nodes) {
        auto tokens = tokenize(node.genre);
        for (const std::string& word : tokens) {
            countMatrix[node.name + node.platform][word]++;
        }
    }

    std::unordered_map<std::string, std::vector<double>> genreMap;

    for ( auto& node : nodes) {
        std::vector<double> row;
        row.reserve(vocabulary.size());
        for (const std::string& word : vocabulary) {
            row.push_back(countMatrix[node.name+node.platform][word]);
        }
        node.genreVec = row;
    }
}

setupMethods::setupMethods() {
    std::ifstream inputFile("assets/games-data.csv");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the CSV file.\n";
        return;
    }

    std::string header;
    std::getline(inputFile, header);


    int asdf = 0;
    while (std::getline(inputFile, row)) {
        GameNode node = parseCSVRow();
        nodes.push_back(node);
    }
    countVectorization(nodes);
    for (const auto& node: nodes) {
    games.insert(std::pair<std::string, GameNode>(node.name, node));
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
        //std::replace(token.begin(), token.end(), ',', ' ');
        node.name = token;
        std::getline(iss,token,',');
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
        similarity += .05;
    }
    if(node.developer == root.developer){
        similarity += .1;
    }
    if(node.players == root.players){
        similarity += .05;
    }
    similarity += cosineSimilarity(root.genreVec,node.genreVec) * .45;

    std::vector<double> nodeNums, rootNums;
    nodeNums.emplace_back(node.releaseYear/2023);
    nodeNums.emplace_back(node.score/100);
    nodeNums.emplace_back(node.userScore);
    nodeNums.emplace_back(node.critics/100);
    nodeNums.emplace_back(node.users/800);


    rootNums.emplace_back(root.releaseYear/2023);
    rootNums.emplace_back(root.score/100);
    rootNums.emplace_back(root.userScore);
    rootNums.emplace_back(root.critics/100);
    rootNums.emplace_back(root.users/2000);

    similarity += cosineSimilarity(nodeNums,rootNums)*.35;

    //similarity += (node.userScore)/2;


    return similarity;
}


template <typename T> void setupMethods::printVector(const std::vector<T>& vec) {
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}
#endif //UNTITLED2_READCSV_H
