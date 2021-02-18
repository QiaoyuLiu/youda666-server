#include <iostream>
#include <regex>
using namespace std;
int main(){
    std::string request = "GET / HTTP/1.1";
    regex re("[A-Z]+\\s/\\S*\\sHTTP\\/\\d\\.\\d");
    auto i = regex_match(request,re);
    std::vector<std::string> lines(std::sregex_token_iterator(request.begin(), request.end(), re, -1),
              std::sregex_token_iterator());
    for(auto line : lines){
        std::cout<<line<<std::endl;
    }
    std::cout<<i<<std::endl;
}