#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>


#pragma warning (disable: 4996)
//Function Declaration
int sumUp(int a, int b);
double minus(double a, double b);
double division(double a, double  b);
double roundOff(double variable);
void design();
void day9Table(const int DAY9_NEW_CASES, const int DAY9_TOTAL_CASES, const int DAY9_TOTAL_DEATHS, const int  DAY9_TOTAL_RECOVERED, const int  DAY9_UNDER_TREATMENT, const int DAY9);
void displayDay(int day);
void remind();
int userInputLocal(int localNewCase);
int userInputImported(int importedNewCase);
int displayTotalNewCase(int localNewCase, int importedNewCase, int totalNewCase, int pretotalNewCase);
int userInputNumOfDeaths(int numOfDeaths, int totalCases);
int userInputNumRecovered(int numOfRecovered, int totalCases);
void doubleCheck(int local, int import, int totalNewCase, int deaths, int recovered);
char makeChanges();
int chooseReport();
void dailyComparativeReport(int preDay, int currentDay, int preTotalNewCase, int nowTotalNewCase, double diffOfNewCases, int preTotalCases, int nowTotalCases, double diffOfTotalCases, double prePercentTotalDeaths, double nowPercentTotalDeaths, double diffOfDeathRate, double prePercentTotalRecovered, double nowPercentTotalRecovered, double diffOfRecoveryRate);
void dailySummaryReport(int localNewCase, int importedNewCase, int  totalNewCase, int totalCases, int  totalRecovered, int totalDeaths, int numOfUnderTreatment, double  percentTotalDeaths, double percentTotalRecovered, double percentUnderTreatment);
char update();
void displayLowHighCase(int totalDayRecorded, int highestDailyCase, int highestDayNum, int lowestDayNum, int lowestDailyCase);
int checkUserInput(int covidCase, int status);
char checkErrorForChar(char yesNo);
int checkUserInputDeathsRecovered(int covidCase, int status, int totalCases);


