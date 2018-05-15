T6713.out: BBB_i2c_lib.o t6713_5k_i2c_lib.o T6713.o
	g++ -o T6713.out BBB_i2c_lib.o t6713_5k_i2c_lib.o T6713.o

T6713.o: T6713.cpp
	g++ -std=c++11 -c T6713.cpp

BBB_i2c_lib.o: BBB_i2c_lib.cpp BBB_i2c_lib.h
	g++ -c BBB_i2c_lib.cpp

t6713_5k_i2c_lib.o: t6713_5k_i2c_lib.cpp t6713_5k_i2c_lib.h
	g++ -c t6713_5k_i2c_lib.cpp

clean:
	rm -f *.o *.out
