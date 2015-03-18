#include "table.hpp"
#include <string>

using namespace myun2::memorize;

class users_table : public file_pool_table<4>
{
public:
	users_table() : file_pool_table<4>("users") {}

	struct id_type {
		unsigned int id;
	};
	struct name_type {
		::std::string name;
	};
	struct screen_name_type {
		::std::string screen_name;
	};
	struct flags_type {
		unsigned int flags;
		flags_type() { flags = 0; }
	};
	struct user
	{
		id_type id;
		name_type name;
		screen_name_type screen_name;
		flags_type flags;
		user(const char* _name, const char* _screen_name) {
			id.id = 0;
			name.name = _name;
			screen_name.screen_name = _screen_name;
		}
	};

	void add(const user& u) {
	}
};
typedef users_table::user user;

int main()
{
	users_table users;
	users.add(user("hoge", "hogehoge"));
	return 0;
}
