#ifndef GRAPHFORMATTOKENS_HPP
#define GRAPHFORMATTOKENS_HPP

// See 2ByteSequences.md for more information

const std::unordered_map<char, std::wstring> graph_format_tokens = {
  { 0x00, L"Sequential" },
  { 0x01, L"Simul" },
  { 0x02, L"PolarGC" },
  { 0x03, L"RectGC" },
  { 0x04, L"CoordOn" },
  { 0x05, L"CoordOff" },
  { 0x06, L"Connected" },
  { 0x07, L"Dot" },
  { 0x08, L"AxesOn" },
  { 0x09, L"AxesOff" },
  { 0x0A, L"GridOn" },
  { 0x0B, L"GridOff" },
  { 0x0C, L"LabelOn" },
  { 0x0D, L"LabelOff" },
  { 0x0E, L"Web" },
  { 0x0F, L"Time" },
  { 0x10, L"uvAxes" },
  { 0x11, L"vwAxes" },
  { 0x12, L"uwAxes" }
};

#endif // !GRAPHFORMATTOKENS_HPP
