// This file is a part of Akel
// Authors : @kbz_8
// Created : 31/01/2024
// Updated : 31/01/2024

#ifndef __AK_CORE_ENTRY_POINT__
#define __AK_CORE_ENTRY_POINT__

#include <Core/CompilationProfile.h>

#ifdef AK_PLAT_WINDOWS
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	{
		char szFileName[MAX_PATH];
		GetModuleFileName(NULL, szFileName, MAX_PATH);
		char* argv[2] = { szFileName, NULL};

		return 0;
	}
#else
	int main(int argc, char** argv)
	{
		return 0;
	}
#endif

#endif
