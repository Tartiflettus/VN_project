#ifndef DEF_FILELOADER_HPP
#define DEF_FILELOADER_HPP

#include <string>
#include <fstream>


//create an empty object, use the loadFromfile method, and return it
template <typename T>
T createFromFile(const std::wstring &file);

#include "FileLoader.tpp"



const std::string SCENE_DIRECTORY = std::string("gameData/scenario/");
const std::wstring CHARACHTER_DIRECTORY = std::wstring(L"gameData/images/characters/");


std::wstring getBlock(std::wifstream &scenario, wchar_t start = L'[', wchar_t end = L']');

std::wstring getBlock(const std::wstring &scenario, std::size_t &pos, wchar_t start = L'[', wchar_t end = L']');


//Test if \prefix is prefix of \str, starting at \pos
//Return the first character after the prefix, or npos if not found
std::wstring::size_type findPrefix(const std::wstring &str, const std::wstring &prefix, std::wstring::size_type pos = 0);



std::wstring cutPath(const std::wstring &str);


std::wstring selectFile(const std::wstring& message = std::wstring(L"select a file"));



//std::wstring getPrefix(const std::wstring &str);



#endif
