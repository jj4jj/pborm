#pragma once
namespace google {
    namespace protobuf {
        class Message;
    }
}
enum        pborm_op_type {
	PBORM_CMD = 0,
    PBORM_UPDATE = 1,
    PBORM_DELETE = 2,
    PBORM_INSERT = 3,
    PBORM_GET = 4,
    PBORM_BATCH_GET = 5,
    PBORM_COUNT = 6
};
struct pborm_result_t {
    pborm_op_type   op;
    int             ret;
	//////////////////////
	//COMMON - UPDATE / SELECT / DELETE / COUNT / INSERT
	const	char    * msg_type_name;
	int              count;
	//SELECT
    int             offset;
	int				limit;
	//SELECT MSG (COUNT)
    struct msg_buff_t {const char * data; int size;} * msgs;
	//
	const	char	* result_msg; //result msg for custom command or error

	////////////////////////
    //CALL BACK
	const char *    cb_data;
    int             cb_size;
};

int         pborm_init(const char * ormaddr);
void        pborm_destroy();
int         pborm_poll(int timeout_us = 1000);
typedef void (* pborm_cb_t)(void *ud, const pborm_result_t & result);
void        pborm_set_cb(pborm_cb_t cb, void *ud);
int         pborm_update(const google::protobuf::Message & msg, const char * cb_data = 0, int cb_size = 0);
int         pborm_delete(const google::protobuf::Message & msg, const char * cb_data = 0, int cb_size = 0);
int         pborm_insert(const google::protobuf::Message & msg, const char * cb_data = 0, int cb_size = 0);
int         pborm_get(const google::protobuf::Message & msg, const char * fields = nullptr, const char * cb_data = 0, int cb_size = 0);
int         pborm_batch_get(const google::protobuf::Message & msg,const char * fields = nullptr,
			const char * where_ = nullptr, int offset = 0, int limit = 0 ,
			const char * orderby = nullptr, int order = 0, const char * cb_data = 0, int cb_size = 0);
int         pborm_count(const google::protobuf::Message & msg, const char * cb_data = 0, int cb_size = 0);




