#include <cstdlib>

class cplus_base {
public:
	virtual void Run(int loop) {
		for (volatile int l = 0; l < loop; l++) {
			for (volatile int i = 0; i < 1000000; i++)
				base_ok++;
		}
	}
private:
	volatile int base_ok;
};

class cplus_vtable : public cplus_base {
public:
	void Run(int loop) override {
		for (volatile int l = 0; l < loop; l++) {
			for (volatile int i = 0; i < 1000000; i++)
				vtable_ok++;
		}
	}
private:
	volatile int vtable_ok;
};

int main(int argc, char *argv[]) {
	int l = 100;
	if (argc > 1)
		l = atoi(argv[1]);

	cplus_vtable *cpp = new cplus_vtable;
	cpp->Run(l);
	delete(cpp);
	return 0;
}
