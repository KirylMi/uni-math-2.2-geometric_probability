#include <iostream>

//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////TASKS::::::::::::::::::::
//////////////////////////1)ADD INFO ABOUT CURRENT RUN + STATS
//////////////////////////2)MAKE IT INTERACTIVE
//////////////////////////3)SWAP ENDL TO \n check if it's working
#include <time.h>
#include <windows.h>
#include <math.h>
#define widthW 35
#define lengthW 10
using namespace std;


class BombSimulation {
public:
	void printline(int width = widthW, char element='-') {
		cout << ' ';
		for (int i = 0; i < width; i++) cout << element;
		cout << endl;
	}
	bool IsRunning(int currentTime) {
		if (currentTime >= runStart && currentTime <= runStart + runDuration)
			return true;
		return false;
	}
	bool IsAttacking(int currentTime) {
		if (currentTime >= attackStart && currentTime <= attackStart + attackDuration)
			return true;
		return false;
	}
	bool IsSuccess(float atStart, float rnStart, float atTime, float rnTime) {
		//SPECIALCOUNTER
		if (rnStart + rnTime == atStart || rnStart == atStart + atTime) specialcounter++;
		//
		return !(rnStart + rnTime >= atStart && rnStart <= atStart + atTime);
	}
	char	runnerMark, attackerMark;						//Marks of 'characters'
	float	runDuration, attackDuration;					//Durations of actions
	int		successes,fails,specialcounter;					//Counters for results
	float	timeAll = 60,attackStart, runStart;				//Timings
	char	simulation[lengthW][widthW];
	char*	failMsg;
	char*	succMsg;
	bool	sceneEnded;
	int		sleeptime;
	char	deadMark;

	void printInfo(int time) {
		//TIME
		cout << "Current time: \t\t\t->" << time <<"<-"<<'\n' << '\n';

		//STATUS
		cout << "STATUS: " << '\n';
		cout << "\tAttack status:\t";
		if (IsAttacking(time)) {
			//cout << "ATTACKING";
			cout << "ATTACKING\tends in " << this->attackDuration + (int)attackStart - time;
		}
		else {
			if (time > attackStart + attackDuration) {
				cout << "FINISHED";
			}
			else {
				cout << "STARTS IN: " <<((int)this->attackStart-time);
			}
		}
		cout << '\n';
		cout << "\tRun status:\t";
		if (IsRunning(time)) {
			//cout << "RUNNING";
			cout << "RUNNING  \tends in "<<this->runDuration+ (int)runStart-time;
		}
		else {
			if (time > runStart+runDuration) {
				cout << "FINISHED";
			}
			else {
				cout << "STARTS IN: " <<((int)this->runStart-time);
			}
		}
		cout << '\n';
		cout << '\n';

		//VALUES
		cout << "Current values :\n\tAttack:\n\t" << "\tstart:\t\t" << this->attackStart << '\n' << '\t' << "\tduration:\t" << this->attackDuration << "\n\tRun:\n\t\tstart:\t\t" << this->runStart << '\n' << '\t' << "\tduration:\t" << this->runDuration;
		cout<< '\n';
		cout << "Stats :\n\tSuccesses: " << successes << "\n\tFails: " << fails << '\n';
		cout << '\n';
	}

	void showSimulation(int counter) {
		for (int count = 0; count < counter; count++) {
			this->setValues();
			sceneEnded = false;
			for (int time = 0; time < timeAll; time++) {

				if (sceneEnded) break;
				
				BuildSim(time);
				

				printline();
				for (int i = 0; i < lengthW; i++) {
					cout << '|';
					for (int j = 0; j < widthW; j++) {
						cout << simulation[i][j];
					}
					cout << '|';
					cout << endl;
				}
				printline();
				printInfo(time);

				if (time == 0 && count == 0) Sleep(15000);  //if first attempt
				if (sceneEnded)		// if scene ended -> show result
					Sleep(3000);
				else				// if scene is going
					Sleep(this->sleeptime);
					

				system("cls");
			}
			if (IsSuccess(attackStart, runStart, attackDuration, runDuration)) {
				successes++;
			}
			else fails++;
		}
	}

	int getPosition(int currentTime, float runStart, float runDuration){  //position of runner

		if (runStart > currentTime || runStart + runDuration < currentTime) return 0;
		if (((currentTime - runStart) / runDuration) * lengthW < 0) throw exception ("Something is wrong in the Position section");
		return ((currentTime - runStart)/runDuration)*lengthW;
	}

