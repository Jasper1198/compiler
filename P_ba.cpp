#include<iostream>
#include <vector>
using namespace std;




void program();
void stmt();
void phone();
void date();
vector<string> tokens;
int current_token_index = 0;

void program(){
    stmt();
}

bool matchmon(string mon){
    if(mon=="JAN"||mon=="FEB"||mon=="MAR"||mon=="APR"||mon=="MAY"||mon=="JUN"||mon=="JUL"||mon=="AUG"||mon=="SEP"||mon=="OCT"||mon=="NOV"||mon=="DEC"){
        return true;
    }else{
        return false; 
    }
}




void stmt(){
    if(current_token_index>=tokens.size()){
        return; // end
    }else{          //  判斷是月份還是電話
        if((tokens[current_token_index][0]=='+')){
            phone();
        }else{
            date();
        }
    }
}

void phone(){
    string na;
    string ph;
    if(tokens[current_token_index][0]!='+'){
        cout<<"Invalid input"<<endl;
        return;
    }
    if(tokens[current_token_index][1]!='('){
        cout<<"Invalid input"<<endl;
        return;
    }
    if(!(isdigit(tokens[current_token_index][2])&&isdigit(tokens[current_token_index][3])&&isdigit(tokens[current_token_index][4]))){
        cout<<"Invalid input"<<endl;
        return;
    }else{
        na = tokens[current_token_index].substr(2,3);
    }
    if(tokens[current_token_index][5]!=')'){
        cout<<"Invalid input"<<endl;
        return;
    }
    if(!(isdigit(tokens[current_token_index][6])&&isdigit(tokens[current_token_index][7])&&isdigit(tokens[current_token_index][8])&&(isdigit(tokens[current_token_index][9]))&&(isdigit(tokens[current_token_index][10]))&&(isdigit(tokens[current_token_index][11]))&&(isdigit(tokens[current_token_index][12]))&&(isdigit(tokens[current_token_index][13]))&&(isdigit(tokens[current_token_index][14])))){
        cout<<"Invalid input"<<endl;
        return;
    }else{
        ph = tokens[current_token_index].substr(6,9);
    }
    cout<<"+ PLUS\n( LBR\n"<<na<<" NATIONNUM\n) RBR\n"<<ph<<" PHONENUM\n";
    
}



void date(){
    int format = 0;
    string year;
    int day;
    string mon; 
    if(isalpha(tokens[current_token_index][0])){          //先 month   jun.15.2014
        format = 1;
        mon=tokens[current_token_index].substr(0,3);
        if(!matchmon(mon)){
            cout<<"Invalid input"<<endl;
            return;
        }
        if(tokens[current_token_index][3]=='.'||tokens[current_token_index][6]=='.'){
            day = (int(tokens[current_token_index][4])-48)*10+(int(tokens[current_token_index][5])-48);
            if(!(0<day)&&(day<=31)){
                cout<<"Invalid input"<<endl;
                return;
            }
            if(isdigit(tokens[current_token_index][7])&&isdigit(tokens[current_token_index][8])&&isdigit(tokens[current_token_index][9])&&isdigit(tokens[current_token_index][10])){
                year=tokens[current_token_index].substr(7,4);
            }else{
                cout<<"Invalid input"<<endl;
                return;               
            }
        }else if (tokens[current_token_index][3]=='.'||tokens[current_token_index][5]=='.'){
            day = int(tokens[current_token_index][4])-48;
            if(isdigit(tokens[current_token_index][7])&&isdigit(tokens[current_token_index][8])&&isdigit(tokens[current_token_index][9])&&isdigit(tokens[current_token_index][6])){
                year=tokens[current_token_index].substr(6,4);
            }else{
                cout<<"Invalid input"<<endl;
                return;               
            }
        }else{
            cout<<"Invalid input"<<endl;
            return;  
        }
        cout<<mon<<" MONTH\n"<<". DOT\n"<<day<<" DAY\n. DOT\n"<<year<<" YEAR"<<endl;
    // 先 year 2014/jun/15
    }else if(isdigit(tokens[current_token_index][0])&&isdigit(tokens[current_token_index][1])&&isdigit(tokens[current_token_index][2])&&isdigit(tokens[current_token_index][3])&&tokens[current_token_index][4]=='/'&&tokens[current_token_index][8]=='/'){
        format = 2;
        year=tokens[current_token_index].substr(0,4);
        mon=tokens[current_token_index].substr(4,3);
        if(!matchmon(mon)){
            cout<<"Invalid input"<<endl;
            return;
        }
        if(tokens[current_token_index].size()==11){
            if(isdigit(tokens[current_token_index][9])&&isdigit(tokens[current_token_index][10])){
                day = (int(tokens[current_token_index][7])-48)*10+(int(tokens[current_token_index][8])-48);
            }else{
                cout<<"Invalid input"<<endl;
                return;
            }
        }else{
            if(isdigit(tokens[current_token_index][9])){
                day = int(tokens[current_token_index][7])-48;
            }else{
                cout<<"Invalid input"<<endl;
                return;
            } 
        }

        if(!(0<day)&&(day<=31)){
            cout<<"Invalid input"<<endl;
            return;
        }
        cout<<year<<" YEAR\n"<<"SLASH /\n"<<mon<<"MON \nSLASH /\n"<<day<<" DAY"<<endl;
    }
}


int main(){
    string value;
    cin>>value;
    tokens.push_back(value);
    
    program();
    


}
