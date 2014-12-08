#include "main.h"

int cli(char * filename, char * pwd, char * cmdstr, char ** cmdpar)
{
	char cmd[1025];
	printf("%s:%s ] ", filename, pwd);
	fgets(cmdstr, 1024, stdin);
	sscanf(cmdstr, "%s", cmd);
	for ( * cmdpar = cmdstr; 
		*(*cmdpar) != '\0' && *(*cmdpar) != ' '; 
		(*cmdpar) ++ 
	);
	while ( ' ' == *(*cmdpar) )
	{
		(*cmdpar) ++;
	}
	if ( ! strcmp(cmd, "exit") )
	{
		return -1;
	}
	else if ( ! strcmp(cmd, "new") )
	{
		return 1;
	}
	else if ( ! strcmp(cmd, "sfs") )
	{
		return 2;
	}
	else if ( ! strcmp(cmd, "mkdir") )
	{
		return 3;
	}
	else if ( ! strcmp(cmd, "rmdir") )
	{
		return 4;
	}
	else if ( ! strcmp(cmd, "ls") )
	{
		return 5;
	}
	else if ( ! strcmp(cmd, "cd") )
	{
		return 6;
	}
	else if ( ! strcmp(cmd, "create") )
	{
		return 7;
	}
	else if ( ! strcmp(cmd, "open") )
	{
		return 8;
	}
	else if ( ! strcmp(cmd, "close") )
	{
		return 9;
	}
	else if ( ! strcmp(cmd, "read") )
	{
		return 10;
	}
	else if ( ! strcmp(cmd, "write") )
	{
		return 11;
	}
	else if ( ! strcmp(cmd, "delete") )
	{
		return 12;
	}
	else return 0;
/*	else if ( ! strcmp(cmd, "new") )
	{
		return 1;
	}
*/
}

void cmderror()
{
	printf("\033[31m>>> Command cannot be understand.\033[0m\n");
	return ;
}

int main(int argc, char * argv[])
{
	int cmd;
	char cmdstr[1025], filename[1024] = "(NULL)", pwd[1024] = "";
	char * cmdpar;
	while ( ~ (cmd = cli(filename, pwd, cmdstr, &cmdpar)) )
	{
		printf("%d %s\n%s\n", cmd, cmdstr, cmdpar);
		switch ( cmd )
		{
			case  0: cmderror(); break;
			case  1: New(filename, cmdpar, pwd, &disk, &status); break;
			case  2: break;
			case  3: Mkdir(pwd, cmdpar, disk, &status); break;
			case  4: break;
			case  5: break;
			case  6: break;
			case  7: break;
			case  8: break;
			case  9: break;
			case 10: break;
			case 11: break;
			case 12: break;
		}
	}
	
	return 0;
}