//MAIN
void main()
{
	//intro
	design();

	//Constant
	const int DAY9_TOTAL_NEW_CASES = 9, DAY9_TOTAL_CASES = 100, DAY9_TOTAL_DEATHS = 2, DAY9_TOTAL_RECOVERED = 10, DAY9_UNDER_TREATMENT = 88;
	const double DAY9_DEATH_RATE = 2.0, DAY9_RECOVERY_RATE = 10.0;
	const int DAY9 = 9;//day 9 as first day


	//user input variables
	int localNewCase[100] = { 0 };//day 9 dont know what number
	int importedNewCase[100] = { 0 };//day 9 dont know what number
	int totalNewCase[100] = { DAY9_TOTAL_NEW_CASES };//day 9 =9
	int numOfDeaths[100] = { DAY9_TOTAL_DEATHS };    //day 9 =2
	int numOfRecovered[100] = { DAY9_TOTAL_RECOVERED };//day9 =10 

	//Total
	int totalCases[100] = { DAY9_TOTAL_CASES };
	int totalDeaths[100] = { DAY9_TOTAL_DEATHS };
	int totalRecovered[100] = { DAY9_TOTAL_RECOVERED };
	int numOfUnderTreatment[100] = { DAY9_UNDER_TREATMENT };

	//percentage variables
	double percentTotalDeaths[100] = { DAY9_DEATH_RATE };
	double percentTotalRecovered[100] = { DAY9_RECOVERY_RATE };
	double percentUnderTreatment[100] = { 0 };

	//difference variables
	double diffOfNewCases[100] = { 0 };
	double diffOfTotalCases[100] = { 0 };
	double diffOfDeathRate[100] = { 0 };
	double diffOfRecoveryRate[100] = { 0 };

	//validation variable
	char changes, yesNo;
	int  reportChoice;

	int day[100] = { DAY9 };

	//high low daily case
	int totalDayRecorded = 0, lowestDayNum = 9, highestDayNum = 9;
	int highestDailyCase, lowestDailyCase;

	lowestDailyCase = totalNewCase[0];
	highestDailyCase = totalNewCase[0];


	int i = 1;
	//DAY 9 TABLE 
	day9Table(DAY9_TOTAL_NEW_CASES, DAY9_TOTAL_CASES, DAY9_TOTAL_DEATHS, DAY9_TOTAL_RECOVERED, DAY9_UNDER_TREATMENT, DAY9);

	//REMINDER DURING INPUT
	remind();

	do {

		day[i] = day[i - 1] + 1;
		//User input
		displayDay(day[i]);


		//USER INPUT
		do {




			localNewCase[i] = userInputLocal(localNewCase[i]);

			importedNewCase[i] = userInputImported(importedNewCase[i]);

			totalNewCase[i] = displayTotalNewCase(localNewCase[i], importedNewCase[i], totalNewCase[i], totalNewCase[i - 1]);

			//calculation
			totalCases[i] = sumUp(totalNewCase[i], totalCases[i - 1]);//

			numOfDeaths[i] = userInputNumOfDeaths(numOfDeaths[i], totalCases[i]);


			numOfRecovered[i] = userInputNumOfDeaths(numOfRecovered[i], totalCases[i]);



			//Confirm your data?
			doubleCheck(localNewCase[i], importedNewCase[i], totalNewCase[i], numOfDeaths[i], numOfRecovered[i]);

			//Make change?
			changes = makeChanges();


		} while (changes == 'y' || changes == 'Y');






		//Choose report== summary / comparative
		reportChoice = chooseReport();



		//Calculation
		totalCases[i] = sumUp(totalNewCase[i], totalCases[i - 1]);
		totalDeaths[i] = sumUp(numOfDeaths[i], totalDeaths[i - 1]);
		totalRecovered[i] = sumUp(numOfRecovered[i], totalRecovered[i - 1]);
		numOfUnderTreatment[i] = totalCases[i] - totalRecovered[i] - totalDeaths[i];
		//Percentages
		percentTotalDeaths[i] = division(totalDeaths[i], totalCases[i]);
		percentTotalRecovered[i] = division(totalRecovered[i], totalCases[i]);
		percentUnderTreatment[i] = division(numOfUnderTreatment[i], totalCases[i]);


		percentTotalDeaths[i] = roundOff(percentTotalDeaths[i]);
		percentTotalRecovered[i] = roundOff(percentTotalRecovered[i]);
		percentUnderTreatment[i] = roundOff(percentUnderTreatment[i]);




		//Difference
		diffOfNewCases[i] = minus(totalNewCase[i], totalNewCase[i - 1]);
		diffOfTotalCases[i] = minus(totalCases[i], totalCases[i - 1]);
		diffOfDeathRate[i] = minus(percentTotalDeaths[i], percentTotalDeaths[i - 1]);
		diffOfRecoveryRate[i] = minus(percentTotalRecovered[i], percentTotalRecovered[i - 1]);


		//1 summary / 2 comparative
		if (reportChoice == 1)//summary report
		{
			dailySummaryReport(localNewCase[i], importedNewCase[i], totalNewCase[i], totalCases[i], totalRecovered[i], totalDeaths[i], numOfUnderTreatment[i], percentTotalDeaths[i], percentTotalRecovered[i], percentUnderTreatment[i]);
		}
		else
		{
			dailyComparativeReport(day[i - 1], day[i], totalNewCase[i - 1], totalNewCase[i], diffOfNewCases[i], totalCases[i - 1], totalCases[i], diffOfTotalCases[i], percentTotalDeaths[i - 1], percentTotalDeaths[i], diffOfDeathRate[i], percentTotalRecovered[i - 1], percentTotalRecovered[i], diffOfRecoveryRate[i]);
		}


		printf("\n\n");
		printf(".............................................................................................END OF DAY %d..............\n", day[i]);


		yesNo = update();
		//UPDATES FOR DO WHILE LOOP

		if (yesNo == 'Y' || yesNo == 'y')
		{
			i++;
		}

		totalDayRecorded += 1;

	} while (yesNo == 'Y' || yesNo == 'y');


	//LOOP 
	//FIND HIGHEST LOWEST DAILY CASE
	for (int i = 1; i <= totalDayRecorded; i++)
	{
		

		if (totalNewCase[i] >= highestDailyCase)
		{
			highestDayNum = day[i];
			highestDailyCase = totalNewCase[i];
		}

		else if (totalNewCase[i] <= lowestDailyCase)
		{

			lowestDayNum = day[i];
			lowestDailyCase = totalNewCase[i];
		}

	}

	displayLowHighCase(totalDayRecorded, highestDailyCase, highestDayNum, lowestDayNum, lowestDailyCase);

	system("pause");
}
//DESIGN
void design()
{
	printf("\033[0;31m");
	printf("\n\n\n\n\n\n");
	printf("                       VVVVV\\   VVVVVVV\\  VV\\     VV\\  VVVVVV\\  VVVVVVV\\            VV\\   VVVVVV\\    \n");	printf("\033[0m");
	printf("\033[1;31m");
	printf("                      VV  __VV\\ VV  __VV\\ VV |    VV | \\_VV  _| VV  __VV\\         VVVV | VV  __VV\\      \n"); printf("\033[0m");
	printf("\033[0;31m");
	printf("                      VV / \\__| VV /  VV |VV |    VV |   VV |   VV  | VV |        \\_VV | VV /  VV |        \n"); printf("\033[0m");
	printf("\033[1;31m");
	printf("                      VV |      VV |  VV | \\VV\\  VV  |   VV |   VV  | VV | VVVVVV\\  VV | \\VVVVVVV |      \n"); printf("\033[0m");
	printf("\033[0;31m");
	printf("                      VV |      VV |  VV |  \\VV\\VV  /    VV |   VV  | VV | \\______ |VV |  \\____vv |      \n"); printf("\033[0m");
	printf("\033[1;31m");
	printf("                      VV |  VV\\ VV |  VV |   \\VVV  /     VV |   VV  | VV |          VV | VV\\   VV |       \n"); printf("\033[0m");
	printf("\033[0;31m");
	printf("                      \\VVVVVV  | VVVVVV  |    \\V  /    VVVVVV\\  VVVVVVV  |        VVVVVV\\\\VVVVVV  |     \n"); printf("\033[0m");
	printf("\033[1;31m");
	printf("                       \\______/  \\______/      \\_/    \\______ | \\_______/        \\______| \\______/    \n"); printf("\033[0m");
	

	printf("\033[1;33m");
	printf("\n\n");
	printf("                         _                  _     _                             _                                    \n");
	printf("                        | |_ _ __ __ _  ___| |  _(_)_ __   __ _   ___ _   _ ___| |_ ___ _ __ ___                     \n");
	printf("                        | __| '__/ _` |/ __| |/ /  | '_ \\ / _` | / __| | | / __| __/ _ \\ '_ ` _ \\                 \n");
	printf("                        | |_| | | (_| | (__|   <|  | | | | (_| | \\__ \\ |_| \\__ \\ ||  __/ | | | | |               \n");
	printf("                        \\___|_|  \\__,_|\\___|_|\\_ \\_|_| |_|\\__, | |___/\\__, |___/\\__\\___|_| |_| |_|          \n");
	printf("                                                          |___/       |___/                                          \n");
	printf("\n\n\n\n\n\n");
	printf("\033[0m");
}
//DAY 9 TABLE
void day9Table(const int DAY9_NEW_CASES, const int DAY9_TOTAL_CASES, const int DAY9_TOTAL_DEATHS, const int  DAY9_TOTAL_RECOVERED, const int  DAY9_UNDER_TREATMENT, const int DAY9)
{



	printf("\n");
	printf("........................................................................................................................\n\n\n");
	printf("\033[1;34m");
	printf("  ++--Previous Day Cases--++( DAY %d )\n\n", DAY9);
	printf("\033[0m");
	printf("  +--------------+-------------+-------------+---------------+-----------------+-----------------+\n");
	printf("  |              |  New Cases  | Total Cases | Total Dealths | Total Recovered | Under Treatment |\n");
	printf("  +--------------+-------------+-------------+---------------+-----------------+-----------------+\n");
	printf("  | Previous Day |%6s%d%6s|%5s%d%5s|%7s%d%7s|%8s%d%7s|%8s%d%7s|\n", "", DAY9_NEW_CASES, "", "", DAY9_TOTAL_CASES, "", "", DAY9_TOTAL_DEATHS, "", "", DAY9_TOTAL_RECOVERED, "", "", DAY9_UNDER_TREATMENT, "");
	printf("  |%3s(DAY %d)%4s|%13s|%13s|%15s|%17s|%17s|\n", "", DAY9, "", "", "", "", "", "");
	printf("  +--------------+-------------+-------------+---------------+-----------------+-----------------+\n");
	printf("\n\n\n");
	printf("........................................................................................................................\n\n\n");

}
//REMIND
void remind()
{
	printf("\033[1;31m");
	printf("  +=========================================================+\n");
	printf("  |  REMINDER ! ! !                                         |\n");
	printf("  |  --------------                                         |\n");
	printf("  | Accidentally press enter key without inputing any data? |\n");
	printf("  | No worries ! Just continue input your number.           |\n");
	printf("  +=========================================================+\n");
	printf("\033[0m");
	/*printf("  +=========================================================+\n");
	printf("  |");
	printf("\033[0;32m");
	printf("  REMINDER !!!                                           ");
	printf("\033[0m");
	printf("|\n");
	printf("  |  --------------                                         |\n");
	printf("  | Accidentally press enter key without inputing any data? |\n");
	printf("  | No worries ! Just continue input your number.           |\n");
	printf("  +=========================================================+\n");*/
}

