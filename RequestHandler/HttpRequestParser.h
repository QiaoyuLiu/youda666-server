#ifndef HTTP_REQUEST_PARSER_H
#define HTTP_REQUEST_PARSER_H
#include <unordered_map>
#include <vector>
#include <string>

#include "RequestParser.h"

class HttpRequestParser: public RequestParser{
    public:
        void parse(std::string& request, std::unordered_map<std::string, std::string*>& request_environment)  override;
        void parse_first_line(std::string& line, std::unordered_map<std::string, std::string*>& request_environment);
        void parse_header(std::string& line, std::unordered_map<std::string, std::string*>& request_environment);
        void parse_body(std::string& body, std::unordered_map<std::string, std::string*>& request_environment);
};

#endif