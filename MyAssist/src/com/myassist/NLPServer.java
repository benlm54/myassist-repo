/**
 * 
 */
package com.myassist;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

/**
 * @author Ben
 *
 */
public class NLPServer {

	//Constants
	private static final int PORT      = 3000;
	
	//Global Variable
	private static ArrayList<ServerTask> tasks = new ArrayList<ServerTask>();
	
	/**
	 * @throws IOException 
	 * 
	 */
	private static void ServerThread() throws IOException
	{
		ServerSocket sock = new ServerSocket(PORT);	
		while (true)
		{
			Socket conn                   = sock.accept();
			BufferedReader inputStream    = new BufferedReader(new InputStreamReader(conn.getInputStream()));
			DataOutputStream outputStream = new DataOutputStream(conn.getOutputStream());
			
			tasks.add(new ServerTask(conn, inputStream, outputStream));		
		}
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			ServerThread();
		} catch (IOException e) {
			Logger.log("Unable to start server!");
			e.printStackTrace();
		}
	}

}
