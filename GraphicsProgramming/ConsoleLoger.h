#pragma once

#include "Light.h"
#include "Mesh.h"
#include "Camera.h"
class ConsoleLoger
{
	public:
		void Init();
		void DisplayPositionsUpdate(Light* light, Mesh mesh, Camera* camera, bool isInInsideMode);

	private:
		int consoleRowStart;
		int consoleRowEnd;
};

