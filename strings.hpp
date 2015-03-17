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
	namespace memorize
	{
		class pool_file
		{
		private:
			FILE* fp;
		public:
			pool_file(const char* filename) {
				const char* mode = ( access(filename, 0) ? "w+b" : "r+b" );
				fp = fopen(filename, mode);
			}
			virtual ~pool_file() { close(); }
			void close() { if(fp) fclose(fp); }
		};
	}
}

#endif//__MYUN2__STRINGS__HPP__
