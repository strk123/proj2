#include <iostream>
#include <string>
#include "space.h"
using namespace std;

space :: space(){
	user = "";
	time = 0;
	status = 0;
}
void space :: set_user(string suser){
	user = suser;
}
string space :: get_user(){
	return user;
}

void space :: set_time(int stime){
	time = stime;
}
int space :: get_time(){
	return time;
}

void space :: set_status(int sstatus){
	status = sstatus;
}
int space :: get_status(){
	return status;
}


studyroom :: studyroom(){
	room_num = "0";
}
void studyroom :: set_room_num(string sroom_num){
	room_num = sroom_num;
}
string studyroom :: get_room_num(){
	return room_num;
}

seat :: seat(){
	floor = "0";
}
void seat :: set_floor(string sfloor){
	floor = sfloor;
}
string seat :: get_floor(){
	return floor;
}


