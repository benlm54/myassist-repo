/*
 * Class for the command line MyAssist test application
 */

package com.myassist;

import com.myassist.TextAnalyzer;
import com.myassist.FileContentSource;
import com.myassist.Item;

public class MyAssistTest
{
	public static void main(String[] args)
	{
		System.out.println("Startig MyAssistTest...");
		
		TextAnalyzer analyzer = new TextAnalyzer();
		analyzer.addContentSource(new FileContentSource("test.txt"));

		System.out.println("Getting Item Summaries...");
		while (analyzer.isContentAvailable())
		{
			analyzer.scanForItems();

			while(analyzer.hasItems())
			{
				Item item = analyzer.popItem();
				System.out.println(item.getSummary());
			}
		}

		System.out.println("Exiting MyAssistTest");
	}
}

