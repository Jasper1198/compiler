#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector<string> tokens;

void decompose_line(string line){
    string copy = "";
    for(int i=0;i<line.size();i++){
        if(line[i]==' '){
            if(copy.size()!=0){
                tokens.push_back(copy);
                copy="";
            }
        }else if(line[i]=='+'||line[i]=='-'||line[i]=='*'||line[i]=='/'||line[i]=='{'||line[i]=='}'||line[i]=='('||line[i]==')'||line[i]=='<'||line[i]=='>'||line[i]=='='||line[i]==';'){
            if(copy.size()!=0){
                tokens.push_back(copy);
                copy="";
                copy+=line[i];
                tokens.push_back(copy);
                copy="";
            }else{
                copy+=line[i];
                tokens.push_back(copy);
                copy="";
            }
        }else{
            copy+=line[i];
        }
    }
    if (!copy.empty()) {
        tokens.push_back(copy);
    }
}

int main() {
    string line;
    while (getline(cin, line)) {
        decompose_line(line);
    }
    int i=0;
    while(i<tokens.size()){
        // 先看是不是keyword 若是keyword則直接輸出
        if(tokens[i]=="if"||tokens[i]=="else"||tokens[i]=="while"){
            cout<<"KEYWORD "<<"\""<<tokens[i]<<"\""<<endl;
            i++;
            continue;
        }

        // 依照第一個字決定是哪一種 若是symbol則直接輸出
        int now=0;
        if(isdigit(tokens[i][0])){
            now = 1;
        }else if(tokens[i][0] == '+'||tokens[i][0] == '-'||tokens[i][0] == '*'||tokens[i][0] == '/'||tokens[i][0] == '>'||tokens[i][0] == '<'||tokens[i][0] == '='||tokens[i][0] == ';'||tokens[i][0] == '{'||tokens[i][0] == '}'||tokens[i][0] == '('||tokens[i][0] == ')'){
            if(tokens[i].size()==1){
                cout<<"SYMBOL "<<"\""<<tokens[i][0]<<"\""<<endl;
                i++;
                continue;
            }else{
                cout<<"Invalid"<<endl;
                i++;
                continue;
            }   
        }else if(isalpha(tokens[i][0])){
            now = 2;
        }else{
            cout<<"Invalid"<<endl;
            i++;
            continue;
        }

        // 檢查後面的字是否符合種類 若符合則輸出
        bool invalid=false;
        switch (now)
        {
        case 1:
            for(int k=1;k<tokens[i].size();k++){
                if(!isdigit(tokens[i][k])){
                    cout<<"Invalid"<<endl;
                    i++;
                    invalid=true;
                    break;
                }
            }
            if(!invalid){
                cout<<"NUM \""<<tokens[i]<<"\""<<endl;
                i++;
            }

            break;
        case 2:
            for(int k=1;k<tokens[i].size();k++){
                if(!((tokens[i][k]=='_')||isalpha(tokens[i][k])||isdigit(tokens[i][k]))){
                    cout<<"Invalid"<<endl;
                    i++;
                    invalid=true;
                    break;
                }
            }
            if(!invalid){
                cout<<"IDENTIFIER \""<<tokens[i]<<"\""<<endl;
                i++;
            }
            break;
                
        default:
            break;
        }


    }

}
