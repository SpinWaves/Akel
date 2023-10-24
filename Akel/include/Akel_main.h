// This file is a part of Akel
// Authors : @kbz_8
// Created : 08/06/2021
// Updated : 24/10/2023

#ifndef __AK_MAIN__
#define __AK_MAIN__

#include <Akpch.h>
#include <Core/engine.h>

#ifdef AK_PLATFORM_WINDOWS

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	char szFileName[MAX_PATH];
	GetModuleFileName(NULL, szFileName, MAX_PATH);
	char* argv[2] = { szFileName, NULL};

	Ak::Engine engine;
	engine.init(argc, argv);
	engine.run();
	engine.destroy();
	return 0;
}

#else

int main(int argc, char** argv)
{
	Ak::Engine engine;
	engine.init(argc, argv);
	engine.run();
	engine.destroy();
	return 0;
}

#endif

#endif // __AK_MAIN__
