## 실행
	make 명령어 입력 시 proj생성.
	proj 실행.
## main
main에서는 ` library YSC; `라는 코드를 통해서 library에 정의된 library()를 call하게 된다. 이 과제의 모든 동작은 library()함수 내부에서 처리해주게 된다.
## library
library는 다음과 같이 정의되어 있다.
```
private:
	vector<book> books;
	vector<magazine> magazines;
	vector<e_book> e_books;
	vector<undergraduate> undergraduates;
	vector<graduate> graduates;
	vector<faculty> faculties;
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
```
- private
	- library에서는 book과 undergraduate를 vector로 가지고 있게 해서 books는 resource의 목록을 나타내고 undergraduates는 member의 목록을 저장한다.
- public
	- library
		- input을 받아 output을 내보내는 모든 동작이 이루어지는 함수이다.
	- set_books
		- 초기 resource를 받아준다.
	- set_data
		- 1줄씩 받은 input을 보고 비교를 통해서 return_code를 return해주고 날짜를 함께 나타내야하는 4, 5, 6, 7의 경우에는 날짜를 int로 변경해서 10을 곱해 return_code에 더해서 전달해준다.
	- output
		- output으로 내보내기 위한 목차를 받고 return_code를 받아 해당되는 output을 파일에 써준다.
		- return_code는 1의 자리만 확인하고 날짜 값은 10으로 나눈 나머지를 취해 출력해준다.
	- day2int
		- string으로 받은 날짜를 int 값으로 반환해준다.
	- int2day
		- int로 받은 날짜를 string으로 반환해준다.


## resource, member
##### 이번 과제에서는 각각 3가지 class로 구성되고 모두 동일한 구조를 가지며 policy에 따른 비교 변수의 차이만 가진다.
resource와 member에서 필요한 변수들을 class로 만들어주고 이를 get하고 set하기 위한 함수들로 이루어져있다.
- resource
	- resource class가 있고 book, magazine, e-book이 resource를 상속받아 사용하게 된다.
- member
	- member class가 있고 undergraduate, graduate, faculty가 member를 상속받아 사용하게 된다.
	
## space
##### space의 경우 모든 member에게 같은 policy가 적용되기 때문에 member type을 확인하지 않고 동작하게 된다. 
space에 필요한 변수들을 class로 만들어주고 이를 get하고 set하기 위한 함수들로 이루어져있다.
space는 studyroom과 seat 두가지로 구성되어 있고 이 사용 멤버 이름, 사용 시작 시간, 예정 사용 시간 등, return code 판단을 위한 정보를 저장하고 studyroom의 경우에는 1번방부터 10번방까지 `room_num`으로 저장했고 seat의 경우에는 1층부터 3층까지 `floor`로 저장했다.
space.h file은 아래와 같고 space.cpp파일은 모두 private 변수들을 set화고 get하는 함수로 구성되어 있다.
```
class space {
private:
	string user;
	int time;
	int status;
	int come_time;
	int borrow_time;
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
	void set_borrow_time(int sborrow_time);
	int get_borrow_time();
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
```
