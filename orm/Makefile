all: msg conf test


msg: proto/pborm.proto 
	cd proto && protoc pborm.proto --cpp_out=.

conf: proto/pborm_conf.proto 
	cp ../3rd/hpbex/extensions.proto proto/
	cd proto && protoc -I/usr/local/include -I. pborm_conf.proto extensions.proto --cpp_out=.
	cd proto && ../../3rd/hpbex/hpbex pborm_conf.proto pborm.Config -I. -I/usr/local/include  -o pborm_conf.hpb.h

test: proto/db.proto proto/comm.proto proto/extensions.proto
	cd proto && protoc -I/usr/local/include -I. db.proto comm.proto extensions.proto --cpp_out=.
	cd proto && ../../3rd/hpbex/hpbex db.proto test.DBTest -I. -I/usr/local/include  -o db.hpb.h
	cd proto && ../../3rd/hpbex/hpbex comm.proto CommBase -I. -I/usr/local/include  -o comm.hpb.h




