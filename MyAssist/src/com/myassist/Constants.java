package com.myassist;

public class Constants {
	//NLP Constants
	public static final double ITEM_THRESHOLD = 0.5;
	
	//Client Server Communication Constants
	public static final String CONNECT_CMD     = "<CONNECT>";
	public static final String DISCONNECT_CMD  = "<DISCONNECT>";
	public static final String START_REQ_TAG   = "<REQ>";
	public static final String END_REQ_TAG     = "</>";
	public static final String START_REPLY_TAG = "<REP>";
	public static final String END_REPLY_TAG   = "</>";
	
	//Item Serialization Constants
	public static final String ITEM_START_TAG = "<I>";
	public static final String ITEM_END_TAG   = "</>";
	public static final String TXT_START_TAG  = "<T>";
	public static final String TXT_END_TAG    = "</>";
	public static final String PER_START_TAG  = "<PR>";
	public static final String PER_END_TAG    = "</>";
	public static final String PLA_START_TAG  = "<PL>";
	public static final String PLA_END_TAG    = "</>";
	public static final String TIM_START_TAG  = "<TM>";
	public static final String TIM_END_TAG    = "</>";
	public static final String CAT_START_TAG  = "<C>";
	public static final String CAT_END_TAG    = "</>";
	public static final String TYPE_START_TAG = "<T>";
	public static final String TYPE_END_TAG   = "</>";
	public static final String QUAL_START_TAG = "<Q>";
	public static final String QUAL_END_TAG   = "</>";
}
