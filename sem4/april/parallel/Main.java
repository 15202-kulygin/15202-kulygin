package parallel;

public class Main
{
	static class HelloRunnable implements Runnable
	{
		@Override
		public void run()
		{
			System.out.println("Hello! " + Thread.currentThread().getId());
			// try
			// {
			// 	Thread.sleep(12);
			// }
			// catch (Exception exc)
			// {

			// }
		}
	}
	public static void main(String [] args) throws Exception
	{
		ThreadPool threadPool = new ThreadPool(40);
		for (int i = 0; i < 10000; ++i)
		{
			threadPool.addTask(new HelloRunnable());
		}
		Thread.sleep(5000);
		System.out.println("STOPPING THREADS");
		threadPool.stopThreads();
	}

}