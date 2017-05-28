package parallel;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.List;

public class ThreadPool {
	List<Thread> threads;
	Queue<Runnable> tasks = new LinkedList<Runnable>();
	public ThreadPool (int threads_num)
	{
		threads = new ArrayList<Thread>();
		for (int i = 0; i < threads_num; ++i)
		{
			Thread t = new Thread(new Worker());
			threads.add(t);
			t.start(); // стартовать thread методом start, а не run (почему?)
		}
	}
	public void addTask (Runnable task)
	{
		synchronized(tasks)
		{
			tasks.add(task);
			tasks.notify();
		}
	}


	public void stopThreads()
	{
		for (Thread t : threads)
		{
			t.interrupt();
		}
	}


	private void log(String s)
	{
		System.out.println(s);
	}

	private class Worker implements Runnable
	{
		@Override
		public void run()
		{	
				while (!Thread.interrupted())
				{
					Runnable task;
					synchronized(tasks)
					{
						if (tasks.isEmpty())
						{
							try
							{
								log("Waiting: " + Thread.currentThread().getId());
								tasks.wait();
							}
							catch (InterruptedException e)
							{
								log("Wait interrupted! " + Thread.currentThread().getId());
								return;
							}
						}
						task = tasks.poll();
					}
					task.run();
				}
			log("Interrupted! " + Thread.currentThread().getId());
		}
	}
}
