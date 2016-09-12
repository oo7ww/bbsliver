#include <iostream>
#include <ctime>
#include <fstream>
#include"bbsliver.h" 

using namespace std;

void get_start(Forum* forum) {
	vector<Board*> list_board;
	vector<User*> list_user;
	Board* ini_board = new Board;
	string ini_b;
	ifstream user_ifile;
	ifstream post_ifile;
	ifstream comt_ifile;
	ofstream user_ofile;
	ofstream post_ofile;
	ofstream comt_ofile;

	user_ifile.open("user.txt");
	cout << "this is a cut" << endl;

	Plain_user plain; 
	//plain->initialize();
	user_ifile >> plain;
	while (!user_ifile.eof()) {
		user_ifile >> plain;
		cout << plain;
	}

	//list_user.push_back(&plain);

	cout << "this is a cut" << endl;

	Admin_user* adminster = new Admin_user;
	adminster->initialize();
	list_user.push_back(adminster);
	fflush(stdin);

	ini_board->initialize("1024");
	list_board.push_back(ini_board);

	cout << "this is a cut" << endl;

	Monderator* boardhost = new Monderator;
	boardhost->initialize();
	boardhost->set_board(ini_board);
	list_user.push_back(boardhost);

	forum->update_board(list_board);
	forum->update_user(list_user);
}

