package brainfuck;

import java.io.FileInputStream;
import java.io.File;

public class CommandExecutionContext
{
	private char source_code[];
	private int memory[];
	private int current_memory_pointer;
	private int current_symbol;

	public CommandExecutionContext()
	{
		current_memory_pointer = 0;
		current_symbol = 0;
		source_code = new char[100];
		memory = new int[100];
	}
	public void loadSourceCode(File input_file)
	{
		int file_size = (int) input_file.length();
		//REMOVE TO MAIN
		source_code = new char[file_size];
		memory = new int[file_size];
		FileInputStream file_input_stream = null;
		try
		{
			file_input_stream = new FileInputStream(input_file);
			while (file_input_stream.available() > 0) 
      		{
        		source_code[current_symbol++] = (char) file_input_stream.read();
      		}
      		current_symbol = 0;

		}
		catch (Exception exc) 
		{
			System.out.println("Cannot open input file stream");
		}
		finally
		{
			try
			{
				file_input_stream.close();
			}
			catch (Exception exc) 
			{
				System.out.println("Cannot close input file stream");
			}
		}
	}
	public void printSourceCode()
	{
		System.out.println(source_code);
	}
	public int getCurrentSymbol()
	{
		return current_symbol;
	}
	public char getSymbol(int index)
	{
		try
		{
			return
		}
	}
}