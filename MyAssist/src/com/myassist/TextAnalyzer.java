/*
 *
 */
package com.myassist;

import java.util.ArrayList;
import java.util.List;

public class TextAnalyzer
{
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
					Category cat = nlp.GetCategory(sentences[i]);

					Item item = new Item(cat, sentences[i], chunk);
					
					//TODO if catgory is vaid, create item and get named entities
					items.add(item);
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
		return items.remove(items.size() - 1);
	}

	public boolean hasItems()
	{
		return !items.isEmpty();
	}
}
