#ifndef EQUATIONTOKENS_HPP
#define EQUATIONTOKENS_HPP

// See 2ByteSequences.md for more information

const std::unordered_map<char, std::wstring> equation_tokens = {
  { 0x10, L"Y1" },
  { 0x11, L"Y2" },
  { 0x12, L"Y3" },
  { 0x13, L"Y4" },
  { 0x14, L"Y5" },
  { 0x15, L"Y6" },
  { 0x16, L"Y7" },
  { 0x17, L"Y8" },
  { 0x18, L"Y9" },
  { 0x19, L"Y0" },
  { 0x20, L"X1T" },
  { 0x21, L"Y1T" },
  { 0x22, L"X2T" },
  { 0x23, L"Y2T" },
  { 0x24, L"X3T" },
  { 0x25, L"Y3T" },
  { 0x26, L"X4T" },
  { 0x27, L"Y4T" },
  { 0x28, L"X5T" },
  { 0x29, L"Y5T" },
  { 0x2A, L"X6T" },
  { 0x2B, L"Y6T" },
  { 0x40, L"r1" },
  { 0x41, L"r2" },
  { 0x42, L"r3" },
  { 0x43, L"r4" },
  { 0x44, L"r5" },
  { 0x45, L"r6" },
  { 0x80, L"u" },
  { 0x81, L"v" },
  { 0x82, L"w" }
};

#endif // !EQUATIONTOKENS_HPP
