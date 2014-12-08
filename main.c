#include "main.h"

int cli(char * pwd, char * cmdstr)
{
	char cmd[1025];
	printf("sfs:%s ] ", pwd);
	fgets(cmdstr, 1024, stdin);
	sscanf(cmdstr, "%s", cmd);
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
	printf("Command cannot be understand.\n");
	return ;
}

int main()
{
	int cmd;
	char cmdstr[1025], pwd[1024] = "(NULL)";
	while ( ~ (cmd = cli(pwd, cmdstr)) )
	{
		//printf("%d %s\n", cmd, cmdstr);
		switch ( cmd )
		{
			case  0: cmderror(); break;
			case  1: New(cmdstr, pwd); break;
			case  2: break;
			case  3: break;
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

