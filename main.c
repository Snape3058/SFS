#include "main.h"

int cli(char * filename, char * pwd, char * cmdstr, char ** cmdpar)
{
	char cmd[1025];
	printf("%s:%s %s ", filename, pwd, (status.disk)?"]":"X");
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
	else if ( ! strcmp(cmd, "tree") )
	{
  		return 13;
	}
	else if ( ! strcmp(cmd, "fcbs") )
	{
		return 14;
	}
	else if ( ! strcmp(cmd, "readfcb") )
	{
		return 15;
	}
	else if ( ! strcmp(cmd, "readdisk") )
	{
		return 16;
	}

/*	else if ( ! strcmp(cmd, "new") )
	{
		return 1;
	}
*/
	else return 0;
}

void cmderror()
{
	printf("\033[31m>>> Command cannot be understand.\033[0m\n");
	return ;
}

long min(long a, long b)
{
	return (a < b)?(a):(b);
}

long max(long a, long b)
{
	return (a > b)?(a):(b);
}

void readDisk(char * cmdstr)
{
	int i, j;
	int begin = 0, end = (diskSize >> 4);
	sscanf(cmdstr, "%x%x", &begin, &end);
	for ( i = begin; i < min(end, (diskSize >> 4)); i ++ )
	{
		printf("%05X :", i);
		for ( j = 0; j < 16; j ++ )
		{
			printf("  %02X", (unsigned char) status.disk[(i << 4) + j]);
		}
		putchar('\n');
	}
	return ;
}

int main(int argc, char * argv[])
{
	int cmd;
	char cmdstr[1025], filename[1024] = "(NULL)", pwd[1024] = "";
	char * cmdpar;
	FCB tempFCB;
	int tempInt;
	while ( ~ (cmd = cli(filename, pwd, cmdstr, &cmdpar)) )
	{
		//printf("%d %s\n%s\n", cmd, cmdstr, cmdpar);
		if ( cmd > 2 && ! status.disk )
		{
			printf("\033[31m>>> No SFS opened, please new or open an SFS first!\033[0m\n");
			continue ;
		}
		switch ( cmd )
		{
			case  0: cmderror(); break;
			case  1: New(filename, cmdpar, pwd, &status); break;
			case  2: break;
			case  3: Mkdir(pwd, cmdpar, &status); break;
			case  4: rmdir(&status, cmdpar); break;
			case  5: ls(&status); break;
			case  6: cd(&status, cmdpar, pwd); break;
			case  7: break;
			case  8: break;
			case  9: break;
			case 10: break;
			case 11: break;
			case 12: break;
			case 13: printf("/\n"); tree(&status, 0, 0); break;
			case 14: fcbs(&status, cmdpar); break;
			case 15:
				sscanf(cmdpar, "%d", &tempInt);
				readFCB(&status, tempInt, &tempFCB);
				printFCB(tempFCB);
				break;
			case 16: readDisk(cmdpar); break;
		}
	}
	
	return 0;
}

