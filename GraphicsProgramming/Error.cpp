#include "Error.h"

void Error::CheckError(int errorCode, std::string errorMessage)
{
	if (errorCode != 0)
	{
		std::cerr << errorMessage << "\n";
	}
}
