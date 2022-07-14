//
//  client.c
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
    SOCKET socket_send;
    SOCKADDR_IN Server_add;
    WORD wVersionRequested;
    WSADATA wsaData;
    int error;
    // 初始化套接字库
    wVersionRequested=MAKEWORD(2,2);
    error=WSAStartup(wVersionRequested,&wsaData);//定义错误变量
    if(error!=0)
    {
        printf("加载套接字失败!");
        return 0;
    }
    //判断请求加载的版本号是否符合要求
    if(LOBYTE(wsaData.wVersion)!= 2||HIBYTE(wsaData.wVersion)!=2)
    {
        WSACleanup();
        return 0;
    }
    //设置服务器地址
    Server_add.sin_family=AF_INET;/*地址家族，必须是AF_ INET,注意只有它不是网络字节顺序*/
    Server_add.sin_addr.S_un.S_addr=inet_addr("192.168.1.43");
    Server_add.sin_port=htons(5000):/*端口号*/
    //连接服务器
    socket_send=socket(AF_INET,SOCK_STREAM,O);
    //创建用于连接的套接字
    if(connect(socket_send,(SOCKADDR*)&Server_add,sizeof(SOCKADDR))==SOCKET_ERROR)
    {
        printf("连接失败!\n");
    }
    else
    {
        printf("连接成功！\n");
    }
    //进行聊天
    while(1)
    {
        printf("please enter message:");
        scanf("%s" ,Sendbuf);
        SendLen=send(socket_send,Sendbuf,100,0);
        if(SendLen<0)
        {
            printf("发送失败!n");
        }
        ReceiveLen=recv(socket_send,Receivbuf,100,0);
        if(ReceiveLen<0)
        {
            printf("接收失败\n");
            printf("程序退出\n");
            break;
        }
        else
        {
            printf("Server say:%s\n",Receivebuf);
        }
    }
    //释放套接字，关闭动态库
    closesocket(socket_send);
    WSACleanup();
    return 0;
}
