#pragma once
//BBS 接口
//Author：BearYu
//Time：2016/9/5

#include<string>
#include<vector>
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<ctime>
//#include"post.h"
using namespace std;

//评论
class Comment {
private: 
	float currenttime; //评论时间
	string content; //评论内容
	string author;
public:
	void initialize() { //初始化，设置comment属性
		string content;
		string author;
		cin.ignore();
		cout << "input your comment" << endl;
		fflush(stdin);
		std::getline(std::cin, content);
		//cin >> content;
		
		cin.ignore();
		fflush(stdin);
		cout << "input your username" << endl;
		std::getline(std::cin, author);
		//cin >> author;
		time_t now_time;
		now_time = time(NULL);
		this->currenttime = now_time;
		this->content = content;
		this->author = author;
	};
	friend istream& operator>>(istream& is, Comment& comment) {
		is >> comment.author >> comment.content >> comment.currenttime;
		return is;
	};
	friend ostream& operator<<(ostream& os, Comment& comment) {
		os << comment.author <<" " << comment.content << " " << comment.currenttime;
		return os;
	};

	float get_time() { //获取评论时间
		return this->currenttime;
	};
	string get_content() { //获取评论内容
		return this->content;
	};
	string get_author() {
		return this->author;
	}
	void show_c() { //输出评论内容
		float t = this->currenttime;
		string c = this->content;
		cout << t << " " << c << " " << this->author <<endl;
	};
};

//帖子
class Post {
private:
	string id; //id
	string title; //主题
	string content; //内容
	float currenttime; //发帖时间
	vector<Comment*> comment; //该帖下的评论
public:
	void initialize(/*string& id, string& title, string& content, float time*/) { //初始化，设置post属性		
		string id;
		string title;
		string content;
		string trash;
		//fflush(stdin);
		cin.ignore();
		cout << "input id"<<endl;
		std::getline(std::cin, id);
		
		fflush(stdin);
		cin.ignore();
		cout << "input title"<<endl;
		std::getline(std::cin, title);
		
		cin.ignore();
		cout << "input content" << endl;
		fflush(stdin);
		std::getline(std::cin, content);
		
		time_t now_time;
		now_time = time(NULL);
		this->id = id;
		this->title = title;
		this->content = content;
		this->currenttime = now_time;
	};
	friend istream& operator>>(istream& is, Post& post) {
		is >> post.id >> post.title >> post.content;
		return is;
	};
	friend ostream& operator<<(ostream& os, Post& post) {
		os << post.id << " " << post.title << " " << post.content;
		return os;
	};
	void add_comment(Comment* comment) { //添加评论
		this->comment.push_back(comment);
	};
	void delete_comment(Comment* comment) { //删除评论
		vector<Comment*>::iterator it;
		for (it = (this->comment).begin(); it != (this->comment).end(); ) {
			if (*it == comment) {
				delete *it;
				it = (this->comment).erase(it);
			}
			else {
				++it;
			}
		}
		//this->comment.pop_back();
	};
	void show_d() { //输出帖子内容及评论
		cout << id << " " << title << " " << content << endl;
		for (vector<Comment*>::iterator it = this->comment.begin(); it != this->comment.end(); ++it) {
			(*it)->show_c();
		}
		cout << endl;
	};
	string get_id() { //获取帖子id
		return this->id;
	};
	string get_title() { //获取帖子主题
		return this->title;
	};
	string get_content() { //获取帖子内容
		return this->content;
	};
	float get_time() { //获取发帖时间
		return this->currenttime;
	};
	vector<Comment*> get_comment() { //获取该帖下的评论
		return this->comment;
	};
	Comment* search_comment(string author) {
		vector<Comment*> list = this->comment;
		Comment* ptr = new Comment;
		int cnt = 0;
		for (vector<Comment*>::iterator it = list.begin(); it != list.end(); ++it) {
			if ((*it)->get_author() == author) {
				cnt = 1;
				ptr = *it;
			}
		}
		if (cnt != 0)
			return ptr;
		else
			return nullptr;
	};
};

