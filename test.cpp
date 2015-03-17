#include "strings.hpp"
#include "with_size.hpp"

using namespace myun2::memorize;

int main()
{
	pool_file<42> f("example.db");

	int pos;
	printf("wrote: %d\n", pos = f.write("aaabbb\n"));
	printf("read: %s", f.read(pos, 7).c_str());

	//	With size
	short_string s("abcdefgabcdefgabcdefg0000\n");
	printf("wrote: %d\n", pos = s.write(f));
	printf("read: %s", s.read(f, pos).c_str());

	return 0;
}