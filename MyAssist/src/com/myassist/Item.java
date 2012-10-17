/*
 *
 */

package com.myassist;

public class Item
{
	private Category   category;
	private String     originalText;
	private Chunk      source;
	private String[]   personHits;
	private String[]   placeHits;
	private String[]   timeHits;

	public Item (Category cat, String txt, Chunk src)
	{
		category     = cat;
		originalText = txt;
		source       = src;
	}

	/*
	 *  Getters and setters
	 */
	public void setNameHits(String[] hits)
	{
		personHits = hits;
	}

	public void setPlaceHits(String[] hits)
	{
		placeHits = hits;
	}

	public void setTimeHits(String[] hits)
	{
		timeHits = hits;
	}

}
