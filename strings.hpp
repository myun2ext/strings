#ifndef __MYUN2__STRINGS__HPP__
#define __MYUN2__STRINGS__HPP__

#include <stdio.h>
#include <string>

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
		template <unsigned int _blockSize = 64>
		class pool_file
		{
		private:
			FILE* fp;

			long cur() {
				fseek(fp, 0, SEEK_END);
				return ftell(fp);
			}
		public:
			class open_failed {};

			pool_file(const char* filename) { fp = NULL; open(filename); }
			virtual ~pool_file() { close(); }

			bool open(const char* filename) {
				if ( access(filename, 0) ) {
					fp = fopen(filename, "w+b");
					if ( fp == NULL ) throw open_failed();
				}
				else
				{
					fp = fopen(filename, "r+b");
					if ( fp == NULL ) throw open_failed();
					fseek(fp, 0, SEEK_END);
				}
			}
			void close() { if(fp) fclose(fp); }
			long write(const char* s) {
				long pos = cur();
				fwrite(s, strlen(s), 1, fp);
				return pos;
			}
			::std::string read(long pos, size_t length) {
				fseek(fp, pos, SEEK_SET);
				::std::string s(length, '\0');
				fread((char*)s.data(), length, 1, fp);
				return s;
			}
		};
	}
}

#endif//__MYUN2__STRINGS__HPP__
