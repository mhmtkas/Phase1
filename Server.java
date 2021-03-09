import java.net.*;
import java.io.*;

public class Server {
	public static void main(String[] args) throws Exception
    {
		ServerSocket ss = new ServerSocket(5999); // creating socket
		Socket s = ss.accept(); // accepting coming connections
		
		InputStreamReader in = new InputStreamReader(s.getInputStream());
		BufferedReader bf = new BufferedReader(in);
		
		String str = bf.readLine(); // coming message from client			
		str = (str + " mesaji alindi"); // writing message that came from client to console
		System.out.println(str);
		
		PrintWriter pr = new PrintWriter(s.getOutputStream());
		pr.println(str);
		pr.flush(); // sending response message to client
		
		ss.close();
		s.close();
    }
}
