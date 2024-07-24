//数据库连接池
#pragma once
#include<iostream>
#include<string>
#include<mysql/mysql.h>
#include<queue>

class Mysql_conPool
{
public:



private:
    //连接池用队列实现
    queue<MYSQL *> conPool;

    //成员变量有：url port user password databaseName
    string m_url;
    string m_port;
    string m_user;
    string m_password;
    string m_databaseName;
};

