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
	
	public String serialize()
	{
		StringBuffer sbuf = new StringBuffer();
		sbuf.append(Constants.CAT_START_TAG);
		sbuf.append(Constants.TYPE_START_TAG);
		sbuf.append(type);
		sbuf.append(Constants.TYPE_END_TAG);
		sbuf.append(Constants.QUAL_START_TAG);
		sbuf.append(qualityIndicator);
		sbuf.append(Constants.QUAL_END_TAG);
		sbuf.append(Constants.CAT_END_TAG);
		return sbuf.toString();
	}
	
	public void deserialize(String str)
	{
		int start = str.indexOf(Constants.TYPE_START_TAG);
		int end   = str.indexOf(Constants.TYPE_END_TAG, start);
		
		if (start != -1 && end != -1)
		{
			start += Constants.TYPE_START_TAG.length();
			type = str.substring(start, end);
		}
		
		start = str.indexOf(Constants.QUAL_START_TAG);
		end   = str.indexOf(Constants.QUAL_END_TAG, start);
		
		if (start != -1 && end != -1)
		{
			start += Constants.QUAL_START_TAG.length();
			qualityIndicator = Double.parseDouble(str.substring(start, end));
		}
	}
}
