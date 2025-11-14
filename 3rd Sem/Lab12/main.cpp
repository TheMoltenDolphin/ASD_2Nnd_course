#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <vector>
#include <queue>
#include "RAM.h"

void splitFileIntoChunks(const std::string& inputFileName, size_t chunkSize) {
    std::ifstream inputFile(inputFileName, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть входной файл." << std::endl;
        return;
    }

    size_t fileIndex = 0;
    char c;
    std::string tmp;
    int bytesRead = 0;
    while (inputFile.get(c)) {
        tmp.push_back(c);
        bytesRead += sizeof(c);
        if (bytesRead >= chunkSize) {
            bytesRead = 0;
            std::ofstream tempFile("chunk_" + std::to_string(++fileIndex) + ".txt", std::ios::binary);
            if (!tempFile.is_open()) {
                std::cerr << "Ошибка: Не удалось создать временный файл." << std::endl;
                return;
            }
            tempFile.write(tmp.c_str(), tmp.size());
            tmp.clear();
        }
    }
    inputFile.close();
}

void SortChunkFiles() {
    size_t fileIndex = 0;
    while(true) {
        std::string fileName = "chunk_" + std::to_string(fileIndex++) + ".txt";
        if (std::ifstream(fileName).good()) {
            std::ifstream tempFile(fileName);
            std::vector<int> values;
            int value;
            while (tempFile >> value) {
                values.push_back(value);
            }

            std::sort(values.begin(), values.end());

            std::ofstream sortedFile(fileName);
            for (int sortedValue : values) {
                sortedFile << sortedValue << ' ';
            }
            sortedFile.close();
            tempFile.close();
        }
        else
            break;
    }
}


void cleanUpTempFiles() {
    size_t fileIndex = 1;
    while(true) {
        std::string fileName = "chunk_" + std::to_string(fileIndex++) + ".txt";
        if (!std::ifstream(fileName).good()) {
            std::cout << fileIndex;
            break;
        }
        else {
            std::remove(fileName.c_str());
        }
    }
}

const int BUFFER_SIZE_BYTES = 1024;
const int BUFFER_CAPACITY_INTS = BUFFER_SIZE_BYTES / sizeof(int);

class BufferedIntReader {
private:
    std::ifstream& inStream;      
    std::vector<int> buffer;
    int bufferIndex;              
    int bufferSize;              

    bool fillBuffer() {
        bufferIndex = 0; 
        bufferSize = 0;  
        
        int value;
        while (bufferSize < BUFFER_CAPACITY_INTS && inStream >> value) {
            buffer[bufferSize] = value;
            bufferSize++;
        }
        return bufferSize > 0; 
    }

public:

    BufferedIntReader(std::ifstream& stream) 
        : inStream(stream), 
          buffer(BUFFER_CAPACITY_INTS),
          bufferIndex(0), 
          bufferSize(0) {}

    bool getNext(int& value) {
        if (bufferIndex >= bufferSize) {
            if (!fillBuffer()) {
                return false;
            }
        }
        
        value = buffer[bufferIndex];
        bufferIndex++;
        return true;
    }

    ~BufferedIntReader() {
        inStream.close();
    }
};

class BufferedIntWriter {
private:
    std::ofstream& outStream;     
    std::vector<int> buffer;      
    int bufferIndex;              

public:

    BufferedIntWriter(std::ofstream& stream)
        : outStream(stream),
          buffer(BUFFER_CAPACITY_INTS), 
          bufferIndex(0) {}

    void flush() {
        for (int i = 0; i < bufferIndex; ++i) {
            outStream << buffer[i] << "\n";
        }
        bufferIndex = 0; 
    }

    void write(int value) {
        buffer[bufferIndex] = value;
        bufferIndex++;
        
        if (bufferIndex >= BUFFER_CAPACITY_INTS) {
            flush();
        }
    }

    ~BufferedIntWriter() {
        flush();
        outStream.close();
    }
};

void mergeFiles(const std::string& inputFile1, const std::string& inputFile2, const std::string& outputFile) {
    std::ifstream in1(inputFile1);
    std::ifstream in2(inputFile2);
    std::ofstream out(outputFile);
    if (!in1.is_open() || !in2.is_open() || !out.is_open()) {
        std::cerr << "Ошибка открытия файла!" << std::endl;
        return;
    }

    BufferedIntReader reader1(in1);
    BufferedIntReader reader2(in2);
    BufferedIntWriter writer(out);

    int val1, val2;
    bool hasVal1 = reader1.getNext(val1); 
    bool hasVal2 = reader2.getNext(val2); 

    while (hasVal1 && hasVal2) {
        if (val1 < val2) {
            writer.write(val1);
            hasVal1 = reader1.getNext(val1); 
        } else {
            writer.write(val2);
            hasVal2 = reader2.getNext(val2); 
        }
    }

    while (hasVal1) {
        writer.write(val1);
        hasVal1 = reader1.getNext(val1);
    }

    while (hasVal2) {
        writer.write(val2);
        hasVal2 = reader2.getNext(val2);
    }



    in1.close();
    in2.close();
    out.close();
}

std::string externalMergeSort(const std::vector<std::string>& initialFiles) {
    if (initialFiles.empty()) {
        return "error_empty_list.txt";
    }
    std::queue<std::string> fileQueue;
    for (const std::string& file : initialFiles) {
        fileQueue.push(file);
    }

    int tempFileCounter = 0;
    int passCounter = 0;

    while (fileQueue.size() > 1) {
        std::cout << "--- Проход слияния #" << ++passCounter << " ---" << std::endl;
        
        int filesInThisPass = fileQueue.size();
        int mergesInThisPass = filesInThisPass / 2;
        
        for (int i = 0; i < mergesInThisPass; ++i) {
            std::string file1 = fileQueue.front();
            fileQueue.pop();
            std::string file2 = fileQueue.front();
            fileQueue.pop();

            std::string tempOutputName = "temp_pass_" + std::to_string(passCounter) + 
                                         "_merge_" + std::to_string(tempFileCounter++) + ".txt";

            mergeFiles(file1, file2, tempOutputName);

            fileQueue.push(tempOutputName);
            std::remove(file1.c_str());
            std::remove(file2.c_str());
        }
    }

    std::string finalFile = fileQueue.front();
    std::string finalResultName = "sorted_output.txt";
    std::rename(finalFile.c_str(), finalResultName.c_str());
    
    return finalResultName;
}

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    splitFileIntoChunks("input.txt", 1024);

    SortChunkFiles();

    std::vector<std::string> chunkFiles;
    size_t fileIndex = 1;
    while (true) {
        std::string fileName = "chunk_" + std::to_string(fileIndex++) + ".txt";
        if (std::ifstream(fileName).good()) {
            chunkFiles.push_back(fileName);
        } else {
            break;
        }
    }
    std::cout << "Пиковая память: " << getPeakRSS() << " КБайт" << std::endl;

    std::string sortedFile = externalMergeSort(chunkFiles);
    
    cleanUpTempFiles();

    std::cout << "Пиковая память: " << getPeakRSS() << " КБайт" << std::endl;
    return 0;
}