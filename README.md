# Mini Search Engine in C++  
A full search engine built from scratch using **C++**, capable of processing multiple text documents, indexing every word, and ranking query results using **TF-IDF (Term Frequency – Inverse Document Frequency)**.  
This project demonstrates how real search engines work internally — from text preprocessing to ranking relevant results.

---

# 1. Introduction

This project is a **Mini Search Engine** implemented completely in C++ without any external libraries.  
It supports:

- Reading and indexing multiple documents  
- Cleaning and normalizing text  
- Stemming words  
- Building a term-frequency map  
- Searching single and multi-word queries  
- Ranking results using TF-IDF  
- Working through a simple command-line interface  

It is designed to be simple but realistic, showing core search engine concepts.

---

# 2. Features (Detailed)

### **2.1 Multi-Document Parsing**
- Supports any number of `.txt` files.
- Each file is scanned line by line.
- Every word is:
  - Cleaned (punctuation removed)
  - Converted to lowercase
  - Stemmed (simple rule-based stemmer)
- A master dictionary (`unordered_map<string, vector<int>>`) stores counts of all terms across documents.

###  **2.2 Text Preprocessing**
Includes:
- Removing symbols  
- Normalizing case  
- Splitting into tokens  
- Basic stemming for:
  - plural words (`stories → story`)
  - words ending with `ing`, `ed`, `es`
  - trailing `s`

###  **2.3 TF-IDF Ranking Engine**
For each search query, TF-IDF score is calculated as:
TF = term_count_in_doc / total_words_in_doc
IDF = log(N / df)
Score = TF × IDF

This gives:
- Higher score for rare and meaningful terms  
- Lower score for common words  

###  **2.4 Single Word Search**
Example: Query: apple
The program:
- Finds all documents containing “apple”
- Calculates TF-IDF per document
- Sorts and prints from most relevant to least

###  **2.5 Multi-Word Search (AND Logic)**
Example: Query: machine learning
The program:
- Stems each word  
- Checks documents containing **all** words  
- Computes combined TF-IDF score  
- Ranks and prints them  

###  **2.6 Command Line Interface**
The interaction is simple:
Enter your search query (or 'exit'): 

---

#  3. Project Structure

Mini_Search_Engine_Cpp/
│── src/
│    └── main.cpp
│── data/
│    └── your .txt files
│── README.md
│── .gitignore


---

#  4. How It Works (Behind the Scenes)

###  Step 1: Read all files  
Each file is read line-by-line.

###  Step 2: Clean the words  
All non-alphanumeric characters are removed.

###  Step 3: Tokenize  
The cleaned line is broken into individual words.

###  Step 4: Stemming  
Simple stemming rules are applied so similar words map to a single token.

###  Step 5: Build Index  
A global term-frequency dictionary is built:
---

## How to Run

1. Compile using g++:
g++ main.cpp -o search

2. Run:
./search

3. Enter queries (or exit):
Artificial intelligence 
banana 
Data quantum
exit
---


---

#  7. TF-IDF Formula Explanation

TF-IDF is used in real search engines (including Google-like systems) because it balances:

- **Term Frequency (TF):** How often a word appears in a document  
- **Inverse Document Frequency (IDF):** How rare the word is across all documents  

The intuition:
- Common words → low score  
- Rare, meaningful words → high score  

This gives better relevancy ranking.

---

#  10. Future Improvements 

If you ever expand the project:
- OR / NOT logic queries  
- Phrase search  
- Wildcard search  
- Better stemming algorithm  
- Web-based frontend  
- JSON output  
- Real inverted index (map<word, vector<pair<doc, freq>>>)  

---


