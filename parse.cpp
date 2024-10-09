#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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

void trim(string &str){
    string temp;
    for(int i = str.length() - 1; i > 0; i--){
        if(str.at(i--) == ' '){
            
        }
        if(str.at(i--) != ' '){
            for(int j = i; j > 0; j--){
                
            }
            break;
        }
    }

}

void removeExcessSpaces(string &str){
    string temp;
    for(int i = 0; i < str.length(); i++){
        if(str.at(i) == ' ' && str.at(i+1) == ' '){
            
        }
        else{
            temp.push_back(str.at(i));
        }
    }
    str = temp;
}

void removeSpaces(ifstream &file){
    string line;
    while(getline(file, line)){
        trim(line);
        removeExcessSpaces(line);
    }
}

int main(){
    ifstream file;
    file.open("input.cpp");
    
    cout << "original file" << endl;
    printFile(file);
    cout << endl;
    file.clear();
    file.seekg(0);
    removeSpaces(file);
    cout << "After modification" << endl;
    file.clear();
    file.seekg(0);
    printFile(file);

    file.close();
    
}
