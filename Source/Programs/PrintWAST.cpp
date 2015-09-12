#include "Core/Core.h"
#include "Core/CLI.h"
#include "AST/AST.h"
#include "WebAssembly/WebAssembly.h"

int main(int argc,char** argv)
{
	AST::Module* module;
	const char* outputFilename;
	if(!stricmp(argv[1],"-text") && argc == 4)
	{
		module = loadTextModule(argv[2]);
		outputFilename = argv[3];
	}
	else if(!stricmp(argv[1],"-binary") && argc == 5)
	{
		module = loadBinaryModule(argv[2],argv[3]);
		outputFilename = argv[4];
	}
	else
	{
		std::cerr <<  "Usage: Print -binary in.wasm in.js.mem out.wast" << std::endl;
		std::cerr <<  "       Print -text in.wast out.wast" << std::endl;
		return -1;
	}
	
	if(!module) { return -1; }

	std::ofstream outputStream(outputFilename);
	if(!outputStream.is_open())
	{
		std::cerr << "Failed to open " << outputFilename << std::endl;
		return -1;
	}
	outputStream << WebAssemblyText::print(module);
	outputStream.close();

	return 0;
}