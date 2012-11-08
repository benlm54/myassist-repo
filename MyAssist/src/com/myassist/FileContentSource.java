/*
 *
 */

package com.myassist;
 
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Date;

public class FileContentSource extends ContentSource
{
	private FileReader file;
	private String filename;

	public FileContentSource(String f)
	{
		Logger.log("FileContentSource: Reading file " + f + "...");
		filename = f;
		try
		{
			file = new FileReader(filename);
			
			while (file.ready())
			{
				int r = file.read();
				if (r != -1)
				{
					text += String.valueOf((char) r);
				}
				else
				{
					break;
				}
			}

			chunkSize = text.length();

			file.close();
		}
		catch (FileNotFoundException e)
		{
			System.out.println("File " + filename + " not found!");
		}
		catch (IOException e)
		{
			System.out.println("IOException on " + filename);
		}
	}

	public Chunk getNextChunk()
	{
		Date d = new Date();
		cursor += chunkSize;
		return new Chunk(text, "Source File: " + filename, d.toString());	
	}
}
