package brainfuck;

import java.io.*;
import java.util.HashMap;
import java.lang.reflect.*;	
import brainfuck.commands.*;

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
    	int file_size = (int)input_file.length();
    	Factory factory = new Factory();
    	HashMap<Character, Class> hashmap = new HashMap<Character, Class>();
    	hashmap.put('+', null);
    	hashmap.put('-', null);
    	hashmap.put('>', null);
    	hashmap.put('<', null);
    	hashmap.put('.', null);
    	hashmap.put(',', null);
    	//hashmap.put('[', null);
    	//hashmap.put(']', null);
    	//System.out.println(hashmap.toString());
    	try 
    	{
      		FileInputStream file_input_stream = new FileInputStream(input_file);
      		char current;
      		char text_array[] = new char[file_size];
      		int text_index = 0;
      		char exe_array[] = new char[30000]; //exe_array[0] is our index of current element
      		exe_array[0] = 1;
      		//System.out.println("Size " + file_size);
      		while (file_input_stream.available() > 0) 
      		{
        		text_array[text_index] = (char) file_input_stream.read();
        		text_index++;
      		}
      		text_index = 0;
      		//System.out.println(text_array);

      		
        	while (text_index < file_size) 
        	{
        		if ('[' == text_array[text_index])
        		{
        			if (0 == exe_array[exe_array[0]])
        			{
        				while (']' != text_array[text_index])
        				{
        					text_index++;
        				}
        				text_index++;
        			}
        			else
        			{
        				text_index++;
        				continue;
        			}
        		}
        		else if (']' == text_array[text_index])
        		{
        			//System.out.println((int)exe_array[0]);
        			if (0 != exe_array[exe_array[0]])
        			{
        				while ('[' != text_array[text_index])
        				{
        					text_index--;
        				}
        			}
        			else
        			{
        				text_index++;
        				continue;
        			}
        		}
        		else
        		{
        			if (!hashmap.containsKey(text_array[text_index]))
                 	{
                 		System.out.println("Wrong symbol in the source file.");
                 		text_index++;
                 		continue;
                 		//return;
                 	}
                 	if (null == hashmap.get(text_array[text_index]))
                 	{
                 		hashmap.put(text_array[text_index], factory.loadCommand(Character.toString(text_array[text_index])));
                    }	 
                 	//System.out.print(text_array[text_index]);
                 	try
                 	{
                 		Command command = (Command)(hashmap.get(text_array[text_index]).newInstance());
                 		command.execute(exe_array);
                 		
                 		//System.out.println("Index now " + (int)exe_array[0]);
                 	}
                 	catch (Exception exc)
                 	{
                 		System.out.println("Cannot make a new instance of " + hashmap.get(text_array[text_index]) + text_index);
        		    }
        		    text_index++;
        		}
        	} 
    	} 
    	catch (IOException e) 
    	{
      		e.printStackTrace();
    	}

	}


}