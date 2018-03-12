import java.io.*;
import java.util.Map;
import java.util.HashMap;


public class FrequencyAnalysis {

	//Initialise an array holding the alphabet
	static char[] letter = "abcdefghijklmnopqrstuvwxyz".toCharArray();

	public static void main(String[] args) throws IOException {

		// Analyse frequencies of pg1661.txt
		System.out.println("pg1661.txt's letter frequencies: ");
		BufferedReader in = inputFile("pg1661.txt");

		// Counting variables for pg1661.txt
		int nextChar;
		char currentChar;
		int[] count = new int[26];
		float[] messageFreq = new float[26];
		int totalChars = 0;

		// Hashmap for pg1661.txt
		Map<Character, Float> messageCharMap = new HashMap<Character, Float>();

		// Increment the number of each letter as it is read in
		while ((nextChar = in.read()) != -1) {
			currentChar = (char) nextChar;
			if (currentChar >= 'a' && currentChar <= 'z') {

				count[currentChar - 'a']++;
				totalChars++;
			}
		}

		in.close();

		// Input the values into the Hashmap
		inputToMap(messageCharMap, messageFreq, count, totalChars);

		// Display the frequencies of each letter in pg1661.txt
		for (int i = 0; i < 26; i++) {
			System.out.printf("%c = %f\n", letter[i], messageCharMap.get(letter[i]));
		}

		// Analyse frequencies of cipher1.txt
		System.out.println("cipher1.txt's frequencies: ");
		in = inputFile("cipher1.txt");

		// reuse some of pg1661.txt's counting variables, and add cipherFreq for
		count = new int[26];
		float[] cipherFreq = new float[26];
		totalChars = 0;

		// Hashmap for cipher1.txt
		Map<Character, Float> cipherCharMap = new HashMap<Character, Float>();

		// Increment the number of each letter as it is read in
		while ((nextChar = in.read()) != -1) {
			currentChar = (char) nextChar;
			if (currentChar >= 'a' && currentChar <= 'z') {
				count[currentChar - 'a']++;
				totalChars++;
			}
		}

		in.close();

		// Input the values into the Hashmap
		inputToMap(cipherCharMap, cipherFreq, count, totalChars);

		// Display the frequencies of each letter in cipher1.txt
		for (int i = 0; i < 26; i++) {
			System.out.printf("%c = %f\n", letter[i], cipherCharMap.get(letter[i]));
		}

		// Decipher the cipherText
		in = inputFile("cipher1.txt");
		FileWriter decipher = new FileWriter("deciphered message.txt");
		while ((nextChar = in.read()) != -1) {
			currentChar = (char) nextChar;
			if (Character.isLetter(currentChar)) {
				if (currentChar - 4 < 'a') {
					currentChar = (char) (currentChar + 26);
				}
				currentChar = (char) (currentChar - 4);
			}
			decipher.write(currentChar);
		}
		decipher.close();

	}

	/*
	 * This function takes a map, an empty array of frequencies, an array of
	 * individual letter totals, and a total number of letters and calculates a
	 * frequency, storing it in the map next to its corresponding letter
	 */
	public static void inputToMap(Map<Character, Float> map, float[] frequency, int[] count, int totalChars) {

		for (int i = 0; i < 26; i++) {

			frequency[i] = (float) count[i] / (float) totalChars;
			map.put(letter[i], frequency[i]);

		}

	}

	public static BufferedReader inputFile(String path) throws FileNotFoundException {
		File file = new File(path);
		return new BufferedReader(new FileReader(file));

	}

	public static Character getKeyFromValue(Map<Character, Float> map, Float value) {
		for (Character c : map.keySet()) {
			if (map.get(c).equals(value)) {
				return c;
			}
		}
		return null;
	}

}
