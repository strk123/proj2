#include <iostream>
#include <vector>
#include <string>
#include "member.h"
#include "resource.h"
#include "space.h"

using namespace std;

class library {
private:
	vector<book> books;
	vector<undergraduate> undergraduates;
	vector<studyroom> studyrooms;
	vector<seat> seats;
public:
	library();
	void set_books(); // resource file을 읽어 초기 books에 저장
	void input(); // input.dat file을 읽고 output을 생성
	int set_data(string date, string resource_type, string resource_name, string operation, string member_type, string member_name); // 한 줄에 대해서 return code 결정
	void output(int operation_num, int return_code); //return code에 따라서 output 생성
	int day2int(string day); // 날짜 string을 int로 변경
	string int2day(int day); // 날짜 int를 string으로 변경
	int sday2int(string sday);
	string sint2day(int sday);
	int set_sdata(string sdate, string space_type, string space_number, string soperation, string smember_type, string smember_name, string number_of_member, string time);
	void soutput(int soperation_num, int sreturn_code);
	int day2time(string day);
	bool isinnum(string s);
};