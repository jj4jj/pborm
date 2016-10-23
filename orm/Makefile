all: msg conf test


msg: proto/pborm.proto 
	cd proto && protoc pborm.proto --cpp_out=.

conf: proto/pborm_conf.proto 
	#cp ../../pbdcex/include/extensions.proto proto/
	cd proto && protoc -I/usr/local/include -I. -I../../pbdcex/include/pbdcex pborm_conf.proto --cpp_out=.
	cd proto && ../../../pbdcex/bin/pbdcexer -I../../pbdcex/include/pbdcex -ppborm_conf.proto -mpborm.Config -I. -I/usr/local/include --cpp_out=. 

test: proto/db.proto proto/comm.proto proto/extensions.proto
	cd proto && protoc -I/usr/local/include -I. db.proto comm.proto extensions.proto --cpp_out=.
	cd proto && ../../../pbdcex/bin/pbdcexer -pdb.proto -mtest.DBTest -I. -I/usr/local/include --cpp_out=. 
	cd proto && ../../../pbdcex/bin/pbdcexer -pcomm.proto -mCommBase -I. -I/usr/local/include --cpp_out=. 




