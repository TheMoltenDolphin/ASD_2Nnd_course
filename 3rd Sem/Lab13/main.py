import string

class OpenAddressingHashTable:
    def __init__(self, size):
        self.size = size
        self.table = [' '] * self.size
        self.count = 0

    def _hash(self, key):

        return hash(key) % self.size

    def insert(self, word):
        if self.count >= self.size:
            self.size *= 2
            self.table.extend([' '] * self.size)

        for i in range(self.size):
            current_index = (self._hash(word) + i) % self.size
            
            if self.table[current_index] is ' ':
                self.table[current_index] = word
                self.count += 1
                return

    def save_to_file(self, filename):
        try:
            with open(filename, 'w', encoding='utf-8') as f:
                
                for i in range(self.size):
                    item = self.table[i]
                    
                    if item is not ' ':
                        f.write(f"Индекс {i}: {item}\n")
                        
            print(f"Таблица успешно сохранена в '{filename}'.")
        
        except IOError as e:
            print(f"Ошибка при записи в файл '{filename}': {e}")

    def print_table(self):

        for i in range(self.size):
            item = self.table[i]
            print(f"Индекс {i}: {item}")



def clean_word(word):
    word = word.lower().strip(string.punctuation)
    return word

def process_file_to_hashtable(filename, table_size):

    hash_table = OpenAddressingHashTable(size=table_size)
    
    try:
        with open(filename, 'r', encoding='utf-8') as f:
            words = f.read().split()
            
            for word in words:
                    hash_table.insert(word)
                    
        return hash_table

    except FileNotFoundError:
        print(f"Ошибка: Файл '{filename}' не найден.")
        return None
    


if __name__ == "__main__":
    INPUT_FILENAME = "input.txt"
    OUTPUT_FILENAME = "output.txt" 
    TABLE_SIZE = 10
    
    my_table = process_file_to_hashtable(INPUT_FILENAME, TABLE_SIZE)
    if my_table:
        my_table.print_table()
        
        my_table.save_to_file(OUTPUT_FILENAME)