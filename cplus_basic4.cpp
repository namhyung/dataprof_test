#include <cstdlib>

class cplus_primary_base {
public:
	void Primary(int loop) {
		for (volatile int l = 0; l < loop; l++) {
			for (volatile int i = 0; i < 1000000; i++)
				primary_ok++;
		}
	}
private:
	volatile int primary_ok;
	unsigned long unused;
};

class cplus_secondary_base {
public:
	void Secondary(int loop) {
		for (volatile int l = 0; l < loop; l++) {
			for (volatile int i = 0; i < 1000000; i++)
				secondary_ok++;
		}
	}
private:
	volatile int secondary_ok;
	int unused;
};

class cplus_inherit_multi : public cplus_primary_base, cplus_secondary_base {
};

int main(int argc, char *argv[]) {
	int l = 100;
	if (argc > 1)
		l = atoi(argv[1]);

	cplus_inherit_multi *cpp = new cplus_inherit_multi;
	cpp->Primary(l);
	delete(cpp);
	return 0;
}
