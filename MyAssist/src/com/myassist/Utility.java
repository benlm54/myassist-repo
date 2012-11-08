/*
 * A general utility class with static methods for performaing simple or generic tasks.
 */

package com.myassist;

public class Utility
{

	/*
	 *	Returns the largest value in the given array. -1 if array is empty.
	 */
	public static double max(double[] d)
	{
		double res = -1.0;
		if (d.length > 0)
		{
			res = d[0];
			for (int i = 0; i < d.length; i++)
			{
				if (d[i] > res)
				{
					res = d[i];
				}
			}
		}

		return res;
	}
}
