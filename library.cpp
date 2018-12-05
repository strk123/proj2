#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "library.h"
using namespace std;

library :: library() { // main에서 library를 선언했을때 모든 동작이 실행할 수 있게 만들었다.
	for(int i = 0; i < 10 ; i++){ // studyroom의 초기화
		studyroom a;
		a.set_room_num(i+1);
		studyrooms.push_back(a);
	}
	for(int i = 0; i < 3 ; i++){ // seat의 초기화
		for(int j = 0; j < 50 ; j++){
			seat b;
			b.set_floor(i+1);
			seats.push_back(b);
		}
	}
	set_books(); // 초기 resource setting
	input(); // input 받고 output 생성
}
void library :: set_books(){
	int state = 0;
	ifstream input;
	input.open("resource.dat"); // resource.dat 값을 읽는다.
	string temp;
	string type;
	string ssize;
	int size;
	input >> temp;
	input >> temp;
	while(input >> type){
		input >> temp;
		if(type == "Book"){
			book book_temp(temp);
			books.push_back(book_temp); // books vector에 저장
		}
		else if(type == "Magazine"){
			magazine magazine_temp(temp);
			magazines.push_back(magazine_temp); // magazines vector에 저장
		}
		else if(type == "E-book"){ // E-books vector에 저장
			int i = 0;
			while(temp.at(i) != ']'){ // size 분리
				if(temp.at(i)=='[') state = 1;
				else if(state == 1){
					ssize.push_back(temp.at(i));
				}
				i++;
			}
			while(temp.back() != '['){
				temp.pop_back();
			}
			temp.pop_back();
			e_book e_book_temp(temp);
			e_books.push_back(e_book_temp);
			size = stoi(ssize);
			while(ssize.back()) ssize.pop_back();
			e_books.back().set_size(size); // size 저장
			state = 0;
		}
	}
	input.close();
}
void library :: input(){
	ifstream i_dat;
	ifstream s_dat;
	ofstream o_dat;
	int sinput_state = 0;
	int input_state = 0;
	int tempi = 1;
	int cnt = 1;
	int state = 0;
	int k;
	int datetemp=0;
	string date, resource_type, resource_name, operation, member_type, member_name;
	string sdate, space_type, space_number, soperation, smember_type, smember_name, number_of_member, time;
	i_dat.open("input.dat");
	s_dat.open("space.dat");
	o_dat.open("output.dat");
	string temp;
	for(int i = 0; i<6 ; i++){ // 가정 첫줄을 무시하기위해서 여섯번 input을 받아준다.
		i_dat >> temp;
		s_dat >> temp;
	}
	s_dat >> temp;
	s_dat >> temp;
	o_dat << "Op_#\tReturn_code\tDescription" << endl; // output file의 첫줄 생성
s_dat >> sdate;
	i_dat >> date;
	datetemp = sday2int(sdate);
	while(true) { // intput data를 한줄씩 받아서 output 생성
		if(day2int(date)>sday2int(sdate)){
			if(sinput_state == 0){
				s_dat >> space_type;
				s_dat >> space_number;
				s_dat >> soperation;
				s_dat >> smember_type;
				s_dat >> smember_name;
				if(soperation == "B"){
					s_dat >> number_of_member;
					s_dat >> time;	
				}
				if(datetemp< sday2int(sdate)){ // 날짜가 바뀌었을 때
					studyrooms.clear();
					seats.clear();
					for(int i = 0; i < 10 ; i++){ // studyroom의 초기화
						studyroom a;
						a.set_room_num(i+1);
						studyrooms.push_back(a);
					}
					for(int i = 0; i < 3 ; i++){ // seat의 초기화
						for(int j = 0; j < 50 ; j++){
							seat b;
							b.set_floor(i+1);
							seats.push_back(b);
						}
					}
				}
				//만료 좌석 확인
				int i = 0;
				for(auto a : studyrooms){
					if(a.get_status() != 0){
						if(day2time(sdate) > a.get_time() + a.get_borrow_time()){
							a.set_user("");
							a.set_time(0);
							a.set_status(0);
							a.set_borrow_time(0);
							studyrooms.push_back(a);
							studyrooms.erase(studyrooms.begin() + i);
						}
						i++;	
					}
				}
				for(auto a: seats){
					if(a.get_status() != 0){
						if(day2time(sdate) > a.get_time() + a.get_borrow_time()){
							a.set_user("");
							a.set_time(0);
							a.set_status(0);
							a.set_borrow_time(0);
							seats.push_back(a);
							seats.erase(seats.begin() + i);
						}
						i++;
					}
				}
				// 오래 비운 자리 자동 반납
				i = 0;
				for(auto a : studyrooms){
					if(a.get_status() == 2){
						if(day2time(sdate) > a.get_come_time()){
							a.set_user("");
							a.set_time(0);
							a.set_status(0);
							a.set_borrow_time(0);
							a.set_come_time(0);
							studyrooms.push_back(a);
							studyrooms.erase(studyrooms.begin() + i);
						}
						i++;	
					}
				}
				for(auto a: seats){
					if(a.get_status() == 2){
						if(day2time(sdate) > a.get_come_time()){
							a.set_user("");
							a.set_time(0);
							a.set_status(0);
							a.set_borrow_time(0);
							a.set_come_time(0);
							seats.push_back(a);
							seats.erase(seats.begin() + i);
						}
						i++;
					}
				}
				try{
					if(sday2int(sdate)<sday2int("2010/01/01/00")) throw 1;
					else if(space_type != "StudyRoom" && space_type != "Seat") throw 2;
					else if(soperation !="B" && soperation != "R" && soperation != "E" && soperation !="C") throw 3;
					else if(smember_type != "Undergraduate" && smember_type != "Graduate" && smember_type != "Faculty") throw 4;
					else if(isinnum(smember_name)) throw 5;
					else if(time.at(0)=='-') throw 6;
					else{
						tempi = set_sdata(sdate, space_type, space_number, soperation, smember_type, smember_name, number_of_member, time);
						soutput(cnt,tempi);
					}
				}
				catch(int a){
					char c;
						while(s_dat.get(c)){
							if(c == '\n') break;
						}
					ofstream out;
					out.open("output.dat", ios::app);
					out << cnt << "\t" << "-1" ;
					if(a == 1) out << "\tDate out of range" << endl;
					if(a == 2){
			
						out << "\tNon-exist space type" << endl;
					}
					if(a == 3) out << "\tNon-exist operation" << endl;
					if(a == 4) out << "\tNon-exist member type" << endl;
					if(a == 5) out << "\tMember name with numbers" << endl;
					if(a == 6) out << "\tNegative time" << endl;
					out.close();
				}	
				cnt++;
				datetemp = sday2int(sdate);
				if(!(s_dat >> sdate)){
					sdate = "9999/99/99/99";
					sinput_state = 1;
				}
			}

		}
		else{
			if(input_state == 0){
				i_dat >> resource_type;
				i_dat >> resource_name;
				i_dat >> operation;
				i_dat >> member_type;
				i_dat >> member_name;
				tempi = set_data(date, resource_type, resource_name, operation, member_type, member_name); // set_data를 이용해서 return_code값을 받는다.
				output(cnt,tempi); // output을 이용해서 return_code에 따라 output file 생성
				cnt++;	
				if(!(i_dat >> date)){
					input_state = 1;
					date = "99/99/99";
				}
			}
			
		}
		if((input_state + sinput_state) == 2) {
			break;
		}
	}
	i_dat.close();
	s_dat.close();
	o_dat.close();// file을 닫는다.
}
int library :: set_data(string date, string resource_type, string resource_name, string operation, string member_type, string member_name){
	int state;
	string temp;
	string magazine_day;
	int i = 0;
	state = 0;
	int capacity2 = 0;
	if(resource_type == "E-book"){ // E-book의 자동반납
		if(member_type == "Undergraduate"){
			for (auto a : undergraduates) {
				if(a.get_name() == member_name) {
					if(a.search_book_name(resource_name) && day2int(a.get_day(resource_name)) + 13 < day2int(date)){
						a.erase_day(resource_name);
						a.set_ban(false);
						a.set_ban_day("");
						a.erase_book_name(resource_name);
						for(auto b : e_books){
							if(b.get_name() == resource_name){
								capacity2 = b.get_size();
							}
						}
						capacity2 = a.get_capacity() - capacity2;
						a.set_capacity(capacity2);		
						undergraduates.push_back(a);
						undergraduates.erase(undergraduates.begin() + i);
					}
				}
				i++;
			}
		}
		else if(member_type == "Graduate"){
			for (auto a : graduates) {
				if(a.get_name() == member_name) {
					if(a.search_book_name(resource_name) && day2int(a.get_day(resource_name)) + 29 < day2int(date)){
						a.erase_day(resource_name);
						a.set_ban(false);
						a.set_ban_day("");
						a.erase_book_name(resource_name);
						for(auto b : e_books){
							if(b.get_name() == resource_name){
								capacity2 = b.get_size();
							}
						}
						capacity2 = a.get_capacity() - capacity2;
						a.set_capacity(capacity2);		
						graduates.push_back(a);
						graduates.erase(graduates.begin() + i);
					}
				}
				i++;
			}
		}
		else if(member_type == "Faculty"){
			for (auto a : faculties) {
				if(a.get_name() == member_name) {
					if(a.search_book_name(resource_name) && day2int(a.get_day(resource_name)) + 29 < day2int(date)){
						a.erase_day(resource_name);
						a.set_ban(false);
						a.set_ban_day("");
						a.erase_book_name(resource_name);
						for(auto b : e_books){
							if(b.get_name() == resource_name){
								capacity2 = b.get_size();
							}
						}
						capacity2 = a.get_capacity() - capacity2;
						a.set_capacity(capacity2);		
						faculties.push_back(a);
						faculties.erase(faculties.begin() + i);						
					}
				}
				i++;
			}
		}
	}
	i = 0;
	if(operation == "B" && resource_type == "Magazine"){ // 유효한 magazine을 추가 
		int k = 0;
		while(resource_name.at(k) != ']'){ // 날짜 분리
			if(resource_name.at(k)=='[') state = 1;
			else if(state == 1){
				magazine_day.push_back(resource_name.at(k));
			}
			k++;
		}
		magazine_day = magazine_day + "/00";
		if(day2int(date) - 360 < day2int(magazine_day) && day2int(date)> day2int(magazine_day)){
			magazine magazine_temp(resource_name);
			magazines.push_back(magazine_temp);	
		}
		else{
			return 1;
		}
	}
	state = 0;
	if(resource_type == "Book"){
		for(auto a : books){ // book이 vector에 없는 경우
			if(a.get_name() == resource_name) state = 1;
		}
	}
	else if(resource_type == "Magazine"){
		for(auto a : magazines){ // magazine이 vector에 없는 경우
			if(a.get_name() == resource_name) state = 1;
		}
	}
	else if(resource_type == "E-book"){
		for(auto a : e_books){ // E-book이 vector에 없는 경우
			if(a.get_name() == resource_name) state = 1;
		}
	}
	if(state == 0){
		return 1;
	}
	
	if(operation == "B"){ // borrow case
		state = 0;
		if(member_type == "Undergraduate"){
			for(auto a : undergraduates){
				if(a.get_name() == member_name && resource_type != "E-book"){
					if(a.get_book_num() > 0){
						return 2 + 100; // 학부생은 1권만 빌릴 수 있으므로 book_num이 1이면 빌릴 수 없다.
					}
				}
			}
			for(auto a: undergraduates){
				if(a.get_name() == member_name){
					if(a.search_book_name(resource_name)){
						return 4 + day2int(a.get_day(resource_name))*100; // 이미 빌린 책인 case
					}
				}
			}	
		}
		else if(member_type == "Graduate"){
			for(auto a : graduates){
				if(a.get_name() == member_name && resource_type != "E-book"){
					if(a.get_book_num() > 4){
						return 2 + 500; // 대학원생은 5권만 빌릴 수 있으므로 book_num이 5이면 빌릴 수 없다.
					}
				}
			}
			for(auto a: graduates){
				if(a.get_name() == member_name){
					if(a.search_book_name(resource_name)){
						return 4 + day2int(a.get_day(resource_name))*100; // 이미 빌린 책인 case
					}
				}
			}	
		}
		else if(member_type == "Faculty"){
			for(auto a : faculties){
				if(a.get_name() == member_name && resource_type != "E-book"){
					if(a.get_book_num() > 9){
						return 2 + 1000; // 교직원은 10권만 빌릴 수 있으므로 book_num이 10이면 빌릴 수 없다.
					}
				}
			}
			for(auto a: faculties){
				if(a.get_name() == member_name){
					if(a.search_book_name(resource_name)){
						return 4 + day2int(a.get_day(resource_name))*100; // 이미 빌린 책인 case
					}
				}
			}	
		}
		if(resource_type == "Book"){
			for(auto a : books){
				if(a.get_name() == resource_name){
					if(a.get_member() != member_name && a.get_member() != ""){
						return 5 + day2int(a.get_day_return())*100; // 책이 다른 사람에게 이미 빌려진 case
					}
				}
			}
		}
		else if(resource_type == "Magazine"){
			for(auto a : magazines){
				if(a.get_name() == resource_name){
					if(a.get_member() != member_name && a.get_member() != ""){
						return 5 + day2int(a.get_day_return())*100; // 책이 다른 사람에게 이미 빌려진 case
					}
				}
			}
		}
		if(member_type == "Undergraduate"){
			for(auto a : undergraduates){
				if(a.get_name() == member_name){
					if(a.get_ban() == true && day2int(a.get_ban_day()) >= day2int(date)){
						return 6 + day2int(a.get_ban_day())*100; // 책 대여가 금지된 case
					}
				}
			}
		}
		else if(member_type == "Graduate"){
			for(auto a : graduates){
				if(a.get_name() == member_name){
					if(a.get_ban() == true && day2int(a.get_ban_day()) >= day2int(date)){
						return 6 + day2int(a.get_ban_day())*100; // 책 대여가 금지된 case
					}
				}
			}
		}
		else if(member_type == "Faculty"){
			for(auto a : faculties){
				if(a.get_name() == member_name){
					if(a.get_ban() == true && day2int(a.get_ban_day()) >= day2int(date)){
						return 6 + day2int(a.get_ban_day())*100; // 책 대여가 금지된 case
					}
				}
			}
		}
		int capacity= 0;
		if(resource_type =="E-book"){ // capacity를 초과한 경우
			if(member_type == "Undergraduate"){
				for(auto a : undergraduates){
					if(a.get_name() == member_name){
						for(auto b : e_books){
							if(b.get_name() == resource_name){
								capacity = a.get_capacity();
								if(b.get_size() + a.get_capacity() > 100) return 15;
							}
						}
					}
				}
			}
			else if(member_type == "Graduate"){
				for(auto a : graduates){
					if(a.get_name() == member_name){
						for(auto b : e_books){
							if(b.get_name() == resource_name){
								capacity = a.get_capacity();
								if(b.get_size() + a.get_capacity() > 500) return 15;
							}
						}
					}
				}
			}
			else if(member_type == "Faculty"){
				for(auto a : faculties){
					if(a.get_name() == member_name){
						for(auto b : e_books){
							if(b.get_name() == resource_name){
								capacity = a.get_capacity();
								if(b.get_size() + a.get_capacity() > 1000) return 15;
							}
						}
					}
				}
			}
		}
		if(member_type == "Undergraduate"){
			for(auto a : undergraduates){
				if(a.get_name() == member_name){
					for(int l = 0; l < a.get_book_num(); l++){
						if(day2int(a.get_dayi(l))+13 < day2int(date)){ // 연체되어 대여 금지 시켜야 하는 경우
							return 16; 
						}
					}
					
				}
			}
		}
		else if(member_type == "Graduate"){
			for(auto a : graduates){
				if(a.get_name() == member_name){
					for(int l = 0; l < a.get_book_num(); l++){
						if(day2int(a.get_dayi(l))+29 < day2int(date)){ // 연체되어 대여 금지 시켜야 하는 경우
							return 16; 
						}
					}
					
				}
			}
		}
		else if(member_type == "Faculty"){
			for(auto a : faculties){
				if(a.get_name() == member_name){
					for(int l = 0; l < a.get_book_num(); l++){
						if(day2int(a.get_dayi(l))+29 < day2int(date)){ // 연체되어 대여 금지 시켜야 하는 경우
							return 16; 
						}
					}
					
				}
			}
		}
		// 이외의 경우로 빌릴 수 있는 경우
		if(member_type == "Undergraduate"){
			i = 0;
			for(auto a :undergraduates){
				if(a.get_name() == member_name){ // 등록된 학생의 경우
					if(resource_type == "E-book"){
						capacity = capacity + a.get_capacity();
						a.set_capacity(capacity);
					}
					a.set_day(date);
					a.set_ban(false);
					a.set_ban_day("");
					a.set_book_name(resource_name); // 빌려간 resource의 이름을 입력
					if(resource_type != "E-book") a.set_book_num(a.get_book_num()+1); // 빌린 책의 수를 늘려준다.
					undergraduates.push_back(a);
					undergraduates.erase(undergraduates.begin()+i);
					state = 1;
				}
				i++;
			}
			if(state == 0){ // 등록되지 않은 학생의 경우
				undergraduate b(member_name);
				if(resource_type == "E-book"){
					b.set_capacity(capacity);
				}
				b.set_day(date);
				b.set_ban(false);
				b.set_ban_day("");
				b.set_book_name(resource_name);
				if(resource_type != "E-book") b.set_book_num(1);
				undergraduates.push_back(b);// 등록시킨다.
			}
		}
		else if(member_type == "Graduate"){
			i = 0;
			for(auto a :graduates){
				if(a.get_name() == member_name){ // 등록된 학생의 경우
					if(resource_type == "E-book"){
						capacity = capacity + a.get_capacity();
						a.set_capacity(capacity);
					}
					a.set_day(date);
					a.set_ban(false);
					a.set_ban_day("");
					a.set_book_name(resource_name); // 빌려간 resource의 이름을 입력
					if(resource_type != "E-book") a.set_book_num(a.get_book_num()+1); // 빌린 책의 수를 늘려준다.
					graduates.push_back(a);
					graduates.erase(graduates.begin()+i);
					state = 1;
				}
				i++;
			}
			if(state == 0){ // 등록되지 않은 학생의 경우
				graduate b(member_name);
				if(resource_type == "E-book"){
					b.set_capacity(capacity);
				}
				b.set_day(date);
				b.set_ban(false);
				b.set_ban_day("");
				b.set_book_name(resource_name);
				if(resource_type != "E-book") b.set_book_num(1);
				graduates.push_back(b);// 등록시킨다.
			}
		}
		else if(member_type == "Faculty"){
			i = 0;
			for(auto a : faculties){
				if(a.get_name() == member_name){ // 등록된 학생의 경우
					if(resource_type == "E-book"){
						capacity = capacity + a.get_capacity();
						a.set_capacity(capacity);
					}
					a.set_day(date);
					a.set_ban(false);
					a.set_ban_day("");
					a.set_book_name(resource_name); // 빌려간 resource의 이름을 입력
					if(resource_type != "E-book") a.set_book_num(a.get_book_num()+1); // 빌린 책의 수를 늘려준다.
					faculties.push_back(a);
					faculties.erase(faculties.begin()+i);
					state = 1;
				}
				i++;
			}
			if(state == 0){ // 등록되지 않은 학생의 경우
				faculty b(member_name);
				if(resource_type == "E-book"){
					b.set_capacity(capacity);
				}
				b.set_day(date);
				b.set_ban(false);
				b.set_ban_day("");
				b.set_book_name(resource_name);
				if(resource_type != "E-book") b.set_book_num(1);
				faculties.push_back(b);// 등록시킨다.
			}
		}
		
		
		i = 0;
		if(resource_type == "Book"){
			for(auto a : books){
				if(a.get_name()==resource_name){ // 해당 resource에 대해서 정보를 입력한다.
					a.set_member(member_name);
					a.set_day_borrow(date);
					if(member_type == "Undergraduate") a.set_day_return(int2day(day2int(date)+13));
					else a.set_day_return(int2day(day2int(date)+29));
					books.push_back(a);
					books.erase(books.begin()+i);
				}
				i++;
			}
		}
		else if(resource_type == "Magazine"){
			for(auto a : magazines){
				if(a.get_name()==resource_name){ // 해당 resource에 대해서 정보를 입력한다.
					magazine x(member_name);
					x.set_day_borrow(date);
					if(member_type == "Undergraduate") x.set_day_return(int2day(day2int(date)+13));
					else x.set_day_return(int2day(day2int(date)+29));
					magazines.push_back(x);
				}
			}
		}
		else if(resource_type == "E-book"){
			for(auto a : e_books){
				if(a.get_name()==resource_name){ // 해당 resource에 대해서 정보를 입력한다.
					a.set_member(member_name);
					a.set_day_borrow(date);
					if(member_type == "Undergraduate") a.set_day_return(int2day(day2int(date)+13));
					else a.set_day_return(int2day(day2int(date)+29));
					e_books.push_back(a);
					e_books.erase(e_books.begin()+i);
				}
				i++;
			}
		}
		
		return 0;
	}
	else if(operation == "R"){ //return case
		state = 0;
		
		if(member_type == "Undergraduate"){
			for(auto a : undergraduates){
				if(a.get_name() == member_name){
					state = 1;
					if(!a.search_book_name(resource_name)){ // 빌려간 책이 아닌 경우
						return 3;
					}
				}
			}
		}
		else if(member_type == "Graduate"){
			for(auto a : graduates){
				if(a.get_name() == member_name){
					state = 1;
					if(!a.search_book_name(resource_name)){ // 빌려간 책이 아닌 경우
						return 3;
					}
				}
			}
		}
		else if(member_type == "Faculty"){
			for(auto a : faculties){
				if(a.get_name() == member_name){
					state = 1;
					if(!a.search_book_name(resource_name)){ // 빌려간 책이 아닌 경우
						return 3;
					}
				}
			}
		}
		
		if(state == 0){ // 등록되지 않은 학생이므로 빌려간 적이 없다.
			return 3;
		}
		if(resource_type != "E-book"){
			if(member_type == "Undergraduate"){
				for(auto a : undergraduates){
					if(a.get_name() == member_name){
						if(day2int(a.get_day(resource_name))+13 < day2int(date)){ // 연체되어 대여 금지 시켜야 하는 경우
							a.set_ban_day(int2day(2*day2int(date) - day2int(a.get_day(resource_name))-13)); // ban_day등의 정보를 저장한다.
							a.set_day("");
							a.set_ban(true);
							a.set_book_name("");
							a.set_book_num(a.get_book_num()-1);
							undergraduates.push_back(a);
							undergraduates.erase(undergraduates.begin()+i);
							i = 0;
							if(resource_type == "Book"){
								for (auto a : books){ // 책이 돌아왔다는 정보를 입력한다.
									if(a.get_name() == resource_name){
										a.set_member("");
										a.set_day_borrow("");
										a.set_day_return("");
										books.push_back(a);
										books.erase(books.begin()+i);
									}
									i++;
								}
							}
							else if(resource_type == "Magazine"){
								for (auto a : magazines){ // 책이 돌아왔다는 정보를 입력한다.
									if(a.get_name() == resource_name){
										a.set_member("");
										a.set_day_borrow("");
										a.set_day_return("");
										magazines.push_back(a);
										magazines.erase(magazines.begin()+i);
									}
									i++;
								}
							}
							return 7 + day2int(a.get_ban_day())*100;
						}
					}
				}
			}
			else if(member_type == "Graduate"){
				for(auto a : graduates){
					if(a.get_name() == member_name){
						if(day2int(a.get_day(resource_name))+29 < day2int(date)){ // 연체되어 대여 금지 시켜야 하는 경우
							a.set_ban_day(int2day(2*day2int(date) - day2int(a.get_day(resource_name))-29)); // ban_day등의 정보를 저장한다.
							a.set_day("");
							a.set_ban(true);
							a.set_book_name("");
							a.set_book_num(a.get_book_num()-1);
							graduates.push_back(a);
							graduates.erase(graduates.begin()+i);
							i = 0;
							if(resource_type == "Book"){
								for (auto a : books){ // 책이 돌아왔다는 정보를 입력한다.
									if(a.get_name() == resource_name){
										a.set_member("");
										a.set_day_borrow("");
										a.set_day_return("");
										books.push_back(a);
										books.erase(books.begin()+i);
									}
									i++;
								}
							}
							else if(resource_type == "Magazine"){
								for (auto a : magazines){ // 책이 돌아왔다는 정보를 입력한다.
									if(a.get_name() == resource_name){
										a.set_member("");
										a.set_day_borrow("");
										a.set_day_return("");
										magazines.push_back(a);
										magazines.erase(magazines.begin()+i);
									}
									i++;
								}
							}
							return 7 + day2int(a.get_ban_day())*100;
						}
					}
				}
			}
			else if(member_type == "Faculty"){
				for(auto a : faculties){
					if(a.get_name() == member_name){
						if(day2int(a.get_day(resource_name))+29 < day2int(date)){ // 연체되어 대여 금지 시켜야 하는 경우
							a.set_ban_day(int2day(2*day2int(date) - day2int(a.get_day(resource_name))-29)); // ban_day등의 정보를 저장한다.
							a.set_day("");
							a.set_ban(true);
							a.set_book_name("");
							a.set_book_num(a.get_book_num()-1);
							faculties.push_back(a);
							faculties.erase(faculties.begin()+i);
							i = 0;
							if(resource_type == "Book"){
								for (auto a : books){ // 책이 돌아왔다는 정보를 입력한다.
									if(a.get_name() == resource_name){
										a.set_member("");
										a.set_day_borrow("");
										a.set_day_return("");
										books.push_back(a);
										books.erase(books.begin()+i);
									}
									i++;
								}
							}
							else if(resource_type == "Magazine"){
								for (auto a : magazines){ // 책이 돌아왔다는 정보를 입력한다.
									if(a.get_name() == resource_name){
										a.set_member("");
										a.set_day_borrow("");
										a.set_day_return("");
										magazines.push_back(a);
										magazines.erase(magazines.begin()+i);
									}
									i++;
								}
							}
							return 7 + day2int(a.get_ban_day())*100;
						}
					}
				}	
			}	
		}
		
		
		// 정상적으로 반납하는 경우
		i = 0;
		int capacity = 0;
		
		if(member_type == "Undergraduate"){
			for (auto a : undergraduates) {
				if(a.get_name() == member_name) {
					a.erase_day(resource_name);
					a.set_ban(false);
					a.set_ban_day("");
					a.erase_book_name(resource_name);
					if(resource_type != "E-book") a.set_book_num(a.get_book_num()-1);
					else{
						for(auto b : e_books){
							if(b.get_name() == resource_name){
								capacity = b.get_size();
							}
						}
						capacity = a.get_capacity() - capacity;
						a.set_capacity(capacity);
					}
					undergraduates.push_back(a);
					undergraduates.erase(undergraduates.begin() + i);
				}
				i++;
			}
		}
		else if(member_type == "Graduate"){
			
			for (auto a : graduates) {
				if(a.get_name() == member_name) {
					a.erase_day(resource_name);
					a.set_ban(false);
					a.set_ban_day("");
					a.erase_book_name(resource_name);
					if(resource_type != "E-book") a.set_book_num(a.get_book_num()-1);
					else{
						for(auto b : e_books){
							if(b.get_name() == resource_name){
								capacity = b.get_size();
							}
						}
						capacity = a.get_capacity() - capacity;
						a.set_capacity(capacity);
					}
					graduates.push_back(a);
					graduates.erase(graduates.begin() + i);
				}
				i++;
			}
		}
		else if(member_type == "Faculty"){
			for (auto a : faculties) {
				if(a.get_name() == member_name) {
					a.erase_day(resource_name);
					a.set_ban(false);
					a.set_ban_day("");
					a.erase_book_name(resource_name);
					if(resource_type != "E-book") a.set_book_num(a.get_book_num()-1);
					else{
						for(auto b : e_books){
							if(b.get_name() == resource_name){
								capacity = b.get_size();
							}
						}
						capacity = a.get_capacity() - capacity;
						a.set_capacity(capacity);
					}
					faculties.push_back(a);
					faculties.erase(faculties.begin() + i);
				}
				i++;
			}
		}
		
		i = 0;
		if(resource_type == "Book"){
			for (auto a : books) {
				if(a.get_name() == resource_name) {
					a.set_member("");
					a.set_day_borrow("");
					a.set_day_return("");
					books.push_back(a);
					books.erase(books.begin() + i);
				} 
				i++;
			}
			return 0;
		}
		else if(resource_type == "Magazine"){
			for (auto a : magazines) {
				if(a.get_name() == resource_name) {
					a.set_member("");
					a.set_day_borrow("");
					a.set_day_return("");
					magazines.push_back(a);
					magazines.erase(magazines.begin() + i);
				} 
				i++;
			}
			return 0;
		}
		else if(resource_type == "E-book"){
			for (auto a : e_books) {
				if(a.get_name() == resource_name) {
					a.set_member("");
					a.set_day_borrow("");
					a.set_day_return("");
					e_books.push_back(a);
					e_books.erase(e_books.begin() + i);
				} 
				i++;
			}
			return 0;
		}

	}
}

