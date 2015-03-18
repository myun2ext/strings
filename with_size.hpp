#ifndef __MYUN2__MEMORIZE__SIZED__HPP__
#define __MYUN2__MEMORIZE__SIZED__HPP__

#include <string>
#include <stdio.h>

namespace myun2
{
	namespace memorize
	{
		template <typename T, unsigned char _SizeBytes=1>
		struct with_size
		{
			size_t size;
			T* buffer;

			template <typename Pool>
			long write(Pool &pool)
			{
				long pos = pool.write(&size, _SizeBytes);
				pool.write(buffer, size);
				return pos;
			}
			template <typename Pool>
			void read(Pool &pool, long pos)
			{
				pool.read(pos, &size, _SizeBytes);
				pool.read(pos + _SizeBytes, buffer, size);
			}
		};

		struct short_string : public with_size<char, 1>
		{
			typedef ::std::string type;
			::std::string str;
			short_string(const char* s) : str(s) {}

			template <typename Pool>
			long write(Pool &pool)
			{
				size = str.size();
				buffer = (char*)str.data();
				return with_size<char, 1>::write(pool);
			}
			template <typename Pool>
			::std::string read(Pool &pool, long pos)
			{
				with_size<char, 1>::read(pool, pos);
				return str = ::std::string(buffer, size);
			}
		};
	}
}

#endif//__MYUN2__MEMORIZE__SIZED__HPP__
