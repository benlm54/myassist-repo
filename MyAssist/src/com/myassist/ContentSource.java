/*
 * 
 */

package com.myassist;

public abstract class ContentSource
{
	public abstract boolean hasText();

	public abstract Chunk   getNextChunk(); 
}

