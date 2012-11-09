/*
 *
 */

package com.myassist;

public class Category
{
	public String type;	
	public double qualityIndicator;

	public Category()
	{
		type = "default";
		qualityIndicator = 0;
	}

	public void setCategory(String catTxt, double qual)
	{
		type = catTxt;
		qualityIndicator = qual;
	}
}
