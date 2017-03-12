package reflect; //по умолчанию package private - и для наследников, и для тех, кто в пакете
// private шире protected

public class ClassToLoad
{
	public void methodToCall()
	{
		System.out.println("MethodToCall is called");
	}
}