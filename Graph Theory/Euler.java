/*

Input: adjacency matrix as int[][] 
Output: Whether or not the corresponding graph has an euler circuit, euler path, or neither.

*/

package pack;

import java.util.List;
import java.util.ArrayList;

public class Euler {
	public static boolean isConnected(int matrix[][]){
		//this little class holds corresponding start/end points
		//very simple and efficient to determine
		//if all vertices are connected
		class Links{
			Links(){}
			int start, end;
			}
		
		List links = new ArrayList<Links>();
		
		//for loops make a "Links" class
		//for every positive integer in the matrix
		//it then adds them to the ArrayList called "links"
		//the array list stores every connection in
		//the matrix
		for(int i = 0; i < matrix.length; i++){
			for(int j = 0; j < matrix[i].length; j++){
				Links temp = new Links(); 	
				if ((i != j) && (matrix[i][j] != 0)){
					temp.start = i;
					temp.end = j;
					links.add(temp);
				}
			}
		}
			
		/*this is the good stuff, take the first connection in the list
		then add every connection that is linked to that or any connection
		that is linked to any other connection already in the list. 
		for example if the original matrix was 
		[[0, 0, 1, 1], 
		 [0, 0, 1, 1],
		 [1, 1, 0, 0],
		 [1, 1, 0, 0]]
		 then the links ArrayList will have the following links:
		 (0, 2), (0, 3), (1, 2), (1 ,3), (2, 0), (2, 1), (3 ,0), (3, 1)
		 and then following ArrayList starts off with the first link's vertices
		 so it contains 0 and 2, then it compares every element to the ones in
		 the list and if either the start or end is in then those vertices are
		 added. It repeats a full loop of the array for every individual link,
		 this way no matter where a connection is listed, it will be included
		 
		 The end result of this list is a set of numbers representing every
		 vertex that is connected to the first one. 
		*/
		
		List allConnectedVertices = new ArrayList<Integer>();
		allConnectedVertices.add(links.get(0).start);
		allConnectedVertices.add(links.get(0).end);
		
		for(int a = 0; a < links.size(); a++){
			for(int i = 0; i < links.size(); i++){
				if(allConnectedVertices.contains(links.get(i).start) || allConnectedVertices.contains(links.get(i).end)){
					allConnectedVertices.add(links.get(i).start);
					allConnectedVertices.add(links.get(i).end);
				}
			}
		}
		
		//using this list of vertices, it checks if the numbers 1-n,
		//where n is the number of vertices, are all in the list
		//if so then it is connnected, if any one is not then end the loop
		//and return false
		for(Integer i = 0; i < matrix.length; i++){
			if(!allConnectedVertices.contains(i)){
				return false;
			}
		}
		
		return true;
	}
	
	public static String euler(int [][] matrix){
	
		if(!isConnected(matrix))
			return "This matrix is not connected and cannot have a path or circuit";
			
		//this method adds up the number of degrees for each vertex
		//each vertex with an odd degree is noted, if that amount
		//passes two then the inner loop ends. The method
		//returns a string indicating whether or not the graph
		//has an eulerean circuit or path
		
		int numOdds = 0, sumCurRow = 0;
		
		for(int i = 0; i < matrix.length && numOdds < 2; i++){
			for(int j = 0; j < matrix[i].length; j++){
				sumCurRow += matrix[i][j];
			}
			if(sumCurRow % 2 != 0)
				numOdds++;
			
			sumCurRow = 0;
		}
		
		if(numOdds == 0)
			return "The graph has an eulerean circuit";
		else if(numOdds == 2)
			return "The graph has an eulerean path";
		else
			return "The graph has no eulerean circuit or path";
	}
}