	void clearSim() {
		for (int i = 0; i < lengthW; i++)
		{
			for (int j = 0; j < widthW; j++)
			{
				simulation[i][j] = ' ';
			}
		}
	}

	void BuildSim(int time) {  //Build scene  
		clearSim();
				if (IsAttacking(time)) {  //ATTACKING
						for (int i = 0; i < lengthW-1; i++) {
							for (int j = 0; j < widthW; j++) {
								//RAND
								if (float(rand() / (float)RAND_MAX > 0.9)) simulation[i][j] = attackerMark;
								//X
							/*	if ((float((float)j / (float)widthW) * 1000.0) - (float((float)i / (float)lengthW) * 1000.0) < 50 && (float((float)j / (float)widthW) * 1000.0) - (float((float)i / (float)lengthW) * 1000.0) > -50) {
									simulation[i][j] = attackerMark;
									simulation[i][widthW - j-1] = attackerMark;
								}*/
							}
						}

						if (IsRunning(time)) {  //If Attacking + IsRunning (Auto fail -> Print FAILED :(   //TOP RIGHT
							int position = getPosition(time + 1, runStart, runDuration);
							if (!(position > (lengthW / 2 - 4) && (position < (lengthW / 2 + 4)))) {  //if not in the center
								if (IsRunning(time)) {  //If Attacking + IsRunning (Auto fail -> Print FAILED :(   //CENTER
									for (int i = 0; i < strlen(failMsg) + 2; i++) {
										simulation[lengthW / 2 - 1][(widthW - strlen(failMsg) - 2) / 2 + i] = '-';
									}
									for (int i = 0; i < strlen(failMsg); i++) {
										simulation[lengthW / 2][(widthW - strlen(failMsg)) / 2 + i] = failMsg[i];
									}
									for (int i = 0; i < strlen(failMsg) + 2; i++) {
										simulation[lengthW / 2 + 1][(widthW - strlen(failMsg) - 2) / 2 + i] = '-';
									}
									simulation[lengthW / 2][(widthW - strlen(failMsg)) / 2 - 1] = '|';
									simulation[lengthW / 2][(widthW - strlen(failMsg)) / 2 + strlen(failMsg)] = '|';
									simulation[lengthW / 2 - 1][(widthW - strlen(failMsg) - 2) / 2] = simulation[lengthW / 2 - 1][(widthW - strlen(failMsg) - 2) / 2 + strlen(failMsg) + 1] = '*';
									simulation[lengthW / 2 + 1][(widthW - strlen(failMsg) - 2) / 2] = simulation[lengthW / 2 + 1][(widthW - strlen(failMsg) - 2) / 2 + strlen(failMsg) + 1] = '*';
									sceneEnded = true;

									int position = getPosition(time + 1, runStart, runDuration);      ///OPTIMIZACIA (zakinut kak v php delal kogda-to v nizhnuiy stroky)
									simulation[lengthW - position - 1][widthW / 2] = this->deadMark;
								}
							}
							else {  //IF IN THE CENTER -> TOP RIGHT 
								simulation[0][widthW - strlen(failMsg) - 1] = '|';
								for (int i = 0; i < strlen(failMsg); i++) simulation[0][widthW - strlen(failMsg) + i] = failMsg[i];
								for (int i = 0; i < strlen(failMsg) + 1; i++) simulation[1][widthW - strlen(failMsg) + i] = '-';
								sceneEnded = true;

								int position = getPosition(time + 1, runStart, runDuration);      ///OPTIMIZACIA (zakinut kak v php delal kogda-to v nizhnuiy stroky)
								simulation[lengthW - position - 1][widthW / 2] = this->deadMark;
							}	
						}
						else {
							simulation[lengthW - 1][widthW / 2] = this->runnerMark;
						}
						
						
				}
				else {	//NOT ATTACKING
					if (IsSuccess(attackStart, runStart, attackDuration, runDuration) && time>=runStart+runDuration) { ///CHECK
						for (int i = 0; i < strlen(succMsg); i++) {
							simulation[lengthW / 2][(widthW - strlen(succMsg)) / 2 + i] = succMsg[i];
						}
						sceneEnded = true;
					}
					//////clearSim();
					if (IsRunning(time)) {
						int position = getPosition(time, runStart, runDuration);      ///OPTIMIZACIA (zakinut kak v php delal kogda-to v nizhnuiy stroky)
						simulation[lengthW - position - 1][widthW / 2] = this->runnerMark;
					}
					else {
						simulation[lengthW - 1][widthW / 2] = this->runnerMark;
					}
				}
	}

