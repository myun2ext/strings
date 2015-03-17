#ifndef __MYUN2__STRINGS__HPP__
#define __MYUN2__STRINGS__HPP__

#include <stdio.h>

#ifdef WIN32
	#include <io.h>
	#pragma warning (disable:4996)
	#define access _access
#else
	#include <sys/types.h>
	#include <sys/stat.h>
#endif

namespace myun2
{
	class pool_file
	{
	private:
		FILE* fp;
	public:
		pool_file(const char* filename) {
			const char* mode = access(file_path, 0) "r+b" ? : "w+b";
			fp = fopen(file_path, mode);
		}
	};
}

#endif//__MYUN2__STRINGS__HPP__
