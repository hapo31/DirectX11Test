#pragma once
#include <memory>
#include <d3d11.h>

namespace engine
{
	template<class IUnknown_t>
	class com_ptr
	{
	public:
		com_ptr() = default;
		com_ptr(IUnknown_t* src) : ptr(src) {}

		~com_ptr()
		{
			if (ptr != nullptr)
				ptr->Release();
		}

		IUnknown_t** operator&()
		{
			return &ptr;
		}

		IUnknown_t* operator->()
		{
			return ptr;
		}
		
		operator IUnknown_t*() const
		{
			return ptr;
		}

		IUnknown_t* operator=(IUnknown* source)
		{	
			ptr->Release();
			ptr = source;
		}


	private:
		IUnknown_t *ptr = nullptr;
	};
}