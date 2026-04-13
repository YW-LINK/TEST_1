#ifndef TEST_FIFO_H_
#define TEST_FIFO_H_


#include "main.h"

#define DAYLY_MESAGE_LONG 50       //结构体总长度
#define DAYLY_FLOAT_LONG 4          //浮点数长度
#define DAYLY_U16_LONG 2          //整形长度
#define DALY_RX_LONG (DAYLY_FLOAT_LONG*2 + DAYLY_U16_LONG)
#define DALY_DATA_LONG (DAYLY_FLOAT_LONG + DAYLY_U16_LONG)
#define DAYLY_MESAGE_MODE 2       //发送模式
#define DALY_FLOAT_CHANGE_LONG 2
#define DALY_FLOAT_NO_CHANGE_LONG (DAYLY_FLOAT_LONG-DALY_FLOAT_CHANGE_LONG)

#define LOG_MESAGE_LONG 1000
#define LOG_PACK_LONG LOG_MESAGE_LONG       //默认的每次发送长度
#define LOG_FLOAT_LONG 4
#define LOG_U16_LONG 0
#define LOG_STRUCT_LONG (LOG_FLOAT_LONG*2 + LOG_U16_LONG)
#define LOG_DATA_LONG (LOG_FLOAT_LONG + LOG_U16_LONG)
#define LOG_RX_LONG (LOG_STRUCT_LONG*LOG_PACK_LONG)
#define LOG_MESAFE_MODE 1


#define TEMP_MESAGE_LONG 2
#define TEMP_FLOAT_LONG 8
#define TEMP_U16_LONG 0
#define TEMP_RX_LONG (TEMP_FLOAT_LONG*2)
#define TEMP_DATA_LONG (TEMP_FLOAT_LONG )
#define TEMP_MESAGE_MODE 3


#define RANGE_LONG 25

#define TX_HEADER 0x6A
#define RX_HEADER 0x5A

#define RX_FLOAT_SIZE 64
#define RX_U16_SIZE (RX_FLOAT_SIZE*2)

struct State_Machine_status1{
    Uint16 pwm_on:1;
    Uint16 driver_on:1;
    Uint16 message_effect:1;
    Uint16 reserve1:13;
};
struct State_Machine_status2{
    Uint16 reserve2:16;
};

union U16DalyDate{
    Uint16 int16;
    struct State_Machine_status1 status;
    struct State_Machine_status2 status_reserve2;
};

struct LOG_MESSAGE
{
#if  LOG_FLOAT_LONG >0
    float logfloat[LOG_FLOAT_LONG];
#endif
#if  LOG_U16_LONG >0
    Uint16 logU16[LOG_U16_LONG];
#endif
};

struct DALY_MESSAGE
{
#if  DAYLY_FLOAT_LONG > 0
    float dalyfloat[DAYLY_FLOAT_LONG];
#endif
#if DAYLY_U16_LONG > 0
    union U16DalyDate dalyU16[DAYLY_U16_LONG];
#endif
};

struct TEMP_MESSAGE
{
#if  TEMP_FLOAT_LONG > 0
    float tempfloat[TEMP_FLOAT_LONG];
#endif
#if TEMP_U16_LONG > 0
    Uint16 tempU16[TEMP_U16_LONG];
#endif
};

struct TRIGGER_MAP
{
    Uint16 trindex;
    Uint16 flag;
    Uint16 message_long;
    Uint16 message_old_long;
    Uint16 lastindex;
};

struct LOG_SAVE_MAP
{
    Uint16 read_index;
    Uint16 write_index;
    Uint16 message_long;
    struct TRIGGER_MAP trigger;
};

struct DALY_SAVE_MAP
{
    Uint16 read_index;
    Uint16 write_index;
    Uint16 message_long;

};

struct TEMP_SAVE_MAP
{
    Uint16 read_index;
    Uint16 write_index;
    Uint16 message_long;
};


struct FIFO_TASK
{
    Uint16 message_long;
    Uint16 index;               //mode = 1  index为发送截至位 mode = 2 index为发送当前位
    Uint16 mode;
    Uint16 uint16_long;

};

struct TASK_RANGE{
    Uint16 head;
    Uint16 tail;
    Uint16 task_long;
    struct FIFO_TASK  task[RANGE_LONG];
};

struct RX_PACKET_CTRL {
    Uint16 CtrlByte;
    Uint16 ByteCount;
    Uint16 RxCheckSum;
    Uint16 State;
    Uint16 Index;
    Uint16 CheckSum;
    Uint16 ErrorTurn;
};

union RX_PACKET_BUFFER {
    float float32[RX_FLOAT_SIZE];
    Uint16 uint16[RX_U16_SIZE];
};

union TEMP_RX_PACKET_BUFFER {
    Uint16 uint16[TEMP_FLOAT_LONG*8];
    struct TEMP_MESSAGE temp_message[4];
};


struct ADD_LOG{
    struct LOG_MESSAGE add_log;
};

struct ADD_DALY{
    struct DALY_MESSAGE add_daly;
    Uint16 chose_channel[DALY_DATA_LONG];
};



extern struct LOG_MESSAGE log_buf[LOG_MESAGE_LONG];
extern struct DALY_MESSAGE daly_buf[DAYLY_MESAGE_LONG];
extern struct TEMP_MESSAGE temp_buf[TEMP_MESAGE_LONG];

extern struct LOG_SAVE_MAP log_map;
extern struct DALY_SAVE_MAP daly_map;
extern struct TEMP_SAVE_MAP temp_map;

extern struct LOG_MESSAGE delaylog;
extern struct DALY_MESSAGE delaydaly;
extern struct TEMP_MESSAGE delaytemp;

extern struct ADD_LOG logchose;
extern struct ADD_DALY dalychose;

extern struct TASK_RANGE range;
extern struct RX_PACKET_CTRL RxPacketCtrl;
extern union RX_PACKET_BUFFER RxPacketBuffer;
extern struct RX_PACKET_CTRL TempRxPacketCtrl;
extern union TEMP_RX_PACKET_BUFFER TempRxPacketBuffer;

extern Uint16 data_lock;
extern Uint16 task_lock;
extern Uint16 lock_trig;
extern Uint16 lock_daly;
extern Uint16 dalydata_lock;
extern Uint16 logdata_lock;
extern Uint16 tempdata_lock;
extern Uint16 temp_need_state;

extern float daly_moniter;

extern void SciRxPacketReset(void);
extern void TempSciRxPacketReset(void);
extern void TemprxDecodeWord(Uint16 word);
extern void rxDecodeWord(Uint16 word);


extern void Init_bigLogbuf(void);
extern void Init_dalybuf(void);
extern void Initrangtaske(void);
extern void Init_tempbuf(void);

extern Uint16 addlognumber(struct LOG_MESSAGE* log_message);
extern Uint16 adddalynumber(struct DALY_MESSAGE* daly_message);
extern Uint16 addtempnumber(struct TEMP_MESSAGE* temp_message);
extern Uint16 addtaske(Uint16 mode);

extern Uint16 checksumCalc(Uint16 *addr, Uint16 size);
extern void sendmessage(struct FIFO_TASK task);
extern Uint16 executaske(void);

extern void trigger_data_pack(struct LOG_MESSAGE addlog);
extern void daly_data_pack(struct DALY_MESSAGE adddaly);
extern void log_chose(void);
extern void daly_chose(void);



#endif
