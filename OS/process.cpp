#include <iostream>
#include <vector>

using namespace std;

struct job{
	int arrivalTime = 0, processingTime = 0, priority = 0, startTime,
	endTime, turnaroundTime, number, preMessProcessingTime = processingTime;
	bool started = 0, completed = 0;
};

//boolean function that returns true if all jobs are complete
bool allJobsComplete(vector<job> jobs){
	for (int i = 0; i < jobs.size(); i++){
		if (!jobs[i].completed)
			return false;
	}

	return true;
}

/*function that outputs the data of the jobs
it's quite long because I wanted to ensure
that the jobs are output sequentially*/
void outputJobData(vector<job> jobsToOutput){
	double totalTurnaround = 0;
	cout << "Job \t Start Time \t Time of termination \t Turnaround time \t Execution time " << endl;

	for (int i = 0; i < jobsToOutput.size(); i++){
		for (int j = 0; j < jobsToOutput.size(); j++){
			if (jobsToOutput[j].number == i + 1){
				cout << " " << jobsToOutput[j].number << "\t\t" << jobsToOutput[j].startTime << "\t\t"
					<< jobsToOutput[j].endTime << "\t\t\t" << jobsToOutput[j].turnaroundTime << "\t\t\t" << jobsToOutput[i].preMessProcessingTime << endl;

				totalTurnaround += jobsToOutput[j].turnaroundTime;
			}
		}
	}

	double tAV = totalTurnaround / jobsToOutput.size();

	cout << "Average turnaround time = ";
	
	if (tAV - (int (tAV)) == 0)
		cout << totalTurnaround / jobsToOutput.size() << endl;
	else
		cout << totalTurnaround << "/" << jobsToOutput.size() << endl;

}

//multiple vectors to allow different algorithms 
//to run despite modifying the original vector
vector<job> jobs, jobs2, fcfsJobs, sjnJobs, sjnJobs2;

void firstComeFirstServe(vector<job> fcfsJobs){
	int time = 0;
	for (int i = 0; i < fcfsJobs.size() && !allJobsComplete(fcfsJobs); i++){
		if (fcfsJobs[i].arrivalTime <= time){
			fcfsJobs[i].startTime = time;
			fcfsJobs[i].endTime = time + fcfsJobs[i].processingTime;
			time += fcfsJobs[i].processingTime;
			fcfsJobs[i].completed = 1;
			fcfsJobs[i].turnaroundTime = fcfsJobs[i].endTime - fcfsJobs[i].arrivalTime;
		}
		else{
			time++;
			i--;
		}
	}

	cout << "First come first serve: " << endl;
	outputJobData(fcfsJobs);
}

