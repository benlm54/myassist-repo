package com.myassist;

public class ServerTaskFSM {

	//States
	public static final int INIT       = 0;
	public static final int READY      = 1;
	public static final int PROCESSING = 2;
	
	//Actions
	public static final int WAIT       = 0;
	public static final int ACCUMULATE = 1;
	public static final int SUBMIT     = 2;
	public static final int TERMINATE  = 3;
	
	private int state;
	
	public ServerTaskFSM()
	{
		Reset();
	}
	
	public void Reset()
	{
		state = INIT;
	}
	
	public int GetState()
	{
		return state;
	}
	
	public int Update(String command)
	{
		
		return GetAction();
	}
	
	public int GetAction()
	{
		return ServerTaskFSM.WAIT;
	}
}
