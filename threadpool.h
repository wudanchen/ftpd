/*
 * @Author: wdc 724214532@qq.com
 * @Date: 2022-08-25 17:29:23
 * @LastEditors: wdc 724214532@qq.com
 * @LastEditTime: 2022-10-01 17:49:23
 * @FilePath: /ftpd/threadpool.h
 * @Description: 
 * 
 * Copyright (c) 2022 by wdc 724214532@qq.com, All Rights Reserved. 
 */

#pragma once
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <functional>
#include <assert.h>
#include <atomic>

class Thread_Pool {
public:
    explicit Thread_Pool(size_t threadCount = 8) 
    : isclosed_(false)
    {
        init_thread(threadCount);
    }
    void add_task(const std::function<void()> &task) 
    {
        {
            std::lock_guard<std::mutex> locker(mutex_);
            tasks_.push(task);
        }
        cond_.notify_one();
    }

    ~Thread_Pool() 
    {
        {
            std::lock_guard<std::mutex> locker(mutex_);
            isclosed_ = true;
        }
        cond_.notify_all();
    }

private:

    void init_thread(int threadCount = 8) 
    {
        for(int i = 0; i < threadCount; ++i) {
            std::thread(std::bind(&Thread_Pool::call_back, this)).detach();
        }
    }

    void call_back()
    {
        std::function<void()> task;
        while (true) {
            {
                std::unique_lock<std::mutex> locker(mutex_);
                while (tasks_.empty()){
                    cond_.wait(locker);
                    if(isclosed_) {
                        return;
                    }
                }
                task = tasks_.front();
                tasks_.pop();
            }
            task();
        }
    }

    std::queue<std::function<void()>> tasks_;
    std::mutex mutex_;
    std::condition_variable cond_;
    bool isclosed_;
};