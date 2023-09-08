// This file is a part of Akel   
// Authors : @kbz_8              
// Created : Invalid date        
// Updated : 08/09/2023

#ifndef __AK_MAIN__
#define __AK_MAIN__

#include <Akpch.h>
#include <Core/engine.h>

int main(int argc, char** argv)
{
	Ak::Engine engine;
	engine.init(argc, argv);
	engine.run();
	engine.destroy();
	return 0;
}

#endif // __AK_MAIN__
