#pragma once

#include <iostream>

class Error
{
	public:
		static void CheckError(int errorCode, std::string errorMessage);
};

