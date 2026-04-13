#include "sci_fifo.h"

struct LOG_SAVE_MAP log_map = (struct LOG_SAVE_MAP){0,0,};
struct LOG_MESSAGE log_buf[LOG_MESAGE_LONG] = {{0,},};
#pragma DATA_SECTION(log_buf, ".logport");

struct DALY_SAVE_MAP daly_map = (struct DALY_SAVE_MAP){0,0,0};
struct DALY_MESSAGE daly_buf[DAYLY_MESAGE_LONG] = {{0,},};
#pragma DATA_SECTION(daly_buf, ".logport");

struct TEMP_SAVE_MAP temp_map = (struct TEMP_SAVE_MAP){0,0,0};
struct TEMP_MESSAGE temp_buf[TEMP_MESAGE_LONG] = {{0,},};
#pragma DATA_SECTION(temp_buf, ".logport");

struct LOG_MESSAGE delaylog = {0,};
struct DALY_MESSAGE delaydaly = {0,};
struct TEMP_MESSAGE delaytemp = {0,};
#pragma DATA_SECTION(delaytemp, ".logport");

struct TASK_RANGE range = (struct TASK_RANGE){0,};
struct RX_PACKET_CTRL RxPacketCtrl = {0,};
union RX_PACKET_BUFFER RxPacketBuffer = {0,};

struct RX_PACKET_CTRL TempRxPacketCtrl = {0,};
union TEMP_RX_PACKET_BUFFER TempRxPacketBuffer = {0,};
struct ADD_LOG logchose;
struct ADD_DALY dalychose;

Uint16 data_lock = 1;
Uint16 temp_need_state = 0;
Uint16 dalydata_lock = 1;
Uint16 logdata_lock = 1;
Uint16 tempdata_lock = 1;
Uint16 task_lock = 1;
Uint16 lock_trig = 0;
Uint16 lock_daly_cache = 0;
Uint16 lock_daly_task = 0;
float32 daly_moniter = 0.0f;

void Init_tempbuf(void);
void Init_bigLogbuf(void);
void Init_dalybuf(void);
void Initrangtaske(void);
void SciRxPacketReset(void);
void TempSciRxPacketReset(void);
void TemprxDecodeWord(Uint16 word);
void rxDecodeWord(Uint16 word);
Uint16 addlognumber(struct LOG_MESSAGE* log_message);
Uint16 adddalynumber(struct DALY_MESSAGE* daly_message);
Uint16 addtempnumber(struct TEMP_MESSAGE* temp_message);
Uint16 addtaske(Uint16 mode);
void sendu16(Uint16 *data , Uint16 U16Long);
Uint16 checksumCalc(Uint16 *addr, Uint16 size);
void sendmessage(struct FIFO_TASK task);
Uint16 executaske(void);
void trigger_data_pack(struct LOG_MESSAGE addlog);
void daly_data_pack(struct DALY_MESSAGE adddaly);
void log_chose(void);
void daly_chose(void);

#pragma CODE_SECTION(SciRxPacketReset, ".TI.ramfunc");
void SciRxPacketReset(void)
{
    RxPacketCtrl.State = 0;
    RxPacketCtrl.Index = 0;
    RxPacketCtrl.ErrorTurn = 0;
}


#pragma CODE_SECTION(TempSciRxPacketReset, ".TI.ramfunc");
void TempSciRxPacketReset(void)
{
    TempRxPacketCtrl.State = 0;
    TempRxPacketCtrl.Index = 0;
}

