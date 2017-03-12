package brainfuck;

import java.io.*;
import java.util.HashMap;
import java.lang.reflect.*;	
import brainfuck.commands.*;
import brainfuck.CommandExecutionContext;

//build xml - почистить, скомпилировать, сделать jar, javadoc
// logs - по ключу -v (--v)
//printStackTrace

//можно ли запретить изменение полей класса/интерфейса из других частей программы?

//интерфейс -> наследуется класс контекст исполнения (конкретная реализация)

public class Main
{
    public static void main(String args[])
    {
        if (args.length == 0)
        {
            System.out.println("Put the source file name as an argument.");
            return;
        }	
        File input_file = new File(args[0]);
        if (!input_file.exists()) 
        {
            System.out.println(args[0] + " does not exist.");
            return;
        }
        if (!(input_file.isFile() && input_file.canRead())) 
        {
            System.out.println(input_file.getName() + " cannot be read from.");
            return;
        }
        long size = input_file.length();
        System.out.println(size);
        Factory factory = new Factory();
        CommandExecutionContext exec_context = new CommandExecutionContext();
        exec_context.loadSourceCode(input_file);
        int current;
        while (current = exec_context.getCurrentSymbol() < size)
        {
            Command command = factory.getCommandInstance(exec_context.getSymbol(current));
        }
         
         /*for (int i = 0; i < source.length; ++i)
        
        {
          Command command = factory.getCommandInstance(source[i]);
          //command.execute(exec_context);
        }*/
    
      		
          
         

      		
        // 	while (text_index < file_size) 
        // 	{
        // 		if ('[' == text_array[text_index])
        // 		{
        // 			if (0 == exe_array[exe_array[0]])
        // 			{
        // 				while (']' != text_array[text_index])
        // 				{
        // 					text_index++;
        // 				}
        // 				text_index++;
        // 			}
        // 			else
        // 			{
        // 				text_index++;
        // 				continue;
        // 			}
        // 		}
        // 		else if (']' == text_array[text_index])
        // 		{
        // 			//System.out.println((int)exe_array[0]);
        // 			if (0 != exe_array[exe_array[0]])
        // 			{
        // 				while ('[' != text_array[text_index])
        // 				{
        // 					text_index--;
        // 				}
        // 			}
        // 			else
        // 			{
        // 				text_index++;
        // 				continue;
        // 			}
        // 		}
        // 		else
        // 		{
        // 			if (!hashmap.containsKey(text_array[text_index]))
        //          	{
        //          		System.out.println("Wrong symbol in the source file.");
        //          		text_index++;
        //          		continue;
        //          		//return;
        //          	}
        //          	if (null == hashmap.get(text_array[text_index]))
        //          	{
        //          		hashmap.put(text_array[text_index], factory.loadCommand(Character.toString(text_array[text_index])));
        //             }	 
        //          	//System.out.print(text_array[text_index]);
        //          	try
        //          	{
        //          		Command command = (Command)(hashmap.get(text_array[text_index]).newInstance());
        //          		command.execute(exe_array);
                 		
        //          		//System.out.println("Index now " + (int)exe_array[0]);
        //          	}
        //          	catch (Exception exc)
        //          	{
        //          		System.out.println("Cannot make a new instance of " + hashmap.get(text_array[text_index]) + text_index);
        // 		    }
        // 		    text_index++;
        // 		}
        // 	} 
    

    }
}