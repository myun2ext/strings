#ifndef __MYUN2__MEMORIZE__TYPES__HPP__
#define __MYUN2__MEMORIZE__TYPES__HPP__

#include "with_size.hpp"

namespace myun2
{
	namespace memorize
	{
		template <typename T>
		struct constant_size
		{
			T value;
			typedef T type;
			constant_size() {}
			constant_size(const T& v) : value(v) {}

			template <typename Pool>
			long write(Pool &pool) {
				return pool.write(&value, sizeof(T));
			}
			template <typename Pool>
			void read(Pool &pool, long pos)
			{
				pool.read(pos, &value, sizeof(T));
			}
		};
		typedef constant_size<unsigned int> unsigned_int;
		typedef constant_size<int> integer;
		typedef constant_size<unsigned short> unsigned_short;
		typedef constant_size<short> short_int;
	}
}

#endif//__MYUN2__MEMORIZE__SIZED__HPP__