#pragma CODE_SECTION(TemprxDecodeWord, ".TI.ramfunc");
void TemprxDecodeWord(Uint16 word)
{
    switch(TempRxPacketCtrl.State)
    {
        case 0:
        {
            Uint16 Header = word&0x00ff;
            if(Header == TX_HEADER)
            {
                TempRxPacketCtrl.Index = 0;
                TempRxPacketCtrl.CtrlByte = word >> 8;
//                TempRxPacketCtrl.CheckSum = word;
                TempRxPacketCtrl.State = 1;
            }
            break;
        }
        case 1:
        {
            if(word!=(TEMP_FLOAT_LONG*2))
            {
                TempRxPacketCtrl.State = 0;
                temp_need_state = 2;
            }
            else{
                TempRxPacketCtrl.ByteCount = word;
                TempRxPacketCtrl.CheckSum = 0;
                if(TempRxPacketCtrl.ByteCount==0)
                    TempRxPacketCtrl.State = 3;
                else
                    TempRxPacketCtrl.State = 2;
            }
            break;
        }
        case 2:
        {
            TempRxPacketBuffer.uint16[TempRxPacketCtrl.Index] = word;
            TempRxPacketCtrl.CheckSum += word;
            TempRxPacketCtrl.Index ++;
            if(TempRxPacketCtrl.Index >= TempRxPacketCtrl.ByteCount)
                TempRxPacketCtrl.State = 3;
            break;
        }
        case 3:
        {
            TempRxPacketCtrl.RxCheckSum = word;
            if(TempRxPacketCtrl.RxCheckSum == TempRxPacketCtrl.CheckSum)
            {
                temp_need_state = 1;
            }
            TempRxPacketCtrl.State = 0;
            break;
        }
        default:
        {
            TempRxPacketCtrl.State = 0;
            break;
        }
    }
}

#pragma CODE_SECTION(rxDecodeWord, ".TI.ramfunc");
void rxDecodeWord(Uint16 word)
{
    switch(RxPacketCtrl.State)
    {
        case 0:
        {
            Uint16 Header = word&0x00ff;
            if(Header == RX_HEADER)
            {
                RxPacketCtrl.Index = 0;
                RxPacketCtrl.CtrlByte = word >> 8;
                RxPacketCtrl.CheckSum = word;
                RxPacketCtrl.State = 1;
            }
            else
            {
                RxPacketCtrl.ErrorTurn++;
            }
            break;
        }
        case 1:
        {
            if(word>30)
            {
                RxPacketCtrl.State = 0;
                RxPacketCtrl.CtrlByte = 0;
                RxPacketCtrl.CheckSum = 0;
                break;
            }
            RxPacketCtrl.ByteCount = word;
            RxPacketCtrl.CheckSum += word;
            if(RxPacketCtrl.ByteCount==0)
                RxPacketCtrl.State = 3;
            else
                RxPacketCtrl.State = 2;
            break;
        }
        case 2:
        {
            RxPacketBuffer.uint16[RxPacketCtrl.Index] = word;
            RxPacketCtrl.CheckSum += word;
            RxPacketCtrl.Index ++;
            if(RxPacketCtrl.Index >= (RxPacketCtrl.ByteCount)>>1)
                RxPacketCtrl.State = 3;
            break;
        }
        case 3:
        {
            RxPacketCtrl.RxCheckSum = word;
            if(RxPacketCtrl.RxCheckSum == RxPacketCtrl.CheckSum)
            {
                xSemaphoreGiveFromISR(mySemaphore0Handle,&rxHigherPriorityTaskWoken);
                portYIELD_FROM_ISR(rxHigherPriorityTaskWoken);
            }
            RxPacketCtrl.State = 0;
            break;
        }
        default:
        {
            RxPacketCtrl.State = 0;
            break;
        }
    }
}


void Init_bigLogbuf(void)
{
    log_map.write_index = 0;
    log_map.message_long = 0;
    log_map.trigger.flag = 0;
    log_map.trigger.message_old_long = 0;
    log_map.trigger.message_long = LOG_PACK_LONG;
    logchose.add_log =(struct LOG_MESSAGE){0,};
}

