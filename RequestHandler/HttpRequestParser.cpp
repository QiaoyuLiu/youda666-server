#include <string>
#include <cstring>
#include <regex>
#include "HttpRequestParser.h"

using std::string;
using std::regex;
//regex is slow, rewrite with another way
void HttpRequestParser::parse(std::string& request, std::unordered_map<std::string, std::string*>& request_environment){
    regex re("\\r\\n");
    std::vector<string> lines(std::sregex_token_iterator(request.begin(), request.end(), re, -1),
              std::sregex_token_iterator());
    auto it = lines.begin();
    parse_first_line(*it, request_environment);
    it++;

    while(*it != ""){
        parse_header(*it, request_environment);
        it++;
    }
    it++;
    if ((request_environment[string("Method")] == new string("GET") ||request_environment[string("Method")] == new string("DELETE")) && it != lines.end()) throw "bad request";
    //else parse_body(*it, request_environment);
}

void HttpRequestParser::parse_first_line(std::string& line, std::unordered_map<std::string, std::string*>& request_environment){

    //check if first line match the http format eg. GET /aaaa.html HTTP/1.1
    regex request_fmt("[A-Z]+\\s/\\S*\\sHTTP\\/\\d\\.\\d");
    if((std::regex_match(line, request_fmt)) != true) throw "bad request";

    //split first line into tokens, and store in vector. 
    regex re("\\s");
    std::vector<string> line_tokens(std::sregex_token_iterator(line.begin(), line.end(), re, -1),
              std::sregex_token_iterator());

    //check if the method is allowed    
    const string allowed_method[] = {"GET", "POST", "PUT", "DELETE"};
    bool is_allowed_method = false;
    for(string method:allowed_method){
        if(method == line_tokens[0]){
            is_allowed_method = true;
            break;
        }
    }
    if(!is_allowed_method) throw "unallowed method";

    //method
    request_environment[string("Method")] = new string(line_tokens[0]);

    //uri
    request_environment[string("Uri")] = new string(line_tokens[1]);
    
    //http version
    request_environment[string("Version")] = new string(line_tokens[2]);
}

void HttpRequestParser::parse_header(std::string& line, std::unordered_map<std::string, std::string*>& request_environment){
    
    //check if header line match the http format eg my_header : header_header
    regex request_fmt("^\\S+\\s?:\\s?\\S+");
    if(std::regex_match(line, request_fmt) != true) throw "bad request";

    //split into tokens, and store in vector.
    regex re("\\s");
    std::vector<string> line_tokens(std::sregex_token_iterator(line.begin(), line.end(), re, -1),
              std::sregex_token_iterator());
    
    request_environment[line_tokens[0]] = new string(line_tokens[1]);
}