import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;

public class DictionaryTrie {
	class Node {
		public char value;
		public Node[] children = null;
		public ArrayList<String> wordsAtPosition;

		public Node() {
			value = '!';
			wordsAtPosition = new ArrayList<String>();
		}

		public Node(char ch) {
			value = ch;
			wordsAtPosition = new ArrayList<String>();
		}
	}

	public static Node root;

	public DictionaryTrie() {
		root = new Node('!');
	}

	public Node getRootNode() {
		return root;
	}

	public void populateTrieFromSet(HashSet<String> words) {
		Iterator<String> itr = words.iterator();
		Node runner = root;
		while (itr.hasNext()) {
			String tempString = itr.next();
			runner = root;
			for (int i = 0; i < tempString.length(); ++i) {
				int index = tempString.charAt(i);
			
				if (runner.children == null)
					runner.children = new Node[256];
				if (runner.children[index] == null)
					runner.children[index] = new Node(tempString.charAt(i));
			
				runner = runner.children[index];

				// insert the word into the last node position
				if (i == tempString.length() - 1) {
					runner.wordsAtPosition.add(tempString);
				}
			}
		}	
	}
}