int main() {
	Forum* forum = new Forum;
	//get_start(forum);

	vector<Board*> list_board;
	vector<User*> list_user;
	vector<Post*> list_post;
	Board* ini_board = new Board;
	string ini_b;
	
	ini_board->initialize("1024");
	//list_board.push_back(ini_board);

	cout << "this is a cut" << endl;
	ifstream user_ifile;
	ifstream post_ifile;
	ifstream comt_ifile;
	ofstream user_ofile;
	ofstream post_ofile;
	ofstream comt_ofile;
	
	
	comt_ifile.open("comment.txt");
	cout << "this is a cut" << endl;

	
	//plain->initialize();
	//user_ifile >> plain;
	
	//载入用户信息
	user_ifile.open("user.txt");
	int file_tag = 0;
	while (!user_ifile.eof()) {
		if (file_tag = 0) {
			Admin_user* admin = new Admin_user;
			user_ifile >> (*admin);
			list_user.push_back(admin);
			cout << admin->get_username() << endl;
		}
		else {
			Plain_user* plain = new Plain_user;
			user_ifile >> (*plain);
			list_user.push_back(plain);     
			cout << plain->get_username() << endl;
		}
	}
	user_ifile.close();

	for (vector<User*>::iterator it = list_user.begin(); it != list_user.end(); ++it) {
		cout << *(*it) << endl;
	}

	//载入帖子信息
	post_ifile.open("post.txt");
	while (!post_ifile.eof()) {
		Post* post = new Post;
		post_ifile >> (*post);
		ini_board->add_post(post);
		//cout << plain->get_username() << endl;
	}
	post_ifile.close();

	list_post = ini_board->get_list();

	//载入评论信息，并关联至对应帖子
	comt_ifile.open("comment.txt");
	while (!comt_ifile.eof()) {
		Comment* comment = new Comment;
		comt_ifile >> (*comment);
		string comment_id = comment->get_author();
		string post_id = comment_id.substr(0, 5);
		Post* post_ptr = new Post;
		post_ptr = ini_board->search_post2(post_id);
		post_ptr->add_comment(comment);
	}
	comt_ifile.close();

	list_board.push_back(ini_board);
	//Plain_user* plain = new Plain_user;
	//plain->initialize();
	//list_user.push_back(plain);

//	cout << "this is a cut" << endl;

//	Admin_user* adminster = new Admin_user;
//	adminster->initialize();
//	list_user.push_back(adminster);
//	fflush(stdin);

/*
	cout << "this is a cut" << endl;

	Monderator* boardhost = new Monderator;
	boardhost->initialize();
	boardhost->set_board(ini_board);
	list_user.push_back(boardhost);
*/	
	forum->update_board(list_board);
	forum->update_user(list_user);

	string knock;
	cin >> knock;
	while (knock != "out") {
		cout << "which mode" << endl;
		string mode;
		cin.ignore();
		std::getline(std::cin, mode);
		cout << mode << endl;
		if (mode == "plain user") {
				cout << "what do you want" << endl;
				string event;
				std::getline(std::cin, event);
				cout << event << endl;
				while (event != "over") {
					int cnt = 0;
					if (event == "new user") {
						Plain_user* p_user = new Plain_user;
						p_user->initialize();
						(forum->get_user()).push_back(p_user);
						list_user.push_back(p_user);
						forum->update_user(list_user);
						user_ofile.open("user.txt", ios::app);
						user_ofile << (*p_user);
						user_ofile.close();
						cnt = list_user.size();//(forum->get_user()).size();
						cout << cnt << endl;
					}
					else if (event == "log in") {
						string username;
						string password;
						cout << "input your username" << endl;
						cin >> username;
						cout << "password:" << endl;
						cin >> password;
						vector<User*> list = forum->get_user();
						int flag = 0;
						for (int i = 0; i < list.size(); ++i) {
							if (list[i]->get_username() == username && list[i]->get_password() == password) {
								flag = 1;
								cnt = i + 1;
							}
						}
						if (flag == 0) {
							cout << "user does not exist" << endl;
						}
					}
					cout << "hello" << endl;
					if (cnt != 0) {
						string option;
						std::getline(std::cin, option);
						while (option != "log out") {
							if (option == "show the post") {
								vector<Board*> blist;
								blist = forum->get_board();
								for (vector<Board*>::iterator it = blist.begin(); it != blist.end(); it++) {
									(*it)->show_p();
								}
							}
							else if(option == "search a post"){
								string id_post;
								Post* s_post = new Post;
								cout << "which post" << endl;
								cin >> id_post;
								ini_board->show_p(id_post);
							}
							else if (option == "show my information") {
								//(forum->get_user())[cnt - 1]
								//Plain_user* p = new Plain_user;
								//p = forum->get_user()
							}
							else if (option == "write a post") {
								string id_board;
								Post* n_post = new Post;
								Board* n_board = new Board;

								cout << "which board" << endl;
								fflush(stdin);
								cin >> id_board;

								n_post->initialize();
								n_board = forum->search_board(id_board);

								n_board->add_post(n_post);
								n_board->show_p();
							}
							else if (option == "delete my post") {
								string id_post;
								string d_board_id;
								Post* d_post = new Post;
								Board* d_board = new Board;

								cout << "which board" << endl;
								fflush(stdin);
								cin >> d_board_id;
								d_board = forum->search_board(d_board_id);
								cout << "which post" << endl;
								fflush(stdin);
								cin >> id_post;
								d_post = d_board->search_post2(id_post);

								if (d_post != nullptr)
									d_board->delete_post(d_post);

								d_board->show_p();
							}
							else if (option == "write a comment") {
								string c_post_id;
								string c_board_id;
								Post* c_post = new Post;
								Board* c_board = new Board;
								Comment* c_comment = new Comment;

								cout << "which board" << endl;
								fflush(stdin);
								cin >> c_board_id;
								c_board = forum->search_board(c_board_id);
								cout << "which post" << endl;
								fflush(stdin);
								cin >> c_post_id;
								//cout << "input your comment" << endl;
								c_comment->initialize();

								c_post = c_board->search_post2(c_post_id);
								c_post->add_comment(c_comment);
								c_post->show_d();
							}
							else if (option == "delete my comment") {
								string dc_post_id;
								string dc_board_id;
								string author;
								Post* dc_post = new Post;
								Board* dc_board = new Board;
								Comment* dc_comment = new Comment;

								cout << "which board" << endl;
								fflush(stdin);
								cin >> dc_board_id;
								dc_board = forum->search_board(dc_board_id);
								cout << "which post" << endl;
								fflush(stdin);
								cin >> dc_post_id;
								dc_post = dc_board->search_post2(dc_post_id);
								dc_post->show_d();
								cout << "which comment" << endl;
								cin >> author;
								dc_comment = dc_post->search_comment(author);
								if (dc_comment != nullptr) {
									dc_post->delete_comment(dc_comment);
								}
								dc_post->show_d();
							}
							else if (option == "delete a post") {
								string m_board_s;
								string m_post_s;
								Post* m_post = new Post;
								Board* m_board = new Board;
								cout << "which board" << endl;
								cin >> m_board_s;
								cout << "which post" << endl;
								cin >> m_post_s;
								m_board = forum->search_board(m_board_s);
								m_post = m_board->search_post2(m_post_s);
								m_board->delete_post(m_post);
								m_board->show_p();
							}
							else if (option == "upset a post") {
								string uppost;
								Post* top = new Post;
								cout << "which post to be set top" << endl;
								cin >> uppost;
								top = (forum->search_board("1024"))->search_post2(uppost);
								vector<Post*>::iterator from = find(list_post.begin(), list_post.end(), top);
								vector<Post*>::iterator to = list_post.begin();
								if (from < to) {
									rotate(from, from + 1, to + 1);
								}
								else if (from > to) {
									rotate(to, from, from + 1);
								}
							}
							std::getline(std::cin, option);
						}
					}
					std::getline(std::cin, event);
				}
			}
		else if (mode == "admin") {
				string token;
				std::getline(std::cin, token);
				while (token != "over") {
					int tose = 0;
					if (token == "log in") {
						string ad_username;
						string ad_password;
						cout << "input your username" << endl;
						cin >> ad_username;
						cout << "password:" << endl;
						cin >> ad_password;
						vector<User*> Ad_list = list_user;
						//vector<User*> Ad_list = forum->get_user();//list_user;
						int tag = 0;
						for (int i = 0; i < Ad_list.size(); ++i) {
							if (Ad_list[i]->get_username() == ad_username && Ad_list[i]->get_password() == ad_password) {
								tag = 1;
								tose = i + 1;
							}
						}
						if (tag == 0) {
							cout << "Admin_user does not exist" << endl;
						}
						cout << "hello" << endl;
						if (tose != 0) {
							cin.ignore();
							string action;
							std::getline(std::cin, action);
							while (action != "log out") {
								if (action == "show the post") {
									vector<Board*> ad_list;
									ad_list = forum->get_board();
									for (vector<Board*>::iterator it = ad_list.begin(); it != ad_list.end(); it++) {
										(*it)->show_p();
									}
								}
								else if (action == "appoint a boardhost") {
									Admin_user* adm = new Admin_user;
									Plain_user* adp = new Plain_user;
									Board* adb = new Board;
									string ap_user;
									string ap_board;
									int tick;

									adm->set_username(Ad_list[tose - 1]->get_username());
									adm->set_id(Ad_list[tose - 1]->get_id());
									adm->set_password(Ad_list[tose - 1]->get_password());
									adm->set_state(1);

									cout << "input a username" << endl;
									cin >> ap_user;
									cout << "input a board" << endl;
									cin >> ap_board;

									adb = forum->search_board(ap_board);

									for (int h = 0; h < (forum->get_user()).size(); ++h) {
										if ((forum->get_user())[h]->get_username() == ap_user) {
											tick = h;
											break;
										}
									}
									adm->appoint((forum->get_user())[tick], adb, forum);
								}
								else if (action == "dismiss a boardhost") {
									Admin_user* dis_adm = new Admin_user;
									Plain_user* dis_adp = new Plain_user;
									Board* dis_adb = new Board;
									string dis_ap_user;
									string dis_ap_board;
									int dis_tick;

									dis_adm->set_username(Ad_list[tose - 1]->get_username());
									dis_adm->set_id(Ad_list[tose - 1]->get_id());
									dis_adm->set_password(Ad_list[tose - 1]->get_password());
									dis_adm->set_state(1);

									cout << "input a username" << endl;
									cin >> dis_ap_user;
									cout << "input a board" << endl;
									cin >> dis_ap_board;

									dis_adb = forum->search_board(dis_ap_board);

									for (int h = 0; h < (forum->get_user()).size(); ++h) {
										if ((forum->get_user())[h]->get_username() == dis_ap_user) {
											dis_tick = h;
											break;
										}
									}
									dis_adm->dismiss((forum->get_user())[dis_tick], dis_adb, forum);
								}
								std::getline(std::cin, action);
							}
						}
					}
					std::getline(std::cin, token);
				}
			}
		//std::getline(std::cin, knock);
		cin >> knock;
	}
	return 0;
}
