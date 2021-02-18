#ifndef REQUEST_PARSER_H
#define REQUEST_PARSER_H
#include <unordered_map>
#include <vector>
#include <string>

class RequestParser{
    public:
        virtual void parse(std::string& request, std::unordered_map<std::string, std::string*>& map) = 0;
};

#endif