void Init_dalybuf(void)
{
    daly_map.read_index = 0;
    daly_map.write_index = 0;
    daly_map.message_long = 0;
    dalychose.add_daly = (struct DALY_MESSAGE){0,0,};

    dalychose.chose_channel[0] = FLOAT_INPUT_VOLTAGE;
    dalychose.chose_channel[1] = FLOAT_INPUT_CURRENT;
    dalychose.chose_channel[2] = FLOAT_INDUCTOR_CURRENT;
    dalychose.chose_channel[3] = FLOAT_CIRCULATING_CURRENT;
    dalychose.chose_channel[4] = STATUE_MASTER1;
    dalychose.chose_channel[5] = STATUE_MASTER2;

}

void Init_tempbuf(void)
{
    temp_map.read_index = 0;
    temp_map.write_index = 0;
    temp_map.message_long = 0;
}


void Initrangtaske(void)
{
    range.head = 0;
    range.tail = 0;
    range.task_long = 0;
}

#pragma CODE_SECTION(addlognumber, ".TI.ramfunc");
Uint16 addlognumber(struct LOG_MESSAGE* log_message)
{
    if(logdata_lock)
    {
        logdata_lock = 0;
        if(log_map.message_long<LOG_MESAGE_LONG)
        {
            log_buf[log_map.write_index] = *log_message;
            log_map.message_long++;
            log_map.write_index = (log_map.write_index + 1)%LOG_MESAGE_LONG;
            logdata_lock = 1;
            return SUCCESS;
        }
        else
        {
            log_buf[log_map.write_index] = *log_message;
            log_map.write_index = (log_map.write_index + 1)%LOG_MESAGE_LONG;
            logdata_lock = 1;
            return SUCCESS;
        }
    }
    else
    {
        return ERRO;
    }
}

#pragma CODE_SECTION(adddalynumber, ".TI.ramfunc");
Uint16 adddalynumber(struct DALY_MESSAGE* daly_message)
{
    if(dalydata_lock)
    {
        dalydata_lock = 0;
        if(daly_map.message_long<DAYLY_MESAGE_LONG)
        {
            daly_buf[daly_map.write_index] = *daly_message;
            daly_map.message_long++;
            daly_map.write_index = (daly_map.write_index + 1)%DAYLY_MESAGE_LONG;
            dalydata_lock = 1;
            return SUCCESS;
        }
        else
        {
            dalydata_lock = 1;
            return ERRO;
        }
    }
    else
    {
        return ERRO;
    }
}

#pragma CODE_SECTION(addtempnumber, ".TI.ramfunc");
Uint16 addtempnumber(struct TEMP_MESSAGE* temp_message)
{
    uint16_t i;
    if(tempdata_lock)
    {
        tempdata_lock = 0;
        if(temp_map.message_long<TEMP_MESAGE_LONG)
        {
            for(i=0;i<TEMP_DATA_LONG;i++)
            {
                temp_buf[temp_map.write_index].tempfloat[i] = temp_message->tempfloat[i];
            }
            temp_map.message_long++;
            temp_map.write_index = (temp_map.write_index + 1)%TEMP_MESAGE_LONG;
            tempdata_lock = 1;
            return SUCCESS;
        }
        else
        {
            tempdata_lock = 1;
            return ERRO;
        }
    }
    else
    {
        tempdata_lock = 1;
        return ERRO;
    }
}

