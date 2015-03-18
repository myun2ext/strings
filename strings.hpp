#ifndef __MYUN2__STRINGS__HPP__
#define __MYUN2__STRINGS__HPP__

#include <stdio.h>
#include <string.h>
#include <string>

#ifdef WIN32
	#include <io.h>
	#pragma warning (disable:4996)
	#define access _access
#else
	#include <unistd.h>
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

			void open(const char* filename) {
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
				return write(s, strlen(s));
			}
			long write(const void* buffer, size_t length) {
				long pos = cur();
				fwrite(buffer, length, 1, fp);
				return pos;
			}
			::std::string read(long pos, size_t length) {
				::std::string s(length, '\0');
				read(pos, (char*)s.data(), length);
				return s;
			}
			size_t read(long pos, void* buffer, size_t length) {
				fseek(fp, pos, SEEK_SET);
				return fread(buffer, length, 1, fp);
			}
			size_t write(long pos, const void* buffer, size_t length) {
				fseek(fp, pos, SEEK_SET);
				return write(buffer, length);
			}
		};
	}
}

#endif//__MYUN2__STRINGS__HPP__
