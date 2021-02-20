#ifndef WSGI_ADAPTER_H
#define WSGI_ADAPTER_H
#include <unordered_map>
#include <vector>
#include <string>
#include "RequestAdapter.h"

class WSGIAdapter : public RequestAdapter{
    public:
        void forward(std::unordered_map<std::string, std::string*>&) override;
    private:
        void forward_wsgi(std::unordered_map<std::string, std::string*>&);
};

#endif