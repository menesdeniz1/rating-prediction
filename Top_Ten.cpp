#include "ratings.h"
#include <iostream>

void show(const std::map<int,int>& counts) {
    std::vector<std::pair<int,int>> sorted(counts.begin(),counts.end());
    std::sort(sorted.begin(),sorted.end(),[](auto a,auto b){
        return a.second==b.second ? a.first<b.first : a.second>b.second;
    });
    for (size_t i=0;i<std::min<size_t>(10,sorted.size());++i)
        std::cout<<sorted[i].first<<' '<<sorted[i].second<<'\n';
}
int main(int argc,char** argv) {
    if (argc!=2) { std::cerr<<"Usage: top-ten TRAIN\n"; return 2; }
    try {
        const auto data=training(argv[1]);
        std::map<int,int> users,movies;
        for (const auto& user:data) {
            users[user.first]=static_cast<int>(user.second.size());
            for (const auto& movie:user.second) ++movies[movie.first];
        }
        std::cout<<"Users\n"; show(users); std::cout<<"Movies\n"; show(movies);
    } catch (const std::exception& e) { std::cerr<<e.what()<<'\n'; return 1; }
}
