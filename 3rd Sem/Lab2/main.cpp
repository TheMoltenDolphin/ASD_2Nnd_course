#include <iostream>
#include <windows.h>
#include <string>
#include <stack>
#include <queue>


float Calculate(float x1, float x2, char t)
{
    switch (t)
    {
        case '+':
            return x1 + x2;
        case '-':
            return x1 - x2;
        case '*':
            return x1 * x2;
        case '/':
            return x1 / x2;
    }
}

int Priority(char inp)
{
    return ((inp == '+' || inp == '-') ? 1 : 2);
}

bool CheckExpression(std::string inp)
{
    std::string validChars = "1234567890*-+/()";
    std::stack<char> s;
    for(char i : inp)
    {
        if(validChars.find(i) == std::string::npos)
            return false;

        else if(i != '(' && i != ')')
            continue;
        else if(!s.empty() && i == ')' && s.top() == '(')
            s.pop();
        else
            s.push(i);
    }

    if(s.empty())
        return true;
        
    return false;
}

std::queue<char> EvaluatedExpr(std::string inp)
{
    std::string op = "+-*/";
    std::queue<char> q;
    std::stack<char> s;
    for(int i = 0; i < inp.size(); i++)
    {

        if(inp[i] == '(')
            s.push(inp[i]);
        else if(isdigit(inp[i]))
        {
            q.push(inp[i]);
            continue;
        }
        else if (op.find(inp[i]) != std::string::npos)
        {
            if(inp[i] == '/' && inp[i+1] == '0')
            {
                std::cerr << "Ошибка: Деление на ноль!" << std::endl;
                exit(EXIT_FAILURE);
            }

            
            if(s.empty() || s.top() == '(')
                s.push(inp[i]);
            else if(Priority(inp[i]) > Priority(s.top()))
                s.push(inp[i]);
            else
            {
                while(Priority(inp[i]) <= Priority(s.top()) && s.top() != '(')
                {
                    q.push(s.top());
                    s.pop();
                    if(s.empty())
                        break;
                }
                s.push(inp[i]);
            }
        }
        else
        {
            while(s.top() != '(')
            {
                q.push(s.top());
                s.pop();
                if(s.empty())
                    break;
            }
            s.pop();
        }
    }
    while(!s.empty())
    {
        q.push(s.top());
        s.pop();
    }

    return q;
}

float EvaluateExpression(std::queue<char> q)
{
    std::stack<float> s;
    while (!q.empty())
    {
        char token = q.front();
        q.pop();
        if (isdigit(token))
        {
            s.push(token - '0');
        }
        else
        {
            float right = s.top(); s.pop();
            float left = s.top(); s.pop();
            float result = Calculate(left, right, token);
            s.push(result);
        }
    }
    return s.top();
}

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    std::string inp;
    //std::cin >> inp;

    inp = "8+4*(7-2)/5+6*3-1+(9-4)*2/8+7*2-5=";

    if(inp.back() == '=')
    {
        inp.pop_back();
        if(!CheckExpression(inp))
        {
            std::cerr << "Выражение составлено неправильно!";
            exit(EXIT_FAILURE);
        }
        std::cout << "Выражение составлено правильно!" << std::endl;
    }
    else
    {
        std::cerr << "Выражение составлено неправильно!";
        exit(EXIT_FAILURE);
    }

    std::queue<char> PostExpr = EvaluatedExpr(inp);

    float res = EvaluateExpression(PostExpr);

    while (!PostExpr.empty())  // пока очередь не пуста
    {
        std::cout << PostExpr.front() << ' ';
        PostExpr.pop();    // извлекаем первый элемент
    }

    std::cout << std::endl << res << std::endl;

    return 0;
}