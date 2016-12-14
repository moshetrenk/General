import java.io.*;
import java.net.URL;
import java.util.*;

public class wiki{
	static List urls = new ArrayList<String>();
	static int whatAreWeUpTo = 0;
	// add !url.toLowerCase.contains("portal")
	public static void main(String[] args) throws IOException{
		//getSource(getPage("https://en.m.wikipedia.org/wiki/George_Mason"));
		urls.add("https://en.wikipedia.org/wiki/George_Mason");
		
		while(true){
			System.out.println(((String)urls.get(whatAreWeUpTo)).substring(30));
			getSource(getPage((String)urls.get(whatAreWeUpTo)));
		}
	}
	
	public static String stripSource(String source){
		StringBuilder s = new StringBuilder("");
		
		for(int i = 0; i < source.length(); i++){
			if(source.charAt(i) == '<')
				while(source.charAt(i) != '>' && i < source.length() - 1)
					i++;
			s.append(source.charAt(i));
		}
		String p = s.toString();
		p = p.replace('<', ' ');
		p = p.replace('>', ' ');
		
		return p;
	}
	
	public static void saveContent(String stringToSave, String title) throws IOException{
		//System.out.println("title = " + title);
		PrintWriter out = new PrintWriter("C://Users//Moshe_000//Desktop//wiki//" + title.substring(0, title.length() - 12) + ".txt");
		out.println(title + "\n" + stringToSave);
		whatAreWeUpTo++;
		out.close();
	}
	
	public static void getSource(String source) throws IOException{
		
		String title = "";
		if(source.contains("<title>") && source.contains("</title"))
			title = source.substring(source.indexOf("<title>") + 7, source.indexOf("</title"));
		else
			System.out.println("source = " + source);

		/*PrintWriter pages = new PrintWriter("C://Users//Moshe_000//Desktop//Pages//" + title + ".html");
		try{
			pages.write(source);
		} catch (Exception e){
			pages.println(e.getStackTrace());
		}
		pages.close();*/
		
		try{
			if(source.contains("</table>")){
				if(source.contains("id=\"See_also\">See also"))
					source = source.substring(source.indexOf("</table>"), source.indexOf("id=\"See_also\">See also"));
				else if(source.contains("id=\"References\"")){
					source = source.substring(source.indexOf("</table>"), source.indexOf("id=\"References\""));	
				}
				else if(source.contains("id=\"Notes\"")){
					source = source.substring(source.indexOf("</table>"), source.indexOf("id=\"Notes\""));	
				}
				else if(source.contains("id=\"External_links\"")){
					source = source.substring(source.indexOf("</table>"), source.indexOf("id=\"External_links\""));	
				}
				else
					source = source.substring(source.indexOf("</table>"), source.indexOf("</html>"));	
			}
			else{
				if(source.contains("id=\"See_also\">See also"))
					source = source.substring(source.indexOf("<body"), source.indexOf("id=\"See_also\">See also"));
				else if(source.contains("id=\"References\"")){
					source = source.substring(source.indexOf("<body"), source.indexOf("id=\"References\""));	
				}
				else if(source.contains("id=\"Notes\"")){
					source = source.substring(source.indexOf("</body"), source.indexOf("id=\"Notes\""));	
				}
				else if(source.contains("id=\"External_links\"")){
					source = source.substring(source.indexOf("<body"), source.indexOf("id=\"External_links\""));	
				}
				else
					source = source.substring(source.indexOf("<body"), source.indexOf("</html>"));	
			}
		}
		catch (Exception e){
			PrintWriter failed = new PrintWriter("C://Users//Moshe_000//Desktop//failed.txt");
			failed.println(e.getMessage() + e.getCause() + e.getStackTrace() + title);
			failed.close();
		}
		
		saveContent(stripSource(source), title);
		//at this point, you can strip the source and save the text
		//source contains the article content without the headers and footer
		String url = "";
		while(source.contains("href")){
				source = source.substring(source.indexOf("href=\"") + 7);
				url = "https://en.wikipedia.org/" + source.substring(0, source.indexOf('"'));
				String loc = url.toLowerCase();
				if(!urls.contains(loc) && loc.contains("/wiki/") && !loc.contains("org/ttps") && !loc.contains("foot") 
						&& !loc.contains("note") && !loc.contains("file:") && !loc.contains("#") && !loc.contains("portal") 
						&& (!url.substring(30).toLowerCase().contains(":")))                              
					urls.add(url);
		}
	}
	
	public static String getPage(String url){
		StringBuffer buffer = new StringBuffer();
	
    	try {
	         BufferedReader inStream = new BufferedReader(new InputStreamReader((new URL(url)).openStream()));
	         String inputLine;
	         
	         while ((inputLine = inStream.readLine()) != null)
	        	buffer.append(inputLine);

	         return new String(buffer);	         
    	
    	} catch (IOException e) {
    		e.printStackTrace();
    	}	
    	
    	return "error";
    }      
}
