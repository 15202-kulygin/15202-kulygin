//javac src/brainfuck/factory/Factory.java
//java -cp src brainfuck.factory.Factory

package brainfuck;

//import java.lang.ClassLoader;
import java.io.*;
import java.util.Properties;
import java.util.HashMap;
import java.util.Map;

//хорошо подавать в конструктор фабрики входной и выходной поток (чтобы не скидывать все в один поток, а можно было в мейне писать в консоль, например, а все сообщения из
//фабрики выводить в отдельный файл)
// так будет удобнее для тестирования итд


public class Factory
{
	private Properties config;
	private Map<Character, Class> map;
	public Factory()
	{
		config = new Properties();
		InputStream input_stream = null;
		map = new HashMap<Character, Class>();
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
			catch (Exception exc)// exc.printStackTrace();
			{
				System.out.println("Cannot close input file");
			}
		}
	}
	private void loadCommand(char command_name)
	{
		
		// System.out.println("Loading " + command_name);
		//System.out.println(Character.toString(command_name));
		String commmand_class_name = config.getProperty(Character.toString(command_name));
		if (null == commmand_class_name)
		{
			System.out.println("Wrong command");
			return;
		}
		try
		{
			Class command_class = Factory.class.forName(commmand_class_name);
			map.put(command_name, command_class);
			//return command_class;
		}
		catch (Exception exc) //словить все exception, которые могут вылететь при загрузке класса
		{
			System.out.println("Cannot load command " + command_name);
			//throw (свой exception)
		}
	}
	public Command getCommandInstance(char command_name)
	{
		if (!map.containsKey(command_name))
		{
			this.loadCommand(command_name);
		}
		Class command_class = (Class)map.get(command_name);
		Command command_instance = null;
		try
		{
			command_instance = (Command) command_class.newInstance();
		}
		catch (Exception exc)
		{
			System.out.println("Cannot create class instance");
		}
		return command_instance;
	}

	


	
}