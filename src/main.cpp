#include "utils.h"
#include "Entry.h"

#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

using EntryType = Entry<string, int>;
using EntryTypeSet = set<EntryType>;

static EntryTypeSet entrySet, entrySet2;
static int curLineNr = 0;
static int curLineNr2 = 0;

static void addWord(string word) {
    EntryType e(normalize(word));
    pair<EntryTypeSet::const_iterator, bool> rp = entrySet.insert(e);
    const_cast<EntryType&>(*rp.first).addValue(curLineNr);
}

static void addWord2(string word) {
    EntryType e(normalize(word));
    pair<EntryTypeSet::const_iterator, bool> rp = entrySet2.insert(e);
    const_cast<EntryType&>(*rp.first).addValue(curLineNr2);
}

double wordAmountComparison(EntryTypeSet setA, EntryTypeSet setB) {
    EntryTypeSet helpSet;
    // vector<string> s_intersect;
    std::set_intersection(setA.begin(), setA.end(), setB.begin(), setB.end(), std::inserter(helpSet, std::next(helpSet.begin()))  );
    
    cout << helpSet.size() << endl;

    return 0;
}

// double wordCountComparison

double wordSumComparison(EntryTypeSet setA, EntryTypeSet setB) {
    int sumA = setA.size();
    int sumB = setB.size();
    // cout << sumA << " " << sumB << endl;
    return ( (sumA - (double)abs(sumA - sumB)) / sumA * 100);
}

double wordCountComparison(EntryTypeSet setA, EntryTypeSet setB) {
    int sumA = setA.size();
    int sumB = setB.size();
    // cout << sumA << " " << sumB << endl;
    return ( (sumA - (double)abs(sumA - sumB)) / sumA * 100);
}

void plagiarismCheck(EntryTypeSet setA, EntryTypeSet setB) {
    double WS = wordSumComparison(setA, setB);
    double WAC = wordAmountComparison(setA, setB);
//     double WCC = wordCountComparison(setA, setB);
//     double WLC = wordLineComparison(setA, setB);

    cout << "****\tPlagiarism check: " << endl;
    cout << "\tWord count is identical to " << WS << " percent" << endl;
//     cout << "\tWords overlap by " << WAC << " percent" << endl;
//     cout << "\tCount per word overlaps by "  << WCC << " percent" << endl;
//     cout << "\tWord per line overlaps by "  << WCC << " percent" << endl;
}


int main(int argc, char *argv[]) {
    ifstream fin, finCheck;
    openStream(argc, argv, fin, 1);

    // 1st file
    string line;
    while (fin.good()) {
        curLineNr++;
        getline(fin, line);
        istringstream lineIss(line);
        for_each(
            istream_iterator<string>(lineIss),
            istream_iterator<string>(),
            addWord);
    }
    fin.close();

    // copy(
    //     entrySet.begin(),
    //     entrySet.end(),
    //     ostream_iterator<EntryType>(cout, "\n"));
    // cout << endl << entrySet.size() << " words" << endl;

    // 2nd file
    openStream(argc, argv, finCheck, 2);
    while (finCheck.good()) {
        curLineNr2++;
        getline(finCheck, line);
        istringstream lineIss(line);
        for_each(
            istream_iterator<string>(lineIss),
            istream_iterator<string>(),
            addWord2);
    }
    finCheck.close();

    // copy(
    //     entrySet2.begin(),
    //     entrySet2.end(),
    //     ostream_iterator<EntryType>(cout, "\n"));
    // cout << endl << entrySet2.size() << " words" << endl;

    plagiarismCheck(entrySet, entrySet2);
    plagiarismCheck(entrySet2, entrySet);

    return 0;
}