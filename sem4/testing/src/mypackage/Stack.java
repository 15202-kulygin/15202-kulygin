package mypackage;

// javac -classpath src;test;lib/junit-4.12.jar;lib/hamcrest-core-1.3.jar  ./test/mypackage/StackTest.java
// java -cp test;lib/junit-4.12.jar;src;lib/hamcrest-core-1.3 org.junit.runner.JUnitCore mypackage.StackTest
import java.lang.*;

public class Stack 
{
	public static void main (String args[]) 
	{
		Stack st = new Stack();
		int popped;
		popped = st.pop();
		for (int i = 0; i < 50; ++i)
		{
			st.push(i);
		}
		while (!st.isEmpty())
		{
			popped = st.pop();
			System.out.println(popped);
		}
	}
	public Stack()
	{
		size = 2;
		array = new int[2];
		top = -1;
	}
	public void push(int value)
	{
		if (top + 1 >= size)
		{ 
			int temp[] = new int[size];
			System.arraycopy(array, 0, temp, 0, top + 1);
			size *= 2;
			array = new int[size];
			System.arraycopy(temp, 0, array, 0, top + 1);
			System.out.println("Stack resized");
		}
		array[++top] = value;
	}
	public int pop()
	{
		if(!isEmpty())
		{	
			return array[top--];
		}
		else
		{
			System.out.println("Trying to pop, but stack is empty");
			return -1;
		}
	}
	public boolean isEmpty()
	{
		if (-1 == top)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	private int top;
	private int size;
	private int[] array;


}


// структура директорий (использовать в лабах)
// src - java исходники
// test - тесты
// classes - для компиляции классов
// build.xml - лежит в корне лабы


// junit - библиотека для тестов