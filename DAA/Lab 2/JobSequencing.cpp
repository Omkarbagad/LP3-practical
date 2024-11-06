#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Job {
public:
    char id;
    int deadline;
    int profit;

    Job(char id, int deadline, int profit) {
        this->id = id;
        this->deadline = deadline;
        this->profit = profit;
    }
};

bool compareJobs(Job j1, Job j2) {
    return j1.profit > j2.profit;
}

void printJobSequence(vector<Job> jobs) {
    // Sort jobs by profit in descending order
    sort(jobs.begin(), jobs.end(), compareJobs);

    // Find the maximum deadline to determine the number of time slots
    int maxDeadline = 0;
    for (auto &job : jobs) {
        maxDeadline = max(maxDeadline, job.deadline);
    }

    // Arrays to store result sequence and to track filled time slots
    vector<char> result(maxDeadline, 'X');
    vector<bool> slot(maxDeadline, false);

    // Schedule the jobs
    for (int i = 0; i < jobs.size(); i++) {
        // Find a free slot for this job, starting from the last possible slot
        for (int j = min(maxDeadline - 1, jobs[i].deadline - 1); j >= 0; j--) {
            if (!slot[j]) { // If the slot is free
                result[j] = jobs[i].id; // Assign job to slot
                slot[j] = true; // Mark slot as occupied
                break;
            }
        }
    }

    // Print the job sequence
    cout << "Job Sequence: ";
    for (char jobId : result) {
        if (jobId != 'X') {
            cout << jobId << " ";
        }
    }
    cout << endl;

    // Calculate total profit
    int totalProfit = 0;
    for (int i = 0; i < maxDeadline; i++) {
        if (slot[i]) {
            for (auto &job : jobs) {
                if (job.id == result[i]) {
                    totalProfit += job.profit;
                    break;
                }
            }
        }
    }
    cout << "Total Profit: " << totalProfit << endl;
}

int main() {
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;

    vector<Job> jobs;
    cout << "Enter jobs in the format (id deadline profit):" << endl;
    for (int i = 0; i < n; i++) {
        char id;
        int deadline, profit;
        cin >> id >> deadline >> profit;
        jobs.push_back(Job(id, deadline, profit));
    }

    printJobSequence(jobs);

    return 0;
}
