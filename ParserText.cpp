#include<iostream>
#include <vector>
using namespace std;

enum TokenType {
    ID,      // Identifier
    STRLIT,  // String literal
    DOT,     // '.'
    LBR,     // Left bracket (could be '(' or '[' etc.)
    RBR,     // Right bracket (could be ')' or ']' etc.)
    ERROR    // Error
};

struct Token {
    TokenType type;
    string value;
};

void program();
void stmts();
void stmt();
void primary_tail();
void primary();
vector<Token> tokens;
int current_token_index = 0;

void program(){
    stmts();
}

bool matchid(string a){
    for(int i=0;i<a.size();i++){
        if(i==0){
            if(!((65<=int(a[i])&&int(a[i])<=90)||(97<=int(a[i])&&int(a[i])<=122)||(int(a[i])==95))){
                return false;
            }
        }else if(!((48<=int(a[i])&&int(a[i])<=57)||(65<=int(a[i])&&int(a[i])<=90)||(97<=int(a[i])&&int(a[i])<=122)||(int(a[i])==95))){
                return false;
            }
    }
    return true;
}

void stmts(){
    if(current_token_index>=tokens.size()){
        return; // end
    }else{
        stmt();
        stmts();
        
    }
}

void stmt(){
    if(current_token_index>=tokens.size()){
        return; // end
    }else{          //  若為字串則換下一個token
        if((tokens[current_token_index].value[0]=='\"')&&(tokens[current_token_index].value.back()=='\"')){
            tokens[current_token_index].type = STRLIT;
            cout<<"STRLIT "<<tokens[current_token_index].value<<endl;
            current_token_index++;
        }else{
            primary();
        }
    }
}

void primary(){
    int j = tokens[current_token_index].value.size();
    if(j==0){
        return;
    }             //  在id中找.和(來切割
    for(int i=0;i<tokens[current_token_index].value.size();i++){
        if((tokens[current_token_index].value[i]=='.')||(tokens[current_token_index].value[i]=='(')){
            j=i;
            break;
        }
    }
    if(j==tokens[current_token_index].value.size()){  //如果都是id就不用切
        if(matchid(tokens[current_token_index].value)){
            cout<<"ID "<<tokens[current_token_index].value<<endl;
        }else{
            cout<<"invalid input"<<endl;
        }
        tokens[current_token_index].value="";
        primary_tail();
    }else{
        string sub = tokens[current_token_index].value.substr(0,j);
        if(matchid(sub)){
            cout<<"ID "<<sub<<endl;
        }else{
            cout<<"invalid input"<<endl;
        }
        tokens[current_token_index].value = tokens[current_token_index].value.substr(j,tokens[current_token_index].value.size()-j);
        primary_tail();
    }

    
}
void primary_tail(){
    if(tokens[current_token_index].value.size() == 0 ){
        current_token_index++;
        return;
    }
    else if(tokens[current_token_index].value[0] == '.' ){
        cout<<"DOT"<<" ."<<endl;
        tokens[current_token_index].value = tokens[current_token_index].value.substr(1,tokens[current_token_index].value.size()-1 );
        primary_tail();
    }else if(tokens[current_token_index].value[0] == '(' ){
        cout<<"LBR"<<" ("<<endl;
        tokens[current_token_index].value = tokens[current_token_index].value.substr(1,tokens[current_token_index].value.size()-1 );
        int j = tokens[current_token_index].value.size();
        for(int i=0;i<tokens[current_token_index].value.size();i++){
            if((tokens[current_token_index].value[i]==')')){
                j=i;
                break;
            }
        }
        string copy;
        if((tokens[current_token_index].value.size()-j-1)>=1){
            copy = tokens[current_token_index].value.substr(j+1,tokens[current_token_index].value.size()-j-1);
        }else{
            copy = "";
        }
        tokens[current_token_index].value = tokens[current_token_index].value.substr(0,j);
        stmt();
        cout<<"RBR"<<" )"<<endl;
        if(copy.size()==0){
            return;             // 如果copy已經沒東西了就先 return 是string
        }
        tokens[current_token_index].value = copy;
        primary_tail();
    }
}


int main(){
    string value;
    while(cin>>value){
        Token t = {ID,value};
        tokens.push_back(t);
    }
    program();
    


}
