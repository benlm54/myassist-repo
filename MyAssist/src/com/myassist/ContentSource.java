/*
 * 
 */

package com.myassist;

public abstract class ContentSource
{
	public boolean hasText();

	public Chunk   getNextChunk(); 
}

