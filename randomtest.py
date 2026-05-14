import os
import random

texts = [
    "Artificial intelligence improves search systems.",
    "Blockchain enables decentralized applications.",
    "Database systems use indexing for optimization.",
    "Machine learning models process large datasets.",
    "Search engines rank documents using TF IDF."
]

os.makedirs("data", exist_ok=True)

for i in range(50):
    with open(f"data/doc{i+1}.txt", "w") as f:
        content = " ".join(random.choices(texts, k=20))
        f.write(content)

print("Files generated successfully.")