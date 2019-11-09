import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Scanner;
import java.util.*;

public class UnscrambleWord {
	static DictionaryTrie dw = new DictionaryTrie();
	private static HashSet<String> permutations = new HashSet<String>();
	private String input;

	public static HashSet<String> parseWordsTextFileToSet(String textFile) {
		BufferedReader reader;
		HashSet<String> words = new HashSet<String>();
		try {
			reader = new BufferedReader(new FileReader(textFile));
			String word;
			// the usr/share/dict/words file lists each word is listed on its own line
			// followed by \n
			while ((word = reader.readLine()) != null) {
				words.add(word);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return words;
	}

	public static void populateDictionaryFromSet(HashSet<String> words) {
		dw.populateTrieFromSet(words);
	}

	public void getUserInput() {
		// get input from client
		System.out.println("***************************************************");
		System.out.println("          Welcome to Unscramble Words              ");
		System.out.println("***************************************************");
		System.out.print("\nPlease enter a single word to begin: ");
		Scanner scanner = new Scanner(System.in);
		input = scanner.next();
		scanner.close();
	}

	public void getAllPermutationsOfInputMatchingDictionaryWords() {
		// find all possibilities of target with length > 3
		HashMap<Integer, HashSet<String>> captureList = new HashMap<Integer, HashSet<String>>();

		ArrayList<String> inputVariationList = new ArrayList<String>();
		inputVariationList.add(input);
		int counter = 0;
		while (input.length() - counter > 3) {
			for (int i = 0; i < input.length(); ++i) {
				inputVariationList.add(input.substring(0, i) + input.substring(i + counter));
			}
			counter++;
		}
		for (String input : inputVariationList) {
			getPermutationString("", input.substring(0 + 1, 1) + input.substring(0));
			// insert each permutation into the trie and look for a match
			if (permutations.size() > 0) {
				for (String permutation : permutations) {
					HashSet<String> returnedMatches = getDictionaryWordsMatchingInput(permutation);
					for (String str : returnedMatches)
					{
						if (captureList.get(input.length()) == null)
							captureList.put(input.length(), new HashSet<String>());
						else
							captureList.get(input.length()).add(str);
				}}
				
				permutations.clear();
			}
		}
		for (int i : captureList.keySet())
		{
			System.out.print("Length: " + i + " ");
			Iterator<String> itr = captureList.get(i).iterator();
			while (itr.hasNext()) {
				System.out.print(itr.next() + ", ");
			}
			System.out.println("Count: " +  captureList.get(i).size());
		}
	}

	// print n! permutation of the characters of the string s (in order)
	// source:
	// https://introcs.cs.princeton.edu/java/23recursion/Permutations.java.html
	public static void getPermutationString(String s) {
		getPermutationString("", s);
	}

	private static void getPermutationString(String prefix, String s) {
		int n = s.length();
		if (n == 0) {
			if (prefix.length() > 3)
				permutations.add(prefix);
			return;
		} else {
			for (int i = 0; i < n; i++)
				getPermutationString(prefix + s.charAt(i), s.substring(0, i) + s.substring(i + 1, n));
		}
	}

	public HashSet<String> getDictionaryWordsMatchingInput(String target) {
		HashSet<String> result = new HashSet<String>();
		DictionaryTrie.Node runner = dw.getRootNode();
		for (int i = 0; i < target.length(); ++i) {
			char ch = target.charAt(i);
			if (runner.children != null && runner.children[ch] != null) {
				runner = runner.children[ch];
			} else
				return result;
		}
		if (runner != null) {
			for (String str : runner.wordsAtPosition) {
				result.add(str);
			}
		}
		return result;
	}

	public static void main(String[] args) {
		// read the file into a Set of strings
		HashSet<String> words = parseWordsTextFileToSet("words.txt");
		// create instance of UnscrambleWord program
		UnscrambleWord uw = new UnscrambleWord();
		// populate the internal DictionaryTrie container from the set of words
		UnscrambleWord.populateDictionaryFromSet(words);
		// prompt the user for input
		uw.getUserInput();
		// compute and display all word permutations matching input with length > 3
		uw.getAllPermutationsOfInputMatchingDictionaryWords();
	}

}