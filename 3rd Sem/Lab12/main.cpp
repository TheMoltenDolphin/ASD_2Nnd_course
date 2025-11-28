#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>

using namespace std;

void safe_remove(const string& filename) {
    remove(filename.c_str());
}

int main() {
    const string inputFile = "input.txt";
    const string t1 = "temp1.txt";
    const string t2 = "temp2.txt";
    const string t3 = "temp3.txt";
    const string outputFile = "output.txt";
    
    const int MEMORY_LIMIT = 1000;

    ifstream in(inputFile);
    if (!in.is_open()) return 1;

    ofstream out1(t1), out2(t2);
    vector<int> buffer;
    int val;
    int count = 0;
    
    while (in >> val) {
        buffer.push_back(val);
        if (buffer.size() >= MEMORY_LIMIT) {
            sort(buffer.begin(), buffer.end());
            ofstream& target = (count % 2 == 0) ? out1 : out2;
            for (int v : buffer) target << v << "\n";
            buffer.clear();
            count++;
        }
    }
    
    if (!buffer.empty()) {
        sort(buffer.begin(), buffer.end());
        ofstream& target = (count % 2 == 0) ? out1 : out2;
        for (int v : buffer) target << v << "\n";
        count++;
    }
    
    in.close();
    out1.close();
    out2.close();

    int runSize = MEMORY_LIMIT;
    bool sorted = false;

    while (!sorted) {
        ifstream f1(t1);
        ifstream f2(t2);
        ofstream f3(t3);
        
        int v1, v2;
        bool has1 = (bool)(f1 >> v1);
        bool has2 = (bool)(f2 >> v2);

        while (has1 || has2) {
            int c1 = 0;
            int c2 = 0;
            
            while ((has1 && c1 < runSize) && (has2 && c2 < runSize)) {
                if (v1 < v2) {
                    f3 << v1 << "\n";
                    has1 = (bool)(f1 >> v1);
                    c1++;
                } else {
                    f3 << v2 << "\n";
                    has2 = (bool)(f2 >> v2);
                    c2++;
                }
            }

            while (has1 && c1 < runSize) {
                f3 << v1 << "\n";
                has1 = (bool)(f1 >> v1);
                c1++;
            }
            
            while (has2 && c2 < runSize) {
                f3 << v2 << "\n";
                has2 = (bool)(f2 >> v2);
                c2++;
            }
        }
        
        f1.close();
        f2.close();
        f3.close();

        ifstream src(t3);
        ofstream d1(t1), d2(t2);
        
        runSize *= 2;
        int runs = 0;
        int currentVal;
        
        while (src >> currentVal) {
            ofstream& target = (runs % 2 == 0) ? d1 : d2;
            target << currentVal << "\n";
            
            for (int i = 1; i < runSize; ++i) {
                if (src >> currentVal) {
                    target << currentVal << "\n";
                } else {
                    break;
                }
            }
            runs++;
        }

        src.close();
        d1.close();
        d2.close();

        if (runs <= 1) sorted = true;
    }

    ifstream res(t1);
    ofstream finalOut(outputFile);
    int finalVal;
    while (res >> finalVal) {
        finalOut << finalVal << "\n";
    }

    res.close();
    finalOut.close();

    safe_remove(t1);
    safe_remove(t2);
    safe_remove(t3);

    return 0;
}