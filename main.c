#include "main.h"

int cli(char * filename, char * pwd, char * cmdstr, char ** cmdpar)
{
	char cmd[1025];
	printf("%s:%s %s ", filename, pwd, (status.disk)?(status.opened?":\"":"]"):"X");
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
	else if ( ! strcmp(cmd, "close") || ! strcmp(cmd, "\"") )
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
	else if ( ! strcmp(cmd, "delete") || ! strcmp(cmd, "rm") )
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
	else if ( ! strcmp(cmd, "status") )
	{
		return 17;
	}
	else if ( ! strcmp(cmd, "sync") )
	{
		return 18;
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

void printStatus()
{
	printf("disk:     %s\n"
		   "free_fcb: %d\n"
		   "free_ib:  %d\n"
		   "full_fcb: %d\n"
		   "pwd:      %d\n",
		   status.disk?"memory":"(NULL)",
		   status.free_fcb, status.free_ib, status.full_fcb, status.pwd);
	return ;
}

int main(int argc, char * argv[])
{
	int cmd;
	char cmdstr[1025], filename[1024] = "(NULL)", pwd[1024] = "";
	char * cmdpar;
	FCB tempFCB;
	int tempInt;
	while ( ~ (cmd = cli(filename, pwd, cmdstr, &cmdpar)) || status.opened )
	{
		//printf("%d %s\n%s\n", cmd, cmdstr, cmdpar);
		if ( cmd > 2 && ! status.disk )
		{
			printf("\033[31m>>> No SFS opened, please new or open an SFS first!\033[0m\n");
			continue ;
		}
		if ( status.opened && (cmd < 9 || cmd == 12) )
		{
			printf("\033[31m>>> File opened, please close the file first!\033[0m\n");
			continue ;
		}
		if ( ! status.opened && ( 9 <= cmd && cmd <= 11) )
		{
			printf("\033[31m>>> No file opened, please open a file first\033[0m\n");
			continue;
		}
		switch ( cmd )
		{
			case  0: cmderror(); break;
			case  1: 
				New(filename, cmdpar, pwd, &status); 
				sync(&status, filename); 
				break;
			case  2: load(&status, cmdpar, filename, pwd); break;
			case  3: Mkdir(pwd, cmdpar, &status); break;
			case  4: rmdir(&status, cmdpar); break;
			case  5: ls(&status); break;
			case  6: cd(&status, cmdpar, pwd); break;
			case  7: create(pwd, cmdpar, &status); break;
			case  8: open(&status, cmdpar, pwd); break;
			case  9: close(&status, cmdpar, pwd); break;
			case 10: read(&status, cmdpar); break;
			case 11: write(&status, cmdpar); break;
			case 12: rm(&status, cmdpar); break;
			case 13: printf("/\n"); tree(&status, 0, 0); break;
			case 14: fcbs(&status, cmdpar); break;
			case 15:
				sscanf(cmdpar, "%d", &tempInt);
				readFCB(&status, tempInt, &tempFCB);
				printFCB(tempFCB);
				break;
			case 16: readDisk(cmdpar); break;
			case 17: printStatus(); break;
			case 18: sync(&status, filename); break;
		}
	}
	sync(&status, filename);
	return 0;
}

