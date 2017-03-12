package brainfuck.commands;

import brainfuck.Command;

public class PrintCommand implements Command
{
	@Override
	public void execute(CommandExecutionContext exec_interface)
	{
		System.out.print(array[array[0]]);
		//System.out.println("PrintCommand");
	}
}