//DAY
void displayDay(int day)
{
	
	printf("\n\n");
	printf("   ++  DAY%3d  ++\n", day);
	printf("  =================\n\n");
}

//USER INPUT
int userInputLocal(int localNewCase)
{
	int status;

	printf("\033[1;33m");
	printf("  Number of new cases (local)      >");
	printf("\033[0m");
	rewind(stdin);//avoid string replace when looping happens//exp: 2edf
	status = scanf("%d", &localNewCase);
	localNewCase = checkUserInput(localNewCase, status);

	return localNewCase;
}
int userInputImported(int importedNewCase)
{
	int status;
	printf("\033[1;33m");
	printf("  Number of new cases (imported)   >");
	printf("\033[0m");
	rewind(stdin);
	status = scanf("%d", &importedNewCase);
	importedNewCase = checkUserInput(importedNewCase, status);
	
	return importedNewCase;
}
int displayTotalNewCase(int localNewCase, int importedNewCase, int totalNewCase,int pretotalNewCase)
{
	//total
	totalNewCase = sumUp(localNewCase, importedNewCase);
	printf("\033[1;33m");
	printf("  Total New Cases                  >");
	printf("\033[0m");
	printf("%d ", totalNewCase);

	printf("\033[1;32m");
	if (totalNewCase > pretotalNewCase)
	{
		printf(" (Increased by %d from yesterday.)\n", totalNewCase - pretotalNewCase);

	}
	else if (totalNewCase < pretotalNewCase)
	{
		printf(" (Decreased by %d from yesterday.)\n", abs(totalNewCase - pretotalNewCase));
	}
	else
	{
		printf(" (No change from yesterday.)\n");
	}
	printf("\033[0m");
	return totalNewCase;
}
int userInputNumOfDeaths(int numOfDeaths, int totalCases)
{
	int status;
	printf("\033[1;33m");
	printf("  Number of deaths                 >");
	printf("\033[0m");
	rewind(stdin);
	status = scanf("%d", &numOfDeaths);
	
	numOfDeaths = checkUserInputDeathsRecovered(numOfDeaths, status, totalCases);
	
	return numOfDeaths;
}
int userInputNumRecovered(int numOfRecovered, int totalCases)
{
	int status;
	//recovered
	printf("\033[1;33m");
	printf("  Number recovered / discharged    >");
	printf("\033[0m");
	rewind(stdin);
	status = scanf("%d", &numOfRecovered);
	
	numOfRecovered = checkUserInputDeathsRecovered(numOfRecovered, status, totalCases);
	
	return numOfRecovered;
}

