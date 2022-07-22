#include <iostream>

#include <windows.h>
#include <psapi.h>

#define IMAGE_NAME_LENGTH 1024

bool IsWinLogon(DWORD processID)
{
    bool result = false;
    WCHAR lpExeName[IMAGE_NAME_LENGTH];

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processID);

    if (NULL != hProcess)
    {
        GetProcessImageFileName(hProcess, lpExeName, IMAGE_NAME_LENGTH);
        auto res = wcsstr(lpExeName, L"winlogon");
        if (res)
        {
            //_tprintf(TEXT("%s  (PID: %u)\n"), lpExeName, processID);
            result = true;
        }
        CloseHandle(hProcess);
    }

    return result;
}

int main()
{
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
    {
        return 1;
    }
    cProcesses = cbNeeded / sizeof(DWORD);

    for (i = 0; i < cProcesses; i++)
    {
        if (aProcesses[i] != 0)
        {
            if (IsWinLogon(aProcesses[i]))
            {
                std::cout << "Found with PID " << aProcesses[i] << std::endl;
                const auto process = OpenProcess(PROCESS_TERMINATE, false, aProcesses[i]);
                TerminateProcess(process, 0);
                CloseHandle(process);
            }
        }
    }

    return 0;
}
