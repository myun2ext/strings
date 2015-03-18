#ifndef __MYUN2__MEMORIZE__TABLE__HPP__
#define __MYUN2__MEMORIZE__TABLE__HPP__

#include "strings.hpp"
#include <string>

namespace myun2
{
	namespace memorize
	{
		template <unsigned int _Columns, typename IndexPool, typename DataPool>
		struct table
		{
			IndexPool &index_pool;
			DataPool &data_pool;

			table(IndexPool &_index_pool, DataPool &_data_pool) :
				index_pool(_index_pool), data_pool(_data_pool) {}

			struct record
			{
				IndexPool &index_pool;
				DataPool &data_pool;
				unsigned int recno;

				record(unsigned int _recno, IndexPool &_index_pool, DataPool &_data_pool) :
					recno(_recno), index_pool(_index_pool), data_pool(_data_pool) {}

				template <typename T>
				T operator [](unsigned int x){}
			};

			/*
			long write(Pool &pool)
			{
				long pos = pool.write(&size, _SizeBytes);
				pool.write(buffer, size);
				return pos;
			}
			void read(Pool &pool, long pos)
			{
				pool.read(pos, &size, _SizeBytes);
				pool.read(pos + _SizeBytes, buffer, size);
			}
			*/

			record operator [](unsigned int y){ return record(y, index_pool, data_pool); }
		};

		template <unsigned int _Columns>
		class file_pool_table : public table<_Columns, pool_file<1>, pool_file<1> >
		{
		private:
			pool_file<1> index_pool;
			pool_file<1> data_pool;
			typedef table<_Columns, pool_file<1>, pool_file<1> > _Base;
		public:
			file_pool_table(const char* prefix) :
				index_pool(::std::string(prefix) + ".table.db"),
				data_pool(::std::string(prefix) + ".data.db"),
				_Base(index_pool, data_pool) {}
		};
	}
}

#endif//__MYUN2__MEMORIZE__TABLE__HPP__
