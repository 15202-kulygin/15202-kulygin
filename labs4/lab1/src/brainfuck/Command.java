package brainfuck;

public interface Command
{
	public void execute(CommandExecutionContext exec_interface);//в параметры приезжает интерфейс с методами
}