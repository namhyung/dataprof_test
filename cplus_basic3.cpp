#include <cstdlib>

class cplus_base {
private:
	unsigned long unused;
	int unused2;
	/* padding */
};

class cplus_inherit : public cplus_base {
public:
	void Run(int loop) {
		for (volatile int l = 0; l < loop; l++) {
			for (volatile int i = 0; i < 1000000; i++)
				pad_ok++;
		}
	}
private:
	volatile int pad_ok;
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
