#include <iostream>
#include <string>
#include <vector>
#include "member.h"
using namespace std;

void member :: set_name(string sname){
	name = sname;
}
string member :: get_name(){
	return name;
}


////////////undergraduate/////////
undergraduate :: undergraduate(){
	book_num = 0;
	book_name = "";
	ban_day = "";
	day = "";
	ban = false;
}

undergraduate :: undergraduate(string sname){
	book_num = 0;
	book_name = "";
	ban_day = "";
	day = "";
	ban = false;
	set_name(sname);	
}
void undergraduate :: set_book_num(int sbook_num){
	book_num = sbook_num;
}
int undergraduate :: get_book_num(){
	return book_num;
}
void undergraduate :: set_book_name(string sbook_name){
	book_name = sbook_name;
}
string undergraduate :: get_book_name(){
	return book_name;
}
void undergraduate :: set_ban_day(string sban_day){
	ban_day = sban_day;
}
string undergraduate :: get_ban_day(){
	return ban_day;
}
void undergraduate :: set_day(string sday){
	day = sday;
}
string undergraduate :: get_day(){
	return day;
}
void undergraduate :: set_capacity(int scapacity){
	capacity = scapacity;
}
int undergraduate :: get_capacity(){
	return capacity;
}
void undergraduate :: set_ban(bool sban){
	ban = sban;
}
bool undergraduate :: get_ban(){
	return ban;
}
void undergraduate :: set_e_books(string se_book){
	e_books.push_back(se_book);
}
void undergraduate :: erase_e_books(string se_book){
	for(int i = 0; i < e_books.size() ; i++){
		if(e_books.at(i) == se_book){
			e_books.erase(e_books.begin()+i);
			break;
		}
	}
}


////////////graduate/////////
graduate :: graduate(){
	book_num = 0;
	//book_name = "";
	ban_day = "";
	//day = "";
	ban = false;
}

graduate :: graduate(string sname){
	book_num = 0;
	//book_name = "";
	ban_day = "";
	//day = "";
	ban = false;
	set_name(sname);	
}
void graduate :: set_book_num(int sbook_num){
	book_num = sbook_num;
}
int graduate :: get_book_num(){
	return book_num;
}
void graduate :: set_book_name(string sbook_name){
	book_name.push_back(sbook_name);
}
void graduate :: erase_book_name(string sbook_name){
	for(int i = 0; i < book_name.size() ; i++){
		if(book_name.at(i) == sbook_name){
			book_name.erase(book_name.begin()+i);
			break;
		}
	}
}
bool graduate :: search_book_name(string sbook_name){
	for(auto a : book_name){
		if(a == sbook_name) return true;
	}
	return false;
}
void graduate :: set_ban_day(string sban_day){
	ban_day = sban_day;
}
string graduate :: get_ban_day(){
	return ban_day;
}
void graduate :: set_day(string sday){
	day.push_back(sday);
}
void graduate :: erase_day(string sbook_name){
	int temp;
	for(int i = 0; i < book_num ; i++){
		if(book_name.at(i) == sbook_name){
			 day.erase(book_name.begin()+i);
		}
	}	
}
string graduate :: get_day(string sbook_name){
	for(int i = 0; i < book_name.size() ; i++){
		if(book_name.at(i) == sbook_name){
			return day.at(i);
		}
	}
	return 0;
}
string graduate :: get_dayi(int i){
	return day.at(i);
}
void graduate :: set_capacity(int scapacity){
	capacity = scapacity;
}
int graduate :: get_capacity(){
	return capacity;
}
void graduate :: set_ban(bool sban){
	ban = sban;
}
bool graduate :: get_ban(){
	return ban;
}
void graduate :: set_e_books(string se_book){
	e_books.push_back(se_book);
}
void graduate :: erase_e_books(string se_book){
	for(int i = 0; i < e_books.size() ; i++){
		if(e_books.at(i) == se_book){
			e_books.erase(e_books.begin()+i);
			break;
		}
	}
}

////////////faculty/////////
faculty :: faculty(){
	book_num = 0;
	//book_name = "";
	ban_day = "";
	//day = "";
	ban = false;
}

faculty :: faculty(string sname){
	book_num = 0;
	//book_name = "";
	ban_day = "";
	//day = "";
	ban = false;
	set_name(sname);	
}
void faculty :: set_book_num(int sbook_num){
	book_num = sbook_num;
}
int faculty :: get_book_num(){
	return book_num;
}
void faculty :: set_book_name(string sbook_name){
	book_name.push_back(sbook_name);
}
void faculty :: erase_book_name(string sbook_name){
	for(int i = 0; i < book_name.size() ; i++){
		if(book_name.at(i) == sbook_name){
			book_name.erase(book_name.begin()+i);
			break;
		}
	}
}
bool faculty :: search_book_name(string sbook_name){
	for(auto a : book_name){
		if(a == sbook_name) return true;
	}
	return false;
}
void faculty :: set_ban_day(string sban_day){
	ban_day = sban_day;
}
string faculty :: get_ban_day(){
	return ban_day;
}
void faculty :: set_day(string sday){
	day.push_back(sday);
}
void faculty :: erase_day(string sbook_name){
	int temp;
	for(int i = 0; i < book_name.size() ; i++){
		if(book_name.at(i) == sbook_name){
			 day.erase(book_name.begin()+i);
		}
	}	
}
string faculty :: get_day(string sbook_name){
	for(int i = 0; i < book_num ; i++){
		if(book_name.at(i) == sbook_name){
			return day.at(i);
		}
	}
	return 0;
}
string faculty :: get_dayi(int i){
	return day.at(i);
}
void faculty :: set_capacity(int scapacity){
	capacity = scapacity;
}
int faculty :: get_capacity(){
	return capacity;
}
void faculty :: set_ban(bool sban){
	ban = sban;
}
bool faculty :: get_ban(){
	return ban;
}
void faculty :: set_e_books(string se_book){
	e_books.push_back(se_book);
}
void faculty :: erase_e_books(string se_book){
	for(int i = 0; i < e_books.size() ; i++){
		if(e_books.at(i) == se_book){
			e_books.erase(e_books.begin()+i);
			break;
		}
	}
}

