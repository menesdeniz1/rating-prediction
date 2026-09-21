#include "../ratings.h"
#include <cassert>
int main() {
    assert(jaccard({}, {})==0);
    assert(jaccard({{1,3}},{{2,4}})==0);
    assert(jaccard({{1,3}},{{1,5}})==1);
    Ratings data={{1,{{10,4}}},{2,{{10,3},{20,5}}},{3,{{30,2}}}};
    auto before=data;
    assert(predict(data,1,20)==5);
    assert(predict(data,999,20)==0);
    assert(predict(data,1,999)==0);
    assert(data==before);
}