//CHECK DATA
void doubleCheck(int local, int import, int totalNewCase, int deaths, int recovered)
{
	printf("\n\n");
	printf("\033[1;31m");
	printf("    DOUBLE CHECK YOUR DATA \n");
	printf("  ==========================\n");
	printf("\033[0m");
	printf("  Local New Cases                  : %d\n", local);
	printf("  Imported New Cases               : %d\n", import);
	printf("  Total New Cases                  : %d\n", totalNewCase);
	printf("  Number Of Deaths                 : %d\n", deaths);
	printf("  Number Recovered / Discharged    : %d\n", recovered);
	
}
//MAKE CHANGES ON DATA
char makeChanges()
{

	char changes, yesNo;
//do{
//	printf("\n\n");
//	printf("  Do you want to make any changes?(Y/N)");
//	rewind(stdin);
//	scanf("%c", &changes);
//	changes = checkErrorForChar(changes);
//
//
//	printf("  Your choice is %c? (Y/N)", changes);
//	rewind(stdin);
//	scanf("%c", &yesNo);
//	yesNo = checkErrorForChar(yesNo);
//
//
//} while (yesNo == 'n' || yesNo == 'N');


	do {
		printf("\n\n");
		printf("\033[1;36m");
		printf("  Do you want to make any changes?(Y/N)");
		printf("\033[0m");
		rewind(stdin);
		scanf("%c", &changes);
		changes = checkErrorForChar(changes);

		
		/*printf("  Your choice is %c? (Y/N)", changes);*/
		printf("\033[1;32m");
		printf("  Your choice is ");
		printf("\033[0m");

		printf("\033[1;33m");
		printf("%c", changes);
		printf("\033[0m");

		printf("\033[1;32m");
		printf("? (Y/N)");
		printf("\033[0m");
		rewind(stdin);
		
		scanf("%c", &yesNo);
		yesNo = checkErrorForChar(yesNo);
		printf("\n");

	} while (yesNo == 'n' || yesNo == 'N');


	return changes;
}
//REPORT
int chooseReport()
{
	char yesNo;
	int status, choice;
	do {
		printf("\n\n");
		
		printf("  1--Daily Summary Report\n");
		printf("  2--Daily Comparative Report\n\n");	
		printf("\033[1;36m");
		printf("  What type of report would you like to view ? (choose 1 or 2)");
		printf("\033[0m");

		rewind(stdin);//why i put? Cuz if you type string the next scanf will not eat the \n
		status = scanf("%d", &choice);
		while (choice != 1 && choice != 2 || status == 0) {
		
			printf("\033[0;31m");
			printf("  Error! Invalid input.\n");
			printf("\033[0m");

			printf("\033[0;36m");
			printf("  Please enter again>");
			printf("\033[0m");
			rewind(stdin);
			status = scanf("%d", &choice);
			printf("\n");

		}
		/*printf("  Your choice is %d? (Y/N)", choice);*/
		printf("\033[1;32m");
		printf("  Your choice is ");
		printf("\033[0m");
		
		printf("\033[1;33m");
		printf("%d", choice);
		printf("\033[0m");

		printf("\033[1;32m");
		printf("? (Y / N)");
		printf("\033[0m");

		rewind(stdin);
		scanf("%c", &yesNo);
		yesNo = checkErrorForChar(yesNo);




	} while (yesNo == 'n' || yesNo == 'N');
	return choice;
}
void dailySummaryReport(int localNewCase, int importedNewCase, int  totalNewCase, int totalCases, int  totalRecovered, int totalDeaths, int numOfUnderTreatment, double  percentTotalDeaths, double percentTotalRecovered, double percentUnderTreatment)
{
	printf("\n\n");
	printf("\033[1;33m");
	printf("   -- Daily Summary Report --\n");
	printf("   ==========================\n");
	printf("\033[0m");
	printf("  +-------------------+-----------------++-----------------------+-----------------------+-------------------------+\n");
	printf("  |     New Cases     |   Total Cases   ||     Total dealths     |    Total Recovered    |     Under treatment     |\n");
	printf("  +-------------------+-----------------||-----------------------+-----------------------+-------------------------+\n");
	printf("  | Local    =%4d%4s|%17s||%23s|%23s|%25s|   \n", localNewCase, "", "", "", "", "");
	printf("  | Imported =%4d%4s|%17s||%23s|%23s|%25s|   \n", importedNewCase, "", "", "", "", "");
	printf("  |                   |                 ||                       |                       |                         |\n");
	printf("  |%15s%3d%1s|%13s%4d||%19s%4d|%19s%4d|%21s%4d|\n", "", totalNewCase, "", "", totalCases, "", totalDeaths, "", totalRecovered, "", numOfUnderTreatment);
	printf("  +-------------------+-----------------++-----------------------+-----------------------+-------------------------+\n");
	printf("  |%19s|%17s||%18s%4.1f%%|%18s%4.1f%%|%20s%4.1f%%|\n", "", "", "", percentTotalDeaths, "", percentTotalRecovered, "", percentUnderTreatment);
	printf("  +-------------------+-----------------++-----------------------+-----------------------+-------------------------+\n");
}
void dailyComparativeReport(int preDay, int currentDay, int preTotalNewCase, int nowTotalNewCase, double diffOfNewCases, int preTotalCases, int nowTotalCases, double diffOfTotalCases, double prePercentTotalDeaths, double nowPercentTotalDeaths, double diffOfDeathRate, double prePercentTotalRecovered, double nowPercentTotalRecovered, double diffOfRecoveryRate)
{

	printf("\n\n");
	printf("\033[1;33m");
	printf("   -- Daily Comparative Report --\n");
	printf("   ==============================\n");
	printf("\033[0m");
	printf("  +-------------------+-------------------+-------------------------++--------------------------+\n");
	printf("  |                   |%5sYesterday%5s|%10sToday%10s||%8sDifference%8s|\n", "", "", "", "", "", "");
	printf("  |                   |%6sDay%4d%6s|%9sDay%4d%9s||%26s|\n", "", preDay, "", "", currentDay, "", "");
	printf("  +-------------------+-------------------+-------------------------++--------------------------+\n");
	printf("  | New Cases         |%16s%3d|%22s%3d||%19s+[%4.f]|\n", "", preTotalNewCase, "", nowTotalNewCase, "", diffOfNewCases);
	printf("  +-------------------+-------------------+-------------------------++--------------------------+\n");
	printf("  | Total Cases       |%16s%3d|%22s%3d||%19s+[%4.f]|\n", "", preTotalCases, "", nowTotalCases, "", diffOfTotalCases);
	printf("  +-------------------+-------------------+-------------------------++--------------------------+\n");
	printf("  | Death Rate        |%13s%5.1f%%|%19s%5.1f%%||%18s+[%4.1f%%]|\n", "", prePercentTotalDeaths, "", nowPercentTotalDeaths, "", diffOfDeathRate);
	printf("  +-------------------+-------------------+-------------------------++--------------------------+\n");
	printf("  | Recovered Rate    |%13s%5.1f%%|%19s%5.1f%%||%18s+[%4.1f%%]|\n", "", prePercentTotalRecovered, "", nowPercentTotalRecovered, "", diffOfRecoveryRate);
	printf("  +-------------------+-------------------+-------------------------++--------------------------+\n");
	printf("  Note: +[-number] means the number is decreased while +[number] means the number is increased.\n");
	printf("        if difference is +0, no change from yesterday.\n\n");
}
//USER INPUT UPDATES
char update()
{
	char yesNo, doubleConfirm;
	do {
		printf("\033[1;36m");
		printf("\n\n  Do you want want to continue update your data? (Y/N)");
		printf("\033[0m");
		rewind(stdin);
		scanf("%c", &yesNo);
		yesNo = checkErrorForChar(yesNo);

	/*	printf("  Your choice is %c? (Y/N)", yesNo);*/
		printf("\033[0;32m");
		printf("  Your choice is ");
		printf("\033[0m");

		printf("\033[1;33m");
		printf("%c", yesNo);
		printf("\033[0m");

		printf("\033[0;32m");
		printf("? (Y / N)");
		printf("\033[0m");
		rewind(stdin);
		scanf("%c", &doubleConfirm);
		doubleConfirm = checkErrorForChar(doubleConfirm);
		printf("\n");
	} while (doubleConfirm == 'N' || doubleConfirm == 'n');

	return yesNo;
}
//DISPLAY HIGH LOW CASE
void displayLowHighCase(int totalDayRecorded, int highestDailyCase, int highestDayNum, int lowestDayNum, int lowestDailyCase)
{

	printf("  Total Days Recorded : %d\n", totalDayRecorded);
	printf("  Highest Daily Cases : %d (Day %d)\n", highestDailyCase, highestDayNum);
	printf("  Lowest Daily Cases  : %d (Day %d)\n", lowestDailyCase, lowestDayNum);
	printf("  \n");
	printf("\033[1;33m");
	printf("  THANK YOU SO MUCH FOR USING THIS PROGRAM ! ! !\n\n");
	printf("\033[0m");
}

