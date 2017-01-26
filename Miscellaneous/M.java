import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;

public class M {
	static HashMap<String, HashMap<String, Double>> years = new HashMap<String, HashMap<String, Double>>();
	static ArrayList<String> lines = new ArrayList<String>();
	
	public static void main(String[] args) throws FileNotFoundException{
		setMaps();
		lines = getLines("C:\\Users\\Moshe_000\\Desktop\\o.txt");
		map();
		viewAllCurrentValues();
		
	}
	
	static void map(){
		for (int i = 0; i < lines.size(); i++){
			String cur = lines.get(i);
			try{
				String year = cur.substring(0, 4);
				String month = cur.substring(5, 7);
				Double dollars = Double.valueOf(cur.substring(11));
				
				HashMap<String, Double> temp = years.get(year);
				
				Double dollarsAlreadyThereForCurMonthAndYear = temp.get(month);
				Double newDollarsTotal = dollars + dollarsAlreadyThereForCurMonthAndYear;
				
				years.get(year).remove(month);
				years.get(year).put(month, newDollarsTotal);
				
			} catch(Exception e){ e.printStackTrace(); }
		}	
	}
	
	static void viewAllCurrentValues() throws FileNotFoundException{
		PrintWriter out = new PrintWriter("C:\\Users\\Moshe_000\\Desktop\\amounts.csv");
		for (HashMap.Entry<String, HashMap<String, Double>> entry : years.entrySet()) {
			for(HashMap.Entry<String, Double> sub : entry.getValue().entrySet()){
				String cur = String.valueOf(sub.getValue());
				try{cur = cur.substring(0, cur.indexOf(".") + 3);}catch(Exception e){}
				out.println(entry.getKey() +"." + String.valueOf(sub.getKey()) + ", " + cur);
			}
		}
		out.close();
	}
	
	static void setMaps(){
		for(int i = 2009; i < 2017; i++){
			HashMap<String, HashMap<String, Double>> tempYear = new HashMap<String, HashMap<String, Double>>();
			HashMap<String, Double> temp = new HashMap<String, Double>();
			temp.put("01", 0.0);
			temp.put("02", 0.0);
			temp.put("03", 0.0);
			temp.put("04", 0.0);
			temp.put("05", 0.0);
			temp.put("06", 0.0);
			temp.put("07", 0.0);
			temp.put("08", 0.0);
			temp.put("09", 0.0);
			temp.put("10", 0.0);
			temp.put("11", 0.0);
			temp.put("12", 0.0);
			years.put(String.valueOf(i), temp);
		}
	}
	
	static ArrayList<String> getLines(String fileName){
		ArrayList<String> locBrands = new ArrayList<String>();
		
	    try {
	    	BufferedReader bufferedReader = new BufferedReader(new FileReader(fileName));
	    	String line; 
	    	
	    	while((line = bufferedReader.readLine()) != null){
	    		if(line.length() > 10){
		    		String temp = line.substring(0, line.indexOf(" ") + 1);
		    		line = line.substring(line.indexOf(" ") + 1);
		    		line = line.substring(line.indexOf(" ") + 1);
		            line = (temp + line).substring(0, (temp + line).lastIndexOf(" "));
		    		if(line.length() > 10)//?
		    			locBrands.add(line);
	    		}
	        }
	    } catch (Exception ex) { System.err.println(ex); }
	    
	    return locBrands;
	}
	
}
