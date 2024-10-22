#include <iostream>

#include "Framework.h"

int main(int argc, char* argv[])
{
    std::cout << "Graphics Programming Console:\n";

    Framework framework;

    framework.Init();

    framework.Close();

    return 0;
}
