#include <cstdlib>

class cplus_base {
public:
	void Run(int loop) {
		for (volatile int l = 0; l < loop; l++) {
			for (volatile int i = 0; i < 1000000; i++)
				base_ok++;
		}
	}
private:
	volatile int base_ok;
};

class cplus_inherit : public cplus_base {
};

int main(int argc, char *argv[]) {
	int l = 100;
	if (argc > 1)
		l = atoi(argv[1]);

	cplus_inherit *cpp = new cplus_inherit;
	cpp->Run(l);
	delete(cpp);
	return 0;
}
