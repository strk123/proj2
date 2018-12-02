#include <iostream>
#include "resource.h"
using namespace std;

void resource :: set_name(string sname){
	name = sname;
}
string resource :: get_name(){
	return name;
}


//////////////////book///////////////
book :: book(string smember){
	set_name(smember);
}
void book :: set_member(string smember){
	member = smember;
}
string book :: get_member(){
	return member;
}
void book :: set_day_borrow(string sday_borrow){
	day_borrow = sday_borrow;
}
string book :: get_day_borrow(){
	return day_borrow;
}
void book :: set_day_return(string sday_return){
	day_return = sday_return;
}
string book :: get_day_return(){
	return day_return;
}

//////////////////magazine///////////////
magazine :: magazine(string smember){
	set_name(smember);
}
void magazine :: set_member(string smember){
	member = smember;
}
string magazine :: get_member(){
	return member;
}
void magazine :: set_day_borrow(string sday_borrow){
	day_borrow = sday_borrow;
}
string magazine :: get_day_borrow(){
	return day_borrow;
}
void magazine :: set_day_return(string sday_return){
	day_return = sday_return;
}
string magazine :: get_day_return(){
	return day_return;
}

//////////////////e_book///////////////
e_book :: e_book(string smember){
	set_name(smember);
}
void e_book :: set_member(string smember){
	member = smember;
}
string e_book :: get_member(){
	return member;
}
void e_book :: set_day_borrow(string sday_borrow){
	day_borrow = sday_borrow;
}
string e_book :: get_day_borrow(){
	return day_borrow;
}
void e_book :: set_day_return(string sday_return){
	day_return = sday_return;
}
string e_book :: get_day_return(){
	return day_return;
}
void e_book :: set_size(int ssize){
	size = ssize;
}
int e_book :: get_size(){
	return size;
}