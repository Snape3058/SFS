#include "Mkdir.h"


void Mkdir(
	char * pwd,
	char * cmdstr,
	char * disk,
	sysStatus * pstatus
)
{
	char filename[1025];

	if ( ! disk )
	{
		printf("\033[31m>>> No SFS opened, please new or open an SFS first!\033[0m\n");
		return ;
	}
	if ( '\0' == cmdstr[0] || '\n' == cmdstr[0] )
	{
		printf(">>> mkdir [filename]\n"
			">>> Please enter the name of the new directory.\n");
		return ;
	}
	else
	{
		sscanf(cmdstr, "%s", filename);
		printf(">>> new [%s%s/]\n", pwd, filename);
	}
	/* new a directory in FCB */
	
}
