#include "pborm_api.h"
#include "dcnode/dcnode.h"
#include "base/logger.h"
#include "orm/proto/pborm.pb.h"
#include "orm/pborm_msg.h"

#define MAX_ORM_MSG_BUFF_SIZE   (2*1024*1024)
static struct pborm_ctx_t {
    dcnode_t                    *dc;//receiver from
    pborm_cb_t                  cb;
    void                       *cb_ud;
    msg_buffer_t                msg_buffer;
}  g_ctx ;

static int 
_dispather(void * , const char * src, const msg_buffer_t & msg){
    GLOG_TRA("receive orm(%s) msg size:%d", src, msg.valid_size);
    pborm_msg_t   ormmsg;
    if (!ormmsg.Unpack(msg)){
        GLOG_ERR("unpack receive msg error !");
        return -1;
    }
    return 0;
}
int         
pborm_init(const char * ormaddr){
    g_ctx.msg_buffer.create(MAX_ORM_MSG_BUFF_SIZE);
    dcnode_config_t dconf;
	string connaddr = "push:";
	connaddr += ormaddr;
	dconf.addr = dcnode_addr_t(connaddr.c_str());
    dconf.name = "ormc-";
	dconf.parent_heart_beat_gap = 2;
    dcsutil::strcharsetrandom(dconf.name, 4);
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
    select->set_limit(1);
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
    select->set_offset(offset);
    select->set_limit(limit);
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
