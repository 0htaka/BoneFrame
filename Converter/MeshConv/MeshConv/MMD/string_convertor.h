#ifndef STRING_CONVERTOR_H_
#define STRING_CONVERTOR_H_

#include <string>
#include <vector>

// UTF8をSJISに変換
std::string utf8_to_sjis(const std::vector<unsigned char>& utf8);

// UTF16をSJISに変換
std::string utf16_to_sjis(const std::vector<unsigned char>& utf16);

// SJISをUTF16に変換
std::vector<unsigned char> sjis_to_utf16(const std::string& sjis);

// SJISをwcharに変換
std::string wchar_to_sjis(const std::wstring& utf16);

// SJISをwcharに変換
std::wstring sjis_to_wchar(const std::string& sjis);

// wcharをSJISに変換
std::string wchar_to_sjis(const std::wstring& utf16);

#endif

// end of file
