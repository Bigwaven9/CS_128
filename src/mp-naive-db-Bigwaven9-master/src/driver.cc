#include <fstream>
#include <iostream>

#include "db.hpp"
#include "db_table.hpp"

int main() {
  auto* x = new DbTable();
  x->AddColumn({"name", DataType::kString});
  x->AddColumn({"gpa", DataType::kInt});
  x->AddColumn({"score", DataType::kDouble});
  x->AddRow(std::initializer_list<std::string>({"mark", "3", "4.5"}));
  std::ofstream os("test.txt");
  auto* y = new Database();
  y->CreateTable("table1");
  y->GetTable("table1") = *x;
  delete x;
  auto* s = new Database();
  *s = *y;

  delete y;

  delete s;
}