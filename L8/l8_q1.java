import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.jgrapht.Graph;
import org.jgrapht.alg.shortestpath.DijkstraShortestPath;
import org.jgrapht.graph.DefaultWeightedEdge;

import org.jgrapht.graph.SimpleWeightedGraph;
import org.jgrapht.io.Attribute;
import org.jgrapht.io.EdgeProvider;
import org.jgrapht.io.GmlImporter;
import org.jgrapht.io.ImportException;
import org.jgrapht.io.VertexProvider;

public class l8_q1 {

	@SuppressWarnings({ "unchecked", "static-access" })
	public static void main(String[] args) {
	

	FileReader arg1 = null;
	try {
		 arg1=new FileReader("L8_P1_sample.gml");
	} catch (FileNotFoundException e1) {
		// TODO Auto-generated catch block
		e1.printStackTrace();
		}
	
	Graph<String, DefaultWeightedEdge> g=new SimpleWeightedGraph<String, DefaultWeightedEdge>(DefaultWeightedEdge.class);

	VertexProvider<String> vp = new VertexProvider<String>()
	        {
				@Override
				public String buildVertex(String label, Map<String, Attribute> attributes) {
					return label;
				}

				
	        };

	        EdgeProvider<String, DefaultWeightedEdge> ep = new EdgeProvider<String, DefaultWeightedEdge>()
	        {

	   			@Override
				public DefaultWeightedEdge buildEdge(String from, String to, String label, Map<String, Attribute> attributes) {
					return g.addEdge(from, to);
				}

	        };

	        
	  // importing GML File
	        
	        GmlImporter<String, DefaultWeightedEdge> importer = new GmlImporter<String, DefaultWeightedEdge>(vp, ep);
	        try {
				importer.importGraph(g, arg1);
				System.out.println("THE GRAPH IS SUCCESFULLY IMPORTED");
			} catch (ImportException e) {
				e.printStackTrace();
			}
	 //Creating dijkstra instance from our graph g
	        
	DijkstraShortestPath<String, DefaultWeightedEdge> dijkistra = new DijkstraShortestPath<String, DefaultWeightedEdge>(g);
	
	@SuppressWarnings("rawtypes")
	List list = new ArrayList(g.vertexSet());

    
         Integer[]  betweenness_centrality_counter = new Integer[g.vertexSet().size()];
      	// System.out.println(betweenness_centrality_counter.length);
         for(int i = 0 ; i < betweenness_centrality_counter.length;i++) 
        	 betweenness_centrality_counter[i]=0;
        
          //conputing betweenness_centrality_counter
		// System.out.println(g.vertexSet());    
	        for(String i : g.vertexSet()) {
	        	System.out.println("this is the shortest path from "+i+" to the rest of the nodes");
	        	// System.out.println(dijkstra.)
	        	// System.out.println(list.inde)
	        	// System.out.println(g.vertexSet().size());
	        	for(int s = list.indexOf(i)+1 ;s<g.vertexSet().size();s++ ) {
	        		// System.out.println(s);
	        		System.out.println(i +" to "+ (s) +" is : " +dijkistra.findPathBetween(g, i, String.valueOf(s)));
	        		//incremente counting
	        		// System.out.println(String.valueOf(s).getVertexList());
	        		// System.out.println(String.valueOf(s));
	        		for(String vertex : dijkistra.findPathBetween(g, i, String.valueOf(s)).getVertexList()) {
	        			// System.out.println(vertex);
	        			// System.out.println(Integer.valueOf(vertex));
	        			betweenness_centrality_counter[Integer.valueOf(vertex)]+=1;
	        		}
	        	}
	        	
	        }
	
	        
	   System.out.println("betweennes centrality  of each node is : ");
	   for(int i = 0 ;i<betweenness_centrality_counter.length;i++)
		   System.out.println("node "+(i+1)+" => "+betweenness_centrality_counter[i]);
	  
	        
	}

}