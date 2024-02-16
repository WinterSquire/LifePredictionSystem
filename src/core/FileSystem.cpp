#include "FileSystem.h"

#include <Windows.h>
#include <filesystem>

wchar_t program_name[MAX_PATH];

void FileSystem::Init() {
    GetModuleFileNameW(nullptr, program_name, MAX_PATH);

    std::filesystem::path executablePath(program_name);

    SetCurrentDirectoryW(executablePath.parent_path().wstring().c_str());
}

const wchar_t* FileSystem::GetProgramName() {
    return program_name;
}
