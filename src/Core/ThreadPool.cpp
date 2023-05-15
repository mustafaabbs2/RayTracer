#include "ThreadPool.hpp"
#include "Utils.hpp"

ThreadPool::ThreadPool(size_t num_threads)
{
	for(size_t i = 0; i < num_threads; i++)
	{
		threads_.emplace_back(std::bind(&ThreadPool::workerThread, this));
	}
}

ThreadPool::~ThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(mutex_);
		stop_ = true;
	}

	condition_.notify_all();

	for(auto& thread : threads_)
	{
		thread.join();
	}
}

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
		//is this the best way?
		addRayColor(item.x, item.y, item.cumulativeColor, item.cam, item.world, 50);
	}
}

void ThreadPool::addWorkItem(const WorkItem& item)
{
	std::unique_lock<std::mutex> lock(mutex_);
	workQueue_.push(item);
	condition_.notify_one();
}