#pragma CODE_SECTION(addtaske, ".TI.ramfunc");
Uint16 addtaske(Uint16 mode)
{
    if(task_lock)
    {
        task_lock = 0;
        if(range.task_long<RANGE_LONG)
        {
            switch(mode)
            {
                case LOG_MESAFE_MODE:
                {
                    if(log_map.message_long >= (log_map.trigger.message_long+log_map.trigger.message_old_long))
                    {
                        range.task[range.tail].index = log_map.trigger.lastindex;
                        range.task[range.tail].mode = LOG_MESAFE_MODE;
                        range.task[range.tail].message_long = (log_map.trigger.message_long+log_map.trigger.message_old_long);
                        range.tail = (range.tail+1)%RANGE_LONG;
                        range.task_long++;
                        task_lock = 1;
                        return LOG_MESAFE_MODE;
                    }
                    else
                    {
                        task_lock = 1;
                        return ERRO;
                    }
                }
                case DAYLY_MESAGE_MODE:
                {
                    if(daly_map.message_long>0)
                    {
                        range.task[range.tail].index = daly_map.read_index;
                        range.task[range.tail].mode = DAYLY_MESAGE_MODE;
                        range.task[range.tail].message_long = 1;
                        range.tail = (range.tail+1)%RANGE_LONG;
                        range.task_long++;
                        task_lock = 1;
                        return DAYLY_MESAGE_MODE;
                    }
                    else
                    {
                        task_lock = 1;
                        return ERRO;
                    }
                }
                case TEMP_MESAGE_MODE:
                {
                    if(temp_map.message_long>0)
                    {
                        range.task[range.tail].index = temp_map.read_index;
                        range.task[range.tail].mode = TEMP_MESAGE_MODE;
                        range.task[range.tail].message_long = 1;
                        range.tail = (range.tail+1)%RANGE_LONG;
                        range.task_long++;
                        task_lock = 1;
                        return TEMP_MESAGE_MODE;
                    }
                    else
                    {
                        task_lock = 1;
                        return ERRO;
                    }
                }
                default:
                {
                    task_lock = 1;
                    return ERRO;
                }
            }
        }
        else
        {
            task_lock = 1;
            return ERRO;
        }
    }
    else
    {
        return ERRO;
    }
}

#pragma CODE_SECTION(checksumCalc, ".TI.ramfunc");
Uint16 checksumCalc(Uint16 *addr, Uint16 size)
{
    Uint16 i=0;
    Uint16 checksum = 0;
    for(i=0;i<size;i++)
        checksum += *(addr + i);
    return (checksum&0xffff);
}


#pragma CODE_SECTION(sendu16, ".TI.ramfunc");
void sendu16(Uint16 *data , Uint16 U16Long)
{
    Uint16 i;
    for(i=0;i<U16Long;i++)
    {
        SCI_writeCharBlockingFIFO(mySCI0_BASE, (Uint16)(data[i]));
        SCI_writeCharBlockingFIFO(mySCI0_BASE, (Uint16)(data[i]>>8));
    }
}

