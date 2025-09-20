#include <iostream>
#include <windows.h>
#include <string>
#include <stack>

using namespace std;


int main()
{

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    stack<char> s;
    string inp;
    wcout << "Введите строку" << endl;
    cin >> inp;

    for(char i : inp)
    {
        if(i == '}' && s.top() == '{')
            s.pop();
        else if(i == ']' && s.top() == '[')
            s.pop();
        else if(i == ')' && s.top() == '(')
            s.pop();
        else
            s.push(i);
    }
    if(s.empty())
        cout << "Строка существует" << endl;
    else
        cout << "Строка не существует" << endl;
    return 0;
}