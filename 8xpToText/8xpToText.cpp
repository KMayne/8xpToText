#include "stdafx.hpp"

static const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> utf_converter;

static const std::unordered_map<char, std::wstring> ti_octet_tokens = {
	{ 0x00, L"[error: unused code point]" },
	{ 0x0A, L"r" },
	{ 0x0B, L"\u00B0" },
	{ 0x0C, L"\05BF\u00B9" },
	{ 0x0D, L"\u00B2" },
	{ 0x0E, L"T" },
	{ 0x0F, L"\u00B3" },
	{ 0x01, L"\u25BADMS" },
	{ 0x10, L"(" },
	{ 0x11, L")" },
	{ 0x12, L"round(" },
	{ 0x13, L"pxl-Test(" },
	{ 0x14, L"augment(" },
	{ 0x15, L"rowSwap(" },
	{ 0x16, L"row+(" },
	{ 0x17, L"*row(" },
	{ 0x18, L"*row+(" },
	{ 0x19, L"max(" },
	{ 0x1A, L"min(" },
	{ 0x1B, L"R\u25BAPr(" },
	{ 0x1C, L"R\u25BAP\u03B8(" },
	{ 0x1D, L"P\u25BARx(" },
	{ 0x1E, L"P\u25BARy" },
	{ 0x1F, L"median(" },
	{ 0x02, L"\u25BADec" },
	{ 0x20, L"randM(" },
	{ 0x21, L"mean(" },
	{ 0x22, L"solve(" },
	{ 0x23, L"seq(" },
	{ 0x24, L"fnInt(" },
	{ 0x25, L"nDeriv(" },
	{ 0x26, L"[error: unused code point]" },
	{ 0x27, L"fMin(" },
	{ 0x28, L"fMax(" },
	{ 0x29, L" " },
	{ 0x2A, L"\"" },
	{ 0x2B, L"," },
	{ 0x2C, L"i" },
	{ 0x2D, L"!" },
	{ 0x2E, L"CubicReg" },
	{ 0x2F, L"QuartReg" },
	{ 0x03, L"\u25BAFrac" },
	{ 0x30, L"0" },
	{ 0x31, L"1" },
	{ 0x32, L"2" },
	{ 0x33, L"3" },
	{ 0x34, L"4" },
	{ 0x35, L"5" },
	{ 0x36, L"6" },
	{ 0x37, L"7" },
	{ 0x38, L"8" },
	{ 0x39, L"9" },
	{ 0x3A, L"." },
	{ 0x3B, L"E" },
	{ 0x3C, L"or" },
	{ 0x3D, L"xor" },
	{ 0x3E, L":" },
	{ 0x3F, L"\n" },
	{ 0x04, L"\u2192" },
	{ 0x40, L"and" },
	{ 0x41, L"A" },
	{ 0x42, L"B" },
	{ 0x43, L"C" },
	{ 0x44, L"D" },
	{ 0x45, L"E" },
	{ 0x46, L"F" },
	{ 0x47, L"G" },
	{ 0x48, L"H" },
	{ 0x49, L"I" },
	{ 0x4A, L"J" },
	{ 0x4B, L"K" },
	{ 0x4C, L"L" },
	{ 0x4D, L"M" },
	{ 0x4E, L"N" },
	{ 0x4F, L"O" },
	{ 0x05, L"Boxplot" },
	{ 0x50, L"P" },
	{ 0x51, L"Q" },
	{ 0x52, L"R" },
	{ 0x53, L"S" },
	{ 0x54, L"T" },
	{ 0x55, L"U" },
	{ 0x56, L"V" },
	{ 0x57, L"W" },
	{ 0x58, L"X" },
	{ 0x59, L"Y" },
	{ 0x5A, L"Z" },
	{ 0x5B, L"\u03B8" },
	{ 0x5C, L"[error: unknown 2-byte code]" },
	{ 0x5D, L"[error: unknown 2-byte code]" },
	{ 0x5E, L"[error: unknown 2-byte code]" },
	{ 0x5F, L"prgm" },
	{ 0x06, L"[" },
	{ 0x60, L"[error: unknown 2-byte code]" },
	{ 0x61, L"[error: unknown 2-byte code]" },
	{ 0x62, L"[error: unknown 2-byte code]" },
	{ 0x63, L"[error: unknown 2-byte code]" },
	{ 0x64, L"Radian" },
	{ 0x65, L"Degree" },
	{ 0x66, L"Normal" },
	{ 0x67, L"Sci" },
	{ 0x68, L"Eng" },
	{ 0x69, L"Float" },
	{ 0x6A, L"=" },
	{ 0x6B, L"<" },
	{ 0x6C, L">" },
	{ 0x6D, L"\u2264" },
	{ 0x6E, L"\u2266" },
	{ 0x6F, L"\u2260" },
	{ 0x07, L"]" },
	{ 0x70, L"+" },
	{ 0x71, L"-" },
	{ 0x72, L"Ans" },
	{ 0x73, L"Fix" },
	{ 0x74, L"Horiz" },
	{ 0x75, L"Full" },
	{ 0x76, L"Func" },
	{ 0x77, L"Param" },
	{ 0x78, L"Polar" },
	{ 0x79, L"Seq" },
	{ 0x7A, L"IndpntAuto" },
	{ 0x7B, L"IndpntAsk" },
	{ 0x7C, L"DependAuto" },
	{ 0x7D, L"DependAsk" },
	{ 0x7E, L"[error: unknown 2-byte code]" },
	{ 0x7F, L"[square mark]" },
	{ 0x08, L"{" },
	{ 0x80, L"[plus mark]" },
	{ 0x81, L"[dot mark]" },
	{ 0x82, L"*" },
	{ 0x83, L"/" },
	{ 0x84, L"Trace" },
	{ 0x85, L"ClrDraw" },
	{ 0x86, L"ZStandard" },
	{ 0x87, L"ZTrig" },
	{ 0x88, L"ZBox" },
	{ 0x89, L"Zoom In" },
	{ 0x8A, L"Zoom Out" },
	{ 0x8B, L"ZSquare" },
	{ 0x8C, L"ZInteger" },
	{ 0x8D, L"ZPrevious" },
	{ 0x8E, L"ZDecimal" },
	{ 0x8F, L"ZoomStat" },
	{ 0x09, L"}" },
	{ 0x90, L"ZoomRcl" },
	{ 0x91, L"PrintScreen" },
	{ 0x92, L"ZoomSto" },
	{ 0x93, L"Text(" },
	{ 0x94, L" nPr " },
	{ 0x95, L" nCr " },
	{ 0x96, L"FnOn" },
	{ 0x97, L"FnOff" },
	{ 0x98, L"StorePic" },
	{ 0x99, L"RecallPic" },
	{ 0x9A, L"StoreGDB" },
	{ 0x9B, L"RecallGDB" },
	{ 0x9C, L"Line(" },
	{ 0x9D, L"Vertical" },
	{ 0x9E, L"Pt-On(" },
	{ 0x9F, L"Pt-Off(" },
	{ 0xA0, L"Pt-Change(" },
	{ 0xA1, L"Pxl-On(" },
	{ 0xA2, L"Pxl-Off(" },
	{ 0xA3, L"Pxl-Change(" },
	{ 0xA4, L"Shade(" },
	{ 0xA5, L"Circle(" },
	{ 0xA6, L"Horizontal" },
	{ 0xA7, L"Tangent(" },
	{ 0xA8, L"DrawInv" },
	{ 0xA9, L"DrawF" },
	{ 0xAA, L"[error: unknown 2-byte code]" },
	{ 0xAB, L"rand" },
	{ 0xAC, L"\u03C0" },
	{ 0xAD, L"getKey" },
	{ 0xAE, L"\'" },
	{ 0xAF, L"\?" },
	{ 0xB0, L"-" },
	{ 0xB1, L"int(" },
	{ 0xB2, L"abs(" },
	{ 0xB3, L"det(" },
	{ 0xB4, L"identity(" },
	{ 0xB5, L"dim(" },
	{ 0xB6, L"sum(" },
	{ 0xB7, L"prod(" },
	{ 0xB8, L"not(" },
	{ 0xB9, L"iPart(" },
	{ 0xBA, L"fPart(" },
	{ 0xBB, L"[error: unknown 2-byte code]" },
	{ 0xBC, L"\u221A(" },
	{ 0xBD, L"\u00B3\u221A(" },
	{ 0xBE, L"ln(" },
	{ 0xBF, L"e^(" },
	{ 0xC0, L"log(" },
	{ 0xC1, L"10^(" },
	{ 0xC2, L"sin(" },
	{ 0xC3, L"sin\u05BF\u00B9(" },
	{ 0xC4, L"cos(" },
	{ 0xC5, L"cos\u05BF\u00B9(" },
	{ 0xC6, L"tan(" },
	{ 0xC7, L"tan\u05BF\u00B9(" },
	{ 0xC8, L"sinh(" },
	{ 0xC9, L"sinh\u05BF\u00B9(" },
	{ 0xCA, L"cosh(" },
	{ 0xCB, L"cosh\u05BF\u00B9(" },
	{ 0xCC, L"tanh(" },
	{ 0xCD, L"tanh\u05BF\u00B9(" },
	{ 0xCE, L"If" },
	{ 0xCF, L"Then" },
	{ 0xD0, L"Else" },
	{ 0xD1, L"While" },
	{ 0xD2, L"Repeat" },
	{ 0xD3, L"For(" },
	{ 0xD4, L"End" },
	{ 0xD5, L"Return" },
	{ 0xD6, L"Lbl" },
	{ 0xD7, L"Goto" },
	{ 0xD8, L"Pause" },
	{ 0xD9, L"Stop" },
	{ 0xDA, L"IS>(" },
	{ 0xDB, L"DS<(" },
	{ 0xDC, L"Input " },
	{ 0xDD, L"Prompt " },
	{ 0xDE, L"Disp " },
	{ 0xDF, L"DispGraph" },
	{ 0xE0, L"Output(" },
	{ 0xE1, L"ClrHome" },
	{ 0xE2, L"Fill(" },
	{ 0xE3, L"SortA(" },
	{ 0xE4, L"SortD(" },
	{ 0xE5, L"DispTable" },
	{ 0xE6, L"Menu(" },
	{ 0xE7, L"Send(" },
	{ 0xE8, L"Get(" },
	{ 0xE9, L"PlotsOn" },
	{ 0xEA, L"PlotsOff" },
	{ 0xEB, L"\u221F" },
	{ 0xEC, L"Plot1(" },
	{ 0xED, L"Plot2(" },
	{ 0xEE, L"Plot3(" },
	{ 0xEF, L"[error: unknown 2-byte code]" },
	{ 0xF0, L"^" },
	{ 0xF1, L"\u00D7\u221A" },
	{ 0xF2, L"1-Var Stats" },
	{ 0xF3, L"2-Var Stats" },
	{ 0xF4, L"LinReg(a+bx)" },
	{ 0xF5, L"ExpReg" },
	{ 0xF6, L"LnReg" },
	{ 0xF7, L"PwrReg" },
	{ 0xF8, L"Med-Med" },
	{ 0xF9, L"QuadReg" },
	{ 0xFA, L"ClrList" },
	{ 0xFB, L"ClrTable" },
	{ 0xFC, L"Histogram" },
	{ 0xFD, L"xyLine" },
	{ 0xFE, L"Scatter" },
	{ 0xFF, L"LinReg(ax+b)" }
};
static const std::unordered_map<char, std::wstring> matrix_tokens = {
	{0x00, L"[A]"},
	{0x01, L"[B]"},
	{0x02, L"[C]"},
	{0x03, L"[D]"},
	{0x04, L"[E]"},
	{0x05, L"[F]"},
	{0x06, L"[G]"},
	{0x07, L"[H]"},
	{0x08, L"[I]"},
	{0x09, L"[J]"}
};
static const std::unordered_map<char, std::wstring> list_tokens = {
	{ 0x00, L"L1"},
	{ 0x01, L"L2"},
	{ 0x02, L"L3"},
	{ 0x03, L"L4"},
	{ 0x04, L"L5"},
	{ 0x05, L"L6"}
};
static const std::unordered_map<char, std::wstring> equation_tokens = {
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
static const std::unordered_map<char, std::wstring> picture_tokens = {
	{ 0x00, L"Pic1" },
	{ 0x01, L"Pic2" },
	{ 0x02, L"Pic3" },
	{ 0x03, L"Pic4" },
	{ 0x04, L"Pic5" },
	{ 0x05, L"Pic6" },
	{ 0x06, L"Pic7" },
	{ 0x07, L"Pic8" },
	{ 0x08, L"Pic9" },
	{ 0x09, L"Pic0" }
};
static const std::unordered_map<char, std::wstring> GDB_tokens = {
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
static const std::unordered_map<char, std::wstring> string_tokens = {
	{ 0x00, L"Str1" },
	{ 0x01, L"Str2" },
	{ 0x02, L"Str3" },
	{ 0x03, L"Str4" },
	{ 0x04, L"Str5" },
	{ 0x05, L"Str6" },
	{ 0x06, L"Str7" },
	{ 0x07, L"Str8" },
	{ 0x08, L"Str9" },
	{ 0x09, L"Str0" }
};
static const std::unordered_map<char, std::wstring> statistic_var_tokens = {
	{ 0x00, L"internal use only" },
	{ 0x01, L"RegEq" },
	{ 0x02, L"n" },
	{ 0x03, L"x\u00af" },
	{ 0x04, L"\u03a3x" },
	{ 0x05, L"\u03a3x\u00b2" },
	{ 0x06, L"Sx" },
	{ 0x07, L"\u03c3x" },
	{ 0x08, L"minX" },
	{ 0x09, L"maxX" },
	{ 0x0A, L"minY" },
	{ 0x0B, L"maxY" },
	{ 0x0C, L"y\u00af" },
	{ 0x0D, L"\u03a3y" },
	{ 0x0E, L"\u03a3y\u00b2" },
	{ 0x0F, L"Sy" },
	{ 0x10, L"\u03c3y" },
	{ 0x11, L"\u03a3xy" },
	{ 0x12, L"r" },
	{ 0x13, L"Med" },
	{ 0x14, L"Q1" },
	{ 0x15, L"Q3" },
	{ 0x16, L"a" },
	{ 0x17, L"b" },
	{ 0x18, L"c" },
	{ 0x19, L"d" },
	{ 0x1A, L"e" },
	{ 0x1B, L"x1" },
	{ 0x1C, L"x2" },
	{ 0x1D, L"3" },
	{ 0x1E, L"y1" },
	{ 0x1F, L"y2" },
	{ 0x20, L"3" },
	{ 0x21, L"n" },
	{ 0x22, L"p" },
	{ 0x23, L"z" },
	{ 0x24, L"t" },
	{ 0x25, L"\u03c7\u00b2" },
	{ 0x26, L"F" },
	{ 0x27, L"df" },
	{ 0x28, L"p^" },
	{ 0x29, L"p^1" },
	{ 0x2A, L"p^2" },
	{ 0x2B, L"x\u00af1" },
	{ 0x2C, L"Sx1" },
	{ 0x2D, L"n1" },
	{ 0x2E, L"x\u00af2" },
	{ 0x2F, L"Sx2" },
	{ 0x30, L"n2" },
	{ 0x31, L"Sxp" },
	{ 0x32, L"lower" },
	{ 0x33, L"upper" },
	{ 0x34, L"s" },
	{ 0x35, L"r2" },
	{ 0x36, L"R2" },
	{ 0x37, L"Factor df" },
	{ 0x38, L"Factor SS" },
	{ 0x39, L"Factor MS" },
	{ 0x3A, L"Error df" },
	{ 0x3B, L"Error SS" },
	{ 0x3C, L"Error MS" }
};
static const std::unordered_map<char, std::wstring> window_finance_tokens = {
	{ 0x00, L"ZXscl" },
	{ 0x01, L"ZYscl" },
	{ 0x02, L"Xscl" },
	{ 0x03, L"Yscl" },
	{ 0x04, L"u(nMin)" },
	{ 0x05, L"v(nMin)" },
	{ 0x06, L"u(n-1)" },
	{ 0x07, L"v(n-1)" },
	{ 0x08, L"Zu(nMin)" },
	{ 0x09, L"Zv(nMin)" },
	{ 0x0A, L"Xmin" },
	{ 0x0B, L"Xmax" },
	{ 0x0C, L"Ymin" },
	{ 0x0D, L"Ymax" },
	{ 0x0E, L"Tmin" },
	{ 0x0F, L"Tmax" },
	{ 0x10, L"\u03b8min" },
	{ 0x11, L"\u03b8max" },
	{ 0x12, L"ZXmin" },
	{ 0x13, L"ZXmax" },
	{ 0x14, L"ZYmin" },
	{ 0x15, L"ZYmax" },
	{ 0x16, L"Z\u03b8min" },
	{ 0x17, L"Z\u03b8max" },
	{ 0x18, L"ZTmin" },
	{ 0x19, L"ZTmax" },
	{ 0x1A, L"TblStart" },
	{ 0x1B, L"PlotStart" },
	{ 0x1C, L"ZPlotStart" },
	{ 0x1D, L"nMax" },
	{ 0x1E, L"ZnMax" },
	{ 0x1F, L"nMin" },
	{ 0x20, L"ZnMin" },
	{ 0x21, L"\u0394Tbl" },
	{ 0x22, L"Tstep" },
	{ 0x23, L"\u03b8step" },
	{ 0x24, L"ZTstep" },
	{ 0x25, L"Z\u03b8step" },
	{ 0x26, L"\u0394X" },
	{ 0x27, L"\u0394Y" },
	{ 0x28, L"XFact" },
	{ 0x29, L"YFact" },
	{ 0x2A, L"TblInput" },
	{ 0x2B, L"N" },
	{ 0x2C, L"I%%" },
	{ 0x2D, L"PV" },
	{ 0x2E, L"PMT" },
	{ 0x2F, L"FV" },
	{ 0x30, L"P/Y" },
	{ 0x31, L"C/Y" },
	{ 0x32, L"w(nMin)" },
	{ 0x33, L"Zw(nMin)" },
	{ 0x34, L"PlotStep" },
	{ 0x35, L"ZPlotStep" },
	{ 0x36, L"Xres" },
	{ 0x37, L"ZXres" }
};
static const std::unordered_map<char, std::wstring> graph_format_tokens = {
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
static const std::unordered_map<char, std::wstring> misc_tokens = {
	{ 0x00, L"npv(" },
	{ 0x01, L"irr(" },
	{ 0x02, L"bal(" },
	{ 0x03, L"\u03a3prn(" },
	{ 0x04, L"\u03a3Int(" },
	{ 0x05, L"\u25baNom(" },
	{ 0x06, L"\u25baEff(" },
	{ 0x07, L"dbd(" },
	{ 0x08, L"lcm(" },
	{ 0x09, L"gcd(" },
	{ 0x0A, L"randInt(" },
	{ 0x0B, L"randBin(" },
	{ 0x0C, L"sub(" },
	{ 0x0D, L"stdDev(" },
	{ 0x0E, L"variance(" },
	{ 0x0F, L"inString(" },
	{ 0x10, L"normalcdf(" },
	{ 0x11, L"invNorm(" },
	{ 0x12, L"tcdf(" },
	{ 0x13, L"\u03c7\u00b2cdf(" },
	{ 0x14, L"Fcdf(" },
	{ 0x15, L"binompdf(" },
	{ 0x16, L"binomcdf(" },
	{ 0x17, L"poissonpdf(" },
	{ 0x18, L"poissoncdf(" },
	{ 0x19, L"geometpdf(" },
	{ 0x1A, L"geometcdf(" },
	{ 0x1B, L"normalpdf(" },
	{ 0x1C, L"tpdf(" },
	{ 0x1D, L"\u03c7\u00b2pdf(" },
	{ 0x1E, L"Fpdf(" },
	{ 0x1F, L"randNorm(" },
	{ 0x20, L"tvm_Pmt" },
	{ 0x21, L"tvm_I%%" },
	{ 0x22, L"tvm_PV" },
	{ 0x23, L"tvm_N" },
	{ 0x24, L"tvm_FV" },
	{ 0x25, L"conj(" },
	{ 0x26, L"real(" },
	{ 0x27, L"imag(" },
	{ 0x28, L"angle(" },
	{ 0x29, L"cumSum(" },
	{ 0x2A, L"expr(" },
	{ 0x2B, L"length(" },
	{ 0x2C, L"\u0394List(" },
	{ 0x2D, L"ref(" },
	{ 0x2E, L"rref(" },
	{ 0x2F, L"\u25baRect" },
	{ 0x30, L"\u25baPolar" },
	{ 0x31, L"e" },
	{ 0x32, L"SinReg" },
	{ 0x33, L"Logistic" },
	{ 0x34, L"LinRegTTest" },
	{ 0x35, L"ShadeNorm(" },
	{ 0x36, L"Shade_t(" },
	{ 0x37, L"Shade\u03c7\u00b2" },
	{ 0x38, L"ShadeF(" },
	{ 0x39, L"Matr\u25balist(" },
	{ 0x3A, L"List\u25bamatr(" },
	{ 0x3B, L"Z-Test(" },
	{ 0x3C, L"T-Test" },
	{ 0x3D, L"2-SampZTest(" },
	{ 0x3E, L"1-PropZTest(" },
	{ 0x3F, L"2-PropZTest(" },
	{ 0x40, L"\u03c7\u00b2-Test(" },
	{ 0x41, L"ZInterval" },
	{ 0x42, L"2-SampZInt(" },
	{ 0x43, L"1-PropZInt(" },
	{ 0x44, L"2-PropZInt(" },
	{ 0x45, L"GraphStyle(" },
	{ 0x46, L"2-SampTTest" },
	{ 0x47, L"2-SampFTest" },
	{ 0x48, L"TInterval" },
	{ 0x49, L"2-SampTInt" },
	{ 0x4A, L"SetUpEditor" },
	{ 0x4B, L"Pmt_End" },
	{ 0x4C, L"Pmt_Bgn" },
	{ 0x4D, L"Real" },
	{ 0x4E, L"re^\u03b8i" },
	{ 0x4F, L"a+bi" },
	{ 0x50, L"ExprOn" },
	{ 0x51, L"ExprOff" },
	{ 0x52, L"ClrAllLists" },
	{ 0x53, L"GetCalc(" },
	{ 0x54, L"DelVar" },
	{ 0x55, L"Equ\u25baString(" },
	{ 0x56, L"String\u25baEqu(" },
	{ 0x57, L"Clear Entries" },
	{ 0x58, L"Select(" },
	{ 0x59, L"ANOVA(" },
	{ 0x5A, L"ModBoxplot" },
	{ 0x5B, L"NormProbPlot" },
	{ 0x5C, L"[error: unused code point]" },
	{ 0x5D, L"[error: unused code point]" },
	{ 0x5E, L"[error: unused code point]" },
	{ 0x5F, L"[error: unused code point]" },
	{ 0x60, L"[error: unused code point]" },
	{ 0x61, L"[error: unused code point]" },
	{ 0x62, L"[error: unused code point]" },
	{ 0x63, L"[error: unused code point]" },
	{ 0x64, L"G-T" },
	{ 0x65, L"ZoomFit" },
	{ 0x66, L"DiagnosticOn" },
	{ 0x67, L"DiagnosticOff" },
	{ 0x68, L"Archive" },
	{ 0x69, L"UnArchive" },
	{ 0x6A, L"Asm(" },
	{ 0x6B, L"AsmComp(" },
	{ 0x6C, L"AsmPrgm" },
	{ 0x6D, L"compiled asm" },
	{ 0x6E, L"\u00c1" },
	{ 0x6F, L"\u00c0" },
	{ 0x70, L"\u00c2" },
	{ 0x71, L"\u00c4" },
	{ 0x72, L"\u00e1" },
	{ 0x73, L"\u00e0" },
	{ 0x74, L"\u00e2" },
	{ 0x75, L"\u00e4" },
	{ 0x76, L"\u00c9" },
	{ 0x77, L"\u00c8" },
	{ 0x78, L"\u00ca" },
	{ 0x79, L"\u00cb" },
	{ 0x7A, L"\u00e9" },
	{ 0x7B, L"\u00e8" },
	{ 0x7C, L"\u00ea" },
	{ 0x7D, L"\u00eb" },
	{ 0x7E, L"[error: unused code point]" },
	{ 0x7F, L"\u00cc" },
	{ 0x80, L"\u00ce" },
	{ 0x81, L"\u00cf" },
	{ 0x82, L"\u00ed" },
	{ 0x83, L"\u00ec" },
	{ 0x84, L"\u00ee" },
	{ 0x85, L"\u00ef" },
	{ 0x86, L"\u00d3" },
	{ 0x87, L"\u00d2" },
	{ 0x88, L"\u00d4" },
	{ 0x89, L"\u00d6" },
	{ 0x8A, L"\u00f3" },
	{ 0x8B, L"\u00f2" },
	{ 0x8C, L"\u00f4" },
	{ 0x8D, L"\u00f6" },
	{ 0x8E, L"\u00da" },
	{ 0x8F, L"\u00d9" },
	{ 0x90, L"\u00db" },
	{ 0x91, L"\u00dc" },
	{ 0x92, L"\u00fa" },
	{ 0x93, L"\u00f9" },
	{ 0x94, L"\u00fb" },
	{ 0x95, L"\u00fc" },
	{ 0x96, L"\u00c7" },
	{ 0x97, L"\u00e7" },
	{ 0x98, L"\u00d1" },
	{ 0x99, L"\u00f1" },
	{ 0x9A, L"\u00b4" },
	{ 0x9B, L"`" },
	{ 0x9C, L"\u00a8" },
	{ 0x9D, L"\u00bf" },
	{ 0x9E, L"\u00a1" },
	{ 0x9F, L"\u03b1" },
	{ 0xA0, L"\u03b2" },
	{ 0xA1, L"\u03b3" },
	{ 0xA2, L"\u0394" },
	{ 0xA3, L"\u03b4" },
	{ 0xA4, L"\u03b5" },
	{ 0xA5, L"\u03bb" },
	{ 0xA6, L"\u03bc" },
	{ 0xA7, L"\u03c0" },
	{ 0xA8, L"\u03c1" },
	{ 0xA9, L"\u03a3" },
	{ 0xAA, L"[error: unused code point]" },
	{ 0xAB, L"\u03c6" },
	{ 0xAC, L"\u03a9" },
	{ 0xAD, L"p^" },
	{ 0xAE, L"\u03c7" },
	{ 0xAF, L"F" },
	{ 0xB0, L"a" },
	{ 0xB1, L"b" },
	{ 0xB2, L"c" },
	{ 0xB3, L"d" },
	{ 0xB4, L"e" },
	{ 0xB5, L"f" },
	{ 0xB6, L"g" },
	{ 0xB7, L"h" },
	{ 0xB8, L"i" },
	{ 0xB9, L"j" },
	{ 0xBA, L"k" },
	{ 0xBB, L"[error: unused code point]" },
	{ 0xBC, L"l" },
	{ 0xBD, L"m" },
	{ 0xBE, L"n" },
	{ 0xBF, L"o" },
	{ 0xC0, L"p" },
	{ 0xC1, L"q" },
	{ 0xC2, L"r" },
	{ 0xC3, L"s" },
	{ 0xC4, L"t" },
	{ 0xC5, L"u" },
	{ 0xC6, L"v" },
	{ 0xC7, L"w" },
	{ 0xC8, L"x" },
	{ 0xC9, L"y" },
	{ 0xCA, L"z" },
	{ 0xCB, L"\u03c3" },
	{ 0xCC, L"\u03c4" },
	{ 0xCD, L"\u00cd" },
	{ 0xCE, L"GarbageCollect" },
	{ 0xCF, L"~" },
	{ 0xD0, L"reserved" },
	{ 0xD1, L"@" },
	{ 0xD2, L"#" },
	{ 0xD3, L"$" },
	{ 0xD4, L"&" },
	{ 0xD5, L"`" },
	{ 0xD6, L";" },
	{ 0xD7, L"\\" },
	{ 0xD8, L"|" },
	{ 0xD9, L"_" },
	{ 0xDA, L"%%" },
	{ 0xDB, L"\u2026" },
	{ 0xDC, L"\u2220" },
	{ 0xDD, L"\u00df" },
	{ 0xDE, L"x" },
	{ 0xDF, L"T" },
	{ 0xE0, L"0" },
	{ 0xE1, L"1" },
	{ 0xE2, L"2" },
	{ 0xE3, L"3" },
	{ 0xE4, L"4" },
	{ 0xE5, L"5" },
	{ 0xE6, L"6" },
	{ 0xE7, L"7" },
	{ 0xE8, L"8" },
	{ 0xE9, L"9" },
	{ 0xEA, L"10" },
	{ 0xEB, L"\u2190" },
	{ 0xEC, L"\u2192" },
	{ 0xED, L"\u2191" },
	{ 0xEE, L"\u2193" },
	{ 0xEF, L"[error: unused code point]" },
	{ 0xF0, L"x" },
	{ 0xF1, L"\u222b" },
	{ 0xF2, L"[up arrow]" },
	{ 0xF3, L"[down arrow]" },
	{ 0xF4, L"\u221a" },
	{ 0xF5, L"[equals block]" },
	{ 0xF6, L"[error: unused code point]" },
	{ 0xF7, L"[error: unused code point]" },
	{ 0xF8, L"[error: unused code point]" },
	{ 0xF9, L"[error: unused code point]" },
	{ 0xFA, L"[error: unused code point]" },
	{ 0xFB, L"[error: unused code point]" },
	{ 0xFC, L"[error: unused code point]" },
	{ 0xFD, L"[error: unused code point]" },
	{ 0xFE, L"[error: unused code point]" },
	{ 0xFF, L"[error: unused code point]" }
};
static const std::unordered_map<char, std::wstring> TI_84_tokens = {
	{ 0x00, L"setDate(" },
	{ 0x01, L"setTime(" },
	{ 0x02, L"checkTmr(" },
	{ 0x03, L"setDtFmt(" },
	{ 0x04, L"setTmFmt(" },
	{ 0x05, L"timeCnv(" },
	{ 0x06, L"dayOfWk(" },
	{ 0x07, L"getDtStr" },
	{ 0x08, L"getTmStr(" },
	{ 0x09, L"getDate" },
	{ 0x0A, L"getTime" },
	{ 0x0B, L"startTmr" },
	{ 0x0C, L"getDtFmt" },
	{ 0x0D, L"getTmFmt" },
	{ 0x0E, L"isClockOn" },
	{ 0x0F, L"ClockOff" },
	{ 0x10, L"ClockOn" },
	{ 0x11, L"OpenLib(" },
	{ 0x12, L"ExecLib" },
	{ 0x13, L"invT(" },
	{ 0x14, L"\u03c7\u00b2GOF-Test(" },
	{ 0x15, L"LinRegTInt" },
	{ 0x16, L"Manual-Fit" },
	{ 0x17, L"ZQuadrant1" },
	{ 0x18, L"ZFrac1/2" },
	{ 0x19, L"ZFrac1/3" },
	{ 0x1A, L"ZFrac1/4" },
	{ 0x1B, L"ZFrac1/5" },
	{ 0x1C, L"ZFrac1/8" },
	{ 0x1D, L"ZFrac1/10" },
	{ 0x1E, L"mathprintbox" },
	{ 0x30, L"\u25ban/d\u25c4\u25baUn/d" },
	{ 0x31, L"\u25baF\u25c4\u25baD" },
	{ 0x32, L"remainder(" },
	{ 0x33, L"\u03a3(" },
	{ 0x34, L"logBASE(" },
	{ 0x35, L"randIntNoRep(" },
	{ 0x36, L"MATHPRINT" },
	{ 0x37, L"CLASSIC" },
	{ 0x38, L"n/d" },
	{ 0x39, L"Un/d" },
	{ 0x3A, L"AUTO" },
	{ 0x3B, L"DEC" },
	{ 0x3C, L"FRAC" },
	{ 0x3D, L"FRAC-APPROX" },
	{ 0x41, L"BLUE" },
	{ 0x42, L"RED" },
	{ 0x43, L"BLACK" },
	{ 0x44, L"MAGENTA" },
	{ 0x45, L"GREEN" },
	{ 0x46, L"ORANGE" },
	{ 0x47, L"BROWN" },
	{ 0x48, L"NAVY" },
	{ 0x49, L"LTBLUE" },
	{ 0x4A, L"YELLOW" },
	{ 0x4B, L"WHITE" },
	{ 0x4C, L"LTGREY" },
	{ 0x4D, L"MEDGREY" },
	{ 0x4E, L"GREY" },
	{ 0x4F, L"DARKGREY" },
	{ 0x50, L"Image1" },
	{ 0x51, L"Image2" },
	{ 0x52, L"Image3" },
	{ 0x53, L"Image4" },
	{ 0x54, L"Image5" },
	{ 0x55, L"Image6" },
	{ 0x56, L"Image7" },
	{ 0x57, L"Image8" },
	{ 0x58, L"Image9" },
	{ 0x59, L"Image0" },
	{ 0x5A, L"Gridline" },
	{ 0x5B, L"BackgroundOn" },
	{ 0x64, L"BackgroundOff" },
	{ 0x65, L"GraphColor" },
	{ 0x67, L"TextColor(" },
	{ 0x68, L"Asm84CPrgm" },
	{ 0x6A, L"DetectAsymOn" },
	{ 0x6B, L"DetectAsymOff" },
	{ 0x6C, L"BorderColor" },
	{ 0x73, L"tinydotplot" },
	{ 0x74, L"Thin" },
	{ 0x75, L"Dot-Thin" },
	{ 0x79, L"PlySmth2" },
	{ 0x7A, L"Asm84CEPrgm" },
	{ 0x81, L"Quartiles Setting\u2026" },
	{ 0x82, L"u(n-2)" },
	{ 0x83, L"v(n-2)" },
	{ 0x84, L"w(n-2)" },
	{ 0x85, L"u(n-1)" },
	{ 0x86, L"v(n-1)" },
	{ 0x87, L"w(n-1)" },
	{ 0x88, L"u(n)" },
	{ 0x89, L"v(n)" },
	{ 0x8A, L"w(n)" },
	{ 0x8B, L"u(n+1)" },
	{ 0x8C, L"v(n+1)" },
	{ 0x8D, L"w(n+1)" },
	{ 0x8E, L"pieceWise(" },
	{ 0x8F, L"SEQ(n)" },
	{ 0x90, L"SEQ(n+1)" },
	{ 0x91, L"SEQ(n+2)" },
	{ 0x92, L"LEFT" },
	{ 0x93, L"CENTER" },
	{ 0x94, L"RIGHT" },
	{ 0x95, L"invBinom(" },
	{ 0x96, L"Wait" },
	{ 0x97, L"toString(" },
	{ 0x98, L"eval"  }
};

struct token_block {
	int token_count;
	std::vector<char> tokens;
	std::string name;
};

inline int twobyte2int(char arr[])
{
	return ((unsigned char)arr[1] << 8) + (unsigned char)arr[0];
}

inline std::wstring widen_string(std::string str)
{
	return utf_converter.from_bytes(str);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//Make console output unicode
	_setmode(_fileno(stdout), _O_U8TEXT);
	//Iterate through all the arguments and convert each of them
	for (int i = 1; i < argc; i++)
	{
		try
		{
			//Set up the block vector
			std::vector<token_block> blocks;

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
					std::wstring plaintext_token = ti_octet_tokens.at(byte);

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
