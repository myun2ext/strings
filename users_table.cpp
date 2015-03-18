#include "table.hpp"

using namespace myun2::memorize;

//	id: int
//	name: string
//	id_name: string
//	flg: int
class users_table : public file_pool_table<4>
{
public:
	users_table() : file_pool_table<4>("users") {}
};

int main()
{
	users_table users;
	return 0;
}
