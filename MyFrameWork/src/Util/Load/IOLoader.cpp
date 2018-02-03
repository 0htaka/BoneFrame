#include "IOLoader.h"

#include <fstream>
#include <vector>
#include <filesystem>

std::vector<u_char> IOLoader::Load(const std::string & filePath)
{
	std::ifstream file(filePath, std::ios::in, std::ios::binary);
	if (!file)
		throw std::runtime_error("can not open" + filePath);

	auto size = GerFileSize(file);
	// シェーダーファイルをバッファに読み込む
	std::vector<u_char> buf(size);
	file.read(reinterpret_cast<char*>(buf.data()), size);

	return buf;
}

std::string IOLoader::GetBaseName(const std::string & filePath)
{
	std::tr2::sys::path path(filePath);
	return path.filename().string();
}

std::string IOLoader::GetExtension(const std::string & filePath)
{
	std::tr2::sys::path path(filePath);
	return path.extension().string();
}

std::size_t IOLoader::GerFileSize(std::ifstream & fs)
{
	// ファイルサイズの取得
	auto pos = std::ios_base::cur;
	fs.seekg(0, std::ios_base::end);
	std::size_t size = (std::size_t)fs.tellg();
	fs.seekg(0, pos);
	return size;
}
