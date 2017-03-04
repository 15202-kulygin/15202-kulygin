package brainfuck.commands;

import brainfuck.Command;

public class AddCommand implements Command
{
	@Override
	public void execute(char array[])
	{
		array[array[0]]++;
		//System.out.println("AddCommand");
	}
}