//VALIDATION 
int checkUserInput(int covidCase, int status)
{
	while (covidCase < 0 || status == getchar()) {
		
		/*printf("\033[1;31m");
		printf("  Error! Invalid input.\n");
		printf("\033[0m");*/
		printf("\033[0;31m");
		printf("  Error! Invalid input.\n");
		printf("\033[0m");

		printf("\033[0;36m");
		printf("  Please enter again               >");
		printf("\033[0m");

		rewind(stdin);	
		scanf("%d", &covidCase);
	

		//check for string 
		//scanf("%d",&input)!=1
	}
	return covidCase;
}
int checkUserInputDeathsRecovered(int covidCase, int status, int totalCases)
{
	while (covidCase < 0 || status == getchar() || (covidCase > totalCases)) {

		if (covidCase > totalCases)
		{
			printf("\033[0;36m");
			printf("  The number shouldn't more than %d!( Current Total Case )\n", totalCases);
			printf("  Please enter again               >");
			printf("\033[0m");
			rewind(stdin);
			scanf("%d", &covidCase);
		}
		else {
			printf("\033[0;31m");
			printf("  Error! Invalid input.\n");
			printf("\033[0m");

			printf("\033[0;36m");
			printf("  Please enter again               >");
			printf("\033[0m");

			rewind(stdin);
			scanf("%d", &covidCase);
		}


	}
	return covidCase;
}
char checkErrorForChar(char yesNo)//cannot check for string yet if enter yng still correct
{
	while (isalpha(yesNo) == 0 || isspace(yesNo) == 1 || (!((yesNo == 'y') || (yesNo == 'Y') || (yesNo == 'n') || (yesNo == 'N'))))
	{
		printf("\033[0;31m");
		printf("  Error!");
		printf(" Please type Y or N>"); 
		printf("\033[0m");
		rewind(stdin);
		scanf("%c", &yesNo);
	}
	return yesNo;
}

//CALCULATION
double roundOff(double variable)
{

	int makeItInt;

	makeItInt = variable * 100;

	if (((makeItInt % 10) >= 5) && (((makeItInt % 10) <= 9)))
	{
		variable = floor((((double)makeItInt) + 10) / 10) / 10;
	}
	else if ((((makeItInt * 100) % 10) >= 0) && (((makeItInt % 10) <= 4)))
	{
		variable = floor(((double)makeItInt)) / 100;
	}

	return variable;
}
double division(double a, double  b)
{
	return  (a / b) * 100;
}
int sumUp(int a, int b)
{
	return a + b;
}
double minus(double a, double b)
{
	return a - b;
}