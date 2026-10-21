//лабораторная работа 11
#include <iostream>
#include <fstream>
#include <sstream>

void check_fin(std::ifstream& fin){
    if(!fin.good()) throw "file open error";
    if(!fin) throw "file open error";
    if(fin.peek()==EOF) throw "file open error";
}

void check_fout(std::ofstream& fout){
    if(!fout) throw "file open error";
}

void SearchWords(std::string& min, std::string& max, const char* file_name){
    std::ifstream fin(file_name);
    try{   
        check_fin(fin);

        fin.clear();
        fin.seekg(0,std::ios::beg);

        std::string buff;
        bool flag=true;

        while(fin>>buff){
            if(flag){
                min=buff;
                flag=false;
            }
            if(buff.length()<min.length()){
                min=buff;
            }
            if(buff.length()>max.length()){
                max=buff;
            }
        }
    }catch(const char*){std::cout<<"error"<<'\n';}
}

std::string ReplaceInStr(const std::string& min, const std::string& max, 
    const char* file_name){

    std::ifstream fin(file_name);
    try{    
        check_fin(fin);

        fin.clear();
        fin.seekg(0,std::ios::beg);

        std::string buff="";
        std::stringstream ss;
        bool flag_min=true,flag_max=true;
        char c;

        while(fin.get(c)){
            if(c==' '){
                if(buff==min&&flag_min){
                    ss<<max;
                    flag_min=false;
                }
                else if(buff==max&&flag_max){
                    ss<<min;
                    flag_max=false;
                }
                else ss<<buff;
                
                ss<<c;
                buff="";
            }
            else{
                buff+=c;
            }
        
        }
        return ss.str();
    }catch(const char*){std::cout<<"error"<<'\n';}
}

void WriteFromStr(const std::string& text,const char* file_name){
    std::ofstream fout_clear(file_name, std::ios::trunc);
    std::ofstream fout(file_name, std::ios::app);
    try{
        check_fout(fout_clear);
        check_fout(fout);
        fout<<text;
    }catch(const char*){std::cout<<"error"<<'\n';}
    

}

int main(){
    std::string max="",min="", text;

    SearchWords(min, max, "input.txt");

    text=ReplaceInStr(min, max, "input.txt");

    WriteFromStr(text, "input.txt");

    return 0;
}