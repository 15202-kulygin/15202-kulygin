package brainfuck.commands;

import brainfuck.Command;

public class SubtractCommand implements Command
{
	public void execute(char array[])
	{
		array[array[0]]--;
		//System.out.println("SubtractCommand");
	}
}