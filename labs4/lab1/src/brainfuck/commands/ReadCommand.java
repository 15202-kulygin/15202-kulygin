package brainfuck.commands;

import brainfuck.Command;

public class ReadCommand implements Command
{
	@Override
	public void execute(char array[])
	{
		try
		{
			array[array[0]] = (char)System.in.read();
		}
		catch (Exception exc) {}
		//System.out.println("ReadCommand");
	}
}