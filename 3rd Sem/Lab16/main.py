
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
    for j in range(len(s)):
        if s[j] == '(': 
            balance += 1
        elif s[j] == ')': 
            balance -= 1
        elif s[j] == ',' and balance == 0:
            split_idx = j
            break
    
    if split_idx != -1:
        node.left = build_tree(s[:split_idx])
        node.right = build_tree(s[split_idx+1:])
    
    return node

def preorder_iterative(root):
    if not root:
        return ""
        
    stack = [root]
    result = []
    
    while stack:
        node = stack.pop()
        
        if node:
            result.append(str(node.value))
            
            if node.right:
                stack.append(node.right)
            if node.left:
                stack.append(node.left)
                
    return " ".join(result)

s = "8(5(1  ,6(4,7)), 10  (,14(13,)))"

tree = build_tree(s)

output = preorder_iterative(tree)
print(output)