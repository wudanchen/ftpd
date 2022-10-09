#include "ftpserver.h"
#include "commandparser.h"

#include <ace/Reactor.h>
#include <ace/Event_Handler.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Log_Msg.h>

class Data_Event_Handler : public ACE_Event_Handler {
public:
    Data_Event_Handler();
    ~Data_Event_Handler();
private:

};

class Client_Event_Handler : public ACE_Event_Handler {
public:
    Client_Event_Handler();
    ~Client_Event_Handler();
    int handle_input (ACE_HANDLE fd = ACE_INVALID_HANDLE) override;
    int handle_output (ACE_HANDLE fd = ACE_INVALID_HANDLE) override;
    int handle_close (ACE_HANDLE handle, ACE_Reactor_Mask close_mask) override;
    ACE_HANDLE get_handle (void) const override;

    inline ACE_SOCK_Stream &peer() { return peer_; }

private:
    ACE_SOCK_Stream peer_;
    Command_Parser cmd_parser_;
};

Client_Event_Handler::Client_Event_Handler()
{

}

Client_Event_Handler::~Client_Event_Handler()
{

}

int Client_Event_Handler::handle_input(ACE_HANDLE fd)
{
    ACE_DEBUG((LM_DEBUG, "============client input fd start: %d ============\n", fd));
    char buf[1024] = {0};
    ssize_t ret = peer_.recv(buf, sizeof(buf));
    ACE_DEBUG((LM_DEBUG, "ret : %d\n", ret));
    if(ret < 0) {
        if(ACE_ERRNO_GET == EAGAIN || ACE_ERRNO_GET == EWOULDBLOCK) {
            return 0;
        }
        return -1;
    }else if (ret == 0) {
        ACE_DEBUG((LM_DEBUG, "connect closed.\n"));
        return -1;
    }
    //recv数据处理
    ACE_DEBUG((LM_DEBUG, "data : %s\n", buf));
    cmd_parser_.parsing_data(buf, sizeof(buf));
    ACE_Reactor::instance()->mask_ops(get_handle(), WRITE_MASK, ACE_Reactor::ADD_MASK);
    ACE_DEBUG((LM_DEBUG, "============client input fd end: %d ============\n", fd));
    return 0;
}

int Client_Event_Handler::handle_output(ACE_HANDLE fd)
{
    //发送数据处理
    ACE_DEBUG((LM_DEBUG, "============client output fd start: %d ============\n", fd));
    peer_.send(cmd_parser_.response_data(), sizeof(cmd_parser_.response_data()));
    ACE_Reactor::instance()->cancel_wakeup(get_handle(), WRITE_MASK);
    ACE_DEBUG((LM_DEBUG, "============client output fd end: %d ============\n", fd));
    return 0;
}

int Client_Event_Handler::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask)
{
    ACE_DEBUG((LM_DEBUG, "current function : Read_Event_Handler::handle_close, handle : %d\n", handle));
    if(handle == -1) {
        return 0;
    }
    peer_.close();
    delete this;
    return 0;
}

ACE_HANDLE Client_Event_Handler::get_handle(void) const
{
    return peer_.get_handle();
}

class Accept_Event_Handler : public ACE_Event_Handler {
public:
    Accept_Event_Handler();
    ~Accept_Event_Handler();
    int handle_input (ACE_HANDLE fd = ACE_INVALID_HANDLE) override;
    int handle_close (ACE_HANDLE handle, ACE_Reactor_Mask close_mask) override;
    ACE_HANDLE get_handle (void) const override;
    int open(int port);

private:
    void close();
    
    ACE_SOCK_Acceptor acceptor_;
};

Accept_Event_Handler::Accept_Event_Handler()
{
}

Accept_Event_Handler::~Accept_Event_Handler()
{

}
//返回 0 , 在处理器方法完成后，事件处理器将保持在反应器上的登记
//返回 <0：反应器将自动回调此事件处理器的handle_close()方法，并将它自己的内部分派表肿拆除，handle_close()
//        用于执行处理器特有的任何清除工作，它们需要在时间处理器被拆除前完成，其中可以包括像删除处理器申请的
//        的动态内存，或关闭日志文件这样的工作。
int Accept_Event_Handler::handle_input(ACE_HANDLE fd)
{

    Client_Event_Handler *en = new Client_Event_Handler();
    if(acceptor_.accept(en->peer()) == -1) {
        ACE_DEBUG((LM_ERROR, "Error in conection.\n"));
        delete en;
        return 0;
    }
    ACE_DEBUG((LM_DEBUG, "connection established.\n"));
    ACE_Reactor::instance()->register_handler(en, READ_MASK | WRITE_MASK);
    return 0;
}

int Accept_Event_Handler::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask) 
{
    ACE_DEBUG((LM_DEBUG, "current function : accept_event_handler::handle_close"));
    close();
    return 0;
}

ACE_HANDLE Accept_Event_Handler::get_handle(void) const
{
    return acceptor_.get_handle();
}

int Accept_Event_Handler::open(int port)
{
    return acceptor_.open(ACE_INET_Addr(port));
}

void Accept_Event_Handler::close()
{
    acceptor_.close();
    delete this;
}

Ftp_Server::Ftp_Server(int port)
    :port_(port) 
{
    
}


Ftp_Server::~Ftp_Server()
{

}

int Ftp_Server::run_loop()
{
    Accept_Event_Handler *accept_handler = new Accept_Event_Handler();
    if(accept_handler->open(port_) < 0) {
        ACE_DEBUG((LM_DEBUG, "listren port %d connect failed.\n", port_));
        delete accept_handler;
        return -1;
    }
    ACE_Reactor::instance()->register_handler(accept_handler, ACE_Event_Handler::ACCEPT_MASK);
    return ACE_Reactor::instance()->run_reactor_event_loop();
}
