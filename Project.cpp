#include <iostream>
#include <windows.h>

int main() {
    HANDLE hInputFile = CreateFileA(
        "win_test.txt",         // 파일 경로
        GENERIC_READ,           // 읽기 권한 요청
        FILE_SHARE_READ,        // 다른 프로세스에서 읽기 허용 (공유 모드)
        NULL,                   // 기본 보안 속성
        OPEN_EXISTING,          // 파일이 기존에 존재할 때만 열기
        FILE_ATTRIBUTE_NORMAL,  // 일반 파일 속성
        NULL                    // 템플릿 핸들 없음
    );
    DWORD fileSize = GetFileSize(hInputFile, NULL);
    char* buffer = new char[fileSize + 1];
    DWORD bytesRead = 0;
    BOOL isReadSuccess = ReadFile(
        hInputFile,             // 읽을 파일의 HANDLE (번호표)
        buffer,                 // 데이터를 저장할 메모리 버퍼 주소
        fileSize,               // 읽을 바이트 수
        &bytesRead,             // [출력] 실제 읽은 바이트 수
        NULL                    // 동기식 입출력 방식 사용
    );
    CloseHandle(hInputFile);
    buffer[bytesRead] = '\0';
    for (int i = 0; i < bytesRead; i++) {
        buffer[i] = buffer[i] ^ 'k';
    }
    HANDLE hOutputFile = CreateFileA(
        "win_test.txt",          // 동일한 파일명
        GENERIC_WRITE,           // 쓰기 권한
        0,
        NULL,
        CREATE_ALWAYS,           // 기존 내용을 지우고 새로 작성
        FILE_ATTRIBUTE_NORMAL,
        NULL    
    );

    DWORD bytesWritten = 0;
    WriteFile(hOutputFile, buffer, bytesRead, &bytesWritten, NULL);
    CloseHandle(hOutputFile);
    delete[] buffer;
}