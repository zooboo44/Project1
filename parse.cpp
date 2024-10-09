#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

void printFile(ifstream &file){
    if(!file.is_open()){
        cerr << "Error opening file" << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        cout << line << std::endl;
    }
}

void removeBeginingSpaces(string &str){
    string temp;
    int start = str.find_first_not_of(' ');
    while(start != str.length()){
        temp.push_back(str.at(start));
        start++;
    }
    str = temp;
}

void removeExcessSpaces(string &str){
    string temp;
    removeBeginingSpaces(str);
    for(int i = 0; i < str.length(); i++){
        if(str.at(i) == ' ' && str.at(i+1) == ' '){
            
        }
        else{
            temp.push_back(str.at(i));
        }
    }
    str = temp;
}

void removeSpaces(ifstream &file, vector<string> &lineVector){
    string line;
    while(getline(file, line)){
        if(line.size() != 0){
            if(line.at(0) != '/' && line.at(1) != '/'){
                removeExcessSpaces(line);
                lineVector.push_back(line);
            }
        }
        else{
            continue;
        }
    }
}

void parseFile(ifstream &file, vector<string> &lineVector, map<string, int> &token){
    removeSpaces(file, lineVector);
}

void printLineVector(vector<string> lineVector){
    for(const string &str: lineVector){
        cout << str << endl;
    }
}

int main(){

    //vars and open file
    vector<string> lineVector;
    map<string,int> token;
    ifstream file;
    file.open("temp.cpp");

    //print original file
    cout << "original file" << endl;
    printFile(file);
    cout << endl;
    file.clear();
    file.seekg(0);

    //parse file
    parseFile(file, lineVector, token);

    //print after removing spaces
    cout << "after removing spaces" << endl;
    printLineVector(lineVector);

    //close file
    file.close();
    
}