//版面
class Board {
private:
	string id; //版面id
	vector<Post* > list_post; //版面所含帖子
public:
	void initialize(string id) { //初始化，设置id
		this->id = id;
	};
	string get_id() { //获取版面id
		return this->id;
	};
	vector<Post*> get_list() { //获取该版帖子列表
		return this->list_post;
	};
	void add_post(Post* post) { //增加帖子
		list_post.push_back(post);
	};
	vector<Post*>::iterator search_post(Post* post) { //查找帖子
		vector<Post*> list = this->list_post;
		return find(list.begin(), list.end(), post);
	};
	void delete_post(Post* post) { //删除帖子
		vector<Post*>::iterator it;
		for (it = (this->list_post).begin(); it != (this->list_post).end(); ) {
			if (*it == post) {
				delete *it;
				it = (this->list_post).erase(it);
			}
			else {
				++it;
			}
		}
	};
	Post* search_post2(string id) {
		vector<Post*> list = this->list_post;
		Post* ptr = new Post;
		int cnt = 0;
		for (vector<Post*>::iterator it = list.begin(); it != list.end(); ++it) {
			if ((*it)->get_id() == id) {
				cnt = 1;
				ptr = *it;
			}
		}
		if (cnt != 0)
			return ptr;
		else
			return nullptr;
	};
	void show_p(string post) {
		(this->search_post2(post))->show_d();
		//post->show_d();
	}
	void show_p() { //输出版面下所有帖子
		vector<Post*> list = this->list_post;
		for (vector<Post*>::iterator it = list.begin(); it != list.end(); ++it) {
			(*it)->show_d();
		}
	};
};

//user 基类
class User {
protected:
	string id;       //id
	string username; //用户名
	string password; //密码
	int state;       //状态
public:
	friend istream& operator >> (istream& is, User& user) {
		is >> user.id >> user.username >> user.password >> user.state;
		return is;
	};
	friend ostream& operator << (ostream& os, User& user) {
		os << user.id << " " << user.username << " " << user.password << " " << user.state;
		return os; 
	};
	virtual void initialize(/*string& id, string& username, string& password, int state*/) = 0; //初始化，设置user属性
	virtual void show_info() = 0; //user个人信息

	virtual string get_id() = 0;
	virtual string get_username() = 0;
	virtual string get_password() = 0;
	virtual int get_state() = 0;
	//virtual void show_post() = 0; //显示所有帖子
	virtual void log_in() = 0; //登录;
	virtual void log_out() = 0; //登出	
};

//论坛
class Forum {
private:
	vector<User*> list_user; //用户列表
	vector<Board*> list_board; //版面列表
public:
	vector<Board*> get_board() { //获取论坛版面列表
		return this->list_board;
	};
	void update_board(vector<Board*> list) {
		this->list_board = list;
	};
	vector<User*> get_user() {
		return this->list_user;
	};
	void update_user(vector<User*> list) {
		this->list_user = list;
	};
	void show_bp() { //输出版面及帖子
		vector<Board*> list = this->list_board;
		for (vector<Board*>::iterator it = list.begin(); it != list.end(); it++) {
			(*it)->show_p();
		}
	};
	Board* search_board(string id) {
		vector<Board*> list = this->list_board;
		Board* ptr = new Board;
		int cnt = 0;
		for (vector<Board*>::iterator it = list.begin(); it != list.end(); ++it) {
			if ((*it)->get_id() == id) {
				cnt = 1;
				ptr = *it;
			}
		}
		if (cnt != 0)
			return ptr;
		else
			return nullptr;
	};

/*	User* search_user(string username) {
		vector<User*> list = this->list_user;
		User* ptr = new User;
		int cnt = 0;
		for (vector<User*>::iterator it = list.begin(); it != list.end(); ++it) {
			if ((*it)->get_username() == username) {
				cnt = 1;
				ptr = *it;
			}
		}
		if (cnt != 0)
			return ptr;
		else
			return nullptr;
	};*/
/*	int check_user() {
		string username;
		string password;
		cout << "input your username" << endl;
		cin >> username;
		cout << "password:" << endl;
		cin >> password;
		vector<User*> list = this->list_user;
		int flag = 0;
 		for (int i = 0; i < list.size(); ++i) {
			if (list[i]->get_username() == username && list[i]->get_id() == password) {
				flag = 1;
			}
		}
		return flag;
*/
		//User* user = new User;
		//for(vector<User*>::iterator it = list.begin(); it != list.end() ;++it){
		//	 if((*it)->get_username() == username){
		//	 	user = *it;
		//	 	break;
		//	 }
		//}
		//if((*it)->get_username() == username && (*it)->get_password() == password){
		//	return True;	
		//}
		//else return False;
	//};
};

