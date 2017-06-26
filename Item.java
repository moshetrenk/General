/*     
* TL;DR Makes a directory of all files (windows)    
* 
* This is pretty cool... you know how on windows when you search the entire system
* for a file, the search can take like a week because nothing is indexed? So if you
* run this, it gives you a csv (excel) file with a complete listing of every file on
* your system so if you find you're doing searches often, you can just run this and 
* get whatever info you need and then navigate to the file you want. Also it shows
* file size, most recent modification, if it's an executable and much more    
*     
* output() takes the files in the C folder and if a file is a directory then the         
* it gets passed to output(), otherwise its data is sent to the csv file. This little        
* recursive method pretty much does the whole thing.      
*/

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Date;

class Item{
	static PrintWriter out;
	
	public static void main(String[] args)throws IOException, InterruptedException{
		File du = new File("C:\\Users");
		String[] list = du.list();
		String url = "C:\\Users\\" + list[5] + "\\Desktop\\outFile.csv";
		File f = new File("C:\\");
		
		out = new PrintWriter(url);		
		out.print(", Free Space: " + f.getFreeSpace() + ", Usable Space: " + f.getUsableSpace() + ", Total Space: " + f.getTotalSpace());
	
		output(f);
		
		System.out.println("done");
	}
	
	public static void output(File file) throws IOException{
		if(file.listFiles() != null){
			for(File f : file.listFiles()){			
				if(f.isDirectory()){
					out.println(f.getPath().replace(',', '.'));
					output(f);
				}
				else {
					out.print(f.getName().replace(',', '.') + ", Size: ," + f.length() + ",Last Modified: " + new Date(f.lastModified()));
					out.print(", Is Executable: " + f.canExecute() + ", Can read: " + f.canRead() + ", Can Write: " + f.canWrite());
					out.print(", Is Hidden: " + f.isHidden() + ", Is Directory: " + f.isDirectory() + ", Is File: " + f.isFile());
					out.println(", Is Absolute: " + f.isAbsolute());
				}
			}	
		}	
	}	
}	
