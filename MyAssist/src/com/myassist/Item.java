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
		setCategory(cat);
		setOriginalText(txt);
		setSource(src);
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

	public String[] getPersonHits() {
		return personHits;
	}

	public void setPersonHits(String[] personHits) {
		this.personHits = personHits;
	}

	public String[] getPlaceHits() {
		return placeHits;
	}

	public void setPlaceHits(String[] placeHits) {
		this.placeHits = placeHits;
	}

	public String[] getTimeHits() {
		return timeHits;
	}

	public void setTimeHits(String[] timeHits) {
		this.timeHits = timeHits;
	}

	public String getSummary() {
		return "Item: Category: " + category + " Text: " + originalText;
	}

}
