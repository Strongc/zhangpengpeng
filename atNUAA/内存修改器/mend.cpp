#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

#define PAGE_SIZE 4096
#define KERNEL_ADDRESS 0x80000000
#define INT_SIZE sizeof(int)


void PrintAllProcess()
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "CreateToolhelp32Snapshot failed\n");
        exit(-1);
    }

    PROCESSENTRY32 p;
    Process32First(snapshot, &p);
    do {
        printf("%08x\t%s\n", p.th32ProcessID, p.szExeFile);
    } while (Process32Next(snapshot, &p));

    CloseHandle(snapshot);
}

DWORD FindProcess(char *name)
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "CreateToolhelp32Snapshot failed\n");
        exit(-1);
    }

    DWORD pid = 0;
    
    PROCESSENTRY32 p;
    Process32First(snapshot, &p);
    do {
        if (stricmp(p.szExeFile, name) == 0) {
            pid = p.th32ProcessID;
            break;
        }
    } while (Process32Next(snapshot, &p));
    CloseHandle(snapshot);

    return pid;
}

void PrintMemory(HANDLE process)
{
    MEMORY_BASIC_INFORMATION info;
    for (unsigned long address = 0; address < KERNEL_ADDRESS; address += info.RegionSize) {
        VirtualQueryEx(process, (void *)address, &info, sizeof(info));
        if (info.State != MEM_COMMIT)
            continue;

        char * protect;
        if (info.Protect & PAGE_READONLY)
            protect = "RO";
        else if (info.Protect & PAGE_READWRITE)
            protect = "RW";
        else
            protect = "--";

        printf("%08x %s %dK\n", info.BaseAddress, protect, info.RegionSize/PAGE_SIZE);
    }
}

int candidate(HANDLE process,int value, char *cad[])
{
	MEMORY_BASIC_INFORMATION info;
	DWORD width;
	int buffer;
	int totall = 0;

	for (unsigned long address = 0; address < KERNEL_ADDRESS; address += info.RegionSize) {
		VirtualQueryEx(process, (void *)address, &info, sizeof(info));
		if (info.State != MEM_COMMIT)
			continue;

		if (info.Protect & PAGE_READWRITE){
			//printf("%08x RW %dK\n", info.BaseAddress, info.RegionSize/PAGE_SIZE);
			for(unsigned long i = 0; i < info.RegionSize; i+=INT_SIZE){
				ReadProcessMemory(process, (char *)info.BaseAddress+i, 
									&buffer,INT_SIZE,&width);
				if(buffer == value){
					cad[totall] = (char *)info.BaseAddress + i;
					totall++;
					printf("Candidate: %08x \n",(char*)info.BaseAddress + i);
				}//if
			}//for
		}//if
    }//for

	return totall;
}

int refine(HANDLE process,int value, char *cad[], int totall)
{
	DWORD width;
	int buffer;
	char *newCad[100];
	int newTotall = 0;

	int i;
	for( i = 0; i<totall; i++){
		ReadProcessMemory(process, cad[i], &buffer,INT_SIZE,&width);
		if(buffer == value){
			newCad[newTotall] = cad[i];
			newTotall++;
			printf("Candidate: %08x \n",cad[i]);
		}
	}

	for(i = 0; i<newTotall; i++)
		cad[i] = newCad[i];
	return newTotall;


}

BOOL edit(HANDLE process,int value, char *cad[])
{
	DWORD width;
	return WriteProcessMemory(process, cad[0], &value,INT_SIZE,&width);
}


int main()
{
	char input[100] = "Game.exe";
	PrintAllProcess();
	scanf("%s",input);
	DWORD pid = FindProcess(input);
	printf("\nPID of %s is %08x \n\n", input, pid);
	HANDLE hdl = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	//PrintMemory(hdl);
	char *cad[100];
	int totall;
	int value = 287453760;

	printf("Now please enter the value needed to edit :");
	scanf(" %d",&value);
	totall = candidate(hdl,value,cad);
	if(totall >=1)
		printf("Great! We get %d candidates.\n",totall);
	else
		return 1;

	while(totall>1){
		printf("Please enter the changed value :");
		scanf(" %d",&value);
		totall = refine(hdl,value,cad,totall);
		printf("Now we have %d candidates.\n",totall);
	}
	
	printf("Please input the new value : ");
	scanf(" %d",&value);
	if(TRUE == edit(hdl,value,cad))
		printf("Succeed to edit\n");

	return 0;

}