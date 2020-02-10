/*Job sequencing problem with deadline*/
#include <iostream>
using namespace std;

class Job {
public:
	int profit;
	int deadline;
	void setProfitAndDeadline(int profit, int deadline) {
		this->profit = profit;
		this->deadline = deadline;
	}
};

class JobSequence {
public:
	void sortByProfitAndGetDeadline(Job job[], int totalJobs, int& highestDeadline);
	int getMaxProfit(Job job[], int totalJobs, int highestDeadline);
};

void JobSequence :: sortByProfitAndGetDeadline(Job job[], int totalJobs, int& highestDeadline) {
	for(int i = 0; i < totalJobs; i++) {
		for(int j = 0; j < totalJobs-1-i; j++) {
			if(job[j].profit < job[j+1].profit) {
				Job temp = job[j];
				job[j] = job[j+1];
				job[j+1] = temp;
			}
			if(job[i].deadline > highestDeadline) {
				highestDeadline = job[i].deadline;
			}
		}
	}
}

int JobSequence :: getMaxProfit(Job job[], int totalJobs, int highestDeadline) {
	int maxProfit = 0, jobSlots[highestDeadline] = { 0 };
	for(int i = 0; i < totalJobs; i++) {
		if(jobSlots[job[i].deadline-1] == 0) {
			maxProfit += job[i].profit;
			jobSlots[job[i].deadline-1] = 1;
		} else {
			int it = job[i].deadline - 1;
			while(--it >= 0) {
				if(jobSlots[it] == 0) {
					maxProfit += job[i].profit;
					jobSlots[it] = 1;
					break;
				}
			}
		}
	}
	return maxProfit;
}

int main() {
	int highestDeadline = 0, totalJobs = 7;
	Job job[totalJobs];
	JobSequence JobSequence;
	job[0].setProfitAndDeadline(15, 3);
	job[1].setProfitAndDeadline(5, 2);
	job[2].setProfitAndDeadline(30, 4);
	job[3].setProfitAndDeadline(25, 4);
	job[4].setProfitAndDeadline(35, 3);
	job[5].setProfitAndDeadline(12, 1);
	job[6].setProfitAndDeadline(20, 2);
	JobSequence.sortByProfitAndGetDeadline(job, totalJobs, highestDeadline);
	cout << "The maximum profit is: " << JobSequence.getMaxProfit(job, totalJobs, highestDeadline) << endl;
	return 0;
}