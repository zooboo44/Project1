#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_set>

using namespace std;

// Set of keywords
const unordered_set<string> keywords = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", 
    "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", 
    "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", 
    "union", "unsigned", "void", "volatile", "while", "class", "public", "private", 
    "protected", "virtual", "friend", "inline", "operator", "new", "delete", "try", 
    "catch", "throw", "template", "typename", "this", "namespace", "using"
};

// Set of operators
const unordered_set<string> operators = {
    "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!",
    "++", "--", "+=", "-=", "*=", "/=", "%=", "&", "|", "^", "~", "<<", ">>", "->",
    "::"
};

// Set of separators
const unordered_set<char> separators = {
    '(', ')', '{', '}', '[', ']', ';', ',', '.', ':'
};

vector<string> keywordTokens;
vector<string> operatorTokens;
vector<string> separatorTokens;
vector<string> literalTokens;
vector<string> identifierTokens;

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
            if(line.size() == 1){
                removeExcessSpaces(line);
                lineVector.push_back(line);
            }
            else if(line.at(0) != '/' && line.at(1) != '/'){
                removeExcessSpaces(line);
                lineVector.push_back(line);
            }
        }
        else{
            continue;
        }
    }
}

void parseFile(ifstream &file, vector<string> &lineVector){
    removeSpaces(file, lineVector);
}

void printLineVector(const vector<string> lineVector){
    for(const string &str: lineVector){
        cout << str << endl;
    }
}

bool isIdentifier(const string& str) {
    if (!isalpha(str[0]) && str[0] != '_')
        return false;
    for (char ch : str) {
        if (!isalnum(ch) && ch != '_')
            return false;
    }
    return true;
}

bool isLiteral(const string& str) {
    for (char ch : str) {
        if (!isdigit(ch))
            return false;
    }
    return true;
}

void classifyToken(const string &token){
    if(keywords.find(token) != keywords.end()){
        keywordTokens.push_back(token);
    }
    else if(operators.find(token) != operators.end()){
        operatorTokens.push_back(token);
    }
    else if (token.size() == 1 && separators.find(token[0]) != separators.end()) {
        separatorTokens.push_back(token);
    }
    else if (isLiteral(token)) {
        literalTokens.push_back(token);
    }
    else if (isIdentifier(token)) {
        identifierTokens.push_back(token);
    }
    else{
        cout << "ERROR " << token << "IS AN UNKNOWN TOKEN" << endl;
    }
}

void classifyLiteralQuotes(const string &token){
    literalTokens.push_back(token);
}

void tokenize(vector<string> &lineVector){
    string token;

    for(const string &str : lineVector){
        for(int i = 0; i < str.size(); i++){
            char ch = str.at(i);

            if(ch == '"'){
                token += '"';
                int j = i + 1;
                ch = str.at(j);
                while(str.at(j) != '"'){
                    ch = str.at(j);
                    token += ch;
                    j++;
                }
                token += '"';
                classifyLiteralQuotes(token);
                token.clear();
                i = j;
                continue;
            }

            // Skip space
            if (isspace(ch)) {
                if (!token.empty()) {
                    classifyToken(token);
                    token.clear();
                }
                continue;
            }

            //Separator
            if (separators.find(ch) != separators.end()) {
                if (!token.empty()) {
                    classifyToken(token);
                    token.clear();
                }
                classifyToken(string(1,ch));
                continue;
            }

            // Operators
            if (ispunct(ch) && operators.find(string(1, ch)) != operators.end()) {
                if (!token.empty()) {
                    classifyToken(token);
                    token.clear();
                }

                string op(1, ch);
                if (i + 1 < str.size() && operators.find(op + str[i + 1]) != operators.end()) {
                    op += str[i + 1];
                    i++;
                }
                classifyToken(op);
                continue;
            }

            token += ch;
        }
    }
}

int main(){

    //vars and open file
    vector<string> lineVector;
    ifstream file;
    file.open("temp.cpp");

    //print original file
    cout << "original file" << endl;
    printFile(file);
    cout << endl;
    file.clear();
    file.seekg(0);

    //parse file
    parseFile(file, lineVector);

    //print after removing spaces
    cout << "after removing spaces" << endl;
    printLineVector(lineVector);

    tokenize(lineVector);
    //close file
    file.close();
    
}