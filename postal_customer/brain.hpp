#ifndef BRAIN_HPP
#define BRAIN_HPP
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <malloc.h>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
#include <fcntl.h>
#include <cstdio>   //printf

#include <QString>

class brain
{
    public:
        brain();
        ~brain();

        void initalize_socket();
        void define_postal_service_to_connect_to(QString postal_office_address, int door_number);
        void send_message(char* message_to_send);
        char* recv_message();
        int extract_character_position_of_second_colon(char* packet_to_extract_from);
        int extract_character_position_of_missing_character(char* string_to_extract_from);
        
    private:
        int socket_line;
        struct sockaddr_in service_address_information;
        socklen_t service_address_information_len;
        struct sockaddr_in local_address_information;
        
        char* buffer;

};
#endif
