#include <unordered_map>

#include "tokenBlock.hpp"
#include "tokens/tiCalcTokens.hpp"

// Multi-byte value codes
const int GDB_CODE = 0x61;
const int LIST_CODE = 0x5D;
const int MISC_CODE = 0xBB;
const int TI84_CODE = 0xEF;
const int STRING_CODE = 0xAA;
const int MATRIX_CODE = 0x5C;
const int PICTURE_CODE = 0x60;
const int EQUATION_CODE = 0x5E;
const int STAT_VAR_CODE = 0x62;
const int GRAPH_FORMAT_CODE = 0x7E;
const int WINDOW_FINANCE_CODE = 0x63;

std::unordered_map<char, std::wstring> getTable(char token)
{
  switch (token)
  {
  case GDB_CODE: return GDB_tokens;
  case LIST_CODE: return list_tokens;
  case MISC_CODE: return misc_tokens;
  case TI84_CODE: return TI_84_tokens;
  case MATRIX_CODE: return matrix_tokens;
  case STRING_CODE: return string_tokens;
  case PICTURE_CODE: return picture_tokens;
  case EQUATION_CODE: return equation_tokens;
  case STAT_VAR_CODE: return statistic_var_tokens;
  case GRAPH_FORMAT_CODE: return graph_format_tokens;
  case WINDOW_FINANCE_CODE: return window_finance_tokens;
  default: return single_byte_tokens;
  }
}

std::wstring convertBlock(std::vector<token_block>::value_type block)
{
  std::wstring block_string = L"";
  // Iterate through byte tokens, converting each to their string rep.
  for (unsigned int i = 0; i < block.tokens.size(); i++)
  {
    // Look up table to use based on byte
    auto table = getTable(block.tokens[i]);
    // If it's just the normal table, look up the current token
    if (table == single_byte_tokens) block_string.append(table.at(block.tokens[i]));
    // If not, look up the next token & skip over it
    else block_string.append(table.at(block.tokens[++i]));
  }
  return block_string;
}