int main(){
	int numJobs;

	cout << "How many jobs are there?" << endl;
	cin >> numJobs;

	//get the data about the jobs
	for (int i = 1; i < numJobs + 1; i++){
		job temp;
		temp.number = i;
		cout << "Enter the size of job " << i << endl;
		cin >> temp.processingTime;
		temp.preMessProcessingTime = temp.processingTime;
		cout << "Enter the arrival time of job " << i << endl;
		cin >> temp.arrivalTime;
		cout << "Enter priority of job " << i << endl;
		cin >> temp.priority;

		jobs.push_back(temp);
	}

	sjnJobs = fcfsJobs = jobs;
	firstComeFirstServe(fcfsJobs);

	//priority happens here

	for (int time = 0; !allJobsComplete(jobs); time++){
		int indexOfJobWithHighestPriority = -1;
		/*
		as we go around and around, once per unit of time, if any
		job is completed then it is removed from the current vector
		and placed into "jobs2" to be dealt with later for output
		*/
		for (int i = 0; i < jobs.size(); i++){
			if (jobs[i].completed){
				jobs[i].turnaroundTime = jobs[i].endTime - jobs[i].arrivalTime;
				jobs2.push_back(jobs[i]);
				jobs.erase(jobs.begin() + i);
			}
		}

		/*here we get the index of the lowest job in the vector
		that has already arrived, this is so that the index
		has some value in case no other job has a higher priority
		we can start from the earliest that is ready. If not job
		is ready then the loop will continue, I used a goto statement
		for this even though goto is usually frowned upon*/
		for (int i = jobs.size(); i > 0; i--){
			if (jobs[i - 1].arrivalTime <= time)
				indexOfJobWithHighestPriority = i - 1;
		}

		//here we get the index of of the job with the highest priority
		for (int i = 0; i < jobs.size(); i++){
			if (jobs[i].priority < jobs[indexOfJobWithHighestPriority].priority && jobs[i].arrivalTime <= time)
				indexOfJobWithHighestPriority = i;
		}

		if (indexOfJobWithHighestPriority != -1){

			//set the start time of a job if it hasn't already been set
			if (!jobs[indexOfJobWithHighestPriority].started){
				jobs[indexOfJobWithHighestPriority].started = 1;
				jobs[indexOfJobWithHighestPriority].startTime = time;
			}

			//process the job for one unit of time
			jobs[indexOfJobWithHighestPriority].processingTime--;

			//if a job is done then set it to completed and set its end time
			for (int i = 0; i < jobs.size(); i++){
				if (jobs[i].processingTime == 0){
					jobs[i].completed = 1;
					jobs[i].endTime = time + 1;
				}
			}
		}

	}

	//the last job doesn't get sent to the output vector
	//to avoid overhauling the code, I do it here
	jobs[0].turnaroundTime = jobs[0].endTime - jobs[0].arrivalTime;
	jobs2.push_back(jobs[0]);

	cout << endl << "Priority: " << endl;
	outputJobData(jobs2);

	for (int i = 0; i < jobs2.size(); i++)
		jobs2.erase(jobs2.begin() + i);

	//end of priority
	
	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////

	//shortest job next starts here

	for (int time = 0; !allJobsComplete(sjnJobs); time++){
		int indexOfJobWithShortestNext = -1;
		/*
		as we go around and around, once per unit of time, if any
		job is completed then it is removed from the current vector
		and placed into "sjnJobs2" to be dealt with later for output
		*/
		for (int i = 0; i < sjnJobs.size(); i++){
			if (sjnJobs[i].completed){
				sjnJobs[i].turnaroundTime = sjnJobs[i].endTime - sjnJobs[i].arrivalTime;
				sjnJobs2.push_back(sjnJobs[i]);
				sjnJobs.erase(sjnJobs.begin() + i);
			}
		}

		for (int i = sjnJobs.size(); i > 0; i--){
			if (sjnJobs[i - 1].arrivalTime <= time)
				indexOfJobWithShortestNext = i - 1;
		}

		for (int i = 0; i < sjnJobs.size(); i++){
			if (sjnJobs[i].processingTime < sjnJobs[indexOfJobWithShortestNext].processingTime && sjnJobs[i].arrivalTime <= time)
				indexOfJobWithShortestNext = i;
		}

		//set the start time of a job if it hasn't already been set
		if (!sjnJobs[indexOfJobWithShortestNext].started){
			sjnJobs[indexOfJobWithShortestNext].started = 1;
			sjnJobs[indexOfJobWithShortestNext].startTime = time;
		}

		//process the job for one unit of time
		if (sjnJobs[indexOfJobWithShortestNext].processingTime > 0){
			sjnJobs[indexOfJobWithShortestNext].processingTime--;
			time++;
		}

		//if a job is done then set it to completed and set its end time
		for (int i = 0; i < sjnJobs.size(); i++){
			if (sjnJobs[i].processingTime == 0){
				sjnJobs[i].completed = 1;
				sjnJobs[i].endTime = time;
			}
		}
		time--;

	}

	sjnJobs[0].turnaroundTime = sjnJobs[0].endTime - sjnJobs[0].arrivalTime;
	sjnJobs2.push_back(sjnJobs[0]);

	cout << endl << "Shortest Job Next: " << endl;
	outputJobData(sjnJobs2);

	return 0;
}
