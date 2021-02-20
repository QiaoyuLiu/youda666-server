#include "HttpRequestHandler.h"
#include <string>
#include <iostream>
#include <unordered_map>
#include "HttpRequestParser.h"
#include "WSGIAdapter.h"

using namespace std;
HttpRequestHandler::HttpRequestHandler(){
    parser = new HttpRequestParser();
    adapter = new WSGIAdapter();
}

void HttpRequestHandler::handle(std::string& request){
    parser->parse(request, request_environment);
    for(auto h: request_environment){
        cout<< h.first << " : " << h.second <<endl;
    }
    adapter->forward(request_environment);
}