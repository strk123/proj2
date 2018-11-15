#include <iostream>
#include <string>
using namespace std;

class space {
private:
	string user;
	int time;
	int status;
public:
	space();
	void set_user(string suser);
	string get_user();
	void set_time(int stime);
	int get_time();
	void set_status(int sstatus);
	int get_status();
};



class studyroom : public space{
private:
	string room_num;
public:
	studyroom();
	void set_room_num(string sroom_num);
	string get_room_num();

};



class seat : public space{
private:
	string floor;
public:
	seat();
	void set_floor(string sfloor);
	string get_floor();

};