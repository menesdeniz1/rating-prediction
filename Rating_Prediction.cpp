#include "ratings.h"
#include <iostream>

int main(int argc,char** argv) {
    if (argc!=4) { std::cerr<<"Usage: predict TRAIN QUERIES OUTPUT\n"; return 2; }
    try {
        const auto data=training(argv[1]);
        const auto queries=rows(argv[2]);
        std::ostringstream result;
        for (const auto& row:queries)
            result<<id(row[0])<<','<<predict(data,id(row[1]),id(row[2]))<<'\n';
        // Reject an existing destination to avoid overwriting input/user data.
        if (std::ifstream(argv[3]).good()) throw std::runtime_error("Output exists; choose a new path");
        std::ofstream output(argv[3]);
        if (!output || !(output<<result.str())) throw std::runtime_error("Cannot write output");
    } catch (const std::exception& e) { std::cerr<<e.what()<<'\n'; return 1; }
}
