/*
 * A note to whoever is seeing this: 
 * I want to indicate before you see the code that I am aware of the multitude of
 * software engineering crises that are strewn throughout this file. I appreciate 
 * that if in the real world, this code was submitted for a project, I would be
 * summarily fired, maybe executed. This program's inefficiency is a disgrace to 
 * quality programming but this project is not being graded on efficiency and I  
 * am taking 19 credits while also working so my MVP for this project is a functional 
 * program, not efficient code. So be aware that the poor code you see here is not representative of me.
 * This program allows the user to enter the number of partitions that an operating
 * system is using and their sizes. Then the process to be executed and their sizes
 * and arrival times. The output is the allocation of each process (if possible) and
 * the partition in which each process is executing. The allcation algorithms are
 * first fit, next fit, best fit, worst fit. Their descriptions are as follows:
 * 
 * first fit (non-dynamic):
 * as jobs arrive, assign them the the first partition in which they fit. This can result
 * in a job of 10k being in a partition of 4gb. Massively wasteful, this hasn't been 
 * by any OS in the last few decades.
 * 
 * next fit (non-dynamic):
 * same as first except instead of allocating the next available spot from the first 
 * partition, the allocation is the next available spot from the most recently executed 
 * process.
 * 
 * best fit (non-dynamic):
 * this algorithm compares all immediately avaiable processes to the size of all immediately
 * available partitions and assigns them according the least waste. For example if there are 
 * four partitions of sizes = {900k, 910k, 200k, 300k} and five jobs of sizes = {57k, 920k, 50k, 701k}
 * the jobs would be allocated like so: 57->200, 920k unassigned, 50->300, 701->900 wasting a total of 1502k
 * whereas first fit would be like so: 50->900, 920k unassigned, 50->910, 701k unassigned wasting a total of 2203k*
 *
 * worst fit (dynamic):
 * this does the opposite of best fit, creating the largest holes in memory and then reallocating those spots
 * as new partitions for other jobs
 * four partitions = {300, 200, 400, 100} and five jobs = {200, 300, 100, 200, 150}
 * best fit would do 300->300, 200->200, 100->100, 200->400, 150 unassigned and 200 wasted
 * worst fit would do 200->400 creating a new partition of 200, the second, third and fourth
 * don't change and the fifth fits into the extra 200 so only 50k wasted and everything assigned
 *
 * sorry for the javadoc comment format... I'm used to java but this had to be c++
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct partition{
	int size, number;
	bool inUse = 0;
};

struct job{
	int size, number, partitionProcessing = -1, bestFit = 999;
	vector<int> optionsForBestFit;
	bool processing = 0;
	bool doesntFit;
};

vector<partition> partitions;
vector<job> jobs;

bool initialAssignmentsDone(vector<partition> parts){

	for (int i = 0; i < parts.size(); i++){
		if (!parts[i].inUse)
			return false;
	}

	return true;
}

bool allPossibleJobAssignmentsDone(vector<job> these){

	for (int i = 0; i < these.size(); i++){
		if (!jobs[i].doesntFit && jobs[i].partitionProcessing == -1)
			return false;
	}

	return true;
}

int partitionWithLeastWaste(int iterator){

	for (int i = 0; i < jobs[iterator].optionsForBestFit.size(); i++){
		if (partitions[jobs[iterator].optionsForBestFit[i]].inUse){
			jobs[iterator].optionsForBestFit.erase(jobs[iterator].optionsForBestFit.begin() + i);
			i--;
		}
	}

	if (jobs[iterator].optionsForBestFit.size() == 1)
		return jobs[iterator].optionsForBestFit[0];

	int smallest = jobs[iterator].optionsForBestFit[0];

	for (int i = 0; i < jobs[iterator].optionsForBestFit.size(); i++){
		if (partitions[jobs[iterator].optionsForBestFit[i]].size < partitions[smallest].size)
			smallest = jobs[iterator].optionsForBestFit[i];
	}

	return smallest;
}

int partitionWithMostWaste(int iterator){

	for (int i = 0; i < jobs[iterator].optionsForBestFit.size(); i++){
		if (partitions[jobs[iterator].optionsForBestFit[i]].inUse){
			jobs[iterator].optionsForBestFit.erase(jobs[iterator].optionsForBestFit.begin() + i);
			i--;
		}
	}

	if (jobs[iterator].optionsForBestFit.size() == 0)
		return -1;

	if (jobs[iterator].optionsForBestFit.size() == 1)
		return jobs[iterator].optionsForBestFit[0];

	int largest = jobs[iterator].optionsForBestFit[0];

	for (int i = 0; i < jobs[iterator].optionsForBestFit.size(); i++){
		if (partitions[jobs[iterator].optionsForBestFit[i]].size > partitions[largest].size)
			largest = jobs[iterator].optionsForBestFit[i];
	}

	return largest;
}

int main(){
	int numJobs, numPartitions, fitChoice, *jobSizes, *partitionSizes, *partitionsFF, *partitionsBF, *partitionsNF, *partitionsWF;

	cout << "Enter the number of partitions: ";
	cin >> numPartitions;

	partitionSizes = new int[numPartitions];
	partitionsFF = new int[numPartitions];
	partitionsBF = new int[numPartitions];
	partitionsNF = new int[numPartitions];
	partitionsWF = new int[numPartitions];

	for (int i = 0; i < numPartitions; i++){
		partitionSizes[i] = 0;
		partitionsFF[i] = 0;
		partitionsBF[i] = 0;
		partitionsNF[i] = 0;
		partitionsWF[i] = 0;
	}

	for (int i = 0; i < numPartitions; i++){
		cout << "Enter size of partition " << i + 1 << ": ";
		cin >> partitionSizes[i];
	}

	cout << "How many jobs are there?" << endl;
	cin >> numJobs;
	jobSizes = new int[numJobs];

	for (int i = 0; i < numJobs; i++){
		cout << "Enter the size of job " << i + 1 << ": ";
		cin >> jobSizes[i];
	}

	for (int fitChoice = 1; fitChoice < 5; fitChoice++){
		partitions.clear();
		jobs.clear();

		for (int i = 0; i < numPartitions; i++){
			partition temp;
			temp.number = i + 1;
			temp.size = partitionSizes[i];
			partitions.push_back(temp);
		}

		for (int i = 0; i < numJobs; i++){
			job temp;
			temp.number = i + 1;
			temp.size = jobSizes[i];
			jobs.push_back(temp);
		}

		if (fitChoice == 1 || fitChoice == 2 || fitChoice == 4){
			for (int i = 0; i < jobs.size(); i++){
				for (int j = 0; j < partitions.size(); j++){
					if (fitChoice == 1){
						if (!jobs[i].processing && jobs[i].size <= partitions[j].size && !partitions[j].inUse){
							jobs[i].processing = 1;
							partitions[j].inUse = 1;
							jobs[i].partitionProcessing = j;
						}
					}
					else if ((fitChoice == 2 && i < 5) || (fitChoice == 4 && i < 5)){
						if (jobs[i].size <= partitions[j].size){
							jobs[i].optionsForBestFit.push_back(j);
						}
					}

				}
			}
			if (fitChoice == 2){
				for (int i = 0; i < jobs.size(); i++){

					if (jobs[i].optionsForBestFit.size() > 0){
						jobs[i].processing = 1;
						int f = partitionWithLeastWaste(i);
						partitions[f].inUse = 1;
						jobs[i].partitionProcessing = f;
					}
				}
			}
			if (fitChoice == 4){
				for (int i = 0; i < jobs.size(); i++){

					if (jobs[i].optionsForBestFit.size() > 0 && partitionWithMostWaste(i) != -1){
						int f = partitionWithMostWaste(i);
						partitions[f].inUse = 1;
						jobs[i].partitionProcessing = f;
						jobs[i].processing = 1;
					}
				}

				vector<partition> partitionsWithHoles;
				int a;
				for (int i = 0; i < jobs.size(); i++){
					if (jobs[i].processing && jobs[i].size < partitions[jobs[i].partitionProcessing].size){
						partition temp = partitions[jobs[i].partitionProcessing];
						a = temp.size -= jobs[i].size;
						partitionsWithHoles.push_back(temp);
					}
				}
				for (int i = 0; i < jobs.size(); i++){
					for (int j = 0; j < partitionsWithHoles.size(); j++){
						if (!jobs[i].processing && (jobs[i].size <= partitionsWithHoles[j].size)/* && !partitionsWithHoles[j].inUse*/){
							jobs[i].processing = 1;
							partitionsWithHoles[j].inUse = 1;
							jobs[i].partitionProcessing = partitionsWithHoles[j].number - 1;
						}
					}
				}
			}

			if (fitChoice == 1){
				for (int l = 0; l < jobs.size(); l++){
					if (jobs[l].partitionProcessing == -1)
						partitionsFF[l] = -1;
					else
						partitionsFF[l] = jobs[l].partitionProcessing + 1;
				}
			}
			else if (fitChoice == 2){
				for (int l = 0; l < jobs.size(); l++){
					if (jobs[l].partitionProcessing == -1)
						partitionsBF[l] = -1;
					else
						partitionsBF[l] = jobs[l].partitionProcessing + 1;
				}
			}
			else if (fitChoice == 4){
				for (int l = 0; l < jobs.size(); l++){
					if (jobs[l].partitionProcessing == -1)
						partitionsWF[l] = -1;
					else
						partitionsWF[l] = jobs[l].partitionProcessing + 1;
				}
			}

		}
		else if (fitChoice == 3){

			for (int i = 0; i < jobs.size(); i++){
				for (int j = 0; j < partitions.size(); j++){
					if (jobs[i].size <= partitions[j].size){
						jobs[i].doesntFit = 0;
						j = partitions.size();
					}
				}
			}
			int next = 0;
			for (int p = 0; p < jobs.size(); p++){
				if (!jobs[p].processing && !jobs[p].doesntFit){
					for (int j = 0; j < numPartitions; j++, next++){
						next %= numPartitions;
						if (jobs[p].size <= partitions[next].size && !partitions[next].inUse){
							jobs[p].processing = 1;
							partitions[next].inUse = 1;
							jobs[p].partitionProcessing = next;
							j = numPartitions;
						}
					}
				}
				if (jobs[p].partitionProcessing != -1)
					next = jobs[p].partitionProcessing + 1;

			}

			for (int l = 0; l < jobs.size(); l++){
				if (jobs[l].partitionProcessing == -1)
					partitionsNF[l] = -1;
				else
					partitionsNF[l] = jobs[l].partitionProcessing + 1;
			}
		}
		cout << endl;
	}

	cout << "Fit:\tFirst\tBest\tNext\tWorst\n";
	for (int i = 0; i < jobs.size(); i++){
		cout << "J" << i + 1 << "\t";
		if (partitionsFF[i] == -1)
			cout << "W";
		else
			cout << "P" << partitionsFF[i];
		cout << "\t";

		if (partitionsBF[i] == -1)
			cout << "W";
		else
			cout << "P" << partitionsBF[i];
		cout << "\t";

		if (partitionsNF[i] == -1)
			cout << "W";
		else
			cout << "P" << partitionsNF[i];
		cout << "\t";

		if (partitionsWF[i] == -1)
			cout << "W";
		else
			cout << "P" << partitionsWF[i];
		cout << endl;

	}

	exit(1);

	return 0;
}
