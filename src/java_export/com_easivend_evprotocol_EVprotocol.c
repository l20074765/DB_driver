/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include "db_driver.h"
#include "db_serial.h"
#include "db_json.h"
#include "yoc_serialport.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>


/*********************************************************************************************************
**定义请求包类型
*********************************************************************************************************/
#define EV_NONE             0       //保留类型
#define EV_REGISTER         1       //串口注册
#define EV_RELEASE          2       //串口释放

//=====================快递柜类型==============================================================================


#define EV_BENTO_OPEN       11      //快递柜开门
#define EV_BENTO_CHECK      12      //快递柜查询
#define EV_BENTO_LIGHT      13      //快递柜照明
#define EV_BENTO_COOL       14      //快递柜制冷
#define EV_BENTO_HOT        15      //快递柜加热



//=====================MDB现金模组类型==============================================================================
#define EV_MDB_INIT         21      //MDB设备初始化
#define EV_MDB_ENABLE       22      //MDB设备使能
#define EV_MDB_HEART        23      //MDB设备心跳
#define EV_MDB_B_INFO       24      //MDB纸币器信息
#define EV_MDB_C_INFO       25      //MDB硬币器信息
#define EV_MDB_COST         26      //MDB设备扣款
#define EV_MDB_PAYBACK      27      //MDB设备退币
#define EV_MDB_PAYOUT       28      //MDB设备找币


#define EV_CMD_FAIL         9998
#define EV_JSON_ERR         9999







