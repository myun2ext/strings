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
	int pos;
	printf("wrote: %d\n", pos = f.write("aaabbb\n"));
	printf("read: %s", f.read(pos, 7).c_str());

	//	With size
	short_string s("abcdefgabcdefgabcdefg0000\n");
	printf("wrote: %d\n", pos = s.write(f));
	printf("read: %s", s.read(f, pos).c_str());

	return 0;
}
