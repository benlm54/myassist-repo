/*
 *
 */

package com.myassist;

public class Category
{
	public CategoryType type;	
	public double        qualityIndicator;

	public Category()
	{
		type = CategoryType.DEFAULT;
		qualityIndicator = 0;
	}

	public void setCategory(String catTxt, double qual)
	{
		if (catTxt == "task")
		{
			type = CategoryType.TASK;
		}
		else if (catTxt == "appointment")
		{
			type = CategoryType.APPOINTMENT;
		}
		else if (catTxt == "contact")
		{
			type = CategoryType.CONTACT;
		}
		else if (catTxt == "reminder")
		{
			type = CategoryType.REMINDER;
		}
		else
		{
			type = CategoryType.DEFAULT;
		}

		qualityIndicator = qual;
	}
}
