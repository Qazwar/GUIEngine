
#ifndef KUDEET_WIN32_FILE_HELPER_H_INCLUDED__
#define KUDEET_WIN32_FILE_HELPER_H_INCLUDED__

#pragma once

KDNAMESTART

class KFileSystemHelper
{
public:
	static bool GetHardDriveFreeSpace(LPCTSTR path, UInt64& cbSize)
	{
		if (GetDriveType(path) != DRIVE_FIXED)
			return false;
		ULARGE_INTEGER freeSpace;
		if (!GetDiskFreeSpaceEx(path, &freeSpace, 0, 0))
			return false;
		cbSize = freeSpace.QuadPart;
		return true;
	}

	static bool GetMaxFreeSpaceHardDrivePath(LPTSTR path, UInt64& freeSpace)
	{
		TCHAR testPath[4] = {0};
		wcscpy(testPath, _T("A:\\"));
		freeSpace = 0;
		for (TCHAR i = 0; i < 26; i++)
		{
			testPath[0] = _T('A') + i;
			UInt64 u;
			if (!GetHardDriveFreeSpace(testPath, u) )
				continue;
			if ( u > freeSpace)
			{
				freeSpace = u;
				wcscpy(path, testPath);
			}
		}
		return true;
	}

	static bool GetSizeAvailableHardDrivePath(UInt64 cbSizeRequired, LPTSTR path)
	{
		bool retResult = false;
		TCHAR testPath[4] = _T("A:\\");
		for (TCHAR i = 0; i < 26; i++)
		{
			testPath[0] = _T('A') + i;
			UInt64 cbSizeFree;
			if (!GetHardDriveFreeSpace(testPath, cbSizeFree) )
				continue;
			if (cbSizeFree >= cbSizeRequired)
			{
				wcscpy(path, testPath);
				retResult = true;
				break;
			}
		}
		return retResult;
	}

	static bool GetTempFolderPath(LPTSTR temppath)
	{
		GetTempPath(MAX_PATH, temppath);
		return TRUE;
	}

	static bool GetSizeAvailableTempFilePath(UInt64 cbSizeRequired, LPTSTR lpTempPath)
	{
		//Search a path to hold the temp iso file, preference is system Temp directory.
		TCHAR szPath[MAX_PATH] = {0};
		GetTempPath(MAX_PATH, szPath);

		TCHAR szDrive[4] ={0};
		wcsncpy(szDrive, szPath, 3);
		UInt64 cbSizeFree;
		if (!GetHardDriveFreeSpace(szDrive, cbSizeFree) || cbSizeFree < cbSizeRequired )
		{
			if (!GetSizeAvailableHardDrivePath(cbSizeRequired,szPath))
				return false;
		}

		wcscat(szPath, _T("KudeetBurn\\"));
		CreateDirectory(szPath, 0);
		//when calling this function, a temp file also created on disc.
		if (!GetTempFileName(szPath, _T("KDB"), 0, lpTempPath))
			return false;
		//delete the temp file that created by calling GetTempFileName();
		::DeleteFile(lpTempPath);
		return true;
	}

	static bool CrateTempFolder(LPTSTR lpstrpath)
	{
		if( wcslen(lpstrpath) + 1 > MAX_PATH )
			return false;
		TCHAR szPath[MAX_PATH] = {0};
		int len = (int)(wcslen(lpstrpath) + 1) * sizeof(TCHAR);
		memcpy( szPath, lpstrpath, len );
		CreateDirectory(szPath, 0);
		if (!GetTempFileName(szPath, _T("KDB"), 0, lpstrpath))
			return false;
		::DeleteFile(lpstrpath);
		return true;
	}

