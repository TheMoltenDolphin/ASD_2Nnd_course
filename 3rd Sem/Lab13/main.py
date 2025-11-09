import string


class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [[] for _ in range(self.size)]

    def _hash(self, key):
        return hash(key) % self.size

    def insert(self, word):
        index = self._hash(word)
        bucket = self.table[index]
        if word not in bucket:
            bucket.append(word)

    def print_table(self):
        for i, bucket in enumerate(self.table):
            if bucket: 
                print(f"Индекс {i}: {bucket}")


def clean_word(word):
    word = word.lower()
    word = word.strip(string.punctuation)
    return word

def process_file_to_hashtable(filename, table_size):
    hash_table = HashTable(size=table_size)
    try:
        with open(filename, 'r', encoding='utf-8') as f:
            words = f.read().split()
            for word in words:
                cleaned = clean_word(word)
                if cleaned: 
                    hash_table.insert(cleaned)
        return hash_table
    except FileNotFoundError:
        print(f"Файл '{filename}' не найден.")
        return None
    except Exception as e:
        print(f"Ошибка при чтении файла: {e}")
        return None



if __name__ == "__main__":
    FILENAME = "input.txt"
    TABLE_SIZE = 5 
    
    print(f"файл '{FILENAME}' с таблицей размера {TABLE_SIZE}...")
    
    my_table = process_file_to_hashtable(FILENAME, TABLE_SIZE)
    
    my_table.insert("ПЕНИС")
    

    if my_table:
        my_table.print_table()