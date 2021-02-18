#ifndef HTTP_REQUEST_HANDLER_H
#define HTTP_REQUEST_HANDLER_H
#include <unordered_map>
#include <vector>
#include <string>
#include "HttpRequestParser.h"

class HttpRequestHandler/*: public RequestHandler*/{
    public:
        HttpRequestHandler();
        //how to forward 
        virtual void handle(std::string& request);
    private:
        std::unordered_map<std::string, std::string*> request_environment;
        HttpRequestParser* parser;
};

#endif