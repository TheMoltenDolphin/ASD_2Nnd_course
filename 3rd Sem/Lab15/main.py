class Node:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

def build_tree(s):
    s = s.strip().replace(" ", "")
    if not s:
        return None
    
    val_str = ""
    i = 0
    while i < len(s) and s[i].isdigit():
        val_str += s[i]
        i += 1
    
    if not val_str:
        return None
        
    node = Node(int(val_str))
    
    if i == len(s) or s[i] != '(':
        return node

    s = s[i+1:-1]
    
    balance = 0
    split_idx = -1
    for j, char in enumerate(s):
        if char == '(': 
            balance += 1
        elif char == ')': 
            balance -= 1
        elif char == ',' and balance == 0:
            split_idx = j
            break
    
    if split_idx != -1:
        node.left = build_tree(s[:split_idx])
        node.right = build_tree(s[split_idx+1:])
    
    return node

def preorder(node):
    if node:
        print(node.value, end=' ')
        preorder(node.left)
        preorder(node.right)

def inorder(node):
    if node:
        inorder(node.left)
        print(node.value, end=' ')
        inorder(node.right)

def postorder(node):
    if node:
        postorder(node.left)
        postorder(node.right)
        print(node.value, end=' ')

s = "8(5(1  ,6(4,7)), 10  (,14(13,)))"

tree = build_tree(s)

print("Прямой (Root, Left, Right):")
preorder(tree)
print("\n")

print("Центральный (Left, Root, Right):")
inorder(tree)
print("\n")

print("Концевой (Left, Right, Root):")
postorder(tree)
print()