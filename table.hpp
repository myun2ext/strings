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

			template <typename _DataType>
			struct data
			{
				typedef typename _DataType::type type, data_type;
				DataPool &data_pool;
				long address;
				_DataType _data;
				data(DataPool &pool, long addr) : data_pool(pool), address(addr) {}

				operator data_type() { return _data.read(data_pool, address); }
				template <typename _InDataType>
				data_type operator = (const _InDataType& in_data) {
					_data = _DataType(in_data);
					address = _data.write(data_pool);
					return _data;
				}
			};

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