	static HRESULT DeleteTempFile(LPCTSTR lpstrpath, LPCTSTR FileExt)
	{
		ULARGE_INTEGER llDirSize = {0};
		WIN32_FIND_DATA FindFileData;

		TCHAR szDirPath[MAX_PATH] = {0};
		wcscpy(szDirPath, lpstrpath );

		DWORD dwAttris = GetFileAttributes(szDirPath);
		if (dwAttris == INVALID_FILE_ATTRIBUTES)
			return E_FAIL;
		else if (dwAttris & FILE_ATTRIBUTE_DIRECTORY)
		{
			wcscat(szDirPath, _T("*") );
			wcscat(szDirPath, FileExt );
		}

		HANDLE hFind = FindFirstFile(szDirPath, &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) 
			return E_FAIL;
		do
		{
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				continue;
			else
			{
				std::wstring tempfile = lpstrpath;
				tempfile += FindFileData.cFileName;
				::DeleteFile( tempfile.c_str() );
			}
		}while (FindNextFile(hFind, &FindFileData) );

		DWORD dwError = GetLastError();
		FindClose(hFind);
		if (dwError != ERROR_NO_MORE_FILES) 
			return E_FAIL;
		return S_OK;
	}

	static HRESULT GetFileSize(LPCTSTR lpstrPath, ULONGLONG& cbSize)
	{
		cbSize =0;
		HRESULT hr = S_OK;
		HANDLE  hFile = CreateFile(lpstrPath, GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if (hFile != INVALID_HANDLE_VALUE)
		{
			LARGE_INTEGER liSize;
			if(GetFileSizeEx(hFile,&liSize))
				cbSize = liSize.QuadPart;
			::CloseHandle(hFile);
		}
		hr = HRESULT_FROM_WIN32(GetLastError());
		return hr;
	}

	static bool IsDotsFileName(LPCTSTR lpstrPath)
	{
		return 0 == _tcscmp(lpstrPath, _T(".")) || 0 == _tcscmp(lpstrPath, _T(".."));
	}

	static bool IsFileOnSpecialDisk(LPCTSTR lpstrpath, LPCTSTR  lpDestDisk )
	{
		const wchar_t* ptemp = _tcsstr( lpstrpath, lpDestDisk );
		return ptemp == lpstrpath;
	}

	static bool IsFileFolder( LPCTSTR lpstrPath )
	{
		return (::GetFileAttributes( lpstrPath ) & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY ;
	}

	static HRESULT CalculateFileSize(LPCTSTR lpstrPath, ULONGLONG& cbSize)
	{
		cbSize =0;
		HRESULT hr = S_OK;
		TCHAR szDirPath[MAX_PATH] = {0};
		wcscpy(szDirPath, lpstrPath);
		DWORD dwAttris = GetFileAttributes(szDirPath);
		if(dwAttris == INVALID_FILE_ATTRIBUTES)
			return E_FAIL;
		else if(dwAttris & FILE_ATTRIBUTE_DIRECTORY)
			wcscat(szDirPath, _T("\\*.*") );
		ULARGE_INTEGER llDirSize ={0};
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind = FindFirstFile(szDirPath, &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE)
			return E_FAIL;
		do
		{
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (IsDotsFileName(FindFileData.cFileName))
					continue;

				UInt64 llSubDirSize =0;
				TCHAR szSubDirPath[MAX_PATH] = {0};
				wcscpy(szSubDirPath, lpstrPath );
				if (szSubDirPath[_tcslen(szSubDirPath)-1] != _T('\\'))
					wcscat(szSubDirPath, _T("\\"));
				wcscat(szSubDirPath, FindFileData.cFileName );
				if ( SUCCEEDED(CalculateFileSize(szSubDirPath, llSubDirSize)) )
					llDirSize.QuadPart += llSubDirSize;
			}
			else
			{
				ULARGE_INTEGER llFileSize ={0};
				llFileSize.LowPart = FindFileData.nFileSizeLow;
				llFileSize.HighPart = FindFileData.nFileSizeHigh;
				llDirSize.QuadPart += llFileSize.QuadPart;
			}

		}while (FindNextFile(hFind, &FindFileData) );

		DWORD dwError = GetLastError();
		FindClose(hFind);
		if (dwError != ERROR_NO_MORE_FILES) 
			hr = E_FAIL;
		cbSize = llDirSize.QuadPart;
		return hr;
	}

	static HRESULT GetModulePathInfo(
		HMODULE hModule,
		wchar_t * drive,
		size_t driveSizeInCharacters,
		wchar_t *dir,
		size_t dirSizeInCharacters,
		wchar_t * fname,
		size_t nameSizeInCharacters,
		wchar_t * ext,
		size_t extSizeInCharacters)
	{
		WCHAR szModulePath[MAX_PATH];
		GetModuleFileName(hModule, szModulePath, MAX_PATH);
		_wsplitpath( szModulePath, drive, dir, fname, ext );
		return S_OK;
	}

	static HRESULT GetModulePath(HMODULE hModule, LPTSTR strPath )
	{
		WCHAR szModulePath[MAX_PATH] = {0};
		DWORD ret = ::GetModuleFileName(hModule, szModulePath, MAX_PATH );
		if (ret > 0)
		{
			wchar_t* tempstr = wcsrchr( szModulePath, L'\\');
			int result = (int)( tempstr - szModulePath );
			memcpy(strPath, szModulePath, result * sizeof (WCHAR) );
		}
		return S_OK;
	}

	//*********************************************************************
	//* FUNCTION: GetSecondsElapsed
	static DWORD GetSecondsElapsed(SYSTEMTIME * StartTime, SYSTEMTIME * EndTime)
	{
		FILETIME Start,End;
		unsigned __int64 Start64=0, End64=0, Elapsed64=0; 

		//--- Convert System time
		SystemTimeToFileTime(StartTime, &Start);
		SystemTimeToFileTime(EndTime, &End);

		//---- Convert start and end file 
		//---- time to 2  64 bit usigned integers
		((LPDWORD)(&Start64))[1] = Start.dwHighDateTime;
		((LPDWORD)(&Start64))[0] = Start.dwLowDateTime;
		((LPDWORD)(&End64))[1] = End.dwHighDateTime;
		((LPDWORD)(&End64))[0] = End.dwLowDateTime;
		
		//--- Calc elpased time
		Elapsed64 = End64 - Start64;
		//---- Get micro seconds elpased
		Elapsed64 /= 10;
		//--- Get milly seconds elpased
		Elapsed64 /= 1000;
        //--- Get Secconds elpased
		Elapsed64 /= 1000;
        //--- Return the LowDateTime of seconds elapsed
		//--- This will be good enough for ~136 years elapsed
		return(((LPDWORD)(&Elapsed64))[0]);
	}

	//*********************************************************************
	//* FUNCTION:CalcElapsedTime
	//*          
	//* PURPOSE: 
	//*********************************************************************
#define SECONDS_IN_A_DAY     ((DWORD)(SECONDS_IN_A_HOUR*24))
#define SECONDS_IN_A_HOUR    ((DWORD)(SECONDS_IN_A_MINUTE*60))
#define SECONDS_IN_A_MINUTE  ((DWORD)(60))
	static void CalcElapsedTime(SYSTEMTIME * StartTime, SYSTEMTIME * FinishTime, SYSTEMTIME * ElapsedTime)
	{
		DWORD SecondsElapsed;
		memset(ElapsedTime, 0, sizeof(SYSTEMTIME));
		SecondsElapsed = GetSecondsElapsed(StartTime, FinishTime);
		if (SecondsElapsed >= SECONDS_IN_A_DAY)
		{
			ElapsedTime->wDay = (WORD) (SecondsElapsed / SECONDS_IN_A_DAY);
			SecondsElapsed -= (ElapsedTime->wDay*SECONDS_IN_A_DAY);
		}
		if (SecondsElapsed >= SECONDS_IN_A_HOUR)
		{
			ElapsedTime->wHour  = (WORD) (SecondsElapsed / SECONDS_IN_A_HOUR);
			SecondsElapsed -= (ElapsedTime->wHour * SECONDS_IN_A_HOUR);
		}
		if (SecondsElapsed >= SECONDS_IN_A_MINUTE)
		{
			ElapsedTime->wMinute = (WORD) (SecondsElapsed / SECONDS_IN_A_MINUTE);
			SecondsElapsed -= (ElapsedTime->wMinute * SECONDS_IN_A_MINUTE);
		}
		ElapsedTime->wSecond = (WORD) SecondsElapsed;
	}
};

KDNAMEEND

#endif //KUDEET_WIN32_FILE_HELPER_H_INCLUDED__