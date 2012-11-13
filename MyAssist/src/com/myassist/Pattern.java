/*
 * 
 */
package com.myassist;

public class Pattern {
	public static final int DEFAULT = 0;
	public static final int LIST = 1;
	public static final int EMAIL = 2;
	public static final int URL = 3;
	public static final int KEYWORD = 4;
	
	public int position;
	public int length;
	public int type;
	
	public Pattern(int type, int position, int length)
	{
		this.position = position;
		this.length = length;
		this.type = type;
	}
}
