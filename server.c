//
//  server.c
//  职工管理系统1
//
//  Created by 潘梓坤 on 2022/7/14.
//

#include <stdio.h>
#include<winsock.h>
int main()
{
    //定义变量
    char Sendbuf[100];
    char Receivebuf[100];
    int SendLen;
    int ReceiveLen;
    int Length;
    
    SOCKET socket_server;
    SOCKET socket_receive;
    SOCKADDR_IN Server_add;
    SOCKADDR_IN Client_add;
    WORD wVersionRequested;
    WSADATA wsaData;
    int error;
    //初始化套接字库
    /*定义版本类型。将两个字节组合成一一个字，前面是低字节，后面是高字节*/
    wVersionRequested = MAKEWORD(2, 2);
    /*加载套接字库，初始化Ws2_ 32. dll动态链接库*/
    error = WSAStartup(wVersionRequested, &wsaData);
    if(error!=0)
    {
        printf("加载套接字失败! ");
        return 0;
        /判断请求加载的版本号是否符合要求
        if(LOBYTE(wsaData.wVersion)!=2||HIBYTE(wsaData.wVersion)!= 2)
        {
            WSACleanup();
            return 0;
        }
    }
    //设置连接地址
    Server_add.sin_family=AF_INET;
    Server_add.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//主机地址
    Server_add.sin_port=htons(5000);//端口号
    //创建套接字
    socket_server=socket(AF_INET.SOCK_STREAM,0);
    //绑定套接字到本地某个地址和端口上
    if(bind(socket_server,(SOCKADDR*)&Server_add,sizeof(SOCKADDR)==SOCKET_ERROR)
    {
        printf("绑定失败\n");
    }
    //设置套接字为监听状态
    if(listen(socket_server,5)<0)
    {
        printf(" 监听失败\n");
    }
    //接受连接
    Length=sizeof(SOCKADDR);
    //接受客户端发出的请求，等待客户端发出的connnect请求
    socket_receive=accept(socket_server,(SOCKADDR*)&Client_add,&Length);
    if(socket_receive==SOCKET_ERROR)
    {
        printf("接受连接失败");
    }
    else
    {
        printf("连接成功");
    }
    //进行聊天
    while(1)
    {
        ReceiveLen=recv(socket_receive,Receivebuf,100,0);
        if(ReceiveLen<0)
        {
            print("接收失败\n");
            printf("程序退出\n");
            break;
        }
        else
        {
            printf("client say: %s\n" ,Receivebuf);
        }
        //发送数据
        printf("please enter message:");
        scanf("%s",Sendbuf);
        SendLen=send(socket_receive,Sendbuf,100,0);
        if(SendLen<0)
        {
            printf("发送失败！\n")；
        }
    }
    //释放套接字，关闭动态库
    closesocket(socket_receive);
    closesocket(socket_server);
    WSACleanup();
    return 0;
}
