pborm:
	./autobuild.sh

gen:
	cd orm && make

rebuild: ./3rd/dcpots/lib/libdcnode.a ./3rd/dcpots/lib/libdcutil.a
	touch ./orm/pborm.cpp ./testapi/main.cpp
	./autobuild.sh

clean:
	cd build && make clean
