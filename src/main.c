#include <stdio.h>
#include <dlfcn.h>
#include <libtcc.h>

const char *source = "int get_num(void) { return 5; }";
const char *tdlfile = "./tdl";

typedef int(*getnumfunc)(void);

int main() {
	TCCState *state = tcc_new();
	if (tcc_compile_string(state, source) == -1) {
		printf("Compile Failed.\n");
		return -1;
	}
	tcc_set_output_type(state, 2);
	tcc_output_file(state, tdlfile);
	
	void *tdl = dlopen("./tdl", RTLD_LAZY);
	if (tdl == NULL) {
		printf("Failed to open TDL.\n");
		return -1;
	}
	void *init = dlsym(tdl, "get_num");
	if (init == NULL) {
		printf("Failed to find function 'get_num'.\n");
		return -1;
	}
	getnumfunc gnf = (getnumfunc)init;
	int num = gnf();
	printf("%i\n", num);
	return 0;
}
