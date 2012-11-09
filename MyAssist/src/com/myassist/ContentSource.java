/*
 * 
 */

package com.myassist;

public abstract class ContentSource
{
	protected String text = "";
	protected int cursor = 0;
	protected int chunkSize = 0;

	public boolean hasText()
	{
		return (text.length() > 0) && ((cursor + chunkSize) <= text.length());
	}

	public abstract Chunk   getNextChunk(); 
}