	void setValues() {
		if (timeAll - runDuration <= 0 || timeAll - attackDuration <= 0) throw exception("Wrong Duration");
		attackStart = float(rand() / float(RAND_MAX / (timeAll - attackDuration)));
		runStart = float(rand() / float(RAND_MAX / (timeAll - runDuration)));
	}

	void Calculate() {
		system("cls");
		cout << "Enter the amount of calculations : ";
		int count; cin >> count;
		if (count < 0) throw exception("Wrong amount");
		for (int i = 0; i < count; i++) {
			this->setValues();
			if (IsSuccess(attackStart, runStart, attackDuration, runDuration)) {
				successes++;
			}
			else {
				fails++;
			}
		}
		cout << "Runs: " << fails + successes << endl;
		cout << "Succeeded: " << successes << endl;
		cout << "Failed: " << fails << endl;
		cout << "Chance of success with:" << endl << runDuration << " minutes for run" << endl << attackDuration << " minutes of attack" << endl << "Is -> " << successes / static_cast<float>(fails + successes) << endl;
		cout << "Special cases: " << specialcounter;
		
	}
	BombSimulation() {
		sleeptime = 350;
		deadMark = 'D';
		attackStart = 0;
		runStart = 0;
		runnerMark = 'H';
		runDuration = 5;
		attackerMark = '.';
		attackDuration = 10;
		successes = 0;
		fails = 0;
		specialcounter = 0;
		for (int i = 0; i < lengthW; i++) {
			for (int j = 0; j < widthW; j++) {
				simulation[i][j] = ' ';
			}
		}
		sceneEnded = false;
		//failMsg = (char*)"FAIL :(";
		failMsg = new char[strlen("RUN FAILED :(")+1];
		strcpy_s(this->failMsg, strlen("RUN FAILED :(")+1, "RUN FAILED :(");
		//failMsg = (char*)"RUN FAILED :(";
		succMsg = new char[strlen("SUCCESS! ^_^") + 1];
		strcpy_s(this->succMsg, strlen("SUCCESS! ^_^") + 1, "SUCCESS! ^_^");
		//succMsg = (char*)"SUCCESS! ^_^";
	}
	void settings() {
		cout << "Would you like to tune all the settings, or only the time? (1 - All, 0 - only time): ";
		char choice; cin >> choice;
		system("cls");
		cout << "Enter the duration of run (less than 60): "; cin >> this->runDuration;
		cout << "Etner the duration of attacl (less than 60): "; cin >> this->attackDuration;
		if (choice == '1') {
			cout << "Character for the runner: (H by default): "; cin >> this->runnerMark;
			cout << "Character for the attacker (. by default): "; cin >> this->attackerMark;
			cout << "Character for the failed run(D by default): "; cin >> this->deadMark;
			cout << "Sleeptime (ms) (350 by default): "; cin >> this->sleeptime;
			if (this->failMsg != nullptr) delete this->failMsg;
			cout << "Enter the fail message (without spaces): ";
			char* temp;
			temp = new char[widthW-2];
			cin >> temp;
			this->failMsg = new char[strlen(temp) + 1];
			strcpy_s(this->failMsg, strlen(temp) + 1, temp);
			delete []temp;

			temp = new char[widthW - 2];
			if (this->succMsg != nullptr) delete this->succMsg;
			cout << "Enter the success message (without spaces): ";
			cin >> temp;
			this->succMsg = new char[strlen(temp) + 1];
			strcpy_s(this->succMsg, strlen(temp) + 1, temp);
		}
		system("cls");
	}

};

int main() {
	try {
		srand((unsigned)time(NULL));
		cout << "Default settings, or custom? (0 - Defaul, 1 - Custom): "; char choice;
		cin >> choice;
		BombSimulation Simulator;
		if (choice == '1') {
			Simulator.settings();
		}
		system("cls");
		cout << "Console version (slow), how many attempts you want to see?: ";
		int amountOfAttempts;
		cin >> amountOfAttempts;
		Simulator.showSimulation(amountOfAttempts);
		system("pause");
		system("cls");
		cout << "Want to show some more? (Y/N) : ";
		char YN; cin >> YN;
		while (YN == 'Y') {
			system("cls");
			Simulator.showSimulation(2);
			cout << "Want to show some more?: Y/N";
			cin >> YN;
		}
		cout << "Non-console(no output and simulation) version (fast): ";
		Sleep(3000);
		Simulator.Calculate();
		system("pause");
	}
	catch (exception ex) {
		cout << "The programm has stopped. Error: "<<ex.what();
	}
	
}