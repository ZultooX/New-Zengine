#pragma once

#include <string>
#include <fstream>
#include <chrono>

struct WriteMode {
	int mode = 0;
	bool createNewFile = false;
};

enum class FileOpenMode : int
{
	// std::ios::out
	CreateIfNotExists = 1 << 0,	// Will create a new file if there is none. This is used by default.


	// std::ios::in | std::ios::out
	ReadWriteExisting = 1 << 1,	// Will just open already existing files.


	// std::ios::app
	Append = 1 << 2,			// Will add to the already existing file.	


	// std::ios::trunc
	Overwrite = 1 << 3,			// Will overwrite the file.
};

struct FileInfo
{
	std::string name;
	std::string path;
	std::fstream fileStream;
	WriteMode writeMode;

	std::chrono::system_clock::duration lastWrittenTo;
};

inline FileOpenMode operator |(FileOpenMode lhs, FileOpenMode rhs)
{
	return static_cast<FileOpenMode>(static_cast<char>(lhs) | static_cast<char>(rhs));
}

class File
{
private:
	File() = default;

public:
	~File();

	File(const File&) = delete; 
	File(File&& other) noexcept : myFileInfo(std::move(other.myFileInfo)) 
	{
		other.myFileInfo.fileStream = std::fstream(); 
	}

public: // Methods for handling files, will open a stream the user can handle themselves.
	static File Open(const char* aPath, FileOpenMode aWriteMode = FileOpenMode::CreateIfNotExists);
	static File Get(const char* aPath);

	void Open(FileOpenMode aWriteMode = FileOpenMode::CreateIfNotExists);
	void Close();

	void Write(const char* someContent);
	std::string Read();

	FileInfo& GetFileInfo();


private:
	FileInfo myFileInfo = {};


	 
public: // Mehtods for handling files, will not open a constant stream.
	static File Create(const char* aPath, FileOpenMode aWriteMode = FileOpenMode::CreateIfNotExists, bool aOpen = true);

	static std::string ReadFile(const char* aPath);
	static void WriteFile(const char* aPath, const char* someContent, FileOpenMode aWriteMode = FileOpenMode::CreateIfNotExists, bool aThrowException = true);

private:
	static WriteMode GetWriteMode(FileOpenMode aWriteMode);
};

