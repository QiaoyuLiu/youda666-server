#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H
#include <unordered_map>
#include <vector>
#include <string>
#include "RequestParser.h"
#include "RequestAdapter.h"
class RequestHandler{
    public:
        virtual void handle();
    private:
        std::unordered_map<std::string*, std::string*>& map;
        RequestParser* parser;
        RequestAdapter* adapter;
        //virtual void parse(std::string request, std::unordered_map<std::string*, std::string*>& map);
        
};

#endif