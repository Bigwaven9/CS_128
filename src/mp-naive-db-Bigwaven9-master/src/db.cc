#include "db.hpp"

void Database::CreateTable(const std::string& table_name) {
  if (tables_.count(table_name) == 0) tables_[table_name] = new DbTable();
}

void Database::DropTable(const std::string& table_name) {
  if (tables_.count(table_name) == 0) throw std::invalid_argument("");
  delete tables_[table_name];
  tables_.erase(table_name);
}

DbTable& Database::GetTable(const std::string& table_name) {
  return *tables_[table_name];
}

Database::Database(const Database& rhs) {
  for (const auto& it : rhs.tables_) {
    tables_[it.first] = new DbTable(*it.second);
  }
}

void Database::Clear() {
  for (auto& it : tables_) delete it.second;
  tables_.clear();
}

Database& Database::operator=(const Database& rhs) {
  if (&rhs == this) return *this;
  Clear();
  for (const auto& it : rhs.tables_) {
    tables_[it.first] = new DbTable(*it.second);
  }
  return *this;
}
