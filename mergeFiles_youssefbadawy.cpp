#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct FileContent {
    int num;
    ifstream* stream;

    bool operator>(const FileContent& other) const {
        return num > other.num;
    }
};

void mergeSortedFiles(const vector<string>& inputFiles, const string& resultFile) 
{
    priority_queue<FileContent, vector<FileContent>, greater<FileContent>> pq;
    vector<ifstream> streams(inputFiles.size());

    for (int i = 0; i < inputFiles.size(); ++i) {
        streams[i].open(inputFiles[i]);

        if (!streams[i].is_open()) {
            cerr << "Error opening file: " << inputFiles[i] << endl;
            return;
        }

        int temp;
        if (streams[i] >> temp) {
            pq.push({ temp, &streams[i] });
        }
    }

    ofstream outFile(resultFile);

    if (!outFile.is_open()) {
        cerr << "Error opening output file: " << resultFile << endl;
        return;
    }

    while (!pq.empty()) {
        FileContent smallest = pq.top();
        pq.pop();
        outFile << smallest.num << '\n';

        int nextValue;
        if (*(smallest.stream) >> nextValue) {
            pq.push({ nextValue, smallest.stream });
        }
    }

    outFile.close();
    for (int i = 0; i < streams.size(); ++i) {
        streams[i].close();
    }
}

int main() {
    int totalFiles;
    cout << "number of input files: ";
    cin >> totalFiles;

    vector<string> inputFileNames(totalFiles);
    for (int i = 0; i < totalFiles; ++i) {
        cout << "Enter input file " << i + 1 << ": ";
        cin >> inputFileNames[i];
    }

    string resultFileName;
    cout << "Enter the output file name: ";
    cin >> resultFileName;

    mergeSortedFiles(inputFileNames, resultFileName);

    cout << "Merging done. Output stored in " << resultFileName << endl;
    return 0;
}
