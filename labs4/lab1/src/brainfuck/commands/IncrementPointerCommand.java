package brainfuck.commands;

import brainfuck.Command;

public class IncrementPointerCommand implements Command
{
	@Override
	public void execute(char array[])
	{
		array[0]++;
		//System.out.println("IncrementPointerCommand");
	}
}