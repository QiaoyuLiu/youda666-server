#ifndef REQUEST_ADAPTER_H
#define REQUEST_ADAPTER_H
#include <unordered_map>
#include <vector>
#include <string>

class RequestAdapter{
    public:
        virtual void parse(std::string& request, std::unordered_map<std::string, std::string*>& map) = 0;
};

#endif