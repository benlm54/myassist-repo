/*
 *
 */

package com.myassist;

public class Chunk
{
	public String text;
	public String sourceDescriptor;
	public String timestamp;

	public Chunk (String txt, String src, String time)
	{
		text             = txt;
		sourceDescriptor = src;
		timestamp        = time;
	}
}
