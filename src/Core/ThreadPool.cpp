#include "ThreadPool.hpp"
#include "Utils.hpp"

ThreadPool::ThreadPool(size_t num_threads) {}

ThreadPool::~ThreadPool() {}

void ThreadPool::workerThread()
{
	while(true)
	{
		WorkItem item;
		{
			std::unique_lock<std::mutex> lock(mutex_);
			while(!stop_ && workQueue_.empty())
				condition_.wait(lock);

			if(stop_ && workQueue_.empty())
				return;

			item = workQueue_.front();
			workQueue_.pop();
		}

		rayColor(item.x, item.y, item.cumulativeColor);
	}
}

void ThreadPool::addWorkItem(const WorkItem& item) {}