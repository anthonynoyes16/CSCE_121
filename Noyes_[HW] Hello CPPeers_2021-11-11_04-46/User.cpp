/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <stdexcept>
#include "User.h"

using std::string;
using std::vector;

User::User(string userName) 
  : userName(userName), userPosts({}) {
    if (userName == "") {
      throw std::invalid_argument("user name is blank");
    }
    if (!isalpha(userName.at(0))) {
      throw std::invalid_argument("first digit of user name is not a valid char");
    }
    for (int i = 0; i < userName.size(); i++) {
      if (!isalpha(userName.at(i))) {
        throw std::invalid_argument("user name contains invalid characters");
      }
      else if (!islower(userName.at(i))) {
        throw std::invalid_argument("user name has uppercase letters");
      }
    }
}

string User::getUserName() {
  return userName;
}

vector<Post*>& User::getUserPosts() {
  return userPosts;
}

void User::addUserPost(Post* post) {
  if (post == nullptr) {
    throw std::invalid_argument("Post is a nullptr");
  }
  userPosts.push_back(post);
}
