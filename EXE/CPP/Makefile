T6713.out: BBB_i2c_lib.o t6713_5k_i2c_lib.o MySQL_lib.o T6713.o
	g++ -o T6713.out BBB_i2c_lib.o t6713_5k_i2c_lib.o MySQL_lib.o T6713.o -lmariadbclient

T6713.o: T6713.cpp
	g++ -std=c++11 -c T6713.cpp -I /usr/include/mysql/

BBB_i2c_lib.o: BBB_i2c_lib.cpp BBB_i2c_lib.h
	g++ -c BBB_i2c_lib.cpp

t6713_5k_i2c_lib.o: t6713_5k_i2c_lib.cpp t6713_5k_i2c_lib.h
	g++ -c t6713_5k_i2c_lib.cpp

MySQL_lib.o: MySQL_lib.cpp MySQL_lib.h
	g++ -std=c++11 -c MySQL_lib.cpp -I /usr/include/mysql/

clean:
	rm -f *.o *.out
