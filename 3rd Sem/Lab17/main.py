class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None

class Tree:
    def __init__(self):
        self.root = None

    def insert(self, key):
        if self.root is None:
            self.root = Node(key)
            print(f"Значение {key} добавлено.")
            return

        current = self.root
        while True:
            if key == current.key:
                print(f"Значение {key} уже существует.")
                return
            elif key < current.key:
                if current.left is None:
                    current.left = Node(key)
                    print(f"Значение {key} добавлено.")
                    return
                current = current.left
            else:
                if current.right is None:
                    current.right = Node(key)
                    print(f"Значение {key} добавлено.")
                    return
                current = current.right

    def search(self, key):
        current = self.root
        while current is not None:
            if key == current.key:
                return current
            elif key < current.key:
                current = current.left
            else:
                current = current.right
        return None

    def delete(self, key):
        self.root = self._delete_recursive(self.root, key)

    def _delete_recursive(self, root, key):
        if root is None:
            return None
        
        if key < root.key:
            root.left = self._delete_recursive(root.left, key)
        elif key > root.key:
            root.right = self._delete_recursive(root.right, key)
        else:
            if root.left is None:
                print(f"Узел {key} удален.")
                return root.right
            elif root.right is None:
                print(f"Узел {key} удален.")
                return root.left
            
            temp = self._min_value_node(root.right)
            root.key = temp.key 
            root.right = self._delete_recursive(root.right, temp.key)
            
        return root

    def _min_value_node(self, node):
        current = node
        while current.left is not None:
            current = current.left
        return current


def find_zap(text):
    balance = 0
    for i, char in enumerate(text):
        if char == '(':
            balance += 1
        elif char == ')':
            balance -= 1
        elif char == ',' and balance == 0:
            return i
    return -1

def recursive_parse(sub_str):
    sub_str = sub_str.strip()
    if not sub_str:
        return None

    key_str = ""
    i = 0
    while i < len(sub_str) and sub_str[i].isdigit():
        key_str += sub_str[i]
        i += 1
    
    if not key_str:
        return None
        
    key = int(key_str)
    root = Node(key)
    
    if i < len(sub_str) and sub_str[i] == '(':
        children_str = sub_str[i+1:-1] 
        comma_index = find_zap(children_str)
        
        if comma_index != -1:
            left_str = children_str[:comma_index].strip()
            right_str = children_str[comma_index + 1:].strip()

            root.left = recursive_parse(left_str)
            root.right = recursive_parse(right_str)
        
    return root

def parse_linear_bracket(s):
    s = s.replace(' ', '').strip()
    root_node = recursive_parse(s)
    tree = Tree()
    tree.root = root_node
    return tree
    

def serialize_linear_bracket(root):
    if root is None:
        return ''
    
    result = str(root.key)
    
    left_str = serialize_linear_bracket(root.left)
    right_str = serialize_linear_bracket(root.right)
    
    if left_str or right_str:
        result += '('
        result += left_str
        result += ','
        result += right_str
        result += ')'
        
    return result


def int_input(prompt):
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            print("🚫 Введите корректное целое число.")

def main():    
    
    initial_input = "8(5(1,6(4,7)),10(,14(13,)))"
    tree = parse_linear_bracket(initial_input)
    
    

    while True:
        print("\n--- Меню Операций ---")
        print("1. Добавить вершину (Insert)")
        print("2. Удалить вершину (Delete)")
        print("3. Найти вершину (Search)")
        print("4. Выход и вывод итогового дерева (Exit)")
        current_tree_str = serialize_linear_bracket(tree.root)
        print(f"Текущее БДП: {current_tree_str if current_tree_str else 'Пусто'}")

        
        choice = input("Выберите операцию (1-4): ")
        
        if choice == '1':
            key = int_input("Введите значение для добавления: ")
            tree.insert(key)
            
        elif choice == '2':
            key = int_input("Введите значение для удаления: ")
            if tree.search(key):
                tree.delete(key)
            else:
                print(f"Значение {key} не найдено.")
            
        elif choice == '3':
            key = int_input("Введите значение для поиска: ")
            node = tree.search(key)
            if node:
                print(f"Значение {key} найдено в дереве.")
            else:
                print(f"Значение {key} не найдено.")
            
        elif choice == '4':
            final_output = serialize_linear_bracket(tree.root)
            print("Итоговое БДП в линейно-скобочной записи:")
            print(final_output if final_output else "Дерево пусто.")
            break
            
        else:
            print("Некорректный выбор. Введите 1, 2, 3 или 4.")

if __name__ == "__main__":
    main()