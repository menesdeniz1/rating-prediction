# Rating prediction coursework

An educational user-based collaborative-filtering experiment. Similarity is Jaccard overlap of rated movie IDs; predictions are similarity-weighted neighbor ratings. It does not use rating-value similarity, production ranking or a trained ML model.

## Build and run

Use a C++17 compiler:

```sh
g++ -std=c++17 Rating_Prediction.cpp -o predict
g++ -std=c++17 Top_Ten.cpp -o top-ten
g++ -std=c++17 tests/test.cpp -o checks
./checks
./predict TRAIN QUERIES NEW_OUTPUT
./top-ten TRAIN
```

Inputs are simple comma-separated text without headers or quoted fields. Training rows: `user_id,movie_id,rating` (rating 0.5–5). Query rows: `query_id,user_id,movie_id`. Output preserves query IDs. A prediction of zero means unavailable, not a zero-star rating. Duplicate training pairs and malformed rows are rejected. Output must be a new path.

## Publication maintenance

The original coursework files [train.csv](train.csv) and [test.csv](test.csv) were restored unchanged from backup with the repository owner's explicit authorization. The owner identifies them as public coursework data; the original upstream dataset/version and redistribution terms are not documented here. No MovieLens attribution or additional dataset license is asserted. The automated checks use tiny synthetic inputs.

A September 2026 restoration review found 1,048,575 headerless training rows and 5,000 headerless query rows. The training file contains 7,955 zero ratings, which the current 0.5–5 validator rejects. Their meaning is not documented in the original repository. These original files are historical project evidence, not a ready-to-run fixture for the repaired validator: clarify the rating scale before using the full training file. No rows were silently filtered or relabeled. These counts describe the files, not model accuracy or engineering impact.

September 2026 maintenance replaced unsafe hardcoded-path/input/cache/index handling with portable validated inputs, const lookups and deterministic bounded top-ten output. The original coursework history remains where possible; current repairs are not historical achievements. No accuracy or performance benchmark is claimed. The straightforward neighbor scan is not designed for large-scale deployment.
