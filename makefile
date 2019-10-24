preprocess:
	cl preprocess.c
	
test1:
	preprocess -i math_functions.c
	
test2:
	preprocess -i string_functions.c
	
test3:
	preprocess -i math_functions.c -c
	
test4:
	preprocess -i string_functions.c -c
	
clean:
	del preprocess.obj
	del preprocess.exe