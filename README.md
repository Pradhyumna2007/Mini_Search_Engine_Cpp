# Mini Search Engine in C++

A command-line search engine built from scratch using **C++**, demonstrating the core concepts behind real-world information retrieval systems. The project processes multiple text documents, builds an index, and ranks search results using **TF–IDF (Term Frequency – Inverse Document Frequency)**.

This project focuses on **fundamentals**: text preprocessing, indexing, and relevance ranking — without relying on external libraries.

---

## Key Features

* **Multi-document indexing** from plain `.txt` files
* **Text preprocessing pipeline**

  * Lowercasing
  * Punctuation removal
  * Tokenization
  * Rule-based stemming
* **TF–IDF based relevance ranking**
* **Single-word and multi-word (AND) queries**
* Simple and interactive **command-line interface**

---

## Tech Stack

* **Language:** C++
* **Core Libraries:** STL (`unordered_map`, `vector`, `string`, `algorithm`)
* **Interface:** Command Line

---

## Project Structure

```
Mini_Search_Engine_Cpp/
│── src/
│   └── main.cpp
│── data/
│   └── *.txt
│── README.md
│── .gitignore
```

---

## How It Works

### 1. Document Parsing

All text files in the data directory are read line by line.

### 2. Text Preprocessing

Each word is:

* Cleaned (non-alphanumeric characters removed)
* Converted to lowercase
* Tokenized
* Stemmed using simple rule-based logic

### 3. Index Construction

A global in-memory index is built using:

```
unordered_map<string, vector<int>>
```

Each term maps to its frequency across documents.

### 4. Query Processing

* Query terms are preprocessed using the same pipeline
* Documents containing all query terms are identified
* Relevance scores are calculated using TF–IDF

### 5. Ranking

Documents are sorted by descending TF–IDF score and displayed to the user.

---

## TF–IDF Formula

* **Term Frequency (TF)** = occurrences of term in document / total words in document
* **Inverse Document Frequency (IDF)** = log((double)(N + 1) / (df + 1)) + 1.0;

This ensures:

* Common words receive lower weight
* Rare, meaningful terms influence ranking more

---

## How to Run

### Compile

```
g++ main.cpp -o search
```

### Execute

```
./search
```

### Example Queries

```
artificial intelligence
machine learning
banana
exit
```

---

## Future Improvements

* Phrase search ("machine learning")
* OR / NOT boolean queries
* Inverted index with positional information
* Improved stemming or lemmatization
* JSON-based output
* Web or GUI-based frontend

---

## Author

Pradhyumna Gopisetti
GitHub: [https://github.com/Pradhyumna2007](https://github.com/Pradhyumna2007)

---

## Notes

This project is intended for educational purposes and focuses on clarity and correctness over large-scale optimization.