void library :: output(int operation_num, int return_code){ // return code와 함께 output에 날짜가 출력되어야 하는경우 해당되는 날짜에 10을 곱한값을 더해서 set_data에서 return된다.
	ofstream out;
	out.open("output.dat", ios::app);
	string temp;
	if(return_code == 0) out << operation_num << "\t" << return_code << "\tSuccess." << endl;
	else if(return_code == 1) out << operation_num << "\t" << return_code << "\tNon exist resource." << endl;
	else if(return_code%100 == 2) out << operation_num << "\t" << return_code%100 << "\tExceeds your possible number of borrow. Possible # of borrows: " << return_code/100 << endl;
	else if(return_code == 3) out << operation_num << "\t" << return_code << "\tYou did not borrow this book."<< endl;
	else if(return_code%100 == 4) out << operation_num << "\t" << return_code%100 << "\tYou already borrowed this book at " <<int2day(return_code/100)<< endl; // %10을 통해 1만을 return code로 취하고 출력은 /10을 이용해서 날짜를 얻는다.
	else if(return_code%100 == 5) out << operation_num << "\t" << return_code%100 << "\tOther member already borrowed this book. This book will be returned at " << int2day(return_code/100) << endl;
	else if(return_code%100 == 6) out << operation_num << "\t" << return_code%100 << "\tRestricted member until " << int2day(return_code/100) << endl;
	else if(return_code%100 == 7) out << operation_num << "\t" << return_code%100 << "\tDelayed return. You'll be restricted until " << int2day(return_code/100) << endl;
	else if(return_code == 15) out << operation_num << "\t" << return_code << "\tExceeds your storage capacity." << endl;
	else if(return_code == 16) out << operation_num << "\t" << return_code << "\tPreviously borrowed books are overdue, so borrow is limited." << endl;
	out.close();
}

