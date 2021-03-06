/*
 *
 */

package com.myassist;

import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import opennlp.tools.doccat.DoccatModel;
import opennlp.tools.doccat.DocumentCategorizerME;
import opennlp.tools.doccat.DocumentSample;
import opennlp.tools.doccat.DocumentSampleStream;
import opennlp.tools.namefind.NameFinderME;
import opennlp.tools.namefind.TokenNameFinderModel;
import opennlp.tools.sentdetect.SentenceDetectorME;
import opennlp.tools.sentdetect.SentenceModel;
import opennlp.tools.tokenize.TokenizerME;
import opennlp.tools.tokenize.TokenizerModel;
import opennlp.tools.util.ObjectStream;
import opennlp.tools.util.PlainTextByLineStream;
import opennlp.tools.util.Span;

public class NLPInterface
{
	private TokenNameFinderModel personModel;
	private TokenNameFinderModel timeModel;
	private TokenNameFinderModel dateModel;
	private TokenNameFinderModel placeModel; 
	private TokenNameFinderModel orgModel;  
	private TokenNameFinderModel moneyModel; 
	private SentenceModel        sentModel;
	private TokenizerModel       tokenModel;
	private DoccatModel          catModel;

	public NLPInterface()
	{
		Logger.log("NLPInterface: Training sentencer...");
		TrainSentencer();

		Logger.log("NLPInterface: Training tokenizer...");
		TrainTokenizer();

		Logger.log("NLPInterface: Training name recognizer...");
		TrainNameRecognizer();

		Logger.log("NLPInterface: Training categorizer...");
		TrainCategorizer();
	}

	/*
	 * Sentence and Tokenizer Interface
	 */
	public void TrainSentencer()
	{
		InputStream is;
		try {
			is 		  = new FileInputStream("models/en-sent.bin");
			sentModel = new SentenceModel(is);
			is.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void TrainTokenizer()
	{
		InputStream is;
		try {
			is         = new FileInputStream("models/en-token.bin");
			tokenModel = new TokenizerModel(is);
			is.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
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
		InputStream is;
		try {
			is = new FileInputStream("models/en-ner-person.bin");
			personModel = new TokenNameFinderModel(is);
			is.close();

			is = new FileInputStream("models/en-ner-location.bin");
			placeModel = new TokenNameFinderModel(is);
			is.close();
			
			is = new FileInputStream("models/en-ner-organization.bin");
			orgModel = new TokenNameFinderModel(is);
			is.close();
			
			is = new FileInputStream("models/en-ner-date.bin");
			dateModel = new TokenNameFinderModel(is);
			is.close();

			is = new FileInputStream("models/en-ner-time.bin");
			timeModel = new TokenNameFinderModel(is);
			is.close();
			
			is = new FileInputStream("models/en-ner-money.bin");
			moneyModel = new TokenNameFinderModel(is);
			is.close();
			
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

	public String[] GetNames(String text)
	{
		return getNamedEntities(text, personModel); 
	}

	public String[] GetPlacesAndOrgs(String text)
	{
		String[] places = getNamedEntities(text, placeModel);
		String[] orgs   = getNamedEntities(text, orgModel);
		
		String[] result = new String[places.length + orgs.length];
		for (int i = 0; i < places.length; i++)
		{
			result[i] = places[i];
		}

		for (int i = places.length; i < result.length; i++)
		{
			result[i] = orgs[i];
		}

		return result;
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

	public String[] GetMoney(String text)
	{
		return getNamedEntities(text, moneyModel); 
	}
	
	private String[] getNamedEntities(String text, TokenNameFinderModel model)
	{
		NameFinderME nameFinder = new NameFinderME(model);

		String[] textToks = GetTokens(text);

		Span[] names = nameFinder.find(textToks);

		String[] result = new String[names.length];
		for (int i = 0; i < names.length; i++)
		{
			result[i] = textToks[names[i].getStart()] + " ";
			for (int j = names[i].getStart() + 1; j < names[i].getEnd(); j++)
			{
				result[i].concat(textToks[j] + " ");
			}
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
				OutputStream modelOut = new BufferedOutputStream(new FileOutputStream("models/en-doccat.bin"));
				catModel.serialize(modelOut);
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
		String category   = cat.getBestCategory(outcomes);

		Category result = new Category();
		result.setCategory(category, Utility.max(outcomes));
		return result;
	}
}
