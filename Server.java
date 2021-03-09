import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
	public static void main(String[] args) throws Exception
    {
		while(true) 
		{
		ServerSocket ss = new ServerSocket(4999); // creating socket
		
		Socket s = ss.accept(); // accepting coming connections
		System.out.println("Client Connected.");
		String exit = new String();
		exit = "exit";
		while(true)
		{
			
		InputStreamReader in = new InputStreamReader(s.getInputStream());
		BufferedReader bf = new BufferedReader(in);
		
		String str = bf.readLine(); // coming message from client	
		if (new String(exit).equals(str)) {   // client disconnected or not
			System.err.println("Client Disconnected!");
			System.out.println("Waiting for new connections..");
			break;
		}
		str = (str + " mesaji alindi"); // writing message that came from client to console
		System.out.println(str);
		
		PrintWriter pr = new PrintWriter(s.getOutputStream());
		pr.println(str);
		pr.flush(); // sending response message to client
		
		}
		ss.close();
		s.close();
	}
		
    }
}
