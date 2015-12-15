#pragma once
namespace google {
    namespace protobuf {
        class Message;
    }
}
enum        pborm_op_type {
    PBORM_UPDATE,
    PBORM_DELETE,
    PBORM_INSERT,
    PBORM_GET,
    PBORM_BATCH_GET,
    PBORM_COUNT
};
struct pborm_result_t {
    pborm_op_type   op;
    int             ret;
    int             total;
    int             offset;
    int             count;
    struct msg_buff_t {const char * data; int size;} * msgs;
    const char *    cb_data;
    int             cb_size;
};

int         pborm_init(const char * ormaddr);
int         pborm_destroy();
int         pborm_poll(int timeout_us = 1000);
typedef void (* pborm_cb_t)(void *ud, const pborm_result_t & result);
void        pborm_set_cb(pborm_cb_t cb, void *ud);
int         pborm_update(const google::protobuf::Message & msg, const char * cb_data = 0, int cb_size = 0);
int         pborm_delete(const google::protobuf::Message & msg, const char * cb_data = 0, int cb_size = 0);
int         pborm_insert(const google::protobuf::Message & msg, const char * cb_data = 0, int cb_size = 0);
int         pborm_get(const google::protobuf::Message & msg, const char * cb_data = 0, int cb_size = 0);
int         pborm_batch_get(const google::protobuf::Message & msg, const char * where_ = nullptr, int offset = 0, int limit = 0 , int order = 0, const char * cb_data = 0, int cb_size = 0);
int         pborm_count(const google::protobuf::Message & msg, const char * cb_data = 0, int cb_size = 0);




