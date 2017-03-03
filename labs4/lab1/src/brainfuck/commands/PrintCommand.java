package brainfuck.commands;

import brainfuck.Command;

public class PrintCommand implements Command
{
	public void execute(char array[])
	{
		System.out.print(array[array[0]]);
		//System.out.println("PrintCommand");
	}
}