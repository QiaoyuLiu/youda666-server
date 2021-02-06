#ifndef YSERVER_H
#define YSERVER_H
#include "RequestHandler.h"

class YServer{
    public:
        YServer(int port = 5000, char* host = "0.0.0.0"):port(port),host(host){};
        ~YServer();

        void start();
        void stop();
        //void reload();
    private:
        //void ctl_handler(char*);
        int port;
        char* host;
        RequestHandler* handler;
};

#endif