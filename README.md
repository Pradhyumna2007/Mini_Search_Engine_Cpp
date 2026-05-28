# Mini Search Engine in C++

A command-line search engine built from scratch using C++, demonstrating the core concepts behind real-world information retrieval systems. The project processes multiple text documents, builds an inverted index, and ranks search results using TF–IDF (Term Frequency – Inverse Document Frequency).

This project focuses on the fundamentals of information retrieval, including text preprocessing, indexing, and relevance ranking using only standard C++ libraries.

---

## Features

* Multi-document indexing from plain `.txt` files
* Text preprocessing pipeline

  * Lowercasing
  * Punctuation removal
  * Tokenization
  * Rule-based stemming
* TF–IDF based relevance ranking
* Support for single-word and multi-word (AND) queries
* Interactive command-line interface
* In-memory inverted index implementation

---

## Tech Stack

* **Language:** C++
* **Libraries Used:** Standard Template Library (STL)

  * `unordered_map`
  * `vector`
  * `string`
  * `algorithm`
  * `fstream`
* **Interface:** Command Line

---

## Project Structure

```plaintext
Mini_Search_Engine_Cpp/
│── src/
│   └── main.cpp
│── data/
│   └── *.txt
│── README.md
│── .gitignore
```

---

## Concepts Demonstrated

* Information Retrieval Basics
* Inverted Indexing
* TF–IDF Scoring
* Text Preprocessing
* File Handling in C++
* Hash Maps and STL Usage
* Command-Line Application Design

---

## How It Works

### 1. Document Parsing

All text files inside the `data` directory are read line by line using file handling in C++. Each document is assigned a unique document ID for indexing and retrieval.

---

### 2. Text Preprocessing

Before indexing, every word passes through a preprocessing pipeline:

* Non-alphanumeric characters are removed
* Words are converted to lowercase
* Text is tokenized into individual terms
* Simple rule-based stemming is applied

This helps normalize words and improves search consistency.

---

### 3. Inverted Index Construction

The search engine builds an in-memory inverted index using hash maps.

```cpp
unordered_map<string, unordered_map<int, int>>
```

Where:

* **Key** → term/word
* **Value** → mapping of:

  * document ID
  * frequency of the term inside that document

This structure enables fast lookup of documents containing specific terms.

---

### 4. Query Processing

User queries are processed using the same preprocessing pipeline as the documents.

For multi-word queries:

* Documents containing all query terms are identified
* Relevant documents are collected for ranking

This ensures consistency between indexed data and search queries.

---

### 5. Relevance Ranking using TF–IDF

Each matching document receives a relevance score using TF–IDF.

### Term Frequency (TF)

Measures how often a term appears in a document.

TF = (Occurrences of term in document) / (Total words in document)

---

### Inverse Document Frequency (IDF)

Measures how unique or important a term is across all documents.

IDF = log((N + 1) / (df + 1)) + 1

Where:

* N = total number of documents
* df = number of documents containing the term

---

### Final Score

TF-IDF = TF × IDF

---

## Time Complexity

| Operation          | Complexity                          |
| ------------------ | ----------------------------------- |
| Index Construction | O(total words)                      |
| Query Lookup       | O(query terms × matching documents) |
| Ranking Results    | O(k log k)                          |

Where `k` is the number of matching documents.

---

## How to Run

### Compile

```bash
g++ src/main.cpp -o search
```

### Execute

```bash
./search
```

---

## Example Queries

```plaintext
artificial intelligence
machine learning
banana
exit
```

---

## Example Output

```plaintext
Enter query: machine learning

Results:
1. doc2.txt   Score: 1.82
2. doc5.txt   Score: 1.34
```

---

## Future Improvements

* Phrase search using positional indexing
* Boolean queries (`AND`, `OR`, `NOT`)
* Improved stemming or lemmatization
* Persistent index storage
* JSON-based output
* Web or GUI frontend
* Support for larger document collections

---

## Author

**Pradhyumna Gopisetti**

GitHub: https://github.com/Pradhyumna2007

---

## License

This project is open-source and available under the MIT License.

---

## Notes

This project is intended for educational purposes and focuses on clarity, correctness, and understanding of search engine fundamentals rather than large-scale optimization.