/*
 * Class:     com_easivend_evprotocol_EVprotocol
 * Method:    EV_portRegister
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_easivend_evprotocol_EVprotocol_EVPortRegister
  (JNIEnv *env, jobject obj, jstring jportName)
{
    char *portName;
    int fd;
    jstring msg;
    char *text;
    json_t *root,*entry;

    portName = (char *)(*env)->GetStringUTFChars(env,jportName, NULL);
    fd = EV_portRegister((char *)portName);
    (*env)->ReleaseStringUTFChars(env,jportName,portName);
    portName = yserial_getPortName(fd);
    entry = Json_create_title(EV_REGISTER);
    Json_insert_str(entry,"port",portName);
    Json_insert_int(entry,"port_id",fd);
    root = Json_insert_head(entry);
    if(root != NULL){
        json_tree_to_string(root, &text);
        msg = (*env)->NewStringUTF(env,text);
        free(text);
        json_free_value(&root);
    }
    else{
        msg = (*env)->NewStringUTF(env,"{\"EV_json\":{\"EV_type\":9999}}");
    }


    return msg;
}



/*
 * Class:     com_easivend_evprotocol_EVprotocol
 * Method:    EVPortRelease
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_easivend_evprotocol_EVprotocol_EVPortRelease
  (JNIEnv *env, jclass cls, jint j_fd)
{
    jstring msg;
    char *text;
    json_t *root,*entry;
    int fd = j_fd;

    EV_portRelease(fd);

    entry = Json_create_title(EV_RELEASE);
    Json_insert_int(entry,"result",1);
    root = Json_insert_head(entry);
    if(root != NULL){
        json_tree_to_string(root, &text);
        msg = (*env)->NewStringUTF(env,text);
        free(text);
        json_free_value(&root);
    }
    else{
        msg = (*env)->NewStringUTF(env,"{\"EV_json\":{\"EV_type\":9999}}");
    }
    return msg;
}


/*
 * Class:     com_easivend_evprotocol_EVprotocol
 * Method:    EVBentoOpen
 * Signature: (III)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_easivend_evprotocol_EVprotocol_EVBentoOpen
  (JNIEnv *env, jclass cls, jint fd, jint addr, jint box)
{
    jstring msg;
    char *text;
    json_t *root,*entry;
    int res;
    ST_BT_OPEN_REQ req;
    ST_BT_OPEN_RPT rpt;

    req.fd = fd;
    req.addr = addr;
    req.no = box;
    res = EV_bentoOpen(&req,&rpt);

    entry = Json_create_title(EV_BENTO_OPEN);
    Json_insert_int(entry,"port_id",rpt.fd);
    Json_insert_int(entry,"addr",rpt.addr);
    Json_insert_int(entry,"box",rpt.no);

    if(res == 1){
        Json_insert_int(entry,"is_success",1);
        Json_insert_int(entry,"result",rpt.result);
    }
    else{
        Json_insert_int(entry,"is_success",0);
        Json_insert_int(entry,"result",0);
    }

    root = Json_insert_head(entry);
    if(root != NULL){
        json_tree_to_string(root, &text);
        msg = (*env)->NewStringUTF(env,text);
        free(text);
        json_free_value(&root);
    }
    else{
        msg = (*env)->NewStringUTF(env,"{\"EV_json\":{\"EV_type\":9999}}");
    }

    return msg;
}



/*
 * Class:     com_easivend_evprotocol_EVprotocol
 * Method:    EVBentoCheck
 * Signature: (II)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_easivend_evprotocol_EVprotocol_EVBentoCheck
  (JNIEnv *env, jclass cls, jint fd, jint addr)
{
    ST_BT_CHECK_REQ req;
    ST_BT_CHECK_RPT rpt;
    char ID[64] = {0};
    int res,i;
    json_t *root,*entry,*label,*arr;
    char *text;
    jstring msg;
    req.fd = fd;
    req.addr = addr;
    res = EV_bentoCheck(&req,&rpt);


    entry = Json_create_title(EV_BENTO_CHECK);
    Json_insert_int(entry,"port_id",rpt.fd);
    Json_insert_int(entry,"addr",rpt.addr);
    if(res == 1){
        Json_insert_int(entry,"is_success",1);
        for(i = 0;i < rpt.id_len ;i++){
            sprintf(&ID[i*2],"%02x",rpt.id[i]);
        }
        Json_insert_str(entry,"ID",ID);
        Json_insert_int(entry,"cool",rpt.iscool);
        Json_insert_int(entry,"hot",rpt.ishot);
        Json_insert_int(entry,"light",rpt.islight);
        Json_insert_int(entry,"sum",rpt.sum);

        arr = json_new_array();
        for(i = 0;i < rpt.sum;i++){  //遍历货道
            label = json_new_object();
            Json_insert_int(label,"no",i + 1);
            Json_insert_int(label,"state",1);
            json_insert_child(arr,label);
        }
        label = json_new_string("column");
        json_insert_child(label,arr);
        json_insert_child(entry,label);

    }
    else{
        Json_insert_int(entry,"is_success",0);
    }


    root = Json_insert_head(entry);
    if(root != NULL){
        json_tree_to_string(root, &text);
        msg = (*env)->NewStringUTF(env,text);
        free(text);
        json_free_value(&root);
    }
    else{
        msg = (*env)->NewStringUTF(env,"{\"EV_json\":{\"EV_type\":9999}}");
    }

    return msg;

}



/*
 * Class:     com_easivend_evprotocol_EVprotocol
 * Method:    EVBentoLight
 * Signature: (III)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_easivend_evprotocol_EVprotocol_EVBentoLight
  (JNIEnv *env, jclass cls, jint fd, jint addr, jint opt)
{
    ST_BT_LIGHT_REQ req;
    ST_BT_LIGHT_RPT rpt;
    int res;
    jstring msg;
    char *text;
    json_t *root,*entry;

    req.fd = fd;
    req.addr =addr;
    req.opt = opt;

    res = EV_bentoLight(&req,&rpt);

    entry = Json_create_title(EV_BENTO_LIGHT);
    Json_insert_int(entry,"port_id",rpt.fd);
    Json_insert_int(entry,"addr",rpt.addr);
    Json_insert_int(entry,"opt",rpt.opt);

    if(res == 1){
        Json_insert_int(entry,"is_success",1);
        Json_insert_int(entry,"result",rpt.res);
    }
    else{
        Json_insert_int(entry,"is_success",0);
        Json_insert_int(entry,"result",0);
    }

    root = Json_insert_head(entry);
    if(root != NULL){
        json_tree_to_string(root, &text);
        msg = (*env)->NewStringUTF(env,text);
        free(text);
        json_free_value(&root);
    }
    else{
        msg = (*env)->NewStringUTF(env,"{\"EV_json\":{\"EV_type\":9999}}");
    }

    return msg;


}



/*
 * Class:     com_easivend_evprotocol_EVprotocol
 * Method:    EVmdbInit
 * Signature: (III)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_easivend_evprotocol_EVprotocol_EVmdbInit
  (JNIEnv *env, jclass cls, jint fd, jint bill, jint coin)
{
    ST_MDB_INIT_REQ req;
    ST_MDB_INIT_RPT rpt;
    int res;
    jstring msg;
    char *text;
    json_t *root,*entry;


    req.fd =    fd;
    req.bill =  bill;
    req.coin =  coin;
    res = EV_mdbInit(&req,&rpt);

    entry = Json_create_title(EV_MDB_INIT);
    Json_insert_int(entry,"port_id",rpt.fd);
    Json_insert_int(entry,"bill",rpt.bill);
    Json_insert_int(entry,"coin",rpt.coin);

    if(res == 1){
        Json_insert_int(entry,"is_success",rpt.res);
        Json_insert_int(entry,"bill_result",rpt.billResult);
        Json_insert_int(entry,"coin_result",rpt.coinResult);
    }
    else{
        Json_insert_int(entry,"is_success",0);
    }

    root = Json_insert_head(entry);
    if(root != NULL){
        json_tree_to_string(root, &text);
        msg = (*env)->NewStringUTF(env,text);
        free(text);
        json_free_value(&root);
    }
    else{
        msg = (*env)->NewStringUTF(env,"{\"EV_json\":{\"EV_type\":9999}}");
    }

    return msg;

}




/*
 * Class:     com_easivend_evprotocol_EVprotocol
 * Method:    EVmdbEnable
 * Signature: (IIII)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_easivend_evprotocol_EVprotocol_EVmdbEnable
  (JNIEnv *env, jclass cls, jint fd, jint bill, jint coin, jint opt)
{
    ST_MDB_ENABLE_REQ req;
    ST_MDB_ENABLE_RPT rpt;
    int res;
    jstring msg;
    char *text;
    json_t *root,*entry;


    req.fd =    fd;
    req.bill =  bill;
    req.coin =  coin;
    req.opt =   opt;
    res = EV_mdbEnable(&req,&rpt);

    entry = Json_create_title(EV_MDB_ENABLE);
    Json_insert_int(entry,"port_id",rpt.fd);
    Json_insert_int(entry,"bill",rpt.bill);
    Json_insert_int(entry,"coin",rpt.coin);
    Json_insert_int(entry,"opt",rpt.opt);


    if(res == 1){
        Json_insert_int(entry,"is_success",rpt.res);
        Json_insert_int(entry,"bill_result",rpt.billResult);
        Json_insert_int(entry,"coin_result",rpt.coinResult);
    }
    else{
        Json_insert_int(entry,"is_success",0);
    }

    root = Json_insert_head(entry);
    if(root != NULL){
        json_tree_to_string(root, &text);
        msg = (*env)->NewStringUTF(env,text);
        free(text);
        json_free_value(&root);
    }
    else{
        msg = (*env)->NewStringUTF(env,"{\"EV_json\":{\"EV_type\":9999}}");
    }

    return msg;
}




/*
 * Class:     com_easivend_evprotocol_EVprotocol
 * Method:    EVmdbHeart
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_easivend_evprotocol_EVprotocol_EVmdbHeart
  (JNIEnv *env, jclass cls, jint fd)
{
    ST_MDB_HEART_REQ req;
    ST_MDB_HEART_RPT rpt;
    int res;
    jstring msg;
    char *text;
    json_t *root,*entry;


    req.fd =    fd;
    res = EV_mdbHeartCheck(&req,&rpt);

    entry = Json_create_title(EV_MDB_HEART);
    Json_insert_int(entry,"port_id",rpt.fd);

    if(res == 1){
        Json_insert_int(entry,"is_success",rpt.res);
        Json_insert_int(entry,"bill_enable",rpt.billEnable);
        Json_insert_int(entry,"bill_payback",rpt.billPayback);
        Json_insert_int(entry,"bill_err",rpt.billErr);
        Json_insert_int(entry,"bill_recv",rpt.billAmount);
        Json_insert_int(entry,"bill_remain",rpt.billRemain);

        Json_insert_int(entry,"coin_enable",rpt.coinEnable);
        Json_insert_int(entry,"coin_payback",rpt.coinPayback);
        Json_insert_int(entry,"coin_err",rpt.coinErr);
        Json_insert_int(entry,"coin_recv",rpt.coinAmount);
        Json_insert_int(entry,"coin_remain",rpt.coinRemain);

    }
    else{
        Json_insert_int(entry,"is_success",0);
    }

    root = Json_insert_head(entry);
    if(root != NULL){
        json_tree_to_string(root, &text);
        msg = (*env)->NewStringUTF(env,text);
        free(text);
        json_free_value(&root);
    }
    else{
        msg = (*env)->NewStringUTF(env,"{\"EV_json\":{\"EV_type\":9999}}");
    }

    return msg;
}



/*
 * Class:     com_easivend_evprotocol_EVprotocol
 * Method:    EVmdbBillInfoCheck
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_easivend_evprotocol_EVprotocol_EVmdbBillInfoCheck
  (JNIEnv *env, jclass cls, jint fd)
{
    ST_MDB_BILL_INFO_REQ req;
    ST_MDB_BILL_INFO_RPT rpt;
    int res,i;
    jstring msg;
    char *text,buf[256];
    json_t *root,*entry,*arr,*label;


    req.fd =    fd;
    res = EV_mdbBillInfoCheck(&req,&rpt);

    entry = Json_create_title(EV_MDB_B_INFO);
    Json_insert_int(entry,"port_id",rpt.fd);

    if(res == 1){
        Json_insert_int(entry,"is_success",rpt.res);
        Json_insert_int(entry,"acceptor",rpt.acceptor);
        Json_insert_int(entry,"dispenser",rpt.dispenser);


        Json_insert_str(entry,"code",rpt.code);
        Json_insert_str(entry,"sn",rpt.sn);
        Json_insert_str(entry,"model",rpt.model);

        memset(buf,0,sizeof(buf));
        for(i = 0;i < 2;i++){
           sprintf(&buf[i*2],"%02x",rpt.ver[i]);
        }
        Json_insert_str(entry,"ver",buf);
        Json_insert_int(entry,"capacity",rpt.capacity);

        arr = json_new_array();
        for(i = 0;i < 16;i++){
            label = json_new_object();
            Json_insert_int(label,"ch",i + 1);
            Json_insert_int(label,"value",rpt.ch_r[i]);
            json_insert_child(arr,label);
        }
        label = json_new_string("ch_r");
        json_insert_child(label,arr);
        json_insert_child(entry,label);


        arr = json_new_array();
        for(i = 0;i < 16;i++){
            label = json_new_object();
            Json_insert_int(label,"ch",i + 1);
            Json_insert_int(label,"value",rpt.ch_d[i]);
            json_insert_child(arr,label);
        }
        label = json_new_string("ch_d");
        json_insert_child(label,arr);
        json_insert_child(entry,label);

    }
    else{
        Json_insert_int(entry,"is_success",0);
    }

    root = Json_insert_head(entry);
    if(root != NULL){
        json_tree_to_string(root, &text);
        msg = (*env)->NewStringUTF(env,text);
        free(text);
        json_free_value(&root);
    }
    else{
        msg = (*env)->NewStringUTF(env,"{\"EV_json\":{\"EV_type\":9999}}");
    }

    return msg;
}


/*
 * Class:     com_easivend_evprotocol_EVprotocol
 * Method:    EVmdbCoinInfoCheck
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_easivend_evprotocol_EVprotocol_EVmdbCoinInfoCheck
  (JNIEnv *env, jclass cls, jint fd)
{
    ST_MDB_COIN_INFO_REQ req;
    ST_MDB_COIN_INFO_RPT rpt;
    int res,i;
    jstring msg;
    char *text,buf[256];
    json_t *root,*entry,*arr,*label;


    req.fd =    fd;
    res = EV_mdbCoinInfoCheck(&req,&rpt);

    entry = Json_create_title(EV_MDB_C_INFO);
    Json_insert_int(entry,"port_id",rpt.fd);

    if(res == 1){
        Json_insert_int(entry,"is_success",rpt.res);
        Json_insert_int(entry,"acceptor",rpt.acceptor);
        Json_insert_int(entry,"dispenser",rpt.dispenser);


        Json_insert_str(entry,"code",rpt.code);
        Json_insert_str(entry,"sn",rpt.sn);
        Json_insert_str(entry,"model",rpt.model);

        memset(buf,0,sizeof(buf));
        for(i = 0;i < 2;i++){
           sprintf(&buf[i*2],"%02x",rpt.ver[i]);
        }
        Json_insert_str(entry,"ver",buf);
        Json_insert_int(entry,"capacity",rpt.capacity);

        arr = json_new_array();
        for(i = 0;i < 16;i++){
            label = json_new_object();
            Json_insert_int(label,"ch",i + 1);
            Json_insert_int(label,"value",rpt.ch_r[i]);
            json_insert_child(arr,label);
        }
        label = json_new_string("ch_r");
        json_insert_child(label,arr);
        json_insert_child(entry,label);


        arr = json_new_array();
        for(i = 0;i < 16;i++){
            label = json_new_object();
            Json_insert_int(label,"ch",i + 1);
            Json_insert_int(label,"value",rpt.ch_d[i]);
            json_insert_child(arr,label);
        }
        label = json_new_string("ch_d");
        json_insert_child(label,arr);
        json_insert_child(entry,label);

    }
    else{
        Json_insert_int(entry,"is_success",0);
    }

    root = Json_insert_head(entry);
    if(root != NULL){
        json_tree_to_string(root, &text);
        msg = (*env)->NewStringUTF(env,text);
        free(text);
        json_free_value(&root);
    }
    else{
        msg = (*env)->NewStringUTF(env,"{\"EV_json\":{\"EV_type\":9999}}");
    }

    return msg;
}



/*
 * Class:     com_easivend_evprotocol_EVprotocol
 * Method:    EVmdbCost
 * Signature: (II)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_easivend_evprotocol_EVprotocol_EVmdbCost
  (JNIEnv *env, jclass cls, jint fd, jint cost)
{
    ST_MDB_COST_REQ req;
    ST_MDB_COST_RPT rpt;
    int res;
    jstring msg;
    char *text;
    json_t *root,*entry;


    req.fd =    fd;
    req.cost = cost;
    res = EV_mdbCost(&req,&rpt);

    entry = Json_create_title(EV_MDB_COST);
    Json_insert_int(entry,"port_id",rpt.fd);
    Json_insert_int(entry,"cost",rpt.cost);
    if(res == 1){
        Json_insert_int(entry,"is_success",1);
        Json_insert_int(entry,"result",rpt.res);
        Json_insert_int(entry,"bill_recv",rpt.billAmount);
        Json_insert_int(entry,"coin_recv",rpt.coinAmount);
    }
    else{
        Json_insert_int(entry,"is_success",0);
    }

    root = Json_insert_head(entry);
    if(root != NULL){
        json_tree_to_string(root, &text);
        msg = (*env)->NewStringUTF(env,text);
        free(text);
        json_free_value(&root);
    }
    else{
        msg = (*env)->NewStringUTF(env,"{\"EV_json\":{\"EV_type\":9999}}");
    }

    return msg;
}


/*
 * Class:     com_easivend_evprotocol_EVprotocol
 * Method:    EVmdbPayback
 * Signature: (III)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_easivend_evprotocol_EVprotocol_EVmdbPayback
  (JNIEnv *env, jclass cls, jint fd, jint bill, jint coin)
{

    ST_MDB_PAYBACK_REQ req;
    ST_MDB_PAYBACK_RPT rpt;
    int res;
    jstring msg;
    char *text;
    json_t *root,*entry;


    req.fd =    fd;
    req.bill = bill;
    req.coin = coin;
    res = EV_mdbPayBack(&req,&rpt);

    entry = Json_create_title(EV_MDB_PAYBACK);
    Json_insert_int(entry,"port_id",rpt.fd);
    Json_insert_int(entry,"bill",rpt.bill);
    Json_insert_int(entry,"coin",rpt.coin);
    if(res == 1){
        Json_insert_int(entry,"is_success",1);
        Json_insert_int(entry,"result",rpt.res);
        Json_insert_int(entry,"bill_changed",rpt.billChanged);
        Json_insert_int(entry,"coin_changed",rpt.coinChanged);
    }
    else{
        Json_insert_int(entry,"is_success",0);
    }

    root = Json_insert_head(entry);
    if(root != NULL){
        json_tree_to_string(root, &text);
        msg = (*env)->NewStringUTF(env,text);
        free(text);
        json_free_value(&root);
    }
    else{
        msg = (*env)->NewStringUTF(env,"{\"EV_json\":{\"EV_type\":9999}}");
    }

    return msg;

}

/*
 * Class:     com_easivend_evprotocol_EVprotocol
 * Method:    EVmdbPayout
 * Signature: (IIIII)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_easivend_evprotocol_EVprotocol_EVmdbPayout
  (JNIEnv *env, jclass cls, jint fd, jint bill, jint coin, jint billPay, jint coinPay)
{
    ST_MDB_PAYOUT_REQ req;
    ST_MDB_PAYOUT_RPT rpt;
    int res;
    jstring msg;
    char *text;
    json_t *root,*entry;


    req.fd =    fd;
    req.bill = bill;
    req.coin = coin;
    req.billPayout = billPay;
    req.coinPayout = coinPay;
    res = EV_mdbPayout(&req,&rpt);

    entry = Json_create_title(EV_MDB_PAYOUT);
    Json_insert_int(entry,"port_id",rpt.fd);
    Json_insert_int(entry,"bill",rpt.bill);
    Json_insert_int(entry,"coin",rpt.coin);
    Json_insert_int(entry,"billPayout",rpt.billPayout);
    Json_insert_int(entry,"coinPayout",rpt.coinPayout);
    if(res == 1){
        Json_insert_int(entry,"is_success",1);
        Json_insert_int(entry,"result",rpt.res);
        Json_insert_int(entry,"bill_changed",rpt.billChanged);
        Json_insert_int(entry,"coin_changed",rpt.coinChanged);
    }
    else{
        Json_insert_int(entry,"is_success",0);
    }

    root = Json_insert_head(entry);
    if(root != NULL){
        json_tree_to_string(root, &text);
        msg = (*env)->NewStringUTF(env,text);
        free(text);
        json_free_value(&root);
    }
    else{
        msg = (*env)->NewStringUTF(env,"{\"EV_json\":{\"EV_type\":9999}}");
    }

    return msg;
}
