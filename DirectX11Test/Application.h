#pragma once
#include <Windows.h>
#include "GetterSetter.h"

namespace engine
{
	class Application
	{
	public:
		Application(HWND hwnd)
		{
			this->hwnd = hwnd;
			GetClientRect(hwnd, &client_size);
		}

		GETTERSETTER(HWND, hwnd);
		GETTERSETTER(HINSTANCE, hInstance);
		GETTER(RECT, client_size);

	private:
		HWND hwnd;
		HINSTANCE hInstance;
		RECT client_size;
		
	};
}