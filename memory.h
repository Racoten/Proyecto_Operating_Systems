#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * Calculate the number of page faults using the First-In-First-Out (FIFO) algorithm
 * This function takes the number of frames and a linked list of page references as input
 * and returns the number of page faults that occurred using the FIFO page replacement algorithm.
 * 
 * @param numFrames The number of available frames
 * @param pageReferences Pointer to the head of the linked list of PageFrame structs representing the page reference string
 * @return The number of page faults calculated using the FIFO algorithm
 */
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

/**
 * Calculate the number of page faults using the Least Recently Used (LRU) algorithm
 * This function takes the number of frames and a linked list of page references as input
 * and returns the number of page faults that occurred using the LRU page replacement algorithm.
 * 
 * @param numFrames The number of available frames
 * @param pageReferences Pointer to the head of the linked list of PageFrame structs representing the page reference string
 * @return The number of page faults calculated using the LRU algorithm
 */
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

/**
 * Find the optimal page to replace using the Optimal Page Replacement algorithm
 * This function takes a map of page access positions and a set of pages currently in frames,
 * and returns the page that should be replaced based on the Optimal algorithm.
 * 
 * @param pageAccessPositions A map of page numbers to their positions in the access sequence (a vector of integers)
 * @param pagesInFrames A set containing the pages currently in the frames
 * @return The page number that should be replaced based on the Optimal algorithm
 */
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

/**
 * Calculate the number of page faults using the Optimal Page Replacement algorithm
 * This function takes the number of frames and a linked list of page references as input
 * and returns the number of page faults that occurred using the Optimal page replacement algorithm.
 * 
 * @param numFrames The number of available frames
 * @param pageReferences Pointer to the head of the linked list of PageFrame structs representing the page reference string
 * @return The number of page faults calculated using the Optimal algorithm
 */
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
