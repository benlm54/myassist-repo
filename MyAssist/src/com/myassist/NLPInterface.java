/*
 *
 */

package com.myassist;

public class NLPInterface
{
	private TokenNameFinderModel personModel;
	private TokenNameFinderModel timeModel;
	private TokenNameFinderModel dateModel;
	private TokenNameFinderModel placeModel; 
	private SentenceModel        sentModel;
	private TokenizerModel       tokenModel;
	private DoccatModel          catModel;

	public NLPInterface()
	{
		TrainSentencer();
		TrainTokenizer();
		TrainNameRecognizer();
		TrainCategorizer();
	}

	/*
	 * Sentence and Tokenizer Interface
	 */
	public void TrainSentencer()
	{
		InputStream is = new FileInputStream("models/en-sent.bin");
		sentModel = new SentenceModel(is);
		is.close();
	}

	public void TrainTokenizer()
	{
		InputStream is = new FileInputStream("models/en-token.bin");
		tokenModel = new TokenizerModel(is);
		is.close();
	}

	public String[] GetSentences(String text)
	{
		SentenceDetectorME sDetector = new SentenceDetectorME(sentModel);
		return sDetector.sentDetect(text);
	}

	public String[] GetTokens(String text)
	{
		TokenizerME tokenizer = new TokenizerME(tokenModel);
		return tokenizer.tokenize(text);
	}

	/*
	 *  Named Entity Interface
	 */
	public void TrainNameRecognizer()
	{
		InputStream is = new FileInputStream("models/en-ner-person.bin");
		personModel = new TokenNameFinderModel(is);
		is.close();

		is = new FileInputStream("models/en-ner-location.bin");
		placeModel = new TokenNameFinderModel(is);
		is.close();
		
		InputStream is = new FileInputStream("models/en-ner-date.bin");
		dateModel = new TokenNameFinderModel(is);
		is.close();

		is = new FileInputStream("models/en-ner-time.bin");
		timeModel = new TokenNameFinderModel(is);
		is.close();
	}

	public String[] GetNames(String text)
	{
		return getNamedEntities(text, personModel); 
	}

	public String[] GetPlaces(String text)
	{
		return getNamedEntities(text, placeModel);
	}

	public String[] GetDatesAndTimes(String text)
	{
		String[] dates = getNamedEntities(text, dateModel);
		String[] times = getNamedEntities(text, timeModel);

		String[] result = new String[dates.length + times.length];
		for (int i = 0; i < dates.length; i++)
		{
			result[i] = dates[i];
		}

		for (int i = dates.length; i < result.length; i++)
		{
			result[i] = times[i];
		}

		return result;
	}

	private String[] getNamedEntities(String text, TokenNameFinderModel model)
	{
		NameFinderME nameFinder = new NameFinderME(model);

		String[] textToks = GetTokens(text);

		Span[] names = nameFinder.find(textToks);

		String[] result = new String[names.length];
		for (Span s: names)
		{
			result.add(s.toString());
		}

		return result;
	}

	/*
	 *  Document Categorizer Interface
	 */
	public void TrainCategorizer()
	{
		InputStream dataIn = null;
		try
		{
			dataIn = new FileInputStream("training/en-doccat.train");

			ObjectStream<String> lineStream = new PlainTextByLineStream(dataIn, "UTF-8");
			ObjectStream<DocumentSample> sampleStream = new DocumentSampleStream(lineStream);

			catModel = DocumentCategorizerME.train("en", sampleStream);

			dataIn.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}

		if (catModel != null)
		{
			try
			{
				OutputStream modelOut = new BufferedOutputStream(new FileOutputStream("models/en-doccat.bin");
				model.serialize(modelOut);
				modelOut.close();
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}
		}
	}

	public Category GetCategory(String text)
	{
		DocumentCategorizerME cat = new DocumentCategorizerME(catModel);
		double[] outcomes = cat.categorize(text);
		String category   = cat.getBestOutcome();

		Category result = new Category();
		result.setCategory(category, outcomes[0]); //TODO get right outcome value
		return result;
	}
}
