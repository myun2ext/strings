#include "strings.hpp"

using namespace myun2::memorize;

int main() {
	pool_file<42> f("example.db");
	printf("wrote: %d\n", f.write("aaabbb\n"));
	printf("read: %s", f.read(0, 7).c_str());
	return 0;
}