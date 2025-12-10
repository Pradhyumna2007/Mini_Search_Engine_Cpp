#include <bits/stdc++.h>
using namespace std;

// -------------------------- CLEAN & STEM WORDS --------------------------
string cleanWord(const string &s) {
    string out;
    for (char c : s) {
        if (isalnum(c)) out.push_back(tolower(c));
        else out.push_back(' ');
    }
    return out;
}

string stemWord(const string &w) {
    string s = w;
    int n = s.size();
    if (n <= 3) return s;

    if (n > 4 && s.substr(n - 3) == "ies") return s.substr(0, n - 3) + "y";
    if (n > 4 && s.substr(n - 2) == "es") return s.substr(0, n - 2);
    if (s[n - 1] == 's') return s.substr(0, n - 1);
    if (n > 5 && s.substr(n - 3) == "ing") return s.substr(0, n - 3);
    if (n > 4 && s.substr(n - 2) == "ed") return s.substr(0, n - 2);

    return s;
}

// -------------------------- PARSING FILES --------------------------
void parseFiles(const vector<string> &files,
                unordered_map<string, vector<int>> &termFreq,
                vector<int> &totalWords) {
    int N = files.size();
    totalWords.resize(N, 0);

    for (int file = 0; file < N; file++) {
        ifstream in(files[file]);
        if (!in.is_open()) {
            cerr << "Error opening: " << files[file] << "\n";
            continue;
        }

        string line;
        while (getline(in, line)) {
            string cleaned = cleanWord(line);
            stringstream ss(cleaned);
            string w;
            while (ss >> w) {
                w = stemWord(w); // Apply stemming
                termFreq[w].resize(N);
                termFreq[w][file]++;
                totalWords[file]++;
            }
        }
        in.close();
    }
}

// -------------------------- SINGLE WORD SEARCH --------------------------
void searchSingle(const string &word, const vector<string> &files,
                  const unordered_map<string, vector<int>> &termFreq,
                  const vector<int> &totalWords) {
    string w = stemWord(word);

    if (termFreq.find(w) == termFreq.end()) {
        cout << "Word '" << word << "' not found in any document.\n";
        return;
    }

    int N = files.size();
    vector<double> scores(N, 0.0);

    int df = 0;
    for (int d = 0; d < N; d++)
        if (termFreq.at(w)[d] > 0) df++;
    double idf = log((double)N / df);

    for (int d = 0; d < N; d++)
        scores[d] = ((double)termFreq.at(w)[d] / totalWords[d]) * idf;

    vector<pair<double,int>> ranking;
    for (int d = 0; d < N; d++) ranking.push_back({scores[d], d});
    sort(ranking.rbegin(), ranking.rend());

    cout << "\n--- TF-IDF Ranked Results ---\n";
    for (auto &p : ranking) {
        if (p.first > 0.0)
            cout << "file " << p.second+1 << " (" << files[p.second] 
                 << ") --> Score = " << p.first << "\n";
    }
}

// -------------------------- MULTI WORD SEARCH (AND) --------------------------
void searchMulti(const vector<string> &words, const vector<string> &files,
                 const unordered_map<string, vector<int>> &termFreq,
                 const vector<int> &totalWords) {
    int N = files.size();
    vector<string> stemmedWords;

    for (auto &word : words)
        stemmedWords.push_back(stemWord(word));

    for (auto &w : stemmedWords) {
        if (termFreq.find(w) == termFreq.end()) {
            cout << "Word '" << w << "' not found in any document.\n";
            return;
        }
    }

    vector<double> fileScore(N, 0.0);

    for (int d = 0; d < N; d++) {
        bool containsAll = true;
        double score = 0.0;

        for (auto &w : stemmedWords) {
            if (termFreq.at(w)[d] == 0) {
                containsAll = false;
                break;
            }
            int df = 0;
            for (int k = 0; k < N; k++)
                if (termFreq.at(w)[k] > 0) df++;
            double idf = log((double)N / df);
            double tf = (double)termFreq.at(w)[d] / totalWords[d];
            score += tf * idf;
        }

        if (containsAll) fileScore[d] = score;
    }

    vector<pair<double,int>> ranking;
    for (int d = 0; d < N; d++) ranking.push_back({fileScore[d], d});
    sort(ranking.rbegin(), ranking.rend());

    bool foundAny = false;
    cout << "\n--- TF-IDF Ranked Results (All words must exist) ---\n";
    for (auto &p : ranking) {
        if (p.first > 0.0) {
            cout << "file " << p.second+1 << " (" << files[p.second] 
                 << ") --> Score = " << p.first << "\n";
            foundAny = true;
        }
    }
    if (!foundAny) cout << "No document contains all query words.\n";
}

// -------------------------- MAIN --------------------------
int main() {
    vector<string> files = {
        "file1.txt","file2.txt","file3.txt","file4.txt",
        "file5.txt","file6.txt","file7.txt","xyz.txt"
    };

    unordered_map<string, vector<int>> termFreq;
    vector<int> totalWords;

    parseFiles(files, termFreq, totalWords);

    while (true) {
        cout << "\nEnter your search query (or 'exit'): ";
        string q;
        getline(cin, q);

        if (q.empty()) {
            cout << "No input entered. Try again.\n";
            continue;
        }
        if (q == "exit") break;

        string cleaned = cleanWord(q);
        stringstream ss(cleaned);
        vector<string> queryWords;
        string w;
        while (ss >> w) queryWords.push_back(w);

        if (queryWords.empty()) {
            cout << "No valid words entered. Try again.\n";
            continue;
        }

        if (queryWords.size() == 1) searchSingle(queryWords[0], files, termFreq, totalWords);
        else searchMulti(queryWords, files, termFreq, totalWords);
    }

    return 0;
}
