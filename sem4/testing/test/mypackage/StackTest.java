package mypackage;

public class StackTest
{
	@org.junit.Test
	public void popTest()
	{
		Stack s = new Stack();
		org.junit.Assert.assertEquals(s.pop(), -1); // assertEquals - public static метод класса Assert -> бросает исключение
	}
}

//