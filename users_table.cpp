#include "table.hpp"
#include "with_size.hpp"
#include <string>

using namespace myun2::memorize;

class users_table : public file_pool_table<4>
{
private:
	typedef file_pool_table<4> _Base;
public:
	users_table() : file_pool_table<4>("users") {}

	struct user
	{
		unsigned int id;
		short_string name;
		short_string screen_name;
		unsigned int flags;
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
	return 0;
}
