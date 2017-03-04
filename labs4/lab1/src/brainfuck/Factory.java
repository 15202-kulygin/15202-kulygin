//javac src/brainfuck/factory/Factory.java
//java -cp src brainfuck.factory.Factory

package brainfuck;

//import java.lang.ClassLoader;
import java.io.*;
import java.util.Properties;

public class Factory
{
	public Factory()
	{
		config = new Properties();
		InputStream input_stream = null;
		try
		{
			input_stream = Factory.class.getResourceAsStream("config.properties");
			config.load(input_stream);
			//input_stream.close();
		}
		catch (Exception exc)
		{
			System.out.println("Cannot open config file");
		}
		finally
		{
			try
			{
				input_stream.close();
			}
			catch (Exception exc)
			{
				System.out.println("Cannot close input file");
			}
		}
	}
	public Class loadCommand(String command_name)
	{
		try
		{
			// System.out.println("Loading " + command_name);
			Class command_class = Factory.class.forName(config.getProperty(command_name));
			return command_class;
			
		}
		catch (Exception exc)
		{
			System.out.println("Cannot load command " + command_name);
		}
		return null;
	}
	/*public Command getCommandInstance(String command_name)
	{

	}*/
	


	private Properties config;
}