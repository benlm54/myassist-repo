/*
 *
 */

package com.myassist;

public enum CategoryType
{
	DEFAULT,
	TASK,
	APPOINTMENT,
	CONTACT,
	REMINDER
}

public class Category
{
	public CategoryType type;	
	public double        qualityIndicator;

	public Category()
	{
		type = DEFAULT;
		qualityIndicator = 0;
	}

	public void setCategory(String catTxt, double qual)
	{
		if (catTxt == "task")
		{
			type = TASK;
		}
		else if (catTxt == "appointment")
		{
			type = APPOINTMENT;
		}
		else if (catTxt == "contact")
		{
			type = CONTACT;
		}
		else if (catTxt == "reminder")
		{
			type = REMINDER;
		}
		else
		{
			type = DEFAULT;
		}

		qualityIndicator = qual;
	}
}
