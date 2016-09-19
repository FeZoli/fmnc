#ifndef _DB_H_
#define _DB_H_

#include <my_global.h>
#include <mysql.h>

#include <errorcodes.h>


#define MAX_LEN_OF_DB_DATA_STRING 64

struct DBConnectData
{
  char host[MAX_LEN_OF_DB_DATA_STRING];
  char name[MAX_LEN_OF_DB_DATA_STRING];
  char user[MAX_LEN_OF_DB_DATA_STRING];
  char pass[MAX_LEN_OF_DB_DATA_STRING];
  char socket[MAX_LEN_OF_DB_DATA_STRING];
  int port;
};


ERROR_CODE connect_db(struct DBConnectData* connect_data, MYSQL* db);


#endif
