#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int calculatePageFaultsFIFO(int numFrames, PageFrame* pageReferences) {
    int pageFaults = 0;
    list<int> pageList;
    unordered_set<int> pageSet;

    PageFrame* current = pageReferences;

    while (current != nullptr) {
        int currentPage = current->page;

        if (pageSet.find(currentPage) != pageSet.end()) {
            current = current->next;
            continue;
        }

        pageFaults++;

        if (pageList.size() < numFrames) {
            pageList.push_back(currentPage);
            pageSet.insert(currentPage);
        }
        else {
            int oldestPage = pageList.front();
            pageList.pop_front();
            pageSet.erase(oldestPage);
            pageList.push_back(currentPage);
            pageSet.insert(currentPage);
        }

        current = current->next;
    }

    return pageFaults;
}

int calculatePageFaultsLRU(int numFrames, PageFrame* pageReferences) {
    int pageFaults = 0;
    list<int> pageList;
    unordered_map<int, list<int>::iterator> pageMap;

    PageFrame* current = pageReferences;
    while (current != nullptr) {
        int currentPage = current->page;

        if (pageMap.find(currentPage) != pageMap.end()) {
            pageList.erase(pageMap[currentPage]);
        } else {
            pageFaults++;
            if (pageList.size() >= numFrames) {
                int lruPage = pageList.back();
                pageMap.erase(lruPage);
                pageList.pop_back();
            }
        }

        pageList.push_front(currentPage);
        pageMap[currentPage] = pageList.begin();

        current = current->next;
    }

    return pageFaults;
}

int findOptimalPageToReplace(unordered_map<int, vector<int>>& pageAccessPositions, unordered_set<int>& pagesInFrames) {
    int farthestPage = -1;
    int farthestPosition = -1;

    for (const auto& entry : pageAccessPositions) {
        int page = entry.first;
        const vector<int>& positions = entry.second;

        if (pagesInFrames.find(page) != pagesInFrames.end()) {
            auto nextAccessIt = upper_bound(positions.begin(), positions.end(), farthestPosition);
            if (nextAccessIt == positions.end() || *nextAccessIt > farthestPosition) {
                farthestPage = page;
                farthestPosition = nextAccessIt != positions.end() ? *nextAccessIt : numeric_limits<int>::max();
            }
        }
    }

    return farthestPage;
}

int calculatePageFaultsOptimal(int numFrames, PageFrame* pageReferences) {
    int pageFaults = 0;
    unordered_set<int> pagesInFrames;
    unordered_map<int, vector<int>> pageAccessPositions;
    vector<int> pageReferenceList;

    // Collect page reference list and record access positions
    PageFrame* current = pageReferences;
    int position = 0;
    while (current != nullptr) {
        int currentPage = current->page;
        pageAccessPositions[currentPage].push_back(position);
        pageReferenceList.push_back(currentPage);
        position++;
        current = current->next;
    }

    for (int i = 0; i < pageReferenceList.size(); i++) {
        int currentPage = pageReferenceList[i];

        if (pagesInFrames.find(currentPage) != pagesInFrames.end()) {
            continue;
        }

        pageFaults++;

        if (pagesInFrames.size() < numFrames) {
            pagesInFrames.insert(currentPage);
        } else {
            int pageToReplace = findOptimalPageToReplace(pageAccessPositions, pagesInFrames);
            pagesInFrames.erase(pageToReplace);
            pagesInFrames.insert(currentPage);
        }
    }

    return pageFaults;
}