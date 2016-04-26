
#ifndef KUDEET_WIN32_STRING_HELPER_H_INCLUDED__
#define KUDEET_WIN32_STRING_HELPER_H_INCLUDED__

#pragma once

KDNAMESTART

class KStringHelper
{
public:
	static SInt32 Win32_UTF8_UNICODE(const char* const mbptr, std::wstring & wptr)
	{
		if (NULL == mbptr || strlen(mbptr) == 0)
			return 0;

		int ret;
		size_t len = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, mbptr, -1, NULL, 0);
		if (len == 0) // If UTF8 failed, try to use ASNI ACP.
		{
			len = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, mbptr, -1, NULL, 0);
			if (len != 0)
			{
				wchar_t* buf = (wchar_t*) new wchar_t[len];
				if (NULL != buf)
				{
					ret = MultiByteToWideChar (CP_ACP, MB_ERR_INVALID_CHARS, mbptr, -1, buf, len);
					wptr = buf;
					delete []buf;
					return ret;
				}
			}
			return 0;
		}
		wchar_t* buf = (wchar_t*) new wchar_t[len];
		if (NULL != buf)
		{
			ret = MultiByteToWideChar (CP_UTF8, MB_ERR_INVALID_CHARS, mbptr, -1, buf, len);
			wptr = buf;
			delete []buf;
			return ret;
		}
		else
		{
			return 0;
		}
	}
};

KDNAMEEND

#endif //KUDEET_WIN32_STRING_HELPER_H_INCLUDED__