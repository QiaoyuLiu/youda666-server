#ifndef HTTP_REQUEST_HANDLER_H
#define HTTP_REQUEST_HANDLER_H
#include <hash_map>
#include <vector>
#include "Plugin.h"
#include "RequestHandler.h"
class HttpRequestHandler: public RequestHandler{
    public:
        void prepare_request(char* request);
        void prepare_response(char* response);
        void register_plugin();
        void unregister_plugin();
        //how to forward 
        virtual void handle();
    private:
        std::vector<Plugin*> plugins;
        __gnu_cxx::hash_map<char*, char*> request_environment;

        __gnu_cxx::hash_map<char*, char*> parse_request(char* request);
        void apply_request_plugins();
        void apply_response_plugins();
};

#endif