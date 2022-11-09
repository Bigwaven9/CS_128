#ifndef DB_HPP
#define DB_HPP

#include <iostream>
#include <map>
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
  void Clear();
  ~Database() { Clear(); }
  friend std::ostream& operator<<(std::ostream& os, const Database& db);

private:
  std::map<std::string, DbTable*> tables_;  // maps table name -> table
};

std::ostream& operator<<(std::ostream& os, const Database& db);

#endif