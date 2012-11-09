/*
 *
 */

package com.myassist;

import java.util.ArrayList;

public class Item
{
	private Category  		  category;
	private String     		  originalText;
	private Chunk      		  source;
	private ArrayList<String> personHits;
	private ArrayList<String> placeHits;
	private ArrayList<String> timeHits;

	public Item (Category cat, String txt, Chunk src)
	{
		setCategory(cat);
		setOriginalText(txt);
		setSource(src);
		
		personHits = new ArrayList<String>();
		placeHits  = new ArrayList<String>();
		timeHits   = new ArrayList<String>();
	}

	/*
	 *  Getters and setters
	 */
	public Category getCategory() {
		return category;
	}

	public void setCategory(Category category) {
		this.category = category;
	}

	public String getOriginalText() {
		return originalText;
	}

	public void setOriginalText(String originalText) {
		this.originalText = originalText;
	}

	public Chunk getSource() {
		return source;
	}

	public void setSource(Chunk source) {
		this.source = source;
	}

	public ArrayList<String> getPersonHits() {
		return personHits;
	}

	public void setPersonHits(String[] personHits) {
		for (int i = 0; i < personHits.length; i++)
		{
			this.personHits.add(personHits[i]);
		}
	}

	public ArrayList<String> getPlaceHits() {
		return placeHits;
	}

	public void setPlaceHits(String[] placeHits) {
		for (int i = 0; i < placeHits.length; i++)
		{
			Logger.log("adding " + placeHits[i]);
			this.placeHits.add(placeHits[i]);
			Logger.log(this.placeHits.get(i) + " added");
		}
	}

	public ArrayList<String> getTimeHits() {
		return timeHits;
	}

	public void setTimeHits(String[] timeHits) {
		for (int i = 0; i < timeHits.length; i++)
		{
			Logger.log("adding " + timeHits[i]);
			this.timeHits.add(timeHits[i]);
			Logger.log(this.timeHits.get(i) + " added");
		}
	}

	public String toString() {
		String result = new String("Item:\n" +
									"   Category: " + category.type + " Quality: " + category.qualityIndicator + "\n" +
									"   Text:     " + originalText + "\n" + 
									"   Named Entities:\n");
		
		for (int i = 0; i < personHits.size(); i++)
		{
			result = result.concat("      " + personHits.get(i) + " (person)\n");
		}
		
		for (int i = 0; i < placeHits.size(); i++)
		{
			result = result.concat("      " + placeHits.get(i) + " (place)\n");
		}
		
		for (int i = 0; i < timeHits.size(); i++)
		{
			result = result.concat("      " + timeHits.get(i) + " (time)\n");
		}
		
		return result;
	}

}
