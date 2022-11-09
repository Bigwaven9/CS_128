#include "db_table.hpp"

// const unsigned int kRowGrowthRate = 2;

void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  if (col_descs_.size() == row_col_capacity_) {
    unsigned int new_capacity = row_col_capacity_ * 2;
    for (auto& it : rows_) {
      void** row = new void*[new_capacity];
      for (size_t i = 0; i < row_col_capacity_; ++i) {
        row[i] = it.second[i];
      }
      delete[] it.second;
      it.second = row;
    }
    row_col_capacity_ = new_capacity;
  }
  col_descs_.push_back(col_desc);
  for (auto& it : rows_) {
    if (col_desc.second == DataType::kString)
      it.second[col_descs_.size() - 1] =
          static_cast<void*>(new std::string(""));
    else if (col_desc.second == DataType::kDouble)
      it.second[col_descs_.size() - 1] = static_cast<void*>(new double(0.0));
    else if (col_desc.second == DataType::kInt)
      it.second[col_descs_.size() - 1] = static_cast<void*>(new int(0));
  }
}

void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
  if (col_idx >= col_descs_.size()) throw std::out_of_range("");
  if (col_descs_.size() == 1 && !rows_.empty()) throw std::runtime_error("");
  for (auto& it : rows_) {
    if (col_descs_[col_idx].second == DataType::kString)
      delete (static_cast<std::string*>(it.second[col_idx]));
    else if (col_descs_[col_idx].second == DataType::kDouble)
      delete (static_cast<double*>(it.second[col_idx]));
    else if (col_descs_[col_idx].second == DataType::kInt)
      delete (static_cast<int*>(it.second[col_idx]));
    for (size_t i = col_idx; i < col_descs_.size() - 1; ++i)
      it.second[i] = it.second[i + 1];
  }
  col_descs_.erase(col_descs_.begin() + col_idx);
}

void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  if (col_data.size() != col_descs_.size()) throw std::invalid_argument("");
  void** temp = new void*[row_col_capacity_];
  const auto* it = col_data.begin();
  for (size_t i = 0; i < col_descs_.size(); ++i) {
    if (col_descs_[i].second == DataType::kString)
      temp[i] = static_cast<void*>(new std::string(*it++));
    else if (col_descs_[i].second == DataType::kDouble)
      temp[i] = static_cast<void*>(new double(std::stod(*it++)));
    else if (col_descs_[i].second == DataType::kInt)
      temp[i] = static_cast<void*>(new int(std::stoi(*it++)));
  }
  rows_[next_unique_id_++] = temp;
}

void DbTable::DeleteRowById(unsigned int id) {
  if (rows_.count(id) == 0) throw std::out_of_range("");
  for (size_t i = 0; i < col_descs_.size(); ++i) {
    if (col_descs_[i].second == DataType::kString)
      delete (static_cast<std::string*>(rows_[id][i]));
    else if (col_descs_[i].second == DataType::kDouble)
      delete (static_cast<double*>(rows_[id][i]));
    else if (col_descs_[i].second == DataType::kInt)
      delete (static_cast<int*>(rows_[id][i]));
  }
  delete[] rows_[id];
  rows_.erase(id);
}

DbTable::DbTable(const DbTable& rhs):
    next_unique_id_(rhs.next_unique_id_),
    row_col_capacity_(rhs.row_col_capacity_),
    col_descs_(rhs.col_descs_) {
  for (const auto& it : rhs.rows_) {
    rows_[it.first] = new void*[row_col_capacity_];
    for (size_t i = 0; i < col_descs_.size(); ++i) {
      if (col_descs_[i].second == DataType::kString)
        rows_[it.first][i] = static_cast<void*>(
            new std::string(*(static_cast<std::string*>(it.second[i]))));
      else if (col_descs_[i].second == DataType::kDouble)
        rows_[it.first][i] = static_cast<void*>(
            new double(*(static_cast<double*>(it.second[i]))));
      else if (col_descs_[i].second == DataType::kInt)
        rows_[it.first][i] =
            static_cast<void*>(new int(*(static_cast<int*>(it.second[i]))));
    }
  }
}

void DbTable::Clear() {
  for (auto& it : rows_) {
    for (size_t i = 0; i < col_descs_.size(); ++i) {
      if (col_descs_[i].second == DataType::kString)
        delete static_cast<std::string*>(it.second[i]);
      else if (col_descs_[i].second == DataType::kDouble)
        delete static_cast<double*>(it.second[i]);
      else if (col_descs_[i].second == DataType::kInt)
        delete static_cast<int*>(it.second[i]);
    }
    delete[] it.second;
  }
  rows_.clear();
}

DbTable::~DbTable() { Clear(); }

DbTable& DbTable::operator=(const DbTable& rhs) {
  if (&rhs == this) return *this;
  Clear();
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  col_descs_ = rhs.col_descs_;
  for (const auto& it : rhs.rows_) {
    rows_[it.first] = new void*[row_col_capacity_];
    for (size_t i = 0; i < col_descs_.size(); ++i) {
      if (col_descs_[i].second == DataType::kString)
        rows_[it.first][i] = static_cast<void*>(
            new std::string(*(static_cast<std::string*>(it.second[i]))));
      else if (col_descs_[i].second == DataType::kDouble)
        rows_[it.first][i] = static_cast<void*>(
            new double(*(static_cast<double*>(it.second[i]))));
      else if (col_descs_[i].second == DataType::kInt)
        rows_[it.first][i] =
            static_cast<void*>(new int(*(static_cast<int*>(it.second[i]))));
    }
  }
  return *this;
}

std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  for (size_t i = 0; i < table.col_descs_.size(); ++i) {
    os << table.col_descs_[i].first;
    if (table.col_descs_[i].second == DataType::kString)
      os << "(std::string)";
    else if (table.col_descs_[i].second == DataType::kInt)
      os << "(int)";
    else if (table.col_descs_[i].second == DataType::kDouble)
      os << "(double)";
    if (i != table.col_descs_.size() - 1) os << ", ";
  }
  os << "\n";
  for (const auto& it : table.rows_) {
    for (size_t i = 0; i < table.col_descs_.size(); ++i) {
      if (table.col_descs_[i].second == DataType::kString)
        os << *(static_cast<std::string*>(it.second[i]));
      else if (table.col_descs_[i].second == DataType::kDouble)
        os << *(static_cast<double*>(it.second[i]));
      else if (table.col_descs_[i].second == DataType::kInt)
        os << *(static_cast<int*>(it.second[i]));
      if (i != table.col_descs_.size() - 1) os << ", ";
    }
    os << "\n";
  }
  return os;
}