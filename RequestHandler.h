#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H
#include <hash_map>
#include <vector>
#include "Plugin.h"
class RequestHandler{
    public:
        virtual void prepare_request(char* request);
        virtual void prepare_response(char* response);
        virtual void register_plugin();
        virtual void unregister_plugin();
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