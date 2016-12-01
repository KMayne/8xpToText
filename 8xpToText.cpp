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

#include "tokenBlock.hpp"
#include "blockConversion.hpp"


static const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> utf_converter;


const int BLOCK_HEADER_SIZE = 17;
const int TOKEN_COUNT_FIELD_SIZE = 2;
const char PROG_TYPE_ID = 5;
const char TI_8XP_FILE_SIGNATURE[] = { 
  0x2A, 0x2A, 0x54, 0x49, 0x38, 0x33, 0x46, 0x2A, 0x1A, 0x0A, 0x00
};



inline int twobyte2int(char arr[]);

inline std::wstring widen_string(std::string str);

inline void assert(bool test, std::wstring message)
{
  if (!test) throw std::wstring(message);
}

std::vector<token_block> read8xpFile(std::wstring filename)
{
  // Set up the input file stream
  std::ifstream input_stream;
  input_stream.exceptions(std::ios::badbit | std::ios::failbit);
  input_stream.open(filename, std::ios::in | std::ios::binary | std::ios::beg);

  // Check signature
  char fileSig[11];
  input_stream.read(fileSig, 11);

  if (strcmp(fileSig, TI_8XP_FILE_SIGNATURE))
  {
    // Not valid
    throw "The file '" + std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(std::wstring(filename)) + "' is not a valid TI program.";
  }

  // Ignore comment
  input_stream.seekg(42, std::ios::cur);

  // Read data length
  char bytes[2];
  input_stream.read(bytes, 2);
  int length = twobyte2int(bytes);

  std::vector<token_block> blocks;
  int blockSize = length;
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
    char* ID = new char(0);
    input_stream.read(ID, 1);
    assert(*ID == PROG_TYPE_ID, L"Input file not a TI program.");

    // Read program name
    std::string program_name(8, '\0');
    input_stream.read(&program_name[0], 8);

    // Ignore version & flag
    input_stream.seekg(2, std::ios::cur);

    // Check mirrored length
    input_stream.read(bytes, 2);
    assert(block_length == twobyte2int(bytes), L"Invalid variable block (length mirror).");

    // Get number of tokens
    input_stream.read(bytes, 2);
    int token_count = twobyte2int(bytes);

    // Load the blocks into memory - generally programs written on the 
    // calculators will be on the order of kB so this isn't a problem
    int block_data_length = block_length - TOKEN_COUNT_FIELD_SIZE;
    std::vector<char> block_data = std::vector<char>(block_data_length);
    input_stream.read(&block_data[0], block_data_length);

    // Store the block info in the vector
    blocks.push_back({ token_count, block_data, program_name });
    // Decrement the amount of block data left
    blockSize -= BLOCK_HEADER_SIZE + block_length;
  } while (blockSize > 0);

  return blocks;
}

void saveBlockToFile(std::vector<token_block>::value_type block)
{
  std::wstring block_string = convertBlock(block);

  // Set up output stream
  std::wofstream output_stream;
  output_stream.imbue(utf8_locale);
  output_stream.open(widen_string(block.name) + L".txt");

  // Output contents
  output_stream << block_string << std::endl;
}

bool convertFile(_TCHAR* filename)
{
  try
  {
    // Extract blocks from file
    std::vector<token_block> blocks = read8xpFile(filename);
    // Iterate through the blocks, saving each to their own file
    for (auto block : blocks)
    {
      saveBlockToFile(block);
    }
  }
  catch (std::ios::failure e)
  {
    std::wcout << "There was an I/O error!";
    return false;
  }
  catch (std::out_of_range e)
  {
    std::wcout << "An unknown character was found. File may be corrupt.";
    return false;
  }
  catch (std::wstring e)
  {
    std::wcout << "There was an error: " << e;
    return false;
  }
  return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
  // Make console output unicode
  _setmode(_fileno(stdout), _O_U8TEXT);
  // Iterate through all the arguments and convert each of them
  for (int i = 1; i < argc; i++)
  {
    // If conversion was unsuccessful, exit with failure code
    if (!convertFile(argv[i])) return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

inline std::wstring widen_string(std::string str)
{
  return utf_converter.from_bytes(str);
}

inline int twobyte2int(char arr[])
{
  return (static_cast<unsigned char>(arr[1]) << 8) + static_cast<unsigned char>(arr[0]);
}
