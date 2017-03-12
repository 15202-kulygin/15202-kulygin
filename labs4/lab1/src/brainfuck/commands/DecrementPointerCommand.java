package brainfuck.commands;

import brainfuck.Command;

public class DecrementPointerCommand implements Command
{
	@Override
	public void execute(CommandExecutionContext exec_interface)
	{
		array[0]--;
		//System.out.println("DecrementPointerCommand");
	}
}