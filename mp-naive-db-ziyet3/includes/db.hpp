#ifndef DB_HPP
#define DB_HPP

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

#include "db_table.hpp"

class Database {
public:
  void CreateTable(const std::string& table_name);
  void DropTable(const std::string& table_name);
  DbTable& GetTable(const std::string& table_name);

  Database() = default;
  Database(const Database& rhs);
  Database& operator=(const Database& rhs);
  ~Database();
  friend std::ostream& operator<<(std::ostream& os, const Database& db);

private:
  std::map<std::string, DbTable*> tables_;  // maps table name -> table
  void Copy(const Database& rhs);
  void Destroy();
};

std::ostream& operator<<(std::ostream& os, const Database& db);

#endif