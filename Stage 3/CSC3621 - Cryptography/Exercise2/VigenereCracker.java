import java.io.IOException;
import java.io.PrintWriter;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;

public class VigenereCracker {

	//The frequencies of each letter in the English alphabet in regular text
	private static double[] typicalFreq = { 8.167, 1.492, 2.782, 4.253, 12.702, 2.228,
			2.015, 6.094, 6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507,
			1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
			1.974, 0.074 };
	
	public static void main(String[] args) throws IOException{		

		//Read cipherText into a String
		String cipherText = readFile("cipher2.txt", StandardCharsets.UTF_8);
		
		System.out.println("Decrypting cipher2.txt");
		
		//Recover the plaintext 
		String recoveredText = deVigenere(cipherText);		
		
		//Print the plaintext to a txt file
		PrintWriter plainTextWriter = new PrintWriter("recoveredText.txt");
		plainTextWriter.print(recoveredText);
		plainTextWriter.close();
		
		System.out.println("Decrypted text saved as 'recoveredText.txt'\nCompleted.");
	}
	
	//Helper function to read in a file
	static String readFile(String path, Charset encoding) throws IOException {
		
		byte[] encoded = Files.readAllBytes(Paths.get(path));
		return new String(encoded, encoding);
		
	}
	
	/* 
	 * If text is abcdefghijkl and key length is 3,
	 * the blocks would be divided such that the first 
	 * block would be adgj, the second would be behk, and
	 * the third would be cfil.  
	 */
	static String[] splitIntoBlocks(String text, int length){
		String[] blocks = new String[length]; 
		for(int i = 0; i < blocks.length; i++){
			blocks[i] = new String();
		}
		for(int j = 0; j < text.length(); j++){
			blocks[j % length]+=text.charAt(j); 
		}
		return blocks;
		
	}
			
	/*
	 * Returns a number which indicates how close the frequencies of the letters 
	 * of 'data' are to the frequencies of letters in typical English text.
	 */
	private static double freqDiff(String data) { 
		//Create an array to store frequencies of letters 
		int[] letterFreqs = new int[26];   
		data = data.toLowerCase();
		//Count the occurrences of each letter in the data
		for(char c : data.toCharArray()){
			if(c>='a' && c<='z')letterFreqs[c-'a']++;
		}
		
		/*
		 * Calculates the square of the 'distance' between the data's letter frequencies 
		 * and typical English text's letter frequencies
		 */
		double sumDSquared = 0.0;   
		for(int i = 0; i < typicalFreq.length; i++) {
			sumDSquared += Math.pow((100.0 * letterFreqs[i] / data.length() - typicalFreq[i]), 2);
		}
		return sumDSquared;
	}
	
	/*
	 * Reverse the effect of a Caesar Cipher on a string by looping through 
	 * each letter of the alphabet and shifting the text by that number of 
	 * letters. The frequencies of the letters is then compared to the
	 * frequencies of letters in typical English and returns the text 
	 * that is closest.
	 */
	static String deCaesar(String msg) { 
		String closest = null;
		for(int i = 'a'; i <= 'z'; i++) {
			closest = closestToTypical(closest, VigenereCiphers.encryption(msg, "" + (char) (i)));
		}
		return closest;
	}
	
	//Compares two strings and returns the one with the lowest difference in frequencies
	public static String closestToTypical(String a, String b) { 
		if(a==null || (b!=null && freqDiff(a)>freqDiff(b))){
			return b;
		}else{
			return a;
		}
		
	}
	
	//Crack a Vigenere Cipher
	static String deVigenere(String cipherText){
		String recoveredText = null; 
		//Try deciphering the text with different lengths of key
		for(int keyLength = 1; keyLength<10; keyLength++){
			//Split the cipherText into blocks
			String[] blocks = splitIntoBlocks(cipherText, keyLength);
			String[] decryptedBlocks = new String[keyLength];
			
			//deCaesar each block separately
			for(int i = 0; i<keyLength; i++){
				decryptedBlocks[i] = deCaesar(blocks[i]);			
			}
			
			//Recombine decrypted blocks to form plaintext
			String recombined = new String();
			for(int i = 0; i<cipherText.length(); i++){
				recombined+=decryptedBlocks[i%keyLength].charAt(i/keyLength);
			}
			
			/*
			 * Determine whether currently 'decrypted' text is more likely to 
			 * be close to typical English
			 */
			recoveredText = closestToTypical(recoveredText, recombined);
		}
		
		return recoveredText;
	}
	
}
