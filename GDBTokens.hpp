#ifndef GDBTOKENS_HPP
#define GDBTOKENS_HPP

// See 2ByteSequences.md for more information

const std::unordered_map<char, std::wstring> GDB_tokens = {
  { 0x00, L"GDB1" },
  { 0x01, L"GDB2" },
  { 0x02, L"GDB3" },
  { 0x03, L"GDB4" },
  { 0x04, L"GDB5" },
  { 0x05, L"GDB6" },
  { 0x06, L"GDB7" },
  { 0x07, L"GDB8" },
  { 0x08, L"GDB9" },
  { 0x09, L"GDB0" }
};

#endif // !GDBTOKENS_HPP
