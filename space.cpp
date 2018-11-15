#include <iostream>
#include <string>
#include "space.h"
using namespace std;

space :: space(){
	user = "";
	time = 0;
	status = 0;
	come_time = 0;
	borrow_time = 0;
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
void space :: set_come_time(int stime){
	come_time = stime;
}
int space :: get_come_time(){
	return come_time;
}
void space :: set_borrow_time(int sborrow_time){
	borrow_time = sborrow_time;
}
int space :: get_borrow_time(){
	return borrow_time;
}

studyroom :: studyroom(){
	room_num = 0;
}
void studyroom :: set_room_num(int sroom_num){
	room_num = sroom_num;
}
int studyroom :: get_room_num(){
	return room_num;
}

seat :: seat(){
	floor = 0;
}
void seat :: set_floor(int sfloor){
	floor = sfloor;
}
int seat :: get_floor(){
	return floor;
}


