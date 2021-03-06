#include <stdio.h>

#include <fmconfig.h>

int main(int argc, char** argv)
{
  ERROR_CODE retval = SUCCESS_NO_ERROR;
  
  retval = init_fmnc();

  if (SUCCESS_NO_ERROR != retval)
    {
      printf("Exiting with error code: %i\n", retval);
      return retval;
    }

  LOG("***** Application closed. *****", LOG_INFO);
  exit_fmnc();
  
  
  return retval;
}