int library :: day2int(string day){
	string y, m, d;
	y = day[0];
	y = y + day[1];
	m = day[3];
	m = m + day[4];
	d = day[6];
	d = d + day[7];
	return stoi(y) * 360 + (stoi(m)-1)*30 + (stoi(d)-1); // string으로 받은 날짜를 "/"를 제외한 수로 변경한 뒤 day단위의 int값으로 환산한다.	
}
string library :: int2day(int day){ // int값인 날짜를 연도, 달, 일로 나누어 string으로 바꾸어 "/"을 포함해서 연결한뒤 return한다.
	string y, m, d;
	y = to_string(day/360);
	if(y.length()==1) y = "0" + y;
	m = to_string(((day%360)/30)+1);
	if(m.length()==1) m = "0" + m;
	d = to_string(((day%360)%30+1));
	if(d.length()==1) d = "0" + d;
	return y + "/" + m + "/" + d;	
}

int library :: sday2int(string sday){
	string y, m, d;
	y = sday[2];
	y = y + sday[3];
	m = sday[5];
	m = m + sday[6];
	d = sday[8];
	d = d + sday[9];
	return stoi(y) * 360 + stoi(m)*30 + stoi(d); // string으로 받은 날짜를 "/"를 제외한 수로 변경한 뒤 day단위의 int값으로 환산한다.	
}
string library :: sint2day(int sday){ // int값인 날짜를 연도, 달, 일로 나누어 string으로 바꾸어 "/"을 포함해서 연결한뒤 return한다.
	string y, m, d;
	y = to_string(sday/360);
	if(y.length()==1) y = "0" + y;
	m = to_string((sday%360)/30);
	if(m.length()==1) m = "0" + m;
	d = to_string((sday%360)%30);
	if(d.length()==1) d = "0" + d;
	return "20" + y + "/" + m + "/" + d;	
}
int library :: set_sdata(string sdate, string space_type, string space_number, string soperation, string smember_type, string smember_name, string number_of_member, string time){
	int state = 0;
	if(space_type == "StudyRoom"){
		for(auto a : studyrooms){
			if(a.get_room_num() == stoi(space_number)) state = 1;
		}
		if(state == 0) return 8;
	}
	if(space_type == "Seat"){
		for(auto a : seats){
			if(a.get_floor() == stoi(space_number)) state = 1;
		}
		if(state == 0) return 8;
	}
	
	state = 1;
	if(space_type == "StudyRoom"){
		if(!(day2time(sdate) > 8 && day2time(sdate) < 19)) return 109;////////////////9
	}
	if(space_type == "Seat"){
		if(space_number == "2"){
			if(!(day2time(sdate) > 8 && day2time(sdate) < 22)) return 209;
		}
		else if(space_number == "3"){
			if(!(day2time(sdate) > 8 && day2time(sdate) < 19)) return 309;
		}
	}
	if(soperation != "B"){
		if(space_type == "StudyRoom"){
			for(auto a : studyrooms){
				if(smember_name == a.get_user() && stoi(space_number) == a.get_room_num()) state = 1;
			}
		}
		else if(space_type == "Seat"){
			for(auto a : seats){
				if(smember_name == a.get_user() && stoi(space_number) == a.get_floor()) state = 1;
			}
		}
		if(state == 1) return 10;
	}
	
	if(soperation == "B"){
		if(space_type == "StudyRoom"){
			for(auto a : studyrooms){
				if(smember_name == a.get_user()) return 11;
			}
		}
		else if(space_type == "Seat"){
			for(auto a : seats){
				if(smember_name == a.get_user()) return 11;
			}
		}
	}
	if(space_type == "StudyRoom"){
		if(stoi(number_of_member)>6) return 12;
	}
	else if(space_type == "Seat"){
		if(stoi(number_of_member) != 1) return 12;
	}
	if(soperation == "B"){
		if(stoi(time) > 3) return 13;
	}
	int mintime = 24;
	int i = 0;
	state = 0;
	if(soperation == "B"){
		if(space_type == "StudyRoom"){
			for(auto a : studyrooms){
				if(a.get_status()==0) state = 1;
				else if(a.get_status() == 1){
					if(mintime > 3 + a.get_time() - day2time(sdate)) mintime =  3 + a.get_time() - day2time(sdate);
				}
			}
			if(state == 0){
				if(mintime + day2time(sdate) > 18) return 14 + 1800;
			 	else return 14 + (mintime + day2time(sdate))*100;
			}
		}
		else if(space_type == "Seat"){
			if(space_number == "1"){
				for(auto a : seats){
					if(a.get_floor() == 1){
						if(a.get_status()==0) state = 1;
						else if(a.get_status() == 1){
							if(mintime > 3 + a.get_time() - day2time(sdate)) mintime =  3 + a.get_time() - day2time(sdate);
						}
					}
				}
				if(state == 0){
					return 14 + (mintime + day2time(sdate))*100;
				}
			}
			else if(space_number == "2"){
				for(auto a : seats){
					if(a.get_floor() == 2){
						if(a.get_status()==0) state = 1;
						else if(a.get_status() == 1){
							if(mintime > 3 + a.get_time() - day2time(sdate)) mintime =  3 + a.get_time() - day2time(sdate);
						}
					}
				}
				if(state == 0){
					if(mintime + day2time(sdate) > 21) return 14 + 2100;
					else return 14 + (mintime + day2time(sdate))*100;
				}	
			}
			else if(space_number == "3"){
				for(auto a : seats){
					if(a.get_floor() == 3){
						if(a.get_status()==0) state = 1;
						else if(a.get_status() == 1){
							if(mintime > 3 + a.get_time() - day2time(sdate)) mintime =  3 + a.get_time() - day2time(sdate);
						}
					}
				}
				if(state == 0){
					if(mintime + day2time(sdate) > 18) return 14 + 1800;
					else return 14 + (mintime + day2time(sdate))*100;
				}	
			}
		}
	}
	i = 0;
	if(soperation == "B"){
		if(space_type == "StudyRoom"){
			for(auto a : studyrooms){
				if(a.get_status() == 0){
					a.set_user(smember_name);
					a.set_time(day2time(sdate));
					a.set_status(1);
					a.set_room_num(stoi(space_number));
					a.set_borrow_time(stoi(time));
					studyrooms.push_back(a);
					studyrooms.erase(studyrooms.begin() + i);
					return 0;
				}
				i++;
			}
		}
		else if(space_type == "Seat"){
			for(auto a : seats){
				if(a.get_status() == 0){
					a.set_user(smember_name);
					a.set_time(day2time(sdate));
					a.set_status(1);
					a.set_floor(stoi(space_number));
					a.set_borrow_time(stoi(time));
					seats.push_back(a);
					seats.erase(seats.begin() + i);
					return 0;
				}
				i++;
			}
		}
	}
	else if(soperation == "R"){
		if(space_type == "StudyRoom"){
			for(auto a : studyrooms){
				if(a.get_user() == smember_name){
					a.set_user("");
					a.set_time(0);
					a.set_status(0);
					a.set_room_num(stoi(space_number));
					a.set_borrow_time(0);
					studyrooms.push_back(a);
					studyrooms.erase(studyrooms.begin() + i);
					return 0;
				}
				i++;
			}
		}
		else if(space_type == "Seat"){
			for(auto a : seats){
				if(a.get_user() == smember_name){
					a.set_user("");
					a.set_time(0);
					a.set_status(0);
					a.set_floor(stoi(space_number));
					a.set_borrow_time(0);
					seats.push_back(a);
					seats.erase(seats.begin() + i);
					return 0;
				}
				i++;
			}
		}	
	}
	else if(soperation == "E"){
		if(space_type == "StudyRoom"){
			for(auto a : studyrooms){
				if(a.get_user() == smember_name){
					a.set_status(2);
					studyrooms.push_back(a);
					studyrooms.erase(studyrooms.begin() + i);
					return 0;
				}
				i++;
			}
		}
		else if(space_type == "Seat"){
			for(auto a : seats){
				if(a.get_user() == smember_name){
					a.set_status(2);
					a.set_come_time(day2time(sdate)+1);
					seats.push_back(a);
					seats.erase(seats.begin() + i);
					return 0;
				}
				i++;
			}
		}		
	}
	else if(soperation == "C"){
		if(space_type == "StudyRoom"){
			for(auto a : studyrooms){
				if(a.get_user() == smember_name){
					a.set_status(1);
					studyrooms.push_back(a);
					studyrooms.erase(studyrooms.begin() + i);
					return 0;
				}
				i++;
			}
		}
		else if(space_type == "Seat"){
			for(auto a : seats){
				if(a.get_user() == smember_name){
					a.set_status(1);
					a.set_come_time(0);
					seats.push_back(a);
					seats.erase(seats.begin() + i);
					return 0;
				}
				i++;
			}
		}		
	}
	
	
	
}
int library :: day2time(string day){
	string t;
	t = day[11];
	t = t + day[12];
	return stoi(t);
}
void library :: soutput(int soperation_num, int sreturn_code){
	ofstream out;
	out.open("output.dat", ios::app);
	string temp;
	if(sreturn_code == 0) out << soperation_num << "\t" << sreturn_code << "\tSuccess." << endl;
	else if(sreturn_code == 8) out << soperation_num << "\t" << sreturn_code << "\tInvalid space id." << endl;
	else if(sreturn_code%100 == 9){
		if(sreturn_code/100 == 1) temp = "09 to 18.";
		else if(sreturn_code/100 == 2) temp = "09 to 21.";
		else if(sreturn_code/100 == 3) temp = "09 to 18.";
		else temp = " ";
		out << soperation_num << "\t" << sreturn_code%100 << "\tThis space is not available now. Available from "<< temp << endl;
	}
	else if(sreturn_code == 10) out << soperation_num << "\t" << sreturn_code << "\tYou did not borrow this place."<< endl;
	else if(sreturn_code == 11) out << soperation_num << "\t" << sreturn_code << "\tYou already borrow this kind of space" << endl;
	else if(sreturn_code == 12) out << soperation_num << "\t" << sreturn_code << "\tExceed available number." << endl;
	else if(sreturn_code == 13) out << soperation_num << "\t" << sreturn_code << "\tExceed available time."<< endl;
	else if(sreturn_code%100 == 14){
		temp = to_string(sreturn_code/100);
		out << soperation_num << "\t" << sreturn_code%100 << "\tThere is no remain space. this space is avilable after " << temp << "." << endl;
	}
	out.close();
}
bool library :: isinnum(string s){
	for(int i = 48; i < 58; i++){
		if(s.find(i) != -1) return true;
	}
	return false;
}