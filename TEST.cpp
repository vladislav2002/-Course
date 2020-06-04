#include <iostream>
#include <vector>
#include <string>
using namespace std;



class Task {
private: 
	string mTitle;  // Task contetnt 
	int mDuration;  // time of task execution (in minutes)
	int mStatus;  // status of Task(0 - open, 1 - in work, 2 - closed)
	int mPriority;  // 0 - low priority, 100 - high priority

public:
	Task(string aTitle, int aDuration, int aPriority) {
		mTitle = aTitle;
		mDuration = aDuration;
		mPriority = aPriority;
		mStatus = 0;
	}

	Task() {
		mTitle = "";
		mDuration = 0;
		mStatus = 0;  
		mPriority = 0;
	}

	void SetStatus(int aStatus) {
		mStatus = aStatus;
	}

	string getTitle() {
		return mTitle;
	}

	string getStatusStr() {
		if (mStatus==0)
		{
			return "open";
		}
		if (mStatus == 1)
		{
			return "in work";
		}
		if (mStatus == 2)
		{
			return "closed";
		}

	}

	int getStatus() {
		return mStatus;
	}

	int getPriority() {
		return mPriority;
	}

	int getDuration() {
		return mDuration;
	}
};


class Worker {
private:
	string mName;
	vector<Task> mTasks; 

public:
	Worker(string aName) {
		mName = aName;
	}

	int getTaskCount() {
		return mTasks.size();
	}

	int getActiveTaskCount() {
		int Count = 0;
		for (int i = 0; i < mTasks.size(); i++)
		{
			if (mTasks[i].getStatus() < 2) {
				Count += mTasks[i].getPriority();
			}
		}
		return Count;
	}

	bool AddTask(Task aTask) {
		bool a = false;
		for (int i = 0; i < mTasks.size(); i++)
		{
			if (mTasks[i].getPriority() < aTask.getPriority()) {
				mTasks.insert(mTasks.begin() + i, aTask);
				a = true;
				break;
			}
		}

		if (a == false) {
			mTasks.push_back(aTask);
		}
		return true;
	}

	string GetName() {
		return mName;
	}

	vector<Task> getTasks() {  
		return mTasks;
	}

	void setTaskStatus(int task_no, int status) {
		mTasks[task_no].SetStatus(status);
	}
};

class Team {
private:
	vector<Worker> mWorkers;
public:

	Team() {
	}

	bool AddWorker(string aName) {
		mWorkers.push_back(Worker(aName));
		return true;
	}

	Worker* FindFreeWorker() {
		Worker *best = NULL;
		Worker *worker = NULL;
		int minValue = 32000;
		for (int i = 0; i < mWorkers.size(); i++) {
			worker = &mWorkers[i];
			if (worker->getActiveTaskCount() < minValue) {  
				minValue = worker->getActiveTaskCount();
				best = worker;
			}
		}
		return best;
	}

	bool ScheduleTask(Task task) {
		Worker* worker = FindFreeWorker();
		if (worker == NULL) {
			return false;
		}
		worker->AddTask(task);
		return true;

	}

	bool CloseTask(int worker_no, int task_no) {
		mWorkers[worker_no].setTaskStatus(task_no, 2);
		return true;
	}

	void Print(){
		for (int i = 0; i < mWorkers.size(); i++) {
			cout << mWorkers[i].GetName() << ": have " <<mWorkers[i].getTaskCount() << " task(s)"<<endl;
			for (int j = 0; j < mWorkers[i].getTasks().size(); j++)
			{
				cout << "\tname of task: "<<mWorkers[i].getTasks()[j].getTitle() << " " << endl;
				cout << "\ttatus: " <<mWorkers[i].getTasks()[j].getStatusStr() << endl;
				cout << "\tpriority: " <<mWorkers[i].getTasks()[j].getPriority() << endl;
				cout << "\ttime for fulfillment: " <<mWorkers[i].getTasks()[j].getDuration() << endl;
				cout << endl;
			}
			cout << endl;
		}
	}

};


int main()
{
	setlocale(LC_ALL, "Russian");
	string line = "+--------------------------------------------------+";
	Team team = Team();
	int i = 0;
	string s;
	int time = 0;
	int priority = 0;
	while (true)
	{
		bool aux = true;
		cin.exceptions(istream::failbit);
		do {
			try {
				cout << line << endl;
				cout << "| action: (1 - add worker, 2 - add task, 0 - exit) |"<<endl;
				cout << line << endl;
				cin >> i;
				if (i < 0 || i > 2) {
					aux = false;
				}
				else {
					aux = true;
				}
			}
			catch (ios_base::failure & fail) {
				aux = false;
				cout << "Enter enather correct value" << endl;
				cin.clear();
				string tmp;
				getline(cin, tmp);
			}
		} while (aux == false);

		cout << endl;
		if (i == 0) {
			break;
		}
		if (i == 1) {
			cout << "worker name: ";
			cin >> s;
			team.AddWorker(s);
			team.Print();
		}

		if (i == 2) {
			cout << "task: ";
			cin >> s;
			

			do {
				try {
					cout << "time for fulfillment: ";
					cin >> time;
					if (time <= 0) {
						aux = false;
							cout <<"Enter enather correct value"<<endl;
					}
					else {
						aux = true;
					}
				}
				catch (ios_base::failure & fail) {
					aux = false;
					cout << "Enter enather correct value" << endl;
					cin.clear();
					string tmp;
					getline(cin, tmp);
				}
			} while (aux == false);


			do {
				try {
					cout << "priority: ";
					cin >> priority;
					if (priority > 100 || priority <= 0) {
						aux = false;
						cout << "Enter enather correct value" << endl;
					}
					else {
						aux = true;
					}
				}
				catch (ios_base::failure & fail) {
					aux = false;
					cout << "Enter enather correct value" << endl;
					cin.clear();
					string tmp;
					getline(cin, tmp);
				}
			} while (aux == false);
			cout <<endl;

			Task task = Task(s, time, priority);
			team.ScheduleTask(task);
			team.Print();
		}
	}
	
	return 0;
}


