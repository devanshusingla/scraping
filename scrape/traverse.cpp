#include <bits/stdc++.h>

using namespace std;

string refine(string s){
    int start, end ;
    for(int i=0; i<s.length(); i++){
        if(s[i] == '&'){
            switch(s[i+1]){
                case 'a':
                    s.replace(i, 5, "&", 1) ;
                    break ;
                case 'l':
                    s.replace(i, 4, "<", 1) ;
                    break ;
                case 'g':
                    s.replace(i, 4, ">", 1) ;
                    break ;
                case 'q':
                    s.replace(i, 6, "\"", 1);
                    break ;
            }
        }
    }
    return s ;
}

int main(int num, char **site){
    fstream fin ;
    fin.open("html.txt", ios::in) ;
    fstream fout ;
    fout.open("output.csv", ios::app) ;
    string str, stream;
    //fout<<"Name,Organisation,Project\n" ;
    while(getline(fin, str)){
        stream = str ;
        istringstream ss(stream) ;

        string word ;
        ss >> word ;
        if( word == "<md-card"){

            int start, end ;
            string project, org, name ;

            //extracting names
            while(getline(fin,str)){
                istringstream ss(str) ;
                string word ;
                ss>>word ;
                if(word == "<a") break ;
            }

            for(int i=0; i<str.length(); i++){
                if(str[i]=='>'){
                    i++ ;
                    start = i;
                    while(str[i]!='<'){
                        i++ ;    
                    }
                    end = i;
                    string sub = str.substr(start, end-start) ;
                    name = refine(sub) ;
                    break ;
                }
            }

            //extracting projects
            while(getline(fin,str)){
                istringstream ss(str) ;
                string word ;
                ss>>word ;
                if((word[0] == '<')&&(word[1] == 'd')) break ;
            }
            //fout<<str<<endl ;
            for(int i=0; i<str.length(); i++){
                if(str[i]=='>'){
                    i++ ;
                    start = i;
                    while(str[i]!='<'){
                        i++ ;    
                    }
                    end = i;
                    string sub = str.substr(start, end-start) ;
                    project = refine(sub) ;
                    break ;
                }
            }

            //extracting organisation
            while(getline(fin,str)){
                istringstream ss(str) ;
                string word ;
                ss>>word ;
                if((word[0] == '<')&&(word[1] == 'd')) break ;
            }
            //fout<<str<<endl ;
            for(int i=0; i<str.length(); i++){
                if(str[i]==':'){
                    i+=2 ;
                    start = i;
                    while(str[i]!='<'){
                        i++ ;    
                    }
                    end = i;
                    string sub = str.substr(start, end-start) ;
                    org = refine(sub) ;
                    break ;
                }
            }

            //printing to file
            fout<<name<<","<<org<<","<<project<<endl ;
        }

        //jumping to next page
        if( word == "<a"){
            string link, dummy = "", val ;
            int flag = -1, start, end;
            while(flag <= 0){
                for(int i=0; i<str.length(); i++){
                    if(str[i]=='<'){
                        flag++;
                        if(flag>0) break ;
                    }
                }
                dummy+= str ;
                getline(fin, str) ;
                //fout<<dummy<<endl ;
            }

            for(int i=0; i<dummy.length()-4; i++){
                if(dummy.substr(i,4)=="href"){
                    i+=6 ;
                    start = i;
                    while(dummy[i]!='\"'){
                        i++ ;    
                    }
                    end = i;
                    link = dummy.substr(start, end-start) ;
                    //fout<<link<<endl ;
                    break ;
                }
            }
            
            for(int i=0; i<dummy.length(); i++){
                if(dummy[i]=='>'){
                    i++ ;
                    start = i;
                    while(dummy[i]!='<'){
                        i++ ;    
                    }
                    end = i;
                    string sub = dummy.substr(start, end-start) ;
                    sub.erase(remove_if(sub.begin(), sub.end(), ::isspace), sub.end());
                    val = sub ;
                    //fout<<val<<endl ;
                    break ;
                }
            }
            if(!val.compare("Next")||!val.compare("next")){
                int i, count=-2 ;
                val = *(site+1) ;
                //fout<<val ;
                for(i=0; count <=0 && val[i]; i++){
                    if(val[i] =='/') count++;
                    if(count>0) break ;
                }
                //fout<<i ;
                //fout<<link<<endl ;
                link = val.substr(0, i) + link;
                //fout<<link ;
                link = "./scrape.sh " + link ;
                const char* call = link.c_str() ;
                fin.close() ;
                fout.close() ;
                system(call) ;
                return 0 ;
            }

        }
    }
}