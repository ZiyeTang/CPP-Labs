#include "db.hpp"
void Database::CreateTable(const std::string& table_name) {
  tables_[table_name] = new DbTable();
}

void Database::DropTable(const std::string& table_name) {
  if (tables_.find(table_name) == tables_.end()) {
    throw std::invalid_argument("invalid table name");
  }

  delete tables_[table_name];
  tables_.erase(table_name);
}

DbTable& Database::GetTable(const std::string& table_name) {
  if (tables_.find(table_name) == tables_.end()) {
    throw std::invalid_argument("invalid table name");
  }
  return *(tables_[table_name]);
}

void Database::Copy(const Database& rhs) {
  for (auto i = rhs.tables_.begin(); i != rhs.tables_.end(); i++) {
    tables_[i->first] = new DbTable(*(i->second));
  }
}

void Database::Destroy() {
  for (auto i = tables_.begin(); i != tables_.end(); i++) {
    delete i->second;
  }
  tables_.clear();
}

Database::Database(const Database& rhs) { Copy(rhs); }

Database& Database::operator=(const Database& rhs) {
  if (&rhs == this) {
    return *this;
  }
  Destroy();
  Copy(rhs);
  return *this;
}

Database::~Database() { Destroy(); }
