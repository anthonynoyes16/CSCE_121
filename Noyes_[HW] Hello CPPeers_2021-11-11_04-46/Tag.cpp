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
#include <cctype>
#include "Tag.h"

using std::string;
using std::vector;

Tag::Tag(string tagName)
  : tagName(tagName), tagPosts({}) {
  if (tagName.length() < 2) {
    throw std::invalid_argument("tag size too small");
  }
  if (tagName.at(0) != '#') {
    throw std::invalid_argument("tag doesn't start with #");
  }
  for (int i = 1; i < tagName.length(); i++) {
    if (!isalpha(tagName.at(i)) || isupper(tagName.at(i))) {
      throw std::invalid_argument("non letter or uppercase letters present");
    }
  }
  if (tagName.at(tagName.length()-2) == '!' || tagName.at(tagName.length()-2) == ',' || tagName.at(tagName.length()-2) == '.' || tagName.at(tagName.length()-2) == '?') {
    throw std::invalid_argument("more than one punctuation present at end");
  }
  tagName = tagName;
}

string Tag::getTagName() {
  return tagName;
}

vector<Post*>& Tag::getTagPosts() {
  return tagPosts;
}

void Tag::addTagPost(Post* post) {
  if (post == nullptr) {
    throw std::invalid_argument("Post is a nullptr");
  }
  tagPosts.push_back(post);
}
