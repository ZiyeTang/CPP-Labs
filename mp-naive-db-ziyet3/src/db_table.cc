#include "db_table.hpp"

// const unsigned int kRowGrowthRate = 2;
void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  if (col_descs_.size() == row_col_capacity_) {
    unsigned int new_capacity = 2 * row_col_capacity_;
    for (auto i = rows_.begin(); i != rows_.end(); i++) {
      void** row_data = new void*[new_capacity];
      for (unsigned int j = 0; j < row_col_capacity_; j++) {
        row_data[j] = i->second[j];
      }
      if (col_desc.second == DataType::kString) {
        row_data[row_col_capacity_] = new std::string("");
      }
      if (col_desc.second == DataType::kInt) {
        row_data[row_col_capacity_] = new int(0);
      }
      if (col_desc.second == DataType::kDouble) {
        row_data[row_col_capacity_] = new double(0.0);
      }
      delete[] i->second;
      i->second = row_data;
    }
    row_col_capacity_ = new_capacity;
  } else {
    for (auto i = rows_.begin(); i != rows_.end(); i++) {
      if (col_desc.second == DataType::kString) {
        i->second[col_descs_.size()] = new std::string("");
      }
      if (col_desc.second == DataType::kInt) {
        i->second[col_descs_.size()] = new int(0);
      }
      if (col_desc.second == DataType::kDouble) {
        i->second[col_descs_.size()] = new double(0.0);
      }
    }
  }
  col_descs_.push_back(col_desc);
}

void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
  if (col_idx < 0 || col_idx >= col_descs_.size()) {
    throw std::out_of_range("index out of bounds");
  }

  if (col_descs_.size() == 1 && !(rows_.empty())) {
    throw std::runtime_error("run time error");
  }

  for (auto i = rows_.begin(); i != rows_.end(); i++) {
    if (col_descs_[col_idx].second == DataType::kString) {
      delete static_cast<std::string*>(i->second[col_idx]);
    }
    if (col_descs_[col_idx].second == DataType::kInt) {
      delete static_cast<int*>(i->second[col_idx]);
    }
    if (col_descs_[col_idx].second == DataType::kDouble) {
      delete static_cast<double*>(i->second[col_idx]);
    }

    for (unsigned int j = col_idx; j < col_descs_.size() - 1; j++) {
      i->second[j] = i->second[j + 1];
    }
  }
  col_descs_.erase(col_descs_.begin() + col_idx);
}

void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  if (col_data.size() != col_descs_.size()) {
    throw std::invalid_argument("invalid argument");
  }

  rows_[next_unique_id_] = new void*[row_col_capacity_];

  unsigned int j = 0;
  for (const std::string& str : col_data) {
    if (col_descs_[j].second == DataType::kString) {
      rows_[next_unique_id_][j] = static_cast<void*>(new std::string(str));
    }
    if (col_descs_[j].second == DataType::kInt) {
      rows_[next_unique_id_][j] = static_cast<void*>(new int(stoi(str)));
    }
    if (col_descs_[j].second == DataType::kDouble) {
      rows_[next_unique_id_][j] = static_cast<void*>(new double(stod(str)));
    }
    j++;
  }
  next_unique_id_++;
}

void DbTable::DeleteRowById(unsigned int id) {
  if (rows_.find(id) == rows_.end()) {
    throw std::invalid_argument("invalide id");
  }
  for (unsigned int i = 0; i < col_descs_.size(); i++) {
    if (col_descs_[i].second == DataType::kString) {
      delete static_cast<std::string*>(rows_[id][i]);
    }
    if (col_descs_[i].second == DataType::kInt) {
      delete static_cast<int*>(rows_[id][i]);
    }
    if (col_descs_[i].second == DataType::kDouble) {
      delete static_cast<double*>(rows_[id][i]);
    }
  }
  delete[] rows_[id];
  rows_.erase(id);
}

void DbTable::Copy(const DbTable& rhs) {
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  for (unsigned int i = 0; i < rhs.col_descs_.size(); i++) {
    col_descs_.push_back(rhs.col_descs_[i]);
  }
  for (auto i = rhs.rows_.begin(); i != rhs.rows_.end(); i++) {
    rows_[i->first] = new void*[row_col_capacity_];
    for (unsigned int j = 0; j < col_descs_.size(); j++) {
      if (col_descs_[j].second == DataType::kString) {
        rows_[i->first][j] =
            new std::string(*(static_cast<std::string*>(i->second[j])));
      }
      if (col_descs_[j].second == DataType::kInt) {
        rows_[i->first][j] = new int(*(static_cast<int*>(i->second[j])));
      }
      if (col_descs_[j].second == DataType::kDouble) {
        rows_[i->first][j] = new double(*(static_cast<double*>(i->second[j])));
      }
    }
  }
}

void DbTable::Destroy() {
  for (auto i = rows_.begin(); i != rows_.end(); i++) {
    for (unsigned int j = 0; j < col_descs_.size(); j++) {
      if (col_descs_[j].second == DataType::kString) {
        delete static_cast<std::string*>(i->second[j]);
      }
      if (col_descs_[j].second == DataType::kInt) {
        delete static_cast<int*>(i->second[j]);
      }
      if (col_descs_[j].second == DataType::kDouble) {
        delete static_cast<double*>(i->second[j]);
      }
    }
    delete[] i->second;
  }
  col_descs_.clear();
  rows_.clear();
}

DbTable::DbTable(const DbTable& rhs) { Copy(rhs); }

DbTable& DbTable::operator=(const DbTable& rhs) {
  if (this == &rhs) {
    return *this;
  }
  Destroy();
  Copy(rhs);
  return *this;
}

DbTable::~DbTable() { Destroy(); }

std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  for (unsigned int i = 0; i < table.col_descs_.size(); i++) {
    os << table.col_descs_[i].first;
    if (table.col_descs_[i].second == DataType::kString) {
      os << "(std::string)";
    }
    if (table.col_descs_[i].second == DataType::kInt) {
      os << "(int)";
    }
    if (table.col_descs_[i].second == DataType::kDouble) {
      os << "(double)";
    }
    if (i != table.col_descs_.size() - 1) {
      os << ", ";
    }
  }
  os << "\n";
  for (auto i = table.rows_.begin(); i != table.rows_.end(); i++) {
    for (unsigned int j = 0; j < table.col_descs_.size(); j++) {
      if (table.col_descs_[j].second == DataType::kString) {
        os << *(static_cast<std::string*>(i->second[j]));
      }
      if (table.col_descs_[j].second == DataType::kInt) {
        os << *(static_cast<int*>(i->second[j]));
      }
      if (table.col_descs_[j].second == DataType::kDouble) {
        os << *(static_cast<double*>(i->second[j]));
      }
      if (j != table.col_descs_.size() - 1) {
        os << ", ";
      }
    }

    i++;
    if (i != table.rows_.end()) {
      os << "\n";
    }
    i--;
  }
  return os;
}
