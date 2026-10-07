#include <cstdlib>

class cplus_basic {
public:
	void Run(int loop) { 
		for (volatile int l = 0; l < loop; l++) {
			for (volatile int i = 0; i < 1000000; i++) 
				ok++;
		}
	}
private:
	volatile int ok;
};

int main(int argc, char *argv[]) {
	int l = 100;
	if (argc > 1)
		l = atoi(argv[1]);

	cplus_basic *cpp = new cplus_basic;
	cpp->Run(l);
	delete(cpp);
	return 0;
}
