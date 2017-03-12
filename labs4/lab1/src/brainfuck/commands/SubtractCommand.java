package brainfuck.commands;

import brainfuck.Command;

public class SubtractCommand implements Command
{
	@Override
	public void execute(CommandExecutionContext exec_interface)
	{
		array[array[0]]--;
		//System.out.println("SubtractCommand");
	}
}