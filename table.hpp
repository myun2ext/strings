#ifndef __MYUN2__MEMORIZE__TABLE__HPP__
#define __MYUN2__MEMORIZE__TABLE__HPP__

#include "strings.hpp"
#include <string>

namespace myun2
{
	namespace memorize
	{
		template <unsigned int _Columns, typename IndexPool, typename DataPool, typename _EntryType=unsigned int>
		struct table
		{
			IndexPool &index_pool;
			DataPool &data_pool;

			table(IndexPool &_index_pool, DataPool &_data_pool) :
				index_pool(_index_pool), data_pool(_data_pool) {}

			struct record
			{
				typedef _EntryType index_array_type[_Columns];
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

			template <typename T1, typename T2, typename T3, typename T4>
			void insert(const T1& v1, const T2& v2, const T3 &v3, const T4& v4)
			{
				typename record::index_array_type array;
				data<T1> data1 = v1;
				data<T2> data2 = v2;
				data<T3> data3 = v3;
				data<T4> data4 = v4;
				index_pool.write(&array, sizeof(array));
			}

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
