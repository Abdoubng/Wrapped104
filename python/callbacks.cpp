#include "callbacks.hpp"
#include <iostream>

using namespace std;

Server::Server();

void Server::init(int arg1, int arg2){
     
     //   connectionParameters= Slave_getConnectionParameters(this);
        T104Slave_create(NULL, Arg1, Arg2);
};
/*
void Server::Start(){
        Slave_start(this);
        printf("Server started");
};

void Server::setHandlers(){

        Slave_setClockSyncHandler(this, clockSyncHandler, NULL);

        bool
        clockSyncHandler (void* parameter, MasterConnection connection, ASDU asdu, CP56Time2a newTime)
        {
        printf("Process time sync command with time "); printf("\n");
        
        printf("%02i:%02i:%02i %02i/%02i/%04i", CP56Time2a_getHour(newTime),
                             CP56Time2a_getMinute(newTime),
                             CP56Time2a_getSecond(newTime),
                             CP56Time2a_getDayOfMonth(newTime),
                             CP56Time2a_getMonth(newTime) + 1,
                             CP56Time2a_getYear(newTime) + 2000);
	printf("\n");
        };*/

