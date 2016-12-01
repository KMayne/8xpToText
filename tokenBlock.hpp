#ifndef TOKENBLOCK_HPP
#define TOKENBLOCK_HPP

#include <vector>

struct token_block {
  int token_count;
  std::vector<char> tokens;
  std::string name;
};

#endif //!TOKENBLOCK_HPP