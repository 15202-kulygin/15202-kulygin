package reflect; 

import java.lang.reflect.Method;


//java reflect.Reflection reflect.ClassToLoad methodToCall

public class Reflection 
{
	public static void main (String args[]) throws Exception
	{
		String className = args[0];
		System.out.println("Loading class: " + className);
		Class<?> cl = Class.forName(className);
		String methodName = args[1];
		Method[] methods = cl.getMethods();
		for (Method m : methods)
		{
			System.out.println(m.getName());
			if (m.getName().equals(methodName))
			{
				Object o = cl.newInstance();
				System.out.println("Invocation!!!");
				m.invoke(o);
			}
		}
	}
}
// java -cp directory_name class_name_with_package - добавление директории в classpath
// надо всегда писать ПОЛНОЕ имя класса -  с директориями пакета

//для 1 лабы - нужен class Command
// Command command = (Command)cl.newInstance(); ...
// apache ant (нужно делать build xml) --- типа makefile
// build xml предоставляет возможности скомпилировать, запустить, сделать тесты, почистить, сделать javadoc
// 



//про reflection : bracha.org/mirrors.pdf
// reflection in dart with mirrors (gilad bracha)