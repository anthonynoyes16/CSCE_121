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
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Network.h"

using std::string;
using std::vector;

Network::Network()
{
  // empty containers of vectors already created
  // no implementation is needed here
}

void Network::loadFromFile(string fileName)
{
  std::ifstream inFS;
  inFS.open(fileName);
  if (!inFS.is_open())
  {
    throw std::invalid_argument("file could not be opened");
  }
  string hold = "";
  while (getline(inFS, hold))
  {
    std::stringstream ss = std::stringstream(hold);
    string dataType = "";
    ss >> dataType;
    if (dataType == "User")
    {
      string userName = "";
      ss >> userName;
      try
      {
        addUser(userName);
      }
      catch (std::invalid_argument)
      {
        throw std::runtime_error("invalid data for user");
      }
    }

    else if (dataType == "Post")
    {
      int postNum = 0;
      ss >> postNum;
      if (ss.fail())
      {
        throw std::runtime_error("invalid data for post number");
      }

      string postUser = "";
      ss >> postUser;
      for (int i = 0; i < postUser.size(); i++)
      {
        if (!isalpha(postUser.at(i)))
        {
          throw std::runtime_error("invalid data for post user");
        }
      }

      string hold1 = "";
      string postText = "";
      getline(ss, postText);
      try
      {
        addPost(postNum, postUser, postText);
      }
      catch (std::invalid_argument)
      {
        throw std::runtime_error("invalid data for post text");
      }
    }

    else if (dataType != "")
    {
      throw std::runtime_error("invalid data type");
    }
  }
}

void Network::addUser(string userName)
{
  string hold = "";
  for (int i = 0; i < userName.size(); i++)
  {
    if (isalpha(userName.at(i)))
    {
      hold.push_back(tolower(userName.at(i)));
    }
    else
    {
      hold.push_back(userName.at(i));
    }
  }
  for (int i = 0; i < users.size(); i++)
  {
    if (users.at(i)->getUserName() == hold)
    {
      throw std::invalid_argument("user already exists");
    }
  }
  User *newUser = new User(hold);
  users.push_back(newUser);
  std::cout << "Added User " << hold << std::endl;
}

void Network::addPost(unsigned int postId, string userName, string postText)
{
  for (int i = 0; i < posts.size(); i++)
  {
    if (posts.at(i)->getPostId() == postId)
    {
      throw std::invalid_argument("post ID already exists");
    }
  }
  Post *newPost = new Post(postId, userName, postText);
  posts.push_back(newPost);

  bool user_exists = false;
  for (int i = 0; i < users.size(); i++)
  {
    if (users.at(i)->getUserName() == userName)
    {
      users.at(i)->addUserPost(newPost);
      user_exists = true;
    }
  }
  if (!user_exists)
  {
    throw std::invalid_argument("user doesn't exist");
  }

  vector<string> tagsInPost = newPost->findTags();
  bool tag_found = false;
  Tag* newTag;
  for (int i = 0; i < tagsInPost.size(); i++) {
    tag_found = false;
    for (int j = 0; j < tags.size(); j++) {
      if (tags.at(j)->getTagName() == tagsInPost.at(i)) {
        tags.at(j)->addTagPost(newPost);
        tag_found = true;
      }
    }
    if (tag_found) {
      continue;
    }
    try {
        newTag = new Tag(tagsInPost.at(i));
        newTag->addTagPost(newPost);
        tags.push_back(newTag);
      }
    catch (std::invalid_argument) {
    }
  }

  std::cout << "Added Post " << postId << " by " << userName << std::endl;
}

vector<Post *> Network::getPostsByUser(string userName)
{
  if (userName == "")
  {
    throw std::invalid_argument("user name empty");
  }
  for (int i = 0; i < users.size(); i++)
  {
    if (users.at(i)->getUserName() == userName)
    {
      return users.at(i)->getUserPosts();
    }
  }
  throw std::invalid_argument("user with this name doesn't exist");
}

vector<Post *> Network::getPostsWithTag(string tagName)
{
  if (tagName == "")
  {
    throw std::invalid_argument("tag name empty");
  }
  for (int i = 0; i < tags.size(); i++)
  {
    if (tags.at(i)->getTagName() == tagName)
    {
      return tags.at(i)->getTagPosts();
    }
  }
  throw std::invalid_argument("no tag with this name exists");
}

vector<string> Network::getMostPopularHashtag()
{
  int biggest = 0;
  string mostPopular = "";
  vector<string> final;
  if (tags.size() == 0) {
    return final;
  }
  for (int i = 0; i < tags.size(); i++)
  {
    vector<Post *> test = tags.at(i)->getTagPosts();
    if (i == 0)
    {
      biggest = test.size();
      mostPopular = tags.at(i)->getTagName();
      final.push_back(mostPopular);
    }
    else
    {
      if (test.size() > biggest)
      {
        biggest = test.size();
        mostPopular = tags.at(i)->getTagName();
        int hold = final.size();
        for (int j = 0; j < hold; j++)
        {
          final.pop_back();
        }
        final.push_back(mostPopular);
      }
      else if (test.size() == biggest)
      {
        mostPopular = tags.at(i)->getTagName();
        final.push_back(mostPopular);
      }
    }
  }
  return final;
}

  /**
  * Destructor
  * Do not change; already implemented.
  */
  Network::~Network()
  {
    for (unsigned int i = 0; i < users.size(); ++i)
    {
      delete users.at(i);
    }
    for (unsigned int i = 0; i < tags.size(); ++i)
    {
      delete tags.at(i);
    }
    for (unsigned int i = 0; i < posts.size(); ++i)
    {
      delete posts.at(i);
    }
  }
