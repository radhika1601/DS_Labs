// A Java program for Dijkstra's 
// single source shortest path  
// algorithm. The program is for 
// adjacency matrix representation 
// of the graph. 
import java.util.*;
import java.lang.*;
import java.io.*;

//int[][] shortDist = new int[9][9]; 
//public static int[][] shortDist = new int[9][9];

class ShortestPath { 
  
    private static final int NO_PARENT = -1; 
  
    // Function that implements Dijkstra's 
    // single source shortest path 
    // algorithm for a graph represented  
    // using adjacency matrix 
    // representation 
    private static int[] dijkstra(int[][] adjacencyMatrix, 
                                        int startVertex,int[][] shortDist) 
    { 
        int nVertices = adjacencyMatrix[0].length; 
  
        // shortestDistances[i] will hold the 
        // shortest distance from src to i 
        int[] shortestDistances = new int[nVertices]; 
  
        // added[i] will true if vertex i is 
        // included / in shortest path tree 
        // or shortest distance from src to  
        // i is finalized 
        boolean[] added = new boolean[nVertices]; 
  
        // Initialize all distances as  
        // INFINITE and added[] as false 
        for (int vertexIndex = 0; vertexIndex < nVertices;  
                                            vertexIndex++) 
        { 
            shortestDistances[vertexIndex] = Integer.MAX_VALUE; 
            added[vertexIndex] = false; 
        } 
          
        // Distance of source vertex from 
        // itself is always 0 
        shortestDistances[startVertex] = 0; 
  
        // Parent array to store shortest 
        // path tree 
        Vector[] parents = new Vector[nVertices];
        // int[] parents = new int[nVertices];
  
        // The starting vertex does not  
        // have a parent 
  
        // Find shortest path for all  
        // vertices 
        for (int i = 1; i < nVertices; i++) 
        { 
  
            // Pick the minimum distance vertex 
            // from the set of vertices not yet 
            // processed. nearestVertex is  
            // always equal to startNode in  
            // first iteration.
            Vector nearestVertices = new Vector();
            int nearestVertex = -1; 
            int shortestDistance = Integer.MAX_VALUE; 
            for (int vertexIndex = 0; 
                     vertexIndex < nVertices;  
                     vertexIndex++) 
            { 
                if (!added[vertexIndex] && 
                    shortestDistances[vertexIndex] <  
                    shortestDistance)  
                { 
                    nearestVertex = vertexIndex; 
                    nearestVertices.clear();
                    nearestVertices.add(nearestVertex);
                    shortestDistance = shortestDistances[vertexIndex]; 
                }
                else if(!added[vertexIndex] && 
                    shortestDistances[vertexIndex] == shortestDistance){
                    nearestVertices.add(nearestVertex);
                }
            } 
  
            // Mark the picked vertex as 
            // processed 
            added[nearestVertex] = true; 
  
            // Update dist value of the 
            // adjacent vertices of the 
            // picked vertex. 
            for (int vertexIndex = 0; 
                     vertexIndex < nVertices;  
                     vertexIndex++)  
            { 
                int edgeDistance = adjacencyMatrix[nearestVertex][vertexIndex]; 
                  
                if (edgeDistance > 0
                    && ((shortestDistance + edgeDistance) <  
                        shortestDistances[vertexIndex]))  
                { 
                    parents[vertexIndex] = nearestVertices; 
                    // System.out.println(vertexIndex);
                    shortestDistances[vertexIndex] = shortestDistance +  
                                                       edgeDistance; 
                } 
            } 
        } 
        // printBC(parents, shortestDistances);

        shortDist[startVertex] = shortestDistances; 

        int[] sigma = new int[nVertices];
        for(int i = 0; i < nVertices; i++){
            if(i != startVertex)
                sigma[i] = parents[i].size();
            else
                sigma[i] = 0;
        }
        // sigmaMatrix[u] = shortestDistances;
        // return shortestDistances
        return sigma;
        // printSolution(startVertex, shortestDistances, parents); 
    }

