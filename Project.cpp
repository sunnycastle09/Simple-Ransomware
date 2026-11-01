#include <iostream>
#include <windows.h>

int main() {
    HANDLE hInputFile = CreateFileA(
        "win_test.txt",      
        GENERIC_READ,         
        FILE_SHARE_READ,     
        NULL,                
        OPEN_EXISTING,         
        FILE_ATTRIBUTE_NORMAL,  
        NULL                    
    );
    DWORD fileSize = GetFileSize(hInputFile, NULL);
    char* buffer = new char[fileSize + 1];
    DWORD bytesRead = 0;
    BOOL isReadSuccess = ReadFile(
        hInputFile,         
        buffer,             
        fileSize,    
        &bytesRead,          
        NULL             
    );
    CloseHandle(hInputFile);
    buffer[bytesRead] = '\0';
    for (int i = 0; i < bytesRead; i++) {
        buffer[i] = buffer[i] ^ 'k';
    }
    HANDLE hOutputFile = CreateFileA(
        "win_test.txt",         
        GENERIC_WRITE,       
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL    
    );

    DWORD bytesWritten = 0;
    WriteFile(hOutputFile, buffer, bytesRead, &bytesWritten, NULL);
    CloseHandle(hOutputFile);
    delete[] buffer;
}
