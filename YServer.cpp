#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <errno.h>  
#include <sys/socket.h>  
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>  
#include <netdb.h>
#include <sys/epoll.h>  
#include <string.h>

#include "YServer.h"

#include <iostream>
#include <string>

#define MAX_EVENTS 500
#define _BACKLOG 5

//nonblocking socket
void setnonblocking(int sockfd) {    
    int opts;    
   
   opts = fcntl(sockfd, F_GETFL);    
    if(opts < 0) {    
        perror("fcntl(F_GETFL)\n");    
        exit(1);    
    }    
    opts = (opts | O_NONBLOCK);    
    if(fcntl(sockfd, F_SETFL, opts) < 0) {    
        perror("fcntl(F_SETFL)\n");    
        exit(1);    
    }    
}  


void YServer::start(){
    //fd
    int listen_socket, accept_socket, epoll_fd, ret_fd_number;
    //listen socket initializing
    listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_socket<0) exit(-1);
    struct sockaddr_in sev_address;
    bzero(&sev_address, sizeof(sev_address));
    sev_address.sin_family = AF_INET;
    inet_pton(AF_INET, host, &sev_address.sin_addr);
    sev_address.sin_port = htons(port);
    setnonblocking(listen_socket);

    //set socket reuse
    int so_reuseaddr = 1;
    setsockopt(listen_socket,SOL_SOCKET,SO_REUSEADDR,
    &so_reuseaddr,
    sizeof(so_reuseaddr));

    //start
    if (bind(listen_socket, (sockaddr*)&sev_address, sizeof(sockaddr_in))<0) exit(-2);
    if (listen(listen_socket, _BACKLOG)<0) exit(-3);
    //epoll initializing
    struct epoll_event ev;
    struct epoll_event ret_ev[MAX_EVENTS];
    ev.events = EPOLLIN;
    ev.data.fd = listen_socket;
    epoll_fd = epoll_create(1024);

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_socket, &ev) == -1) {
            perror("epoll_ctl: listen_sock");
            exit(EXIT_FAILURE);
    }
    int i;
    socklen_t sockaddr_in_size = sizeof(sockaddr_in);
    for(;;){
        ret_fd_number = epoll_wait(epoll_fd, ret_ev, MAX_EVENTS, -1);
        if(ret_fd_number == -1) {
            perror("epoll wait failure");
            exit(-1);
        }
        for (i = 0; i<ret_fd_number; i++){
            
            //listen_socket return, new connection in
            if (ret_ev[i].data.fd == listen_socket){
                if((accept_socket = accept(listen_socket, NULL, NULL)) == -1){
                    perror("accept failure");
                    exit(-1);
                }
                setnonblocking(accept_socket);
                ev.events = EPOLLIN | EPOLLET ;
                ev.data.fd = accept_socket;
                std::cout<<accept_socket<<std::endl;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, accept_socket, &ev) == -1) {
                    perror("epoll_ctl: listen_sock");
                    exit(EXIT_FAILURE);
                }
            }
            //normal request in
            else{
                int request_length = 0;
                int pack_length = 0;
                char buffer[50];
                std::string *request = new std::string();
                while((pack_length = read(ret_ev[i].data.fd, &buffer, sizeof(buffer)-1)) > 0){
                        *request += buffer;
                        request_length += pack_length;
                        //std::cout<<request_length<<std::endl;
                        bzero(&buffer, 50);
                }

                //std::cout<<(char*)request.data();
                
                
                handler->handle(*request);
            }
        }
        
    }
}