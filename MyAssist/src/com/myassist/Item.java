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
	
	public Item (Category cat, String txt)
	{
		setCategory(cat);
		setOriginalText(txt);
		source = null;
		
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
			this.placeHits.add(placeHits[i]);
		}
	}

	public ArrayList<String> getTimeHits() {
		return timeHits;
	}

	public void setTimeHits(String[] timeHits) {
		for (int i = 0; i < timeHits.length; i++)
		{
			this.timeHits.add(timeHits[i]);
		}
	}

	public String serialize()
	{
		StringBuffer sbuf = new StringBuffer();
		sbuf.append(Constants.ITEM_START_TAG);
		sbuf.append(category.serialize());
		sbuf.append(Constants.TXT_START_TAG);
		sbuf.append(originalText);
		sbuf.append(Constants.TXT_END_TAG);
		
		for (int i = 0; i < personHits.size(); i++)
		{
			sbuf.append(Constants.PER_START_TAG);
			sbuf.append(personHits.get(i));
			sbuf.append(Constants.PER_END_TAG);
		}
		
		for (int i = 0; i < placeHits.size(); i++)
		{
			sbuf.append(Constants.PLA_START_TAG);
			sbuf.append(placeHits.get(i));
			sbuf.append(Constants.PLA_END_TAG);
		}
		
		for (int i = 0; i < timeHits.size(); i++)
		{
			sbuf.append(Constants.TIM_START_TAG);
			sbuf.append(timeHits.get(i));
			sbuf.append(Constants.TIM_END_TAG);
		}
		
		sbuf.append(Constants.ITEM_END_TAG);
		return sbuf.toString();
	}
	
	public void deserialize(String str)
	{
		int start = str.indexOf(Constants.CAT_START_TAG);
		int end   = str.indexOf(Constants.CAT_END_TAG, start);
		
		if (start != -1 && end != -1)
		{
			start += Constants.CAT_START_TAG.length();
			category.deserialize(str.substring(start, end));
		}
		
		start = str.indexOf(Constants.TXT_START_TAG);
		end   = str.indexOf(Constants.TXT_END_TAG, start);
		if (start != -1 && end != -1)
		{
			start += Constants.TXT_START_TAG.length();
			originalText = str.substring(start, end);
		}
		
		while ((start = str.indexOf(Constants.PER_START_TAG, start)) != -1)
		{
			start += Constants.PER_START_TAG.length();
			end    = str.indexOf(Constants.PER_END_TAG, start);
			personHits.add(str.substring(start, end));
		}
		
		while ((start = str.indexOf(Constants.PLA_START_TAG, start)) != -1)
		{
			start += Constants.PLA_START_TAG.length();
			end    = str.indexOf(Constants.PLA_END_TAG, start);
			placeHits.add(str.substring(start, end));
		}
		
		while ((start = str.indexOf(Constants.TIM_START_TAG, start)) != -1)
		{
			start += Constants.TIM_START_TAG.length();
			end    = str.indexOf(Constants.TIM_END_TAG, start);
			timeHits.add(str.substring(start, end));
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