//普通用户
class Plain_user :public User {
public:
	virtual void initialize(/*string& id, string& username, string& password, int state*/) { //初始化，设置user属性
		string id;
		string username;
		string password;
		fflush(stdin);
		cout << "input your ID" << endl;
		cin >> id;
		cout << "input your username" << endl;
		cin >> username;
		cout << "input your password" << endl;
		cin >> password;
		this->id = id;
		this->username = username;
		this->password = password;
		this->state = 1;
	};
	virtual void show_info() { //user个人信息
		cout << id << " " << username << " " << password << " " << state << endl;
	};
	virtual string get_id() {
		return this->id;
	};
	virtual void set_id(string id) {
		this->id = id;
	};
	virtual string get_username() {
		return this->username;
	};
	virtual void set_username(string name) {
		this->username = name;
	};
	virtual string get_password() {
		return this->password;
	};
	virtual void set_password(string word) {
		this->password = word;
	};
	virtual int get_state() {
		return this->state;
	};
	virtual void set_state(int s) {
		this->state = s;
	};
	//virtual void show_post() = 0; //显示所有帖子

	virtual void log_in() { //登录
		this->state = 1;
	};
	virtual void log_out() { //登出
		this->state = 0;
	};
	void up_post(Board* board, Post* post) { //发帖
		board->add_post(post);
		//vector<Post*> post_list = board->get_list();
	};
	void comment(Post* post, Comment* comment) { //评论
		post->add_comment(comment);
	};
	void show_post(Forum* forum) { //查看所有帖子
		forum->show_bp();
	};
	void delete_post(Post* post, Board* board) { //删除帖子
		board->delete_post(post);
	};
};

//版主
class Monderator :public Plain_user {
public:
	void show_post(Forum* forum) { //查看所有帖子
		forum->show_bp();
		cout << "good";
	};
	void delete_bpost(Post* post) { //删除所管理版面的帖子
		myboard->delete_post(post);
	};
	void set_board(Board* board) {
		myboard = board;
	};
	virtual void  initialize() { //初始化，设置user属性
		string id;
		string username;
		string password;
		fflush(stdin);
		cout << "input your ID" << endl;
		cin >> id;
		cout << "input your username" << endl;
		cin >> username;
		cout << "input your password" << endl;
		cin >> password;
		this->id = id;
		this->username = username;
		this->password = password;
		this->state = state;
	};
	virtual void show_info() { //user个人信息
		cout << id << " " << username << " " << password << " " << state << endl;
	};
	virtual string get_id() {
		return this->id;
	};
	void set_id(string id) {
		this->id = id;
	};
	virtual string get_username() {
		return this->username;
	};
	void set_username(string name) {
		this->username = name;
	};
	virtual string get_password() {
		return this->password;
	};
	void set_password(string word) {
		this->password = word;
	};
	virtual int get_state() {
		return this->state;
	};
	void set_state(int s) {
		this->state = s;
	};
	//virtual void show_post() = 0; //显示所有帖子

