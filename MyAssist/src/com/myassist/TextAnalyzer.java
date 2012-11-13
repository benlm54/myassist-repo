/*
 *
 */
package com.myassist;

import java.util.ArrayList;
import java.util.List;

public class TextAnalyzer
{
	private final double ITEM_THRESHOLD = 0.5;
	
	private NLPInterface        nlp;
	private List<Item>          items;
	private List<ContentSource> sources;

	public TextAnalyzer()
	{
		nlp     = new NLPInterface();
		items   = new ArrayList<Item>();
		sources = new ArrayList<ContentSource>();
	}

	public void scanForItems()
	{
		for (ContentSource src: sources)
		{
			while (src.hasText())
			{
				Chunk chunk = src.getNextChunk();

				String sentences[] = nlp.GetSentences(chunk.text);

				for (int i = 0; i < sentences.length; i++)
				{
					Logger.log(sentences[i]);
					Category cat = nlp.GetCategory(sentences[i]);
					Item item;
					if (cat.qualityIndicator > ITEM_THRESHOLD)
					{
						item = new Item(cat, sentences[i], chunk);
						
						item.setPersonHits(nlp.GetNames(item.getOriginalText()));
						item.setPlaceHits(nlp.GetPlacesAndOrgs(item.getOriginalText()));
						item.setTimeHits(nlp.GetDatesAndTimes(item.getOriginalText()));
						
						items.add(item);
					}
				}
			}
		}
	}

	public void addContentSource(ContentSource source)
	{
		sources.add(source);
	}

	public boolean isContentAvailable()
	{
		for (ContentSource src: sources)
		{
			if (src.hasText())
			{
				return true;
			}
		}
		return false;
	}

	public Item popItem()
	{
		return items.remove(0);
	}

	public boolean hasItems()
	{
		return !items.isEmpty();
	}
}
