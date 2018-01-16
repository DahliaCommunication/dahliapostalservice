#include "brain.hpp"

brain::brain()
{
    
}

brain::~brain()
{
    free(buffer);
}

void brain::initalize_socket()
{
    buffer = (char*)malloc(256);
    memset(buffer, '\0', 256);
    
    service_address_information_len = 0;
    
    socket_line = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    fcntl(socket_line, F_SETFL, O_NONBLOCK);
    if(-1 == socket_line)
    {
        printf("failed to socket\n");
    }
}

void brain::define_postal_service_to_connect_to(QString postal_office_address, int door_number)
{
    memset((char *) &service_address_information, 0, sizeof(service_address_information));
    service_address_information.sin_family = AF_INET;
    service_address_information.sin_port = htons(door_number);

    QByteArray postal_office_address_bytearray = postal_office_address.toUtf8();
    const char* postal_office_address_cchar = postal_office_address_bytearray.toStdString().data();
    inet_aton(postal_office_address_cchar , &service_address_information.sin_addr);//define ip address to connect to
}

void brain::send_message(char* message_to_send)
{
    int slen;
    if(sendto(socket_line, message_to_send, strlen(message_to_send), 0, (struct sockaddr *)&service_address_information, sizeof(service_address_information))==-1)
    {
        printf("failed to send");
    }
}

char* brain::recv_message()
{
    char* output = (char*)malloc(256);
    memset(output, '\0', 256);
    memset(buffer, '\0', 256);
    int amount_recvd = recvfrom(socket_line, buffer, 255, 0, (struct sockaddr *) &service_address_information, &service_address_information_len);
    
    strncpy(output, buffer, 255);
    
    return output;
}

int brain::extract_character_position_of_second_colon(char* packet_to_extract_from)
{
    int output = -1;
    
    //Find the second ":"(colon) position.
    int current_position_to_check = 0;
    int position_detected = 0;
    while(current_position_to_check < strlen(packet_to_extract_from))
    {
        if(packet_to_extract_from[current_position_to_check] == ':')
        {
            position_detected++;
            if(2 == position_detected)
            {
                output = current_position_to_check;
                current_position_to_check = strlen(packet_to_extract_from);
            }
        }
        
        ++current_position_to_check;
    }

    return output;
}

int brain::extract_character_position_of_missing_character(char* string_to_extract_from)
{
    int output = -1;
    
    if(string_to_extract_from[0] != '\a')
    {
        //Find the first "\0" 
        int current_position_to_check = 0;
        while(current_position_to_check < strlen(string_to_extract_from))
        {
            if(string_to_extract_from[current_position_to_check] == '\a')
            {
                output = current_position_to_check;
                current_position_to_check = strlen(string_to_extract_from);
            }
            ++current_position_to_check;
        }
    }
    
    return output;
}
