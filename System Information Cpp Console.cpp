// System Information Cpp Console.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <intrin.h>
#include <iomanip>
#include <string.h>
using namespace std;

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
	
	cout << setw(1) << " " << setw(36) << system("Color 3a") << "CPU Information" << system("Color 3b");
	cout << "\n---------------------------------------------------------------\n";
	printf("CPU: ");
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
	printf("Architecture:");
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
	printf("Clock Speed: ");
	printf("%0.1f GHz", CPUInfo[1] * .01);
	printf("\n");
	//Load Percent
	printf("Load Percent");
	printf("\n");
	
	//Clock Frequency
	printf("Clock Frequency: ");
	unsigned __int64 nStartTime, nEndTime, nTimeDifference, nFrequency, nStart, nEnd, nDiff;
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&nFrequency)) {
		QueryPerformanceCounter((LARGE_INTEGER*)&nStartTime);
		nStart = __rdtsc();
		Sleep(100);
		QueryPerformanceCounter((LARGE_INTEGER*)&nEndTime);
		nEnd = __rdtsc();
		nDiff = nEnd - nStart;
		nTimeDifference = nEndTime - nStartTime;

		__int64 n_Frequency = (unsigned __int64)(((double)nDiff) / (((double)nTimeDifference) / nFrequency));
		(double)n_Frequency;
		printf("%0.1f GHz", n_Frequency * .000000001);
	}
	
	printf("\n\n");
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
			
			
	
	("system,.pause");
	


	/// <summary>
	/// Similar to the C# console app, recreating it in C++
	/// </summary>

}


