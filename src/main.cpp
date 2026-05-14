#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <cctype>
#include<chrono>
using namespace std;

/*
 * Clean a line:
 * - convert to lowercase
 * - replace non-alphanumeric chars with space
 */
string cleanWord(const string &s) {
    string out;
    for (char c : s) {
        if (isalnum((unsigned char)c)) {
            out.push_back(tolower((unsigned char)c));
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
        cout << "Word '" << word << "' not found in any document.\n";
        return;
    }
    double idf = log((double)(N + 1) / (df + 1)) + 1.0;
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
        idf[w] = log((double)(N + 1) / (df + 1)) + 1.0;
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
        "../data/doc1.txt",
        "../data/doc2.txt",
        "../data/doc3.txt",
        "../data/doc4.txt",
        "../data/doc5.txt",
        "../data/doc6.txt",
        "../data/doc7.txt",
        "../data/doc8.txt",
        "../data/doc9.txt",
        "../data/doc10.txt",
        "../data/doc11.txt",
        "../data/doc12.txt",
        "../data/doc13.txt",
        "../data/doc14.txt",
        "../data/doc15.txt",
        "../data/doc16.txt",
        "../data/doc17.txt",
        "../data/doc18.txt",
        "../data/doc19.txt",
        "../data/doc21.txt",
        "../data/doc22.txt",
        "../data/doc23.txt",
        "../data/doc24.txt",
        "../data/doc25.txt",
        "../data/doc26.txt",
        "../data/doc27.txt",
        "../data/doc28.txt",
        "../data/doc29.txt",
        "../data/doc30.txt",
        "../data/doc31.txt",
        "../data/doc32.txt",
        "../data/doc33.txt",
        "../data/doc34.txt",
        "../data/doc35.txt",
        "../data/doc36.txt",
        "../data/doc37.txt",
        "../data/doc38.txt",
        "../data/doc39.txt",
        "../data/doc40.txt",
        "../data/doc41.txt",
        "../data/doc42.txt",
        "../data/doc43.txt",
        "../data/doc44.txt",
        "../data/doc45.txt",
        "../data/doc46.txt",
        "../data/doc47.txt",
        "../data/doc48.txt",
        "../data/doc49.txt",
        "../data/doc50.txt",
        "../data/f1.txt",
        "../data/f2.txt",
        "../data/f3.txt",
        "../data/f4.txt",
        "../data/f5.txt"
    };

    unordered_map<string, vector<int>> termFreq;
    vector<int> totalWords;

    parseFiles(files, termFreq, totalWords);

    int totalIndexedWords = 0;
    int indexedDocs = 0;

    for(int x : totalWords){
        totalIndexedWords += x;
        if(x > 0){
            indexedDocs++;
        }
    }

    cout << "Documents indexed: " << indexedDocs << "\n";
    cout << "Unique tokens: " << termFreq.size() << "\n";
    cout << "Total words indexed: " << totalIndexedWords << "\n";

    long long totalQueryTime = 0;
    int queryCount = 0;

    while(true){
        cout << "\nEnter your search query (or 'exit'): ";
        string q;
        getline(cin, q);

        if(q == "exit"){
            break;
        }

        string cleaned = cleanWord(q);
        stringstream ss(cleaned);
        vector<string> queryWords;
        string w;

        while(ss >> w){
            queryWords.push_back(w);
        }

        if(queryWords.empty()){
            cout << "No valid words entered.\n";
            continue;
        }

        auto start = chrono::high_resolution_clock::now();

        if(queryWords.size() == 1){
            searchSingle(queryWords[0], files, termFreq, totalWords);
        }else{
            searchMulti(queryWords, files, termFreq, totalWords);
        }

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

        cout << "Query time: " << duration.count() << " microseconds\n";

        totalQueryTime += duration.count();
        queryCount++;
    }

    if(queryCount > 0){
        cout << "Average query time: " << (double)totalQueryTime / queryCount << " microseconds\n";
    }

    return 0;
}