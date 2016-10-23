#include "dcpots/dcnode/dcnode.h"
#include "dcpots/base/logger.h"
#include "orm/proto/pborm.pb.h"
#include "orm/pborm_msg.h"
#include "pborm_api.h"

#define MAX_ORM_MSG_BUFF_SIZE   (2*1024*1024)
static struct pborm_ctx_t {
    dcnode_t                    *dc;//receiver from
    pborm_cb_t                  cb;
    void                       *cb_ud;
    msg_buffer_t                msg_buffer;
}  g_ctx ;

static int 
_dispather(void *, const char * src, const msg_buffer_t & msg){
	pborm_msg_t   ormmsg;
	if (!ormmsg.Unpack(msg)){
		GLOG_ERR("unpack receive msg error !");
		return -1;
	}
	GLOG_TRA("recv orm msg:%s", ormmsg.Debug());
	pborm_result_t result;
	memset(&result, 0, sizeof(result));
	result.cb_data = ormmsg.cb().data().data();
	result.cb_size = ormmsg.cb().data().length();
	result.count = ormmsg.rsp().count();
	result.msg_type_name = ormmsg.msg_full_type_name().c_str();
	result.ret = ormmsg.rsp().err_no();
	if (result.ret == 0){
		switch (ormmsg.op()){
		case pborm::ORM_SELECT:
			assert(result.count == ormmsg.rsp().select().msgs_size());
			result.offset = ormmsg.rsp().select().head().offset();
			result.limit = ormmsg.rsp().select().head().limit();
			if (result.limit == 1){
				result.op = PBORM_GET;
			}
			else {
				result.op = PBORM_BATCH_GET;
			}
			//-----------------------------------------------------------------------------
			result.msgs = new pborm_result_t::msg_buff_t[ormmsg.rsp().select().msgs_size()];
			if (!result.msgs){
				GLOG_FTL("allocate msg error size:%zu", sizeof(pborm_result_t::msg_buff_t)*ormmsg.rsp().select().msgs_size());
				break;
			}
			for (int i = 0; i < ormmsg.rsp().select().msgs_size(); ++i){
				result.msgs[i].data = ormmsg.rsp().select().msgs(i).data();
				result.msgs[i].size = ormmsg.rsp().select().msgs(i).length();
			}
			break;
		case pborm::ORM_UPDATE:
			result.op = PBORM_UPDATE;
			break;
		case pborm::ORM_COUNT:
			result.op = PBORM_COUNT;
			break;
		case pborm::ORM_INSERT:
			result.op = PBORM_INSERT;
			break;
		case pborm::ORM_DELETE:
			result.op = PBORM_DELETE;
			break;
		}
	}
	else {
		result.result_msg = ormmsg.rsp().err_msg().c_str();
	}
	g_ctx.cb(g_ctx.cb_ud, result);
	//////////////////////////////////////////////
	if (result.msgs){
		delete result.msgs;
	}
    return 0;
}
int         
pborm_init(const char * ormaddr, const char * name){
    g_ctx.msg_buffer.create(MAX_ORM_MSG_BUFF_SIZE);
    dcnode_config_t dconf;
	string connaddr = "push:";
	connaddr += ormaddr;
	dconf.addr = connaddr.c_str();
    if (name){
        dconf.name = name;
        dconf.durable = true;
    }
    else {
        dconf.name = "pbormc-";
        dcs::strcharsetrandom(dconf.name, 4);
    }
    dconf.parent_heart_beat_gap = 2;
    auto dc = dcnode_create(dconf);
    if (!dc){
        GLOG_ERR("create dcnode error!");
        return -1;
    }
    dcnode_set_dispatcher(dc, _dispather, 0);
    g_ctx.dc = dc;
    g_ctx.cb = nullptr;
    g_ctx.cb_ud = nullptr;
    return 0;
}
void
pborm_destroy(){
    if(g_ctx.dc){
        dcnode_destroy(g_ctx.dc);
        g_ctx.dc = nullptr;
        g_ctx.cb = nullptr;
        g_ctx.cb_ud = nullptr;
    }
}
int
pborm_poll(int timeout_us){
    return dcnode_update(g_ctx.dc, timeout_us);
}
void
pborm_set_cb(pborm_cb_t cb, void *ud){
    g_ctx.cb = cb;
    g_ctx.cb_ud = ud;
}
static inline int 
_pborm_command(const google::protobuf::Message & msg, const char * cb_data, int cb_size,
                pborm::OrmMsgOP op, pborm::OrmMsgReq * ext = nullptr){

    if (!msg.SerializeToArray(g_ctx.msg_buffer.buffer, g_ctx.msg_buffer.max_size)){
        GLOG_ERR("data pack msg error !");
        return -1;
    }
    g_ctx.msg_buffer.valid_size = msg.ByteSize();
    ///////////////////////////////////////
    pborm_msg_t orm_msg;
    if (cb_data){
        orm_msg.mutable_cb()->set_data(cb_data, cb_size);
    }
    if (ext){
        orm_msg.mutable_req()->MergeFrom(*ext);
    }
    orm_msg.set_msg_full_type_name(msg.GetDescriptor()->full_name());
    orm_msg.set_op(op);
    orm_msg.mutable_req()->set_msg_data(g_ctx.msg_buffer.buffer, g_ctx.msg_buffer.valid_size);
	if (!orm_msg.Pack(g_ctx.msg_buffer)){
        GLOG_ERR("orm pack msg:%s error !", orm_msg.Debug());
        return -2;
    }
	GLOG_TRA("send msg to pborm :%s", orm_msg.Debug());
    return dcnode_send(g_ctx.dc, "pborm", g_ctx.msg_buffer.buffer, g_ctx.msg_buffer.valid_size);
}

int
pborm_update(const google::protobuf::Message & msg, const char * cb_data , int cb_size ){
    return _pborm_command(msg, cb_data, cb_size, pborm::ORM_UPDATE);
}
int
pborm_delete(const google::protobuf::Message & msg, const char * cb_data , int cb_size ){
    return _pborm_command(msg, cb_data, cb_size, pborm::ORM_DELETE);
}
int
pborm_insert(const google::protobuf::Message & msg, const char * cb_data , int cb_size ){
    return _pborm_command(msg, cb_data, cb_size, pborm::ORM_INSERT);
}
int
pborm_get(const google::protobuf::Message & msg, const char * fields, const char * cb_data, int cb_size){
    pborm::OrmMsgReq   req;
    auto select = req.mutable_select();
    select->mutable_head()->set_limit(1);
	if (fields && *fields){
		select->set_fields(fields);
	}
    return _pborm_command(msg, cb_data, cb_size, pborm::ORM_SELECT, &req);
}
int
pborm_batch_get(const google::protobuf::Message & msg, const char * fields, const char * where_, int offset, int limit,
				const char * orderby, int order, const char * cb_data, int cb_size){
    pborm::OrmMsgReq   req;
    auto select = req.mutable_select();
    if (where_ && *where_){
        select->set_where(where_);
    }
	if (fields && *fields){
		select->set_fields(fields);
	}
    select->mutable_head()->set_offset(offset);
	select->mutable_head()->set_limit(limit);
    select->set_order(order);
	if (orderby && *orderby){
		select->set_orderby(orderby);
	}
    return _pborm_command(msg, cb_data, cb_size, pborm::ORM_SELECT, &req);
}
int
pborm_count(const google::protobuf::Message & msg, const char * cb_data , int cb_size ){
    return _pborm_command(msg, cb_data, cb_size, pborm::ORM_COUNT);
}
