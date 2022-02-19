#ifndef HEAPTIMER_H
#define HEAPTIMER_H
/*采用小根堆的定时器*/
#include<iostream>
#include<vector>
#include<netinet/in.h>
#include<time.h>
#include "../http/httpConn.h"
const int BUFF_SIZE=64;

class timer;

/*绑定socket与定时器以及http处理对象*/
struct clientData{
    sockaddr_in addr;
    int sockfd;
    char buf[BUFF_SIZE];
    httpConn* clientHttp; 
    timer* clientTimer;
};


/*定时器类*/
class timer{
public:
    time_t expire;                  //定时器生效的绝对时间
    void (*cb_func)(clientData*);   //定时器的回调函数
    clientData* userData;           //用户数据
public:
    timer(int delay){
        expire=time(nullptr)+delay;
    }
};

/*绑定socket与定时器以及http处理对象*/
struct clientData{
    sockaddr_in addr;
    int sockfd;
    char buf[BUFF_SIZE];
    httpConn* clientHttp; 
    timer* clientTimer;
};


class timeHeap{
private:
    std::vector<timer*> heap;
    int size;
public:
    //初始化为一个cap大小的空堆
    timeHeap(int cap);
    ~timeHeap();

    void addTimer(timer* _timer);
    void delTimer(timer* _timer);
    void adjTimer(timer* _timer,int delayTime);
    void popTimer();

    timer* top() const;
    void tick();
private:
    void heapify(int idx);
    void heapInsert(int idx);
};

#endif