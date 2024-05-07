#include "illini_book.hpp"

// Your code here!
IlliniBook::IlliniBook(const std::string &people_fpath,
                       const std::string &relations_fpath) {
  std::ifstream people(people_fpath);

  int datum = 0;
  while (people >> datum) {
    graph_.insert({datum, std::list<std::pair<int, std::string>>()});
  }
  people.close();

  std::ifstream rf(relations_fpath);
  std::string line;
  while (std::getline(rf, line)) {
    size_t pos1 = line.find(',');
    size_t pos2 = line.find(',', pos1 + 1);
    std::string uin1 = line.substr(0, pos1);
    std::string uin2 = line.substr(pos1 + 1, pos2 - pos1 - 1);
    std::string relation = line.substr(pos2 + 1);
    graph_[stoi(uin1)].push_back(
        std::pair<int, std::string>{std::stoi(uin2), relation});
    graph_[stoi(uin2)].push_back(
        std::pair<int, std::string>{std::stoi(uin1), relation});
  }
  rf.close();
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  std::queue<int> q;
  q.push(uin_1);

  std::map<int, bool> visited;
  for (auto i = graph_.begin(); i != graph_.end(); i++) {
    visited[i->first] = false;
  }
  visited[uin_1] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (const std::pair<int, std::string> &i : graph_.at(cur)) {
      if (!visited[i.first]) {
        if (i.first == uin_2) {
          return true;
        }
        q.push(i.first);
        visited[i.first] = true;
      }
    }
  }
  return false;
}

bool IlliniBook::AreRelated(int uin_1, int uin_2,
                            const std::string &relationship) const {
  std::queue<int> q;
  q.push(uin_1);

  std::map<int, bool> visited;
  for (auto i = graph_.begin(); i != graph_.end(); i++) {
    visited[i->first] = false;
  }
  visited[uin_1] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (const std::pair<int, std::string> &i : graph_.at(cur)) {
      if (!visited[i.first] && relationship == i.second) {
        if (i.first == uin_2) {
          return true;
        }
        q.push(i.first);
        visited[i.first] = true;
      }
    }
  }
  return false;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  std::queue<int> q;
  q.push(uin_1);
  q.push(-1);

  std::map<int, bool> visited;
  for (auto i = graph_.begin(); i != graph_.end(); i++) {
    visited[i->first] = false;
  }
  visited[uin_1] = true;

  int length = 0;

  while (q.size() > 1) {
    int cur = q.front();
    q.pop();
    if (cur == -1) {
      q.push(-1);
      cur = q.front();
      q.pop();

      length++;
    }
    for (const std::pair<int, std::string> &i : graph_.at(cur)) {
      if (!visited[i.first]) {
        if (i.first == uin_2) {
          return length + 1;
        }
        q.push(i.first);
        visited[i.first] = true;
      }
    }
  }
  return -1;
}

int IlliniBook::GetRelated(int uin_1, int uin_2,
                           const std::string &relationship) const {
  std::queue<int> q;
  q.push(uin_1);
  q.push(-1);

  std::map<int, bool> visited;
  for (auto i = graph_.begin(); i != graph_.end(); i++) {
    visited[i->first] = false;
  }
  visited[uin_1] = true;

  int length = 0;

  while (q.size() > 1) {
    int cur = q.front();
    q.pop();
    if (cur == -1) {
      cur = q.front();
      q.pop();
      q.push(-1);
      length++;
    }

    for (const std::pair<int, std::string> &i : graph_.at(cur)) {
      if (!visited[i.first] && relationship == i.second) {
        if (i.first == uin_2) {
          return length + 1;
        }
        q.push(i.first);
        visited[i.first] = true;
      }
    }
  }
  return -1;
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::vector<int> res;

  std::queue<long> q;
  q.push(uin);
  q.push(-1);

  std::map<int, bool> visited;
  for (auto i = graph_.begin(); i != graph_.end(); i++) {
    visited[i->first] = false;
  }
  visited[uin] = true;

  int length = 0;

  while (q.size() > 1) {
    int cur = q.front();
    q.pop();
    if (cur == -1) {
      cur = q.front();
      q.pop();
      q.push(-1);
      length++;
      if (length == n) {
        return res;
      }
    }

    for (const std::pair<int, std::string> &i : graph_.at(cur)) {
      if (!visited[i.first]) {
        q.push(i.first);
        visited[i.first] = true;
        if (n - 1 == length) {
          res.push_back(i.first);
        }
      }
    }
  }

  return res;
}

void IlliniBook::BFS(int v, std::map<int, bool> &visited) const {
  std::queue<int> q;
  q.push(v);
  visited[v] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (const std::pair<int, std::string> &i : graph_.at(cur)) {
      if (!visited[i.first]) {
        q.push(i.first);
        visited[i.first] = true;
      }
    }
  }
}

size_t IlliniBook::CountGroups() const {
  std::map<int, bool> visited;
  for (auto i = graph_.begin(); i != graph_.end(); i++) {
    visited[i->first] = false;
  }

  size_t num_comp = 0;
  for (auto i = graph_.begin(); i != graph_.end(); i++) {
    if (!visited[i->first]) {
      BFS(i->first, visited);
      num_comp++;
    }
  }
  return num_comp;
}

bool IlliniBook::InFilter(const std::vector<std::string> &relationships,
                          const std::string &relationship) const {
  for (const std::string &r : relationships) {
    if (relationship == r) {
      return true;
    }
  }
  return false;
}

void IlliniBook::BFSFilter(
    int v, std::map<int, bool> &visited,
    const std::vector<std::string> &relationships) const {
  std::queue<int> q;
  q.push(v);
  visited[v] = true;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    for (const std::pair<int, std::string> &i : graph_.at(cur)) {
      if (!visited[i.first] && InFilter(relationships, i.second)) {
        q.push(i.first);
        visited[i.first] = true;
      }
    }
  }
}

size_t IlliniBook::CountGroups(const std::string &relationship) const {
  std::vector<std::string> rs = {relationship};

  std::map<int, bool> visited;
  for (auto i = graph_.begin(); i != graph_.end(); i++) {
    visited[i->first] = false;
  }

  size_t num_comp = 0;
  for (auto i = graph_.begin(); i != graph_.end(); i++) {
    if (!visited[i->first]) {
      BFSFilter(i->first, visited, rs);
      num_comp++;
    }
  }
  return num_comp;
}

size_t IlliniBook::CountGroups(
    const std::vector<std::string> &relationships) const {
  std::map<int, bool> visited;
  for (auto i = graph_.begin(); i != graph_.end(); i++) {
    visited[i->first] = false;
  }

  size_t num_comp = 0;
  for (auto i = graph_.begin(); i != graph_.end(); i++) {
    if (!visited[i->first]) {
      BFSFilter(i->first, visited, relationships);
      num_comp++;
    }
  }
  return num_comp;
}