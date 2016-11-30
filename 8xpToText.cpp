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

struct token_block {
	int token_count;
	std::vector<char> tokens;
	std::string name;
};

inline int twobyte2int(char arr[]);

inline std::wstring widen_string(std::string str);

int _tmain(int argc, _TCHAR* argv[])
{
	//Make console output unicode
	_setmode(_fileno(stdout), _O_U8TEXT);
	//Iterate through all the arguments and convert each of them
	for (int i = 1; i < argc; i++)
	{
		try
		{
			//Set up the input file stream
			char hextet[2];
			std::ifstream input_stream;
			input_stream.exceptions(std::ios::badbit | std::ios::failbit);
			input_stream.open(argv[i], std::ios::in | std::ios::binary | std::ios::beg);

			//Check signature
			char fileSig[11];
			char sig[] = { 0x2A, 0x2A, 0x54, 0x49, 0x38, 0x33, 0x46, 0x2A, 0x1A, 0x0A, 0x00 };
			input_stream.read(fileSig, 11);

			if (strcmp(fileSig, sig))
			{
				//Not valid
				throw "The file '" + std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(std::wstring(argv[i])) + "' is not a valid TI program.";
			}

			//Ignore comment
			input_stream.seekg(42, std::ios::cur);

			//Read data length
			input_stream.read(hextet, 2);
			int length = twobyte2int(hextet);

			//Set up the block vector
			std::vector<token_block> blocks;

			int blocksize_remain = length;
			do
			{
				//Read first 2 preamble bytes
				input_stream.read(hextet, 2);
				int start = twobyte2int(hextet);
				if (start != 0xB && start != 0xD)
				{
					throw std::wstring(L"Invalid variable block (preamble).");
				}

				//Read block length
				input_stream.read(hextet, 2);
				int block_length = twobyte2int(hextet);

				//Read type ID
				char octet[1];
				input_stream.read(octet, 1);
				char ID = octet[0];
				if (ID != 5)
				{
					//Not a program
					throw std::wstring(L"Input file not a TI program.");
				}

				//Read program name
				char name[9];
				input_stream.read(name, 8);
				name[8] = '\0';
				std::string program_name(name);

				//Ignore version & flag
				input_stream.seekg(2, std::ios::cur);

				//Check mirrored length
				input_stream.read(hextet, 2);
				if (block_length != twobyte2int(hextet))
				{
					//Length mirroring wrong
					throw std::wstring(L"Invalid variable block (length mirror).");
				}

				//Get number of tokens
				input_stream.read(hextet, 2);
				int token_count = twobyte2int(hextet);

				//Read the data
				//Subtract 2 from block length (read # of tokens)
				int block_data_length = block_length - 2;
				char * blockp = new char[block_data_length];
				input_stream.read(blockp, block_data_length);

				//Store the block info in the vector
				blocks.push_back({ token_count, std::vector<char>(blockp, blockp + block_data_length), program_name });
				//Decrement the amount of block data left
				blocksize_remain -= (17 + block_length);
			} while (blocksize_remain > 0);

			//Blocks now separated and ready for detokenising (so close stream)
			input_stream.close();

			//Iterate through the blocks
			for (auto block : blocks)
			{
				std::wstring block_string = L"";
				//Convert each byte and append to string
				for (unsigned int i = 0; i < block.tokens.size(); i++)
				{
					/* Other tokens
					0 unused
					26 unused
					5C	2-byte (matrices)
					5D	2-byte (lists)
					5E	2-byte (equations)
					60	2-byte (pictures)
					61	2-byte (GDB)
					62	2-byte (stats)
					63	2-byte (window/finance)
					7E	2-byte (graph format)
					AA	2-byte (string)
					BB	2-byte (misc)
					EF	2-byte (ti 84)
					*/

					unsigned char byte = block.tokens[i];
					std::wstring plaintext_token = single_byte_tokens.at(byte);

					//Ignore unused but check for 2-byte codes, overwriting the default if found
					if (byte == 0x5C) { plaintext_token = matrix_tokens.at(block.tokens[++i]); }
					if (byte == 0x5D) { plaintext_token = list_tokens.at(block.tokens[++i]); }
					if (byte == 0x5E) { plaintext_token = equation_tokens.at(block.tokens[++i]); }
					if (byte == 0x60) { plaintext_token = picture_tokens.at(block.tokens[++i]); }
					if (byte == 0x61) { plaintext_token = GDB_tokens.at(block.tokens[++i]); }
					if (byte == 0x62) { plaintext_token = statistic_var_tokens.at(block.tokens[++i]); }
					if (byte == 0x63) { plaintext_token = window_finance_tokens.at(block.tokens[++i]); }
					if (byte == 0x7E) { plaintext_token = graph_format_tokens.at(block.tokens[++i]); }
					if (byte == 0xAA) { plaintext_token = string_tokens.at(block.tokens[++i]); }
					if (byte == 0xBB) { plaintext_token = misc_tokens.at(block.tokens[++i]); }
					if (byte == 0xEF) { plaintext_token = TI_84_tokens.at(block.tokens[++i]); }

					block_string.append(plaintext_token);
				}

				//Set up output stream
				std::wofstream output_stream;
				output_stream.imbue(utf8_locale);
				output_stream.open(widen_string(block.name) + L".txt");

				//Then contents
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
  return ((unsigned char)arr[1] << 8) + (unsigned char)arr[0];
}