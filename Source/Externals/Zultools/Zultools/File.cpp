#include "File.h"

#include <sstream>
#include <filesystem>



File::~File() { Close(); }

File File::Open(const char* aPath, FileOpenMode aWriteMode)
{
	File output;

	output.myFileInfo.writeMode = GetWriteMode(aWriteMode);
	output.myFileInfo.path = aPath;

	if (!output.myFileInfo.writeMode.createNewFile && !std::fstream(aPath).good())
	{
		throw std::runtime_error("File failed to open at path: " + std::string(aPath));
	}

	output.myFileInfo.fileStream.open(aPath, output.myFileInfo.writeMode.mode);

	return output;
}

File File::Get(const char* aPath)
{
	File output;
	output.myFileInfo.path = aPath;

	std::filesystem::directory_entry entry(aPath);
	output.myFileInfo.lastWrittenTo = entry.last_write_time().time_since_epoch();

	output.myFileInfo.name = entry.path().stem().string();
	output.myFileInfo.writeMode = GetWriteMode(FileOpenMode::Overwrite);

	return output;
}

void File::Open(FileOpenMode aWriteMode)
{
	if (!myFileInfo.fileStream.is_open()){
		myFileInfo.fileStream.open(myFileInfo.path, myFileInfo.writeMode.mode);
	}
}

void File::Close()
{
	if (myFileInfo.fileStream.is_open()) {
		myFileInfo.fileStream.close();
	}
}

void File::Write(const char* someContent)
{
	if (myFileInfo.writeMode.mode & std::ios::trunc)
	{
		myFileInfo.fileStream.close();
		myFileInfo.fileStream.open(myFileInfo.path, std::ios::out | std::ios::trunc);
	}
	else if (myFileInfo.writeMode.mode & std::ios::app)
	{
		myFileInfo.fileStream.seekg(-1, std::ios::end);
		myFileInfo.fileStream << "\n";
	}

	myFileInfo.fileStream << someContent;
}

std::string File::Read()
{
	std::stringstream buffer;
	buffer << myFileInfo.fileStream.rdbuf();

	myFileInfo.fileStream.seekg(0);

	return buffer.str();
}

FileInfo& File::GetFileInfo() { return myFileInfo; }












File File::Create(const char* aPath, FileOpenMode aWriteMode, bool aOpen)
{
	std::fstream file(aPath, std::ios::out | std::ios::trunc);
	file.close();


	return File::Open(aPath, aWriteMode);
}

std::string File::ReadFile(const char* aPath)
{
	std::fstream file(aPath);

	if (!file.is_open())
	{
		throw std::runtime_error("File failed to open at path: " + std::string(aPath));
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	file.close();

	return buffer.str();
}

void File::WriteFile(const char* aPath, const char* someContent, FileOpenMode aWriteMode, bool aThrowException)
{
	WriteMode writeMode = GetWriteMode(aWriteMode);

	if (!writeMode.createNewFile && !std::fstream(aPath).good())
	{
		if (!aThrowException) return;
		else {
			throw std::runtime_error("File failed to open at path: " + std::string(aPath));
		}
	}

	std::fstream file(aPath, writeMode.mode);

	file << someContent;
	file.close();
}

WriteMode File::GetWriteMode(FileOpenMode aWriteMode)
{
	WriteMode output;
	output.createNewFile = true;
	output.mode = std::ios::out;

	if ((char)aWriteMode & (char)FileOpenMode::Append) {
		output.mode |= std::ios::app;
	}

	if ((char)aWriteMode & (char)FileOpenMode::Overwrite) {
		output.mode |= std::ios::trunc;
	}

	if ((char)aWriteMode & (char)FileOpenMode::ReadWriteExisting) {
		output.createNewFile = false;
		output.mode |= std::ios::in;
	}

	return output;
}