	virtual void log_in() { //登录
		this->state = 1;
	};
	virtual void log_out() { //登出
		this->state = 0;
	};
	void up_post(Board* board, Post* post) { //发帖
		board->add_post(post);
		//vector<Post*> post_list = board->get_list();
	};
	void comment(Post* post, Comment* comment) { //评论
		post->add_comment(comment);
	};
	
	void delete_post(Post* post, Board* board) { //删除帖子
		board->delete_post(post);
	};
private:
	Board* myboard;
};

//管理员
class Admin_user :public User {
public:
	void show_post(Forum* forum) { //查看所有帖子
		forum->show_bp();
	};
	void appoint(User* p_user, Board* board, Forum* forum) { //任命撤销版主
		Monderator* new_moderator = new Monderator;
		string id = p_user->get_id();
		string username = p_user->get_username();
		string password = p_user->get_password();
		int state = p_user->get_state();

		new_moderator->set_id(id);
		new_moderator->set_username(username);
		new_moderator->set_password(password);
		new_moderator->set_state(state);
		//new_moderator->username = p_user->username;
		//new_moderator->password = p_user->password;

		vector<User*> list = forum->get_user();
		vector<User*>::iterator it = find(list.begin(), list.end(), p_user);
		new_moderator->set_board(board);
		*it = new_moderator;
		forum->update_user(list);
		//return new_moderator;
	};
	void dismiss(User* p_user, Board* board, Forum* forum) { //任命撤销版主
		Plain_user* new_moderator = new Plain_user;
		string id = p_user->get_id();
		string username = p_user->get_username();
		string password = p_user->get_password();
		int state = p_user->get_state();

		new_moderator->set_id(id);
		new_moderator->set_username(username);
		new_moderator->set_password(password);
		new_moderator->set_state(state);
		//new_moderator->username = p_user->username;
		//new_moderator->password = p_user->password;

		vector<User*> list = forum->get_user();
		vector<User*>::iterator it = find(list.begin(), list.end(), p_user);
		//new_moderator->set_board(board);
		*it = new_moderator;
		forum->update_user(list);
		//return new_moderator;
	};
	virtual void initialize(/*string& id, string& username, string& password, int state*/) { //初始化，设置user属性
		string id;
		string username;
		string password;
		fflush(stdin);
		cout << "input your ID" << endl;
		cin >> id;
		cout << "input your username" << endl;
		cin >> username;
		cout << "input your password" << endl;
		cin >> password;
		this->id = id;
		this->username = username;
		this->password = password;
		this->state = 1;
	};
	virtual void show_info() { //user个人信息
		cout << id << " " << username << " " << password << " " << state << endl;
	};
	virtual void set_id(string id) {
		this->id = id;
	}
	virtual string get_id() {
		return this->id;
	};
	virtual void set_username(string username) {
		this->username = username;
	}
	virtual string get_username() {
		return this->username;
	}
	virtual void set_password(string password) {
		this->password = password;
	};
	virtual string get_password() {
		return this->password;
	};
	virtual void set_state(int state) {
		this->state = state;
	}
	virtual int get_state() {
		return this->state;
	};
	virtual void log_in() { //登录
		this->state = 1;
	};
	virtual void log_out() { //登出
		this->state = 0;
	};
	void up_post(Board* board, Post* post) { //发帖
		board->add_post(post);
		//vector<Post*> post_list = board->get_list();
	};
	void comment(Post* post, Comment* comment) { //评论
		post->add_comment(comment);
	};
	void delete_post(Post* post, Board* board) { //删除帖子
		board->delete_post(post);
	};
};

class Control {
public:
	void initialize(Forum* forum) {
		cout << "Welcome to bbsliver" << endl;
		vector<Board*> list_board;
		for (int i = 0; i < 4; ++i) {
			Board* ini_board = new Board;
			string id;
			std::getline(std::cin, id);
			ini_board->initialize(id);
			list_board.push_back(ini_board);
			//delete ini_board;
		}
		forum->update_board(list_board);
	}
};