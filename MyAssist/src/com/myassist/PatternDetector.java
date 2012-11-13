/*
 * 
 */
package com.myassist;

import java.util.ArrayList;

public class PatternDetector {
	
	private final int MINCHARS = 4;
	
	private NLPInterface nlp;
	private ArrayList<Pattern> hits;
	
	public PatternDetector(NLPInterface nlp)
	{
		this.nlp = nlp;
		hits = new ArrayList<Pattern>();
	}
	
	/*
	 * Search chunk for patterns. Return true if a hit is found.
	 */
	public boolean ParseChunk(Chunk chunk)
	{
		return false;
	}
	
	private void FindListPatterns(String text)
	{
		final int INIT = 0;
		final int TOKEN = 1;
		final int LIST = 2;
		final int FOUND = 3;
		final int FINISH = 4;
		int state = 0;
		int start = 0;
		int itemLength = 0;
		int tokenType1 = 0;
		int tokenType2 = 0;
		
		for (int i = 0; i < text.length(); i++)
		{
			switch (state)
			{
				case INIT:
					if ((i+2 <= text.length()) && isListToken(text.substring(i, i+2), tokenType1))
					{
						state = TOKEN;
						start = i;
					}
					break;
				case TOKEN:
					if (itemLength > MINCHARS && text.charAt(i) == '\n')
					{
						state = LIST;
					}
					itemLength++;
					break;
					
				case LIST:
					if ((i+2 <= text.length() && isListToken(text.substring(i, i+2), tokenType2)))
					{
						if (tokenType2 == tokenType1)
						{
							state = FOUND;
							itemLength = 0;
						}
						else
						{
							state = TOKEN;
							start = i;
							itemLength = 0;
							tokenType1 = tokenType2;
						}
					}
					else if (text.charAt(i) != ' ')
					{
						state = INIT;
						start = 0;
						itemLength = 0;
					}
					break;
					
				case FOUND:
					if (itemLength > MINCHARS && text.charAt(i) == '\n')
					{
						state = FINISH;
					}
					itemLength++;
					break;
					
				case FINISH:
					if ((i+2 <= text.length() && isListToken(text.substring(i, i+2), tokenType2)))
					{
						if (tokenType2 == tokenType1)
						{
							state = FOUND;
							itemLength = 0;
						}
						else
						{
							hits.add(new Pattern(Pattern.LIST, start, i - start));
							state = TOKEN;
							start = i;
							tokenType1 = tokenType2;
							itemLength = 0;
						}
					}
					else if (text.charAt(i) != ' ')
					{
						hits.add(new Pattern(Pattern.LIST, start, (i - start) + 1));
						state = INIT;
						start = 0;
						itemLength = 0;
					}
					break;
			}
		}
		
		if (state == FOUND || state == FINISH)
		{
			hits.add(new Pattern(Pattern.LIST, start, text.length() - start));
		}
	}
	
	private void FindURLPatterns(String text)
	{
		
	}
	
	private void FindEmailPatterns(String text)
	{
		final int INIT = 0;
		final int USER = 1;
		final int AT   = 2;
		final int HOST = 3;
		final int DOMAIN = 4;
		int state = 0;
		int start = 0;
		
		for (int i = 0; i < text.length(); i++)
		{
			char c = text.charAt(i);
			
			switch (state)
			{
				case INIT:
					if (isLetter(c) || isNumber(c))
					{
						state = USER;
						start = i;
					}
					break;
					
				case USER:
					if (c == '@')
					{
						state = AT;
					}
					else if (!(isLetter(c) || isNumber(c) || isDivider(c)))
					{
						state = INIT;
						start = 0;
					}
					break;
					
				case AT:
					if (isLetter(c) || isNumber(c))
					{
						state = HOST;
					}
					else
					{
						state = INIT;
						start = 0;
					}
					break;
					
				case HOST:
					if (c == '.')
					{
						state = DOMAIN;
					}
					else if (!(isLetter(c) || isNumber(c)))
					{
						state = INIT;
						start = 0;
					}
					break;
					
				case DOMAIN:
					if (!(isLetter(c) || isNumber(c)))
					{
						hits.add(new Pattern(Pattern.EMAIL, start, (i - start) + 1));
						state = INIT;
						start = 0;
					}
					break;
			}
		}
		
		if (state == DOMAIN)
		{
			hits.add(new Pattern(Pattern.EMAIL, start, (text.length() - start)));
		}
	}

	private boolean isLetter(char c)
	{
		return Character.isLetter(c);
	}

	private boolean isNumber(char c)
	{
		return Character.isDigit(c);
	}

	private boolean isDivider(char c)
	{
		return (c == '.' || c == '-' || c == '_');
	}
	
	private boolean isListToken(String s, int type)
	{
		if (isLetter(s.charAt(0)) && isDivider(s.charAt(1)))
		{
			type = 1;
			return true;
		}
		else if (isNumber(s.charAt(0)) && isDivider(s.charAt(1)))
		{
			type = 2;
			return true;
		}
		else if (s.charAt(0) == '-' && s.charAt(1) == ' ')
		{
			type = 3;
			return true;
		}
		else if (s.charAt(0) == '-' && isLetter(s.charAt(1)))
		{
			type = 4;
			return true;
		}
		else
		{
			type = 0;
			return false;
		}
	}
}
