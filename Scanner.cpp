#include <iostream>
using namespace std;

int main() {
    char ch;
    bool con = false;
    int a=0;
    while ((ch = cin.get()) != EOF) {  
        if(48<=int(ch)&&int(ch)<=57){
            con = true;
            a = a * 10 + int(ch) - 48;
        }else if(ch=='+'){
            if(con){
                cout<<"NUM "<< a <<endl; 
                a = 0;
                con = false;
            }
            cout<<"PLUS"<<endl;
        }else if(ch=='-'){
            if(con){
                cout<<"NUM "<< a <<endl; 
                a = 0;
                con = false;
            }
            cout<<"MINUS"<<endl;
        }else if(ch=='*'){
            if(con){
                cout<<"NUM "<< a <<endl; 
                a = 0;
                con = false;
            }
            cout<<"MUL"<<endl;
        }else if(ch=='/'){
            if(con){
                cout<<"NUM "<< a <<endl; 
                a = 0;
                con = false;
            }
            cout<<"DIV"<<endl;
        }else if(ch=='('){
            if(con){
                cout<<"NUM "<< a <<endl; 
                a = 0;
                con = false;
            }
            cout<<"LPR"<<endl;
        }else if(ch==')'){
            if(con){
                cout<<"NUM "<< a <<endl; 
                a = 0;
                con = false;
            }
            cout<<"RPR"<<endl;
        }
    }
    if(con){
        cout<<"NUM "<< a <<endl; 
        a = 0;
        con = false;
    }
}
