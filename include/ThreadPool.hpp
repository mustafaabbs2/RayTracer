// A work item represents a single task to be executed
#include "Color.hpp"
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

struct WorkItem
{
	size_t i;
	size_t j;
	size_t s;
	double x;
	double y;
	HitterList world;
	Camera cam;
};

class ThreadPool
{
public:
	ThreadPool(size_t num_threads);
	~ThreadPool();
	void addWorkItem(const WorkItem& item);

private:
	void workerThread();
	std::vector<std::thread> _threads;
	std::queue<WorkItem> workQueue_;
	std::mutex mutex_;
	std::condition_variable condition_; //how to use this?
	bool stop_ = false;
};