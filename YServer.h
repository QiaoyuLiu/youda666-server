#ifndef YSERVER_H
#define YSERVER_H
//#include "RequestHandler.h"
#include "RequestHandler/HttpRequestHandler.h"

class YServer{
    public:
        YServer(int port = 5000, char* host = (char*)"0.0.0.0"):port(port),host(host),handler(new HttpRequestHandler()){};
        //~YServer();

        void start();
        void stop();
        //void reload();
    private:
        //void ctl_handler(char*);
        int port;
        char* host;
        HttpRequestHandler* handler;
};

#endif