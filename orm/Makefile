all: msg conf


msg: proto/pborm.proto 
	cd proto && protoc pborm.proto --cpp_out=.

conf: proto/pborm_conf.proto 
	cp ../3rd/hpbex/extensions.proto proto/
	cd proto && protoc -I/usr/local/include -I. pborm_conf.proto extensions.proto --cpp_out=.
	cd proto && ../../3rd/hpbex/hpbex pborm_conf.proto pborm.Config -I. -I/usr/local/include  -o pborm_conf.hpb.h
