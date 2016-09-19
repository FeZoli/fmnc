#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>

#include <fmconfig.h>

#define STRING_SIZE 32


const char* inifile_name = "fmconfig.ini";
struct DBConnectData connect_data;
static char logfile_name[MAX_LEN_OF_DB_DATA_STRING];
static FILE* logfile;
static MYSQL* db;


ERROR_CODE parse_line_and_store_data(char* line)
{
  ERROR_CODE retval = SUCCESS_NO_ERROR; 
  char* token;

  if (NULL != (token = strsep(&line, "=")))
    {
      if (0 == strcmp("dbname", token))
	{
	  if (NULL != (token = strsep(&line, "\n")))
	    {
	      strncpy(connect_data.name, token, MAX_LEN_OF_DB_DATA_STRING); 
	    }
	}
      else if (0 == strcmp("dbhost", token))
	{
	  if (NULL != (token = strsep(&line, "\n")))
	    {
	      strncpy(connect_data.host, token, MAX_LEN_OF_DB_DATA_STRING); 
	    }
	}
      else if (0 == strcmp("dbuser", token))
	{
	  if (NULL != (token = strsep(&line, "\n")))
	    {
	      strcpy(connect_data.user, token); 
	    }
	}
      else if (0 == strcmp("dbpass", token))
	{
	  if (NULL != (token = strsep(&line, "\n")))
	    {
	      strncpy(connect_data.pass, token, MAX_LEN_OF_DB_DATA_STRING); 
	    }
	}
      else if (0 == strcmp("dbport", token))
	{
	  if (NULL != (token = strsep(&line, "\n")))
	    {
	      connect_data.port = atoi(token);
	    }
	}
      else if (0 == strcmp("dbsock", token))
	{
	  if (NULL != (token = strsep(&line, "\n")))
	    {
	      strncpy(connect_data.socket, token, MAX_LEN_OF_DB_DATA_STRING); 
	    }
	}
      else if (0 == strcmp("logfile", token))
	{
	  if (NULL != (token = strsep(&line, "\n")))
	    {
	      strncpy(logfile_name, token, MAX_LEN_OF_DB_DATA_STRING); 
	    }
	}

    }
  return retval;
}


ERROR_CODE load_ini()
{
  ERROR_CODE retval = SUCCESS_NO_ERROR;
  FILE* inifile = NULL;
  inifile = fopen(inifile_name, "r");
  char* p_line = NULL;
  size_t line_max_len = 25;

  if (NULL == inifile)
    {
      fprintf(stderr, "Inifile %s could not be opened. Exiting.\n", inifile_name);
      return ERROR_INIFILE_OPEN_FAILED;
    }
  
  while ( -1 != getline(&p_line, &line_max_len, inifile))
    {
      if (0 < strlen(p_line))
	parse_line_and_store_data(p_line);
    }
  
  fclose(inifile);
		    
  return retval; 
}


ERROR_CODE init_logger()
{
  ERROR_CODE retval = SUCCESS_NO_ERROR;
  logfile = fopen(logfile_name, "a+");

  if (NULL == logfile)
    {
      fprintf(stderr, "Logfile %s could not be opened. Exiting.\n", logfile_name);
      return ERROR_LOGFILE_OPEN_FAILED;
    }

  LOG("***** Application started. ******", LOG_INFO);

  return retval;
}




void LOG(const char* message, LOG_MODE mode)
{
  time_t curtime;
  struct tm *loctime;
  char prefix[STRING_SIZE] = "\0";
  char timestamp[STRING_SIZE] = "\0";

  curtime = time (NULL);
  loctime = localtime (&curtime);
  
  strftime(timestamp, STRING_SIZE, "%F %H:%M:%S", loctime);
	   
  switch(mode)
    {
    case LOG_WARNING:
      sprintf(prefix, "WARNING");
    case LOG_DEBUG:
      sprintf(prefix, "DEBUG");
    default:
      sprintf(prefix, "INFO");
    }
  
  fprintf(logfile,
	  "%s: %s : %s\n",
	  prefix,
	  timestamp,
	  message);
}


MYSQL* DB()
{
  return db;
}


void init_screen()
{
  initscr();			/* Start curses mode 		  */
  printw("Hello World !!!");	/* Print Hello World		  */
  refresh();			/* Print it on to the real screen */
  getch();			/* Wait for user input */
}


ERROR_CODE init_fmnc()
{
  ERROR_CODE retval = SUCCESS_NO_ERROR;

  retval = load_ini();
  if (SUCCESS_NO_ERROR != retval) return retval;

  retval = connect_db(&connect_data, db);
  if (SUCCESS_NO_ERROR != retval) return retval;

  retval = init_logger(&connect_data, db);
  if (SUCCESS_NO_ERROR != retval) return retval;

  init_screen();

  return retval;
}


ERROR_CODE exit_fmnc()
{
  if (NULL != DB) mysql_close(db);
  if (NULL != logfile) fclose(logfile);
  
  endwin();
  
  return SUCCESS_NO_ERROR;
}
