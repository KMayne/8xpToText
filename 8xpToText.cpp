#include <stdio.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>

#include <string>
#include <locale>
#include <codecvt>

#include <unordered_map>
#include <vector>
#include <iterator>
#include <numeric>

#include "tiCalcTokens.hpp"

static const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> utf_converter;

// Multi-byte value codes
const int MATRIX_CODE = 0x5C;
const int LIST_CODE = 0x5D;
const int EQUATION_CODE = 0x5E;
const int PICTURE_CODE = 0x60;
const int GDB_CODE = 0x61;
const int STAT_VAR_CODE = 0x62;
const int WINDOW_FINANCE_CODE = 0x63;
const int GRAPH_FORMAT_CODE = 0x7E;
const int STRING_CODE = 0xAA;
const int MISC_CODE = 0xBB;
const int TI84_CODE = 0xEF;

const int BLOCK_HEADER_SIZE = 17;
const int PROG_TYPE_ID = 5;
const char TI_8XP_FILE_SIGNATURE[] = { 0x2A, 0x2A, 0x54, 0x49, 0x38, 0x33, 0x46, 0x2A, 0x1A, 0x0A, 0x00 };

struct token_block {
  int token_count;
  std::vector<char> tokens;
  std::string name;
};

inline int twobyte2int(char arr[]);

inline std::wstring widen_string(std::string str);

std::wstring convertBlock(std::vector<token_block>::value_type block)
{
  std::wstring block_string = L"";

  // Convert each byte and append to string
  for (unsigned int i = 0; i < block.tokens.size(); i++)
  {
    unsigned char byte = block.tokens[i];
    std::wstring plaintext_token = single_byte_tokens.at(byte);

    // Ignore unused but check for 2-byte codes, overwriting the default if found
    if (byte == GDB_CODE) { plaintext_token = GDB_tokens.at(block.tokens[++i]); }
    if (byte == LIST_CODE) { plaintext_token = list_tokens.at(block.tokens[++i]); }
    if (byte == MISC_CODE) { plaintext_token = misc_tokens.at(block.tokens[++i]); }
    if (byte == TI84_CODE) { plaintext_token = TI_84_tokens.at(block.tokens[++i]); }
    if (byte == MATRIX_CODE) { plaintext_token = matrix_tokens.at(block.tokens[++i]); }
    if (byte == STRING_CODE) { plaintext_token = string_tokens.at(block.tokens[++i]); }
    if (byte == PICTURE_CODE) { plaintext_token = picture_tokens.at(block.tokens[++i]); }
    if (byte == EQUATION_CODE) { plaintext_token = equation_tokens.at(block.tokens[++i]); }
    if (byte == STAT_VAR_CODE) { plaintext_token = statistic_var_tokens.at(block.tokens[++i]); }
    if (byte == GRAPH_FORMAT_CODE) { plaintext_token = graph_format_tokens.at(block.tokens[++i]); }
    if (byte == WINDOW_FINANCE_CODE) { plaintext_token = window_finance_tokens.at(block.tokens[++i]); }

    block_string.append(plaintext_token);
  }
  return block_string;
}

inline void assert(bool test, std::wstring message)
{
  if (!test) throw std::wstring(message);
}

std::vector<token_block> extractBlocks(std::ifstream &input_stream, int blockSize)
{
  char bytes[2];
  std::vector<token_block> blocks;
  do
  {
    // Read first 2 preamble bytes
    input_stream.read(bytes, 2);
    int start = twobyte2int(bytes);
    assert(start == 0xB || start == 0xD, L"Invalid variable block (preamble).");

    // Read block length
    input_stream.read(bytes, 2);
    int block_length = twobyte2int(bytes);

    // Check type ID represents TI program
    char octet[1];
    input_stream.read(octet, 1);
    char ID = octet[0];
    assert(ID == PROG_TYPE_ID, L"Input file not a TI program.");
    
    // Read program name
    char name[9];
    input_stream.read(name, 8);
    name[8] = '\0';
    std::string program_name(name);

    // Ignore version & flag
    input_stream.seekg(2, std::ios::cur);

    // Check mirrored length
    input_stream.read(bytes, 2);
    assert(block_length == twobyte2int(bytes), L"Invalid variable block (length mirror).");

    // Get number of tokens
    input_stream.read(bytes, 2);
    int token_count = twobyte2int(bytes);

    // Read the data
    // Subtract 2 from block length (read # of tokens)
    int block_data_length = block_length - 2;
    char * blockp = new char[block_data_length];
    input_stream.read(blockp, block_data_length);

    // Store the block info in the vector
    blocks.push_back({ token_count, std::vector<char>(blockp, blockp + block_data_length), program_name });
    // Decrement the amount of block data left
    blockSize -= (BLOCK_HEADER_SIZE + block_length);
  } while (blockSize > 0);

  return blocks;
}

int _tmain(int argc, _TCHAR* argv[])
{
  // Make console output unicode
  _setmode(_fileno(stdout), _O_U8TEXT);
  // Iterate through all the arguments and convert each of them
  for (int i = 1; i < argc; i++)
  {
    try
    {
      // Set up the input file stream
      char hexDigit[2];
      std::ifstream input_stream;
      input_stream.exceptions(std::ios::badbit | std::ios::failbit);
      input_stream.open(argv[i], std::ios::in | std::ios::binary | std::ios::beg);

      // Check signature
      char fileSig[11];
      input_stream.read(fileSig, 11);

      if (strcmp(fileSig, TI_8XP_FILE_SIGNATURE))
      {
        // Not valid
        throw "The file '" + std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(std::wstring(argv[i])) + "' is not a valid TI program.";
      }

      // Ignore comment
      input_stream.seekg(42, std::ios::cur);

      // Read data length
      input_stream.read(hexDigit, 2);
      int length = twobyte2int(hexDigit);

      std::vector<token_block> blocks = extractBlocks(&input_stream, length);

      // Blocks now separated and ready for detokenising (so close stream)
      input_stream.close();

      // Iterate through the blocks
      for (auto block : blocks)
      {
        std::wstring block_string = convertBlock(block);

        // Set up output stream
        std::wofstream output_stream;
        output_stream.imbue(utf8_locale);
        output_stream.open(widen_string(block.name) + L".txt");

        // Then contents
        output_stream << block_string << std::endl;
      }

    }
    catch (std::ios::failure e)
    {
      std::wcout << "There was an I/O error!";
      return 1;
    }
    catch (std::out_of_range e)
    {
      std::wcout << "An unknown character was found. File may be corrupt.";
      return 1;
    }
    catch (std::wstring e)
    {
      std::wcout << "There was an error: " << e;
      return 1;
    }
  }
  return 0;
}

inline std::wstring widen_string(std::string str)
{
  return utf_converter.from_bytes(str);
}

inline int twobyte2int(char arr[])
{
  return (static_cast<unsigned char>(arr[1]) << 8) + static_cast<unsigned char>(arr[0]);
}