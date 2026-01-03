#include <bits/stdc++.h>
using namespace std;

/*
 * Clean a line:
 * - convert to lowercase
 * - replace non-alphanumeric chars with space
 */
string cleanWord(const string &s) {
    string out;
    for (char c : s) {
        if (isalnum(c)) {
            out.push_back(tolower(c));
        } else {
            out.push_back(' ');
        }
    }
    return out;
}

//  *PARSE FILES 
void parseFiles(const vector<string> &files, unordered_map<string, vector<int>> &termFreq, vector<int> &totalWords) {
    int N = files.size();
    totalWords.assign(N, 0);
    for (int file = 0; file < N; file++) {
        ifstream in(files[file]);
        if (!in.is_open()) {
            cout << "Error opening: " << files[file] << endl;
            continue;
        }
        string line;
        while (getline(in, line)) {
            string cleaned = cleanWord(line);
            stringstream ss(cleaned);
            string w;
            while (ss >> w) {
                if (termFreq.find(w) == termFreq.end()) {
                    termFreq[w] = vector<int>(N, 0);
                }
                termFreq[w][file]++;
                totalWords[file]++;
            }
        }
        in.close();
    }
}

// *SINGLE WORD SEARCH 
void searchSingle(const string &word, const vector<string> &files, const unordered_map<string, vector<int>> &termFreq, const vector<int> &totalWords) {
    if (termFreq.find(word) == termFreq.end()) {
        cout << "Word '" << word << "' not found in any document.\n";
        return;
    }
    int N = files.size();
    vector<double> scores(N, 0.0);

    // compute document frequency
    int df = 0;
    for(int d = 0; d < N; d++){
        if(termFreq.at(word)[d] > 0)df++;
    }
    if(df == 0){
        return;
    }
    double idf = log((double)N / df);
    for (int d = 0; d < N; d++) {
        if (totalWords[d] > 0) {
            double tf = (double)termFreq.at(word)[d] / totalWords[d];
            scores[d] = tf * idf;
        }
    }
    vector<pair<double,int>> ranking;
    for (int d = 0; d < N; d++) {
        ranking.push_back({scores[d], d});
    }
    sort(ranking.rbegin(), ranking.rend());
    cout << "\n * TF-IDF Ranked Results \n";
    for (auto &p : ranking) {
        if (p.first > 0.0) {
            cout << "file " << p.second + 1
                 << " (" << files[p.second]
                 << ") --> Score = " << p.first << "\n";
        }
    }
}

// * MULTI WORD SEARCH (AND QUERY) 
void searchMulti(const vector<string> &words, const vector<string> &files, const unordered_map<string, vector<int>> &termFreq, const vector<int> &totalWords) {
    int N = files.size();
    // check all words exist
    for (const auto &w : words) {
        if (termFreq.find(w) == termFreq.end()) {
            cout << "Word '" << w << "' not found in any document.\n";
            return;
        }
    }

    // precompute IDF for each query word
    unordered_map<string, double> idf;
    for (const auto &w : words) {
        int df = 0;
        for (int d = 0; d < N; d++) {
            if (termFreq.at(w)[d] > 0) df++;
        }
        idf[w] = (df > 0) ? log((double)N / df) : 0.0;
    }

    vector<double> fileScore(N, 0.0);

    for (int d = 0; d < N; d++) {
        if (totalWords[d] == 0) continue;

        bool containsAll = true;
        double score = 0.0;

        for (const auto &w : words) {
            if (termFreq.at(w)[d] == 0) {
                containsAll = false;
                break;
            }
            double tf = (double)termFreq.at(w)[d] / totalWords[d];
            score += tf * idf[w];
        }

        if (containsAll) {
            fileScore[d] = score;
        }
    }

    vector<pair<double,int>> ranking;
    for (int d = 0; d < N; d++) {
        ranking.push_back({fileScore[d], d});
    }

    sort(ranking.rbegin(), ranking.rend());

    cout << "\n* TF-IDF Ranked Results (AND Query) \n";
    bool found = false;
    for (auto &p : ranking) {
        if (p.first > 0.0) {
            cout << "file " << p.second + 1
                 << " (" << files[p.second]
                 << ") --> Score = " << p.first << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No document contains all query words.\n";
    }
}

// * MAIN 
int main() {
    vector<string> files = {
        "f1ile1.txt","f2.txt","f3.txt","f4.txt",
        "f5.txt","f6.txt"
    };

    unordered_map<string, vector<int>> termFreq;
    vector<int> totalWords;

    parseFiles(files, termFreq, totalWords);

    while (true) {
        cout << "\nEnter your search query (or 'exit'): ";
        string q;
        getline(cin, q);

        if (q == "exit") break;

        string cleaned = cleanWord(q);
        stringstream ss(cleaned);
        vector<string> queryWords;
        string w;

        while (ss >> w) queryWords.push_back(w);

        if (queryWords.empty()) {
            cout << "No valid words entered.\n";
            continue;
        }

        if (queryWords.size() == 1)
            searchSingle(queryWords[0], files, termFreq, totalWords);
        else
            searchMulti(queryWords, files, termFreq, totalWords);
    }

    return 0;
}
