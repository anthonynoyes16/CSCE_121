/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include "Post.h"

using std::string;
using std::vector;

Post::Post(unsigned int postId, string userName, string postText)
  : postId(postId), userName(userName), postText(postText) {
  if (postId == 0 || userName == "" || postText == "") {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}

vector<string> Post::findTags() {
  vector<string> tags;
  bool start_tag = false;
  bool dont_add = true;
  string hold = "";
  for (int i = 0; i < postText.size(); i++) {
    if (postText.at(i) == '#') {
      if (hold != "") {
        tags.push_back(hold);
      }
      hold = "";
      start_tag = true;
      dont_add = false;
    }
    if (ispunct(postText.at(i)) && (postText.at(i) != '#' && postText.at(i) != '-')) {
      dont_add = true;
    }
    if (!isspace(postText.at(i)) && start_tag && !dont_add) {
      if (isalpha(postText.at(i))) {
        hold.push_back(tolower(postText.at(i)));
      }
      if (!isalpha(postText.at(i))) {
        hold.push_back(postText.at(i));
      }
    }
    if (isspace(postText.at(i))) {
      start_tag = false;
      if (hold != "") {
        tags.push_back(hold);
      }
      hold = "";
    }
  }
  if (hold != "") {
    tags.push_back(hold);
  }
  return tags;
}
