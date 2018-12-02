#include <iostream>
#include <string>
using namespace std;

class member {
private:
	string name; // member name
public:
	void set_name(string sname);
	string get_name();
};

class undergraduate : public member{
private:
	int book_num; // number of borrowed books
	string book_name;
	string ban_day;
	string day;
	int capacity;
	bool ban;
public:
	undergraduate();
	undergraduate(string sname);
	void set_book_num(int sbook_num);
	int get_book_num();
	void set_book_name(string sbook_name);
	string get_book_name();
	void set_ban_day(string sban_day);
	string get_ban_day();
	void set_day(string sday);
	string get_day();
	void set_capacity(int scapacity);
	int get_capacity();
	void set_ban(bool sban);
	bool get_ban();
};

class graduate : public member{
private:
	int book_num; // number of borrowed books
	vector<string> book_name;
	string ban_day;
	vector<string> day;
	int capacity;
	bool ban;
public:
	graduate();
	graduate(string sname);
	void set_book_num(int sbook_num);
	int get_book_num();
	void set_book_name(string sbook_name);
	void erase_book_name(string sbook_name);
	bool search_book_name(string sbook_name);
	void set_ban_day(string sban_day);
	string get_ban_day();
	void set_day(string sday);
	void erase_day(string sbook_name);
	string get_day(string sbook_name);
	string get_dayi(int i);
	void set_capacity(int scapacity);
	int get_capacity();
	void set_ban(bool sban);
	bool get_ban();
};

class faculty : public member{
private:
	int book_num; // number of borrowed books
	vector<string> book_name;
	string ban_day;
	vector<string> day;
	int capacity;
	bool ban;
public:
	faculty();
	faculty(string sname);
	void set_book_num(int sbook_num);
	int get_book_num();
	void set_book_name(string sbook_name);
	void erase_book_name(string sbook_name);
	bool search_book_name(string sbook_name);
	void set_ban_day(string sban_day);
	string get_ban_day();
	void set_day(string sday);
	void erase_day(string sbook_name);
	string get_day(string sbook_name);
	string get_dayi(int i);
	void set_capacity(int scapacity);
	int get_capacity();
	void set_ban(bool sban);
	bool get_ban();
};