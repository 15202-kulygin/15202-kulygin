package brainfuck.commands;

import brainfuck.Command;

public class IncrementPointerCommand implements Command
{
	public void execute(char array[])
	{
		array[0]++;
		//System.out.println("IncrementPointerCommand");
	}
}