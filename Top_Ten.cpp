#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>

std::vector<int> userID;
std::vector<int> movieID;

struct sort_pred {
    bool operator()(const std::pair<int, int>& left, const std::pair<int, int>& right) {
        return left.second < right.second;
    }
};

void numberOfRatings(std::vector<int> frequent_ID)
{
    std::unordered_map<int, int>freqMap;
    std::vector<std::pair<int, int>> data_set;

    for (int i = 0; i < frequent_ID.size(); i++) {
        freqMap[frequent_ID[i]]++;
    }

    std::copy(freqMap.begin(), freqMap.end(), std::back_inserter(data_set));

    std::sort(data_set.begin(), data_set.end(),sort_pred());

    for (int i = data_set.size()-1; i > data_set.size()-11; i--) {
        std::cout << data_set[i].first <<" " << data_set[i].second << "\n";
    }
}

void read_UserID(std::string path) {
    std::fstream readFile;
  
    readFile.open(path, std::ios::in);

    if (!readFile.is_open()) {
        std::cerr << "can't reach the file" << std::endl;
    }

    std::string user_id;
    std::string movie_id;
    std::string ratings;

    int int_user;

    while (getline(readFile, user_id, ','), getline(readFile, movie_id, ','), getline(readFile, ratings)) {
        int_user = stoi(user_id);
        userID.push_back(int_user);
    }
}

void read_MovieID(std::string path) {
    std::fstream readFile;

    readFile.open(path, std::ios::in);


    if (!readFile.is_open()) {
        std::cerr << "can't reach the file" << std::endl;
    }

    std::string user_id;
    std::string movie_id;
    std::string ratings;

    int int_movie;

    while (getline(readFile, user_id, ','), getline(readFile, movie_id, ','), getline(readFile, ratings)) {
        int_movie = stoi(movie_id);
        movieID.push_back(int_movie);
    }
}

int main()
{
    read_UserID("C:\\Users\\MSI-GL65\\Desktop\\train.csv");
    numberOfRatings(userID);
    read_MovieID("C:\\Users\\MSI-GL65\\Desktop\\train.csv");
    numberOfRatings(movieID);
}