#pragma CODE_SECTION(sendmessage, ".TI.ramfunc");
void sendmessage(struct FIFO_TASK task)
{
    Uint16 sendcode = 0;
    Uint16 first_index = 0;
    if(task_lock)
    {
        task_lock = 0;
        switch(range.task[range.head].mode)
        {
            case LOG_MESAFE_MODE:
            {
                first_index = (range.task[range.head].index + LOG_MESAGE_LONG - range.task[range.head].message_long  +1)%LOG_MESAGE_LONG;
                SCI_writeCharBlockingFIFO(mySCI0_BASE, TX_HEADER);
                SCI_writeCharBlockingFIFO(mySCI0_BASE, LOG_MESAFE_MODE);
                SCI_writeCharBlockingFIFO(mySCI0_BASE, ((range.task[range.head].message_long*LOG_STRUCT_LONG)&0xff));
                SCI_writeCharBlockingFIFO(mySCI0_BASE, ((range.task[range.head].message_long*LOG_STRUCT_LONG)>>8));
                for(sendcode= 0;first_index!=range.task[range.head].index;first_index = (first_index + 1)%LOG_MESAGE_LONG)
                {
                     sendu16((uint16_t *)&log_buf[first_index] , LOG_STRUCT_LONG);
                     sendcode += checksumCalc((uint16_t *)&log_buf[first_index],LOG_STRUCT_LONG);
                }
                sendu16((uint16_t *)&log_buf[range.task[range.head].index] , LOG_STRUCT_LONG);
                sendcode += checksumCalc((uint16_t *)&log_buf[range.task[range.head].index], LOG_STRUCT_LONG);
                SCI_writeCharBlockingFIFO(mySCI0_BASE, (sendcode&0xff));
                SCI_writeCharBlockingFIFO(mySCI0_BASE, (sendcode>>8));
                logdata_lock = 1;
                task_lock = 1;
                break;
            }
            case DAYLY_MESAGE_MODE:
            {
                SCI_writeCharBlockingFIFO(mySCI0_BASE, TX_HEADER);
                SCI_writeCharBlockingFIFO(mySCI0_BASE, DAYLY_MESAGE_MODE);
                SCI_writeCharBlockingFIFO(mySCI0_BASE, (DALY_RX_LONG&0xff));
                SCI_writeCharBlockingFIFO(mySCI0_BASE, (DALY_RX_LONG>>8));
                sendu16((uint16_t *)&daly_buf[range.task[range.head].index] , DALY_RX_LONG);
                sendcode = checksumCalc((uint16_t *)&daly_buf[range.task[range.head].index], DALY_RX_LONG);
                SCI_writeCharBlockingFIFO(mySCI0_BASE, (sendcode&0xff));
                SCI_writeCharBlockingFIFO(mySCI0_BASE, (sendcode>>8));
                task_lock = 1;
                break;
            }
            case TEMP_MESAGE_MODE:
            {
                SCI_writeCharBlockingFIFO(mySCI0_BASE, TX_HEADER);
                SCI_writeCharBlockingFIFO(mySCI0_BASE, TEMP_MESAGE_MODE);
                SCI_writeCharBlockingFIFO(mySCI0_BASE, (TEMP_RX_LONG&0xff));
                SCI_writeCharBlockingFIFO(mySCI0_BASE, (TEMP_RX_LONG>>8));
                sendu16((uint16_t *)&temp_buf[range.task[range.head].index] , TEMP_RX_LONG);
                sendcode = checksumCalc((uint16_t *)&temp_buf[range.task[range.head].index], TEMP_RX_LONG);
                SCI_writeCharBlockingFIFO(mySCI0_BASE, (sendcode&0xff));
                SCI_writeCharBlockingFIFO(mySCI0_BASE, (sendcode>>8));
                task_lock = 1;
                break;
            }
            default:
            {
                task_lock = 1;
                break;
            }
        }
    }
}

#pragma CODE_SECTION(executaske, ".TI.ramfunc");
Uint16 executaske(void)
{
    if(task_lock)
    {
        if(range.task_long>0)
        {
            task_lock = 0;
            switch(range.task[range.head].mode)
            {
                case LOG_MESAFE_MODE:
                {
                    task_lock = 1;
                    sendmessage(range.task[range.head]);
                    log_map.message_long -= range.task[range.head].message_long;
                    range.head = (range.head+1)%RANGE_LONG;
                    range.task_long--;
                    logdata_lock = 1;
                    log_map.trigger.flag = 0;
                    return LOG_MESAFE_MODE;
                }
                case DAYLY_MESAGE_MODE:
                {
                    if(dalydata_lock)
                    {
                        dalydata_lock = 0;
                        task_lock = 1;
                        sendmessage(range.task[range.head]);
                        daly_map.read_index = (daly_map.read_index+1)%DAYLY_MESAGE_LONG;
                        daly_map.message_long--;
                        range.head = (range.head+1)%RANGE_LONG;
                        range.task_long--;
                        dalydata_lock = 1;
                        return DAYLY_MESAGE_MODE;
                    }
                    else
                    {
                        task_lock = 1;
                        return ERRO;
                    }
                }
                case TEMP_MESAGE_MODE:
                {
                    if(tempdata_lock)
                    {
                        tempdata_lock = 0;
                        task_lock = 1;
                        sendmessage(range.task[range.head]);
                        temp_map.read_index = (temp_map.read_index+1)%TEMP_MESAGE_LONG;
                        temp_map.message_long--;
                        range.head = (range.head+1)%RANGE_LONG;
                        range.task_long--;
                        tempdata_lock = 1;
                        return TEMP_MESAGE_MODE;
                    }
                    else
                    {
                        task_lock = 1;
                        return ERRO;
                    }

                }
                default:
                {
                    task_lock = 1;
                    return ERRO;
                }
            }
        }
        else
        {
            task_lock = 1;
            return ERRO;
        }
    }
    else
    {
        return ERRO;
    }

}