    public static int[][] utility(int[][] shortDist){
        int[][] adjacencyMatrix = { { 0, 4, 0, 0, 8, 0, 7, 5, 1, 9}, 
                                    { 4, 0, 0, 8, 0, 6, 8, 2, 4, 0}, 
                                    { 0, 0, 0, 5, 0, 0, 0, 0, 3, 0}, 
                                    { 0, 8, 5, 0, 0, 0, 0, 0, 0, 5}, 
                                    { 8, 0, 0, 0, 0, 8, 0, 0, 0, 8}, 
                                    { 0, 6, 0, 0, 8, 0, 0, 5, 5, 0}, 
                                    { 7, 8, 0, 0, 0, 0, 0, 0, 0, 0}, 
                                    { 5, 2, 0, 0, 0, 5, 0, 3, 0, 0}, 
                                    { 1, 4, 3, 0, 0, 5, 0, 0, 5, 0},
                                    { 9, 0, 0, 5, 8, 0, 0, 0, 0, 0} }; 
        int[][] sigmaMatrix = new int[10][10];
        for(int u = 0; u < 10; u++){
                sigmaMatrix[u] = dijkstra(adjacencyMatrix, u, shortDist);
        }
        for(int i = 0;i < 10; i++){
            for(int j = 0;j<10;j++)
                System.out.print(sigmaMatrix[i][j]+" ");
            System.out.println();
        }
        return sigmaMatrix;
    }


    public static void between() {
        int[][] shortDist=new int[9][9];
        int[][] sigmaMatrix = utility(shortDist);
        // System.out.println(sigmaMatrix);
        for (int w = 0;w < 10 ; w++) {
            double bc = 0;
            for(int u = 0; u < 10; u++)
                for(int v = u+1; v < 10; v++){
                    if(shortDist[u][w] + shortDist[w][v] == shortDist[u][v] )
                        bc += (sigmaMatrix[u][w])*(sigmaMatrix[w][v])/ sigmaMatrix[u][v];
                }
            System.out.println("Betweenness Centrality of " +w+ " :     "+bc);
        }
    }   

    public static void main(String[] args) 
    { 
        // int[][] adjacencyMatrix = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 }, 
        //                             { 4, 0, 8, 0, 0, 0, 0, 11, 0 }, 
        //                             { 0, 8, 0, 7, 0, 4, 0, 0, 2 }, 
        //                             { 0, 0, 7, 0, 9, 14, 0, 0, 0 }, 
        //                             { 0, 0, 0, 9, 0, 10, 0, 0, 0 }, 
        //                             { 0, 0, 4, 0, 10, 0, 2, 0, 0 }, 
        //                             { 0, 0, 0, 14, 0, 2, 0, 1, 6 }, 
        //                             { 8, 11, 0, 0, 0, 0, 1, 0, 7 }, 
        //                             { 0, 0, 2, 0, 0, 0, 6, 7, 0 } }; 
        // between();

        ProcessBuilder processBuilder = new ProcessBuilder();
        processBuilder.command("bash", "-c", "python /home/radhika/DS_Lab/L8/hack.py "+args[0]);

        // List<String> commands = new ArrayList<String>();
        // commands.add("/bin/cat");
        // //Add arguments
        // commands.add("/home/jack_0f_spades/Downloads/serve/data.txt");
        //System.out.println(commands);

        //Run macro on target
        try {

            Process process = processBuilder.start();
    
            StringBuilder output = new StringBuilder();
    
            BufferedReader reader = new BufferedReader(
                    new InputStreamReader(process.getInputStream()));
    
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line + "\n");
            }
    
            int exitVal = process.waitFor();
            if (exitVal == 0) {
                //System.out.println("Success!");
                System.out.println(output);
                System.exit(0);
            } else {
                //abnormal...
            }
    
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    
     } 
} 
