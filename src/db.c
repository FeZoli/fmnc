#include <db.h>



ERROR_CODE connect_db(struct DBConnectData* connect_data, MYSQL* db)
{
  ERROR_CODE retval = SUCCESS_NO_ERROR;

  db = mysql_init(NULL);

  if (mysql_real_connect(db,
			 connect_data->host,
			 connect_data->user,
			 connect_data->pass,
			 connect_data->name,
			 connect_data->port,
			 connect_data->socket, 0) == NULL)
    {
      fprintf(stderr, "Failed to connect database. Error message: \n%s\n",
	      mysql_error(db));
      mysql_close(db);
      retval = ERROR_DB_CONNECTION_FAILED;
    }

  return retval;
}
