/*
 * Class for the command line MyAssist test application
 */

package com.myassist;

public class MyAssistTest
{
	public static void main(String[] args)
	{
		Logger.log("Startig MyAssistTest...");
		
		TextAnalyzer analyzer = new TextAnalyzer();
		analyzer.addContentSource(new FileContentSource("test.txt"));

		Logger.log("Getting Item Summaries...");
		while (analyzer.isContentAvailable())
		{
			analyzer.scanForItems();

			while(analyzer.hasItems())
			{
				Item item = analyzer.popItem();
				Logger.log(item.getSummary());
			}
		}

		Logger.log("Exiting MyAssistTest");
	}
}

