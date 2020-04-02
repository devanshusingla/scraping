#include <bits/stdc++.h>

using namespace std;

struct csv{
    string name;
    string roll_no;
    string branch;
    string org;
    string pro;
};

void print_name(struct csv *c){
    cout<<c->name<<" " ;
}

bool test(string str){
    int upper = 0, many_word = 0;
    for(auto ch:str){
        if(!isupper(ch)&&!islower(ch)&&(ch!=' ')) return 0;
        if(ch == ' ') many_word = 1;
        if(isupper(ch)) upper = 1;
    }
    return (many_word && upper) ;
}

int main(){

    string csv_file, json_file ;
    cout<<"enter csv file with full address\n" ;
    cin>>csv_file ;
    cout<<"enter json_file with full address\n" ;
    cin>>json_file ;
    cout<<endl<<"names which are not official :-"<<endl<<endl ;

    fstream fin, fout, jin ;
    fin.open(csv_file, ios::in) ;
    jin.open(json_file, ios::in) ;
    vector<struct csv *> v;

    string str ;
    while (getline(fin, str))
    {
        string name, org, pro;
        istringstream ss(str) ;
        getline(ss, name, ',') ;
        getline(ss, org, ',') ;
        getline(ss, pro) ;
        struct csv *c = new struct csv ;
        c->name = name;
        c->org = org ;
        c->pro = pro ;
        if(test(c->name))
            v.push_back(c) ;
        else{
            print_name(c) ;
        }
    }

    getline(jin, str) ;
    //str.erase(0,1) ;
    //str.erase(str.length()-1, 1) ;
    istringstream ss(str) ;
    string s;
    while(getline(ss,s,'}')){
        s.erase(0,2) ;
        istringstream stream(s) ;
        string name, roll_no, branch ;
        string element ;
        while(getline(stream, element, ',')){
            //cout<<element<<endl ;
            switch(element[1]){
                case 'n':
                    name = element.substr(5, element.length()-6) ;
                    break;
                case 'r':
                    roll_no = element.substr(5,element.length()-6) ;
                    break;
                case 'd':
                    branch = element.substr(5, element.length() - 6) ;
            }
        }

        for(auto itr:v){
            if(name == itr->name){
                itr->roll_no = roll_no;
                itr->branch = branch;
            }
        }
    }

    cout<<endl<<endl ;
    for(auto itr:v){
        cout<<itr->name<<", "<<itr->roll_no<<", "<<itr->branch<<", "<<itr->org<<", "<<itr->pro<<endl ;
    }
}