// System Information Cpp Console.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <intrin.h>
#include <iomanip>
#include <string.h>
#include <Windows.h>
using namespace std;


static float CalculateLoadPercent();
static unsigned long long FileLoadTickCheck();
float GetCPULoad();

void DisplayCpuInformation()
{
	string cpuType = "";
	SYSTEM_INFO sysInfo;
	int CPUInfo[4] = { -1 };
	unsigned nExIds, i = 0;
	char CpuBrandString[0x400];
	__cpuid(CPUInfo, 0x80000000);
	nExIds = CPUInfo[0];
	 bool run = true;
	 HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);


	GetSystemInfo(&sysInfo);

	//Cpu
	//TODO Print more specific but keep it less detailed-
	//Stylize and color => Total output

	/*Console.WriteLine("\n---------------------------------------------------------------");
	be.SetTextColor(ConsoleColor.Green);
	Console.WriteLine(string.Format("{0}", be.StringFormatLeft("CPU Information", 36)));
	be.DefaultTextColor();
	Console.WriteLine("---------------------------------------------------------------\n\n");*/
	cout << "\n\n---------------------------------------------------------------\n";	
	cout << setw(1) << " " << setw(36)  << "CPU Information";
	cout << "\n---------------------------------------------------------------\n";
	printf("	CPU: ");
	for (i = 0x80000000; i <= nExIds; ++i) {
		__cpuid(CPUInfo, i);
		if (i == 0x80000002) {
			memcpy(CpuBrandString, CPUInfo, sizeof(CPUInfo));
		}
		else if (i == 0x80000003) {
			memcpy(CpuBrandString + 16, CPUInfo, sizeof(CPUInfo));
		}
		else if (i == 0x80000004) {
			memcpy(CpuBrandString + 32, CPUInfo, sizeof(CPUInfo));
		}
	}

	printf("%s", CpuBrandString);
	printf("\n");
	//Architecture
	printf("	Architecture: ");
	if (sysInfo.wProcessorArchitecture == 0) {
		printf("x86");
	}
	else if (sysInfo.wProcessorArchitecture == 5) {
		printf("ARM");
	}
	else if (sysInfo.wProcessorArchitecture == 6) {
		printf("Intel Itanium Based");
	}
	else if (sysInfo.wProcessorArchitecture == 12) {
		printf("ARM64");
	}
	else{
		printf("x64");
	}
	printf("\n");
	//CPU Status
	//Not needed
	//printf("CPU Status:");
	//printf("\n\n");
	//Clock Speed
	printf("	Clock Speed: ");
	printf("%0.1f GHz", CPUInfo[1] * .01);
	printf("\n");
	//Load Percent
	printf("	Load Percent");
	printf("\n");
	
	//Clock Frequency
	printf("	Clock Frequency: ");
	unsigned __int64 FreCheckStartTime, FreCheckEndTime, FreCheckTimeDifference, frequency, FreCheckStart, FreCheckEnd, FreCheckDiff;
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&frequency)) {
		QueryPerformanceCounter((LARGE_INTEGER*)&FreCheckStartTime);
		FreCheckStart = __rdtsc();
		Sleep(100);
		QueryPerformanceCounter((LARGE_INTEGER*)&FreCheckEndTime);
		FreCheckEnd = __rdtsc();
		FreCheckDiff = FreCheckEnd - FreCheckStart;
		FreCheckTimeDifference = FreCheckEndTime - FreCheckStartTime;

		__int64 n_Frequency = (unsigned __int64)(((double)FreCheckDiff) / (((double)FreCheckTimeDifference) / frequency));
		(double)n_Frequency;
		//Get freq in x.x% format
		printf("%0.1f GHz", n_Frequency * .000000001);
		cout << PrintCPULoad();
		
	}
	
	printf("\n\n");
}
int PrintCPULoad() {
	int cpuLoad = 0;
	while (cpuLoad == 0) {
		std::cout << GetCPULoad() * 100;
		Sleep(1000);
	}
	return 0;
}
static float CalculateLoadPercent(unsigned long long idle, unsigned long long ticks) {
	static unsigned long long previousTicks = 0;
	static unsigned long long previousIdleTicks = 0;

	unsigned long long totalTicks = ticks - previousTicks;
	unsigned long long idleTicks = idle - previousIdleTicks;

	float loadPercent = 1.0f - ((totalTicks > 0) ? ((float)previousIdleTicks) / totalTicks : 0);
	previousTicks = ticks;
	previousIdleTicks = idle;

	return loadPercent;
}

static unsigned long long FileLoadTickCheck(const FILETIME& filetime) {
	return (((unsigned long long)(filetime.dwHighDateTime)) << 32) | ((unsigned long long)filetime.dwLowDateTime);
}
float GetCPULoad() {
	FILETIME idleT, kernelT, userT;
	return GetSystemTimes(&idleT, &kernelT, &userT) ? CalculateLoadPercent(FileLoadTickCheck(idleT), FileLoadTickCheck(kernelT) + FileLoadTickCheck(userT)) : -1.0f;
}

void GetGpuInformation() {
	cout << "\n\n---------------------------------------------------------------\n";
	
	cout << setw(0) << " " << setw(36) << "GPU Information";
	cout << "\n---------------------------------------------------------------\n";
}
int main()
{
	//TODO
	//Make refreshable
	DisplayCpuInformation();
	GetGpuInformation();
			
			
	

	


	/// <summary>
	/// Similar to the C# console app, recreating it in C++
	/// </summary>

}


