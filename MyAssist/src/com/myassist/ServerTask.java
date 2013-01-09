package com.myassist;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.ArrayList;

public class ServerTask extends Thread {

	private ServerTaskFSM    fsm;
	private Socket           conn;
	private BufferedReader   inputStream;
	private DataOutputStream outputStream;
	private String           userDataBuffer;
	private String           userResults;
	private NLPInterface     nlp;
	private boolean          running;
	
	public ServerTask(Socket conn, BufferedReader is, DataOutputStream os)
	{
		this.conn           = conn;
		this.inputStream    = is;
		this.outputStream   = os;
		this.fsm            = new ServerTaskFSM();
		this.nlp            = new NLPInterface();
		this.userDataBuffer = "";
		this.userResults    = "";
		start();
	}

	public void run()
	{
		String command = "";
		int    action  = ServerTaskFSM.WAIT;
		running        = true;
		while (running)
		{
			try 
			{
				command = inputStream.readLine();
				action  = fsm.Update(command);
				
				if (action == ServerTaskFSM.ACCUMULATE)
				{
					//Accumulate User Data
					userDataBuffer.concat(command);
				}
				else if (action == ServerTaskFSM.SUBMIT)
				{
					ProcessUserData();
					outputStream.writeChars(userResults);
					userDataBuffer = "";
					userResults    = "";
				}
				else if (action == ServerTaskFSM.TERMINATE)
				{
					running = false;
				}
			} 
			catch (IOException e) 
			{
				e.printStackTrace();
			}
		}
	}
	
	public void ProcessUserData()
	{
		ArrayList<Item> items = new ArrayList<Item>();
		String sentences[]    = nlp.GetSentences(userDataBuffer);
		StringBuffer sbuf     = new StringBuffer();
		
		for (int i = 0; i < sentences.length; i++)
		{
			Logger.log(sentences[i]);
			Category cat = nlp.GetCategory(sentences[i]);
			Item item;
			if (cat.qualityIndicator > Constants.ITEM_THRESHOLD)
			{
				item = new Item(cat, sentences[i]);
				
				item.setPersonHits(nlp.GetNames(item.getOriginalText()));
				item.setPlaceHits(nlp.GetPlacesAndOrgs(item.getOriginalText()));
				item.setTimeHits(nlp.GetDatesAndTimes(item.getOriginalText()));
				
				items.add(item);
			}
		}
		
		sbuf.append(Constants.START_REPLY_TAG);
		for (int i = 0; i < items.size(); i++)
		{
			sbuf.append(items.get(i).serialize());
		}
		
		sbuf.append(Constants.END_REPLY_TAG);
		
		userResults = sbuf.toString();
	}
} 
