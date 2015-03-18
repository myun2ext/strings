#include "table.hpp"
#include "types.hpp"
#include <string>
#include <stdio.h>

using namespace myun2::memorize;

class users_table : public file_pool_table<4>
{
private:
	typedef file_pool_table<4> _Base;
public:
	users_table() : file_pool_table<4>("users") {}

	struct user
	{
		unsigned_int id;
		short_string name;
		short_string screen_name;
		unsigned_int flags;
		user(const char* _name, const char* _screen_name) {
			id = 0;
			name = _name;
			screen_name = _screen_name;
		}
	};

	void add(const user& u) {
		insert(u.id, u.name, u.screen_name, u.flags);
	}
};
typedef users_table::user user;

int main()
{
	users_table users;
	users.add(user("hoge", "hogehoge"));
	printf("%d, %s, %s, %d\n",
			users[0][0],
			users[0][1],
			users[0][2],
			users[0][3]);
	return 0;
}
