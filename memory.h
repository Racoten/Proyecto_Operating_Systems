#include <iostream>
#include <list>
#include <unordered_set>

using namespace std;

int calculatePageFaults(int numFrames, int numReferences, int pageReferences[]) {
    int pageFaults = 0;
    list<int> pageList;
    unordered_set<int> pageSet;

    for (int i = 0; i < numReferences; i++) {
        if (pageSet.find(pageReferences[i]) != pageSet.end()) {
            continue;
        }

        pageFaults++;

        if (pageList.size() < numFrames) {
            pageList.push_back(pageReferences[i]);
            pageSet.insert(pageReferences[i]);
        }
        else {
            int oldestPage = pageList.front();
            pageList.pop_front();
            pageSet.erase(oldestPage);
            pageList.push_back(pageReferences[i]);
            pageSet.insert(pageReferences[i]);
        }
    }

    return pageFaults;
}