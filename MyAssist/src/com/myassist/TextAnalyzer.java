/*
 *
 */
package com.myassist;

public class TextAnalyzer
{
	private NLPInterface nlp;

	public TextAnalyzer()
	{
		nlp = new NLPInterface();	
	}

	public void scanForItems()
	{
		
	}

	public void addContentSource(ContentSource source)
	{

	}

	public boolean isContentAvailable()
	{
		return false;
	}

	public Item popItem()
	{
		return null;
	}

	public boolean hasItems()
	{
		return false;
	}
}
