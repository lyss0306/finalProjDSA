#ifndef UNTITLED2_TOKENS_H
#define UNTITLED2_TOKENS_H

#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <cmath>
#include <regex>
#include "readcsv.h"




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

std::unordered_map<std::string,std::vector<double>> countVectorization(std::vector<GameNode>& nodes) {
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


    return genreMap;
}




#endif //UNTITLED2_TOKENS_H