#pragma CODE_SECTION(trigger_data_pack, ".TI.ramfunc");
void trigger_data_pack(struct LOG_MESSAGE addlog)
{
    if(log_map.trigger.flag == 0)
    {
        addlognumber(&addlog);
    }
    else if(log_map.trigger.flag == 1)
    {
        log_map.trigger.trindex = 0;
        if(addlognumber(&addlog)!=ERRO)
        {
            log_map.trigger.flag = 2;
            log_map.trigger.trindex++;
        }
    }
    else if(log_map.trigger.flag == 2)
    {
        if(log_map.trigger.trindex<log_map.trigger.message_long)
        {
            if(addlognumber(&addlog)!=ERRO)
            {
               log_map.trigger.trindex++;
            }
        }
        else
        {
           log_map.trigger.lastindex = (log_map.write_index-1+LOG_MESAGE_LONG)%LOG_MESAGE_LONG;
           log_map.trigger.trindex = (log_map.trigger.lastindex-(log_map.trigger.message_long+log_map.trigger.message_old_long)+LOG_MESAGE_LONG+1)%LOG_MESAGE_LONG;
           if(addtaske(LOG_MESAFE_MODE)!=ERRO)
           {
               log_map.trigger.flag = 3;
           }
        }
    }
}

#pragma CODE_SECTION(daly_data_pack, ".TI.ramfunc");
void daly_data_pack(struct DALY_MESSAGE adddaly)
{
    if(adddalynumber(&adddaly)!=ERRO)
    {
        if(addtaske(DAYLY_MESAGE_MODE)!=ERRO)
        {
            daly_moniter = daly_moniter+0.001f;
            if(daly_moniter>1)daly_moniter = 0;
        }
        else
        {
            daly_map.message_long--;
            daly_map.write_index = (daly_map.write_index - 1)%DAYLY_MESAGE_LONG;
//            lock_daly_cache = 1;
        }
    }



//    Uint16 i;
//    if(lock_daly_cache == 0)
//    {
//        for(i=0 ;i<DALY_RX_LONG;i++)
//        {
//            if(i<DAYLY_FLOAT_LONG)
//            {
//                delaydaly.dalyfloat[i] = adddaly.dalyfloat[i];
//            }
//            else
//            {
//                delaydaly.dalyU16[i-DAYLY_FLOAT_LONG].int16 = adddaly.dalyU16[i-DAYLY_FLOAT_LONG].int16;
//            }
//        }
//        if(adddalynumber(&TIME_WATCH2_H;)!=ERRO)
//        {
//            if(addtaske(DAYLY_MESAGE_MODE)!=ERRO)
//            {
//                daly_moniter = daly_moniter+0.001f;
//                if(daly_moniter>1)daly_moniter = 0;
//            }
//            else
//            {
//                daly_map.message_long--;
//                daly_map.write_index = (daly_map.write_index - 1)%DAYLY_MESAGE_LONG;
//                lock_daly_cache = 1;
//            }
//        }
//        else
//        {
//            lock_daly_cache = 1;
//        }
//    }
//    else
//    {
//       if(adddalynumber(&delaydaly)!=ERRO)
//       {
//            if(addtaske(DAYLY_MESAGE_MODE)!=ERRO)
//            {
//                  daly_moniter = daly_moniter+0.001f;
//                  if(daly_moniter>1)daly_moniter = 0;
//                  lock_daly_cache = 0;
//            }
//            else
//            {
//                daly_map.message_long--;
//                daly_map.write_index = (daly_map.write_index - 1)%DAYLY_MESAGE_LONG;
//                lock_daly_cache = 1;
//            }
//       }
//    }
}

#pragma CODE_SECTION(daly_chose, ".TI.ramfunc");
void daly_chose(void)
{

}







