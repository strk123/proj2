#include <iostream>
#include <string>
using namespace std;

class space {
private:
	string user;
	int time;
	int status;
	int come_time;
public:
	space();
	void set_user(string suser);
	string get_user();
	void set_time(int stime);
	int get_time();
	void set_status(int sstatus);
	int get_status();
	void set_come_time(int stime);
	int get_come_time();
};



class studyroom : public space{
private:
	int room_num;
public:
	studyroom();
	void set_room_num(int sroom_num);
	int get_room_num();

};



class seat : public space{
private:
	int floor;
public:
	seat();
	void set_floor(int sfloor);
	int get_floor();

};