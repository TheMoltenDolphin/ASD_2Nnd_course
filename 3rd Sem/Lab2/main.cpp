#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int getPriority(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

float applyOperation(float a, float b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0)
            {
                std::cerr << "Деление на ноль" << std::endl;
                exit(EXIT_FAILURE);
            }
            return a / b;
        default: return 0;
    }
}


bool validate(std::string inp)
{
    inp.pop_back();

    std::string validChars = "1234567890*-+/()";
    std::stack<char> s;
    for(char i : inp)
    {
        if(validChars.find(i) == std::string::npos)
            return false;

        if(s.empty() && (i == ')' || i == '('))
        {
            s.push(i);
            continue;
        }

        else if(i != '(' && i != ')')
            continue;
        else if(!s.empty() && i == ')' && s.top() == '(')
            s.pop();
        else
            s.push(i);
    }

    return s.empty();
}

float evaluate(std::string inp) {
    if (!validate(inp))
    {
        std::cerr << "Некорректное выражение" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::stack<float> values;
    std::stack<char> ops;

    for (size_t i = 0; i < inp.length(); i++) {
        
        if (inp[i] == '(') {
            ops.push(inp[i]);
        }
        else if (isdigit(inp[i])) {
            float val = 0;
            while (i < inp.length() && isdigit(inp[i])) {
                val = val * 10 + (inp[i] - '0');
                i++;
            }
            i--;
            values.push(val);
        }
        else if (inp[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                float val2 = values.top(); values.pop();
                float val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperation(val1, val2, op));
            }
            if (!ops.empty()) ops.pop();
        }
        else if (isOperator(inp[i])) {
            while (!ops.empty() && getPriority(ops.top()) >= getPriority(inp[i])) {
                float val2 = values.top(); values.pop();
                float val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOperation(val1, val2, op));
            }
            ops.push(inp[i]);
        }
    }

    while (!ops.empty()) {
        float val2 = values.top(); values.pop();
        float val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOperation(val1, val2, op));
    }

    return values.top();
}

int main() {

    std::string expr = "8+4*(7-2)/5+6*3-1+(9-4)*2/(5*4-5)+7*2-5=";
    float result = evaluate(expr);
    std::cout << "Результат " << result << std::endl;
    return 0;
}
