#include <iostream>
#include <fstream>
#include <sstream>

std::string BigWord(std::ifstream& fin){
    fin.clear();
    fin.seekg(0,std::ios::beg);

    std::string buff, big_word="";
    while(fin>>buff){
        if(buff.length()>big_word.length()){
            big_word=buff;
        }
    }
    return big_word;
}

std::string SmallWord(std::ifstream& fin){
    fin.clear();
    fin.seekg(0,std::ios::beg);

    std::string buff, small_word=BigWord(fin);

    fin.clear();
    fin.seekg(0,std::ios::beg);

    while(fin>>buff){
        if(buff.length()<small_word.length()){
            small_word=buff;
        }
    }
    return small_word;
}

std::string ReplaceInStr(std::ifstream& fin, const std::string& min, const std::string& max){
    std::string buff;
    std::stringstream ss;

    while(fin>>buff){
        if(buff==min)(ss<<max);
        if(buff==max)(ss<<min);
        ss<<buff;
    }
    return ss.str();
}

int main(){
    std::ifstream fin("input.txt");
    std::string max,min;
    
    max=BigWord(fin);

    min=SmallWord(fin);

    std::cout<<max<<' '<<min;

    return 0;
}