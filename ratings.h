#pragma once
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>
#include <vector>

using Ratings = std::map<int, std::map<int, double>>;
inline std::vector<std::vector<std::string>> rows(const std::string& path) {
    std::ifstream file(path);
    if (!file) throw std::runtime_error("Cannot open input file");
    std::vector<std::vector<std::string>> result;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (line.back()=='\r') line.pop_back();
        if (line.empty()) continue;
        std::stringstream stream(line); std::string cell; std::vector<std::string> row;
        while (std::getline(stream,cell,',')) row.push_back(cell);
        if (row.size()!=3 || line.back()==',') throw std::runtime_error("Expected exactly three fields, no header");
        result.push_back(row);
    }
    return result;
}
inline int id(const std::string& s) {
    size_t used; int value=std::stoi(s,&used);
    if (used!=s.size() || value<0) throw std::runtime_error("Invalid ID");
    return value;
}
inline Ratings training(const std::string& path) {
    Ratings data;
    for (const auto& row:rows(path)) {
        size_t used; double rating=std::stod(row[2],&used);
        if (used!=row[2].size() || !std::isfinite(rating) || rating<0.5 || rating>5)
            throw std::runtime_error("Invalid rating; expected 0.5..5");
        auto& user=data[id(row[0])];
        if (!user.emplace(id(row[1]),rating).second) throw std::runtime_error("Duplicate user/movie pair");
    }
    return data;
}
inline double jaccard(const std::map<int,double>& a,const std::map<int,double>& b) {
    size_t intersection=0;
    for (const auto& item:a) if (b.count(item.first)) ++intersection;
    const size_t total=a.size()+b.size()-intersection;
    return total ? static_cast<double>(intersection)/total : 0.0;
}
inline double predict(const Ratings& data,int user,int movie) {
    auto target=data.find(user);
    if (target==data.end()) return 0;
    double numerator=0,denominator=0;
    for (const auto& other:data) {
        if (other.first==user) continue;
        auto rated=other.second.find(movie);
        if (rated==other.second.end()) continue;
        const double similarity=jaccard(target->second,other.second);
        numerator+=similarity*rated->second; denominator+=similarity;
    }
    return denominator ? numerator/denominator : 0;
}
