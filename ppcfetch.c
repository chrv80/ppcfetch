/*
  *	ppcfetch - a simple terminal tool to display information about powerpc mac computers.
  *	
  *	this software is released under MIT lisence.
  *
  *	by chrv80.	contact info: chrv80@gmail.com 
  */


#include <stdio.h>
#include <string.h>

char uptime[100], ramAmount[20], userName[50], comName[100],
	osName[10], osVersion[10], disk[100], kernel[50], 
	shell[50], cpu[60], date[60];


// Get user and host info
void getUserInfo() 
{
	FILE *uName;							//User name
	uName = popen("echo $USER", "r");
	fscanf(uName, "%s", userName);
	fclose(uName);

	FILE *cName;
	cName = popen("scutil --get ComputerName", "r");		//Computer name
	fscanf(cName, "%[^EOF]s", comName);
	fclose(cName);
}

// Get OS version
void getOSInfo() 
{
	FILE *OSName; 
	OSName = popen("/usr/libexec/PlistBuddy -c \"Print:ProductName\" /System/Library/CoreServices/SystemVersion.plist", "r");		//Mac OS X
	fscanf(OSName, "%[^\n]s", osName);
	fclose(OSName);

	FILE *OSVer;
	OSVer = popen("/usr/libexec/PlistBuddy -c \"Print:ProductVersion\" /System/Library/CoreServices/SystemVersion.plist", "r");		//version
	fscanf(OSVer, "%[^\n]s", osVersion);
	fclose(OSVer);
}


// Get kernel info
void getKernelInfo() 
{
	FILE *kernelInfo; 
	kernelInfo= popen("uname -rsm", "r");		//uname kernel info
	fscanf(kernelInfo, "%[^\n]s", kernel);
	fclose(kernelInfo);
}


// Get uptime info
void getUptime() 
{
	//local variables define and init
	char temp[20];
	int len = 0;
	int i = 8;
	
	FILE *uptimecmd; 
	uptimecmd= popen("uptime", "r");
	fscanf(uptimecmd, "%[^,]s", temp);
	fclose(uptimecmd);
	
	len = strlen(temp);			//choosing only time info about uptime
	for (i=10; i<len; i++) 
	{
		uptime[i-10] = temp[i];
	}
}


// Get CPU info
void getCPUInfo() 
{
	FILE *cpuinfo = popen("machine", "r");		//on intel mac should return intel cpu info
	fscanf(cpuinfo, "%[^\n]s", cpu);
	fclose(cpuinfo);

	//PowerPC cpu info choise by type
	//info about CPU speed not found
	
	if (strcmp(cpu,"ppc750") == 0) 
	{
		strcpy(cpu, "Power PC G3");
	}
	if (strcmp(cpu,"ppc7400") == 0) 
	{
		strcpy(cpu, "Power PC G4");
	}
	if (strcmp(cpu,"ppc7450") == 0) 
	{
		strcpy(cpu, "Power PC G4");
	}
	if (strcmp(cpu,"ppc970") == 0) 
	{
		strcpy(cpu, "Power PC G5");
	}
}


// Get RAM info
void getRAMInfo() 
{
	FILE *totalRam; 
	totalRam= popen("hwprefs memory_size", "r");	//total ram amount
	fscanf(totalRam, "%[^\n]s", ramAmount);
	fclose(totalRam);
}


// Get shell info
void getShellInfo() 
{
	FILE *shellInfo;
	shellInfo = popen("echo $SHELL", "r");		//shell info
	fscanf(shellInfo, "%s", shell);
	fclose(shellInfo);
}


// Get disk info
void getDiskInfo() 
{
	//local variables define and init
	char *percent;
	char temp[100];
	int posToCopy;
	int i = 0;
	
	FILE *diskInfo;
	diskInfo= popen("df -h | sed '2!d'", "r");	//df -h for disk info
	fscanf(diskInfo, "%[^\n]s", temp);
	fclose(diskInfo);
	
	percent = strstr(temp, "%");			//to keep usage percentage
	posToCopy = percent - temp;
	for (i=0; i<3; i++) 
	{
		disk[i] = temp[posToCopy - 2 + i];
	}
}


// Get date info
void getDate() 
{
	FILE *dateData; 
	dateData= popen("date", "r");
	fscanf(dateData, "%[^\n]s", date);
	fclose(dateData);
}

// program init
void init() 
{
	getUserInfo();
	getOSInfo();
	getDiskInfo();
	getKernelInfo();
	getShellInfo();
	getCPUInfo();
	getRAMInfo();
	getUptime();
	getDate();
}

int main() 
{
	init();			//initialize program functions
	
	system("clear");	//clear terminal contents
	
	//print system info
	//used colors from retro apple logo
	
	printf("\n ____SystemInfo____\n\n");
	printf("							\n");
	printf("\x1b[32m                 /##/                  \n");
	printf("\x1b[32m                /###/                 \n");              
	printf("\x1b[32m               /##/                   User: %s  \n", userName); 
	printf("\x1b[32m       /#######   /########\\          Hostname: %s ", comName);
	printf("\x1b[33m     /#####################\\         OS: %s %s        \n", osName, osVersion);
	printf("\x1b[33m     /#####################/          Kernel: %s     \n", kernel);
	printf("\033[1;31m     /####################/           Uptime: %s  \n", uptime);
	printf("\033[1;31m     /####################/            \n");  
	printf("\033[0;31m     /#####################/          CPU: %s      \n", cpu);
	printf("\033[0;31m      /#####################/         RAM: %s \n", ramAmount);        
	printf("\x1b[35m       /###################/          Shell: %s      \n", shell); 
	printf("\x1b[35m        /#################/           Disk: %s\n", disk);  
	printf("\x1b[36m         /###############/            Date: %s   \n", date);
	printf("\x1b[36m          /####/   \\####/                                                            \n\n");
	printf("\x1B[0m\n                                                                 \n");

	return 0;
}
