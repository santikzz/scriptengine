#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <fstream>
#include <string>
#include <chaiscript/chaiscript.hpp>

#include "Driver.hpp"
#include "Functions.hpp"

std::string read_script(std::string path) {
	
	std::ifstream file;
	std::string content;
	std::string line;

	file.open(path.c_str());
	if (file.is_open()) {
		while (std::getline(file, line)) {
			content += line;
		}
		file.close();
	}
	else {
		return NULL;
	}
	return content;
}

void throwexception()
{
	throw std::runtime_error("err");
}

int main(int argc, char* argv) {

	printf("[ script engine beta ]\n\n");

	chaiscript::ChaiScript chai;

	// const global variables
	chai.add_global_const(chaiscript::const_var(1),		"MOUSE_LEFT_PRESS");
	chai.add_global_const(chaiscript::const_var(2),		"MOUSE_LEFT_RELEASE");
	chai.add_global_const(chaiscript::const_var(4),		"MOUSE_RIGHT_PRESS");
	chai.add_global_const(chaiscript::const_var(8),		"MOUSE_RIGHT_RELEASE");

	// ddxoft driver functions
	chai.add(chaiscript::fun(&driver_init),				"driverInit");
	chai.add(chaiscript::fun(&driver_MoveAbsolute),		"driverMouseMoveAbs");
	chai.add(chaiscript::fun(&driver_MoveRelative),		"driverMouseMoveRel");
	chai.add(chaiscript::fun(&driver_MouseButton),		"driverMouseBtn");
	chai.add(chaiscript::fun(&driver_Key),				"driverKeyboard");
	
	// structs
	chai.add(chaiscript::fun(&intVector2::x), "x");
	chai.add(chaiscript::fun(&intVector2::y), "y");

	chai.add(chaiscript::fun(&intVector3::x), "x");
	chai.add(chaiscript::fun(&intVector3::y), "y");
	chai.add(chaiscript::fun(&intVector3::z), "z");

	chai.add(chaiscript::fun(&rgbTuple::r), "r");
	chai.add(chaiscript::fun(&rgbTuple::g), "g");
	chai.add(chaiscript::fun(&rgbTuple::b), "b");


	// generic functions
	chai.add(chaiscript::fun(&nc_ThreadSleep),			"Sleep");
	chai.add(chaiscript::fun(&nc_GetCursorPos),			"GetCursorPos");
	chai.add(chaiscript::fun(&nc_GetPixel),				"GetPixel");
	chai.add(chaiscript::fun(&nc_Color),				"Color");
	chai.add(chaiscript::fun(&nc_ColorToRGB),			"ColorToRGB");


	//std::string script = read_script("myscript.lua");
	//chai.eval(script.c_str());
	std::string result = chai.eval_file<std::string>("myscript.chai");


	printf("\n[+] Script Finished\n");
	return 0;
}