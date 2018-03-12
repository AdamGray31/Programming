import java.io.IOException;
import java.io.PrintWriter;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Scanner;

public class VigenereCiphers {

	public static void main(String[] args) throws IOException {
		
		//Store plain text file as a String
		String text = readFile("pg1661.txt", StandardCharsets.UTF_8);
		
		//Read in user's password
		System.out.println("Please enter a password: ");
		Scanner s = new Scanner(System.in);
		String key = s.nextLine();
		s.close();
		
		//Print the key to key.txt
		PrintWriter pass = new PrintWriter("key.txt");
		pass.print(key);
		pass.close();
		
		//Encrypt the text and store it as encrypted
		String encrypted = encryption(text, key);
		
		
		//Count frequencies of pg1661.txt's letters
		char currentChar;
		int[] count = new int[26];
		int total = 0;
		for (int i = 0; i< text.length(); i++) {
			currentChar = text.charAt(i);
			if (currentChar >= 'a' && currentChar <= 'z') {
				
				count[currentChar - 'a']++;
				total++;
			}
		}
		float[] typicalFreq = new float[26];
		System.out.println("Typical frequencies: ");
		for(int i=0; i<26;i++){
			typicalFreq[i] = (float)count[i]/(float)total;
			System.out.printf("%c = %f\n",(char)(i+'a'), typicalFreq[i]);
		}
		
		//Count frequencies of encrypted text's letters
		count = new int[26];
		total = 0;
		for (int i = 0; i< encrypted.length(); i++) {
			currentChar = encrypted.charAt(i);
			if (currentChar >= 'a' && currentChar <= 'z') {
				count[currentChar - 'a']++;
				total++;
			}
		}
		float[] encryptedFreq = new float[26];
		System.out.println("Encrypted frequencies: ");
		for(int i=0; i<26;i++){
			encryptedFreq[i] = (float)count[i]/total;
			System.out.printf("%c = %f\n", (char)(i+'a'), encryptedFreq[i]);
		}
		
		
		//Print the encrypted string to encrypted.txt
		PrintWriter encryption = new PrintWriter("encrypted.txt");
		encryption.print(encrypted);
		encryption.close();
		
		//Decrypt the encrypted string and store it as decrypted
		String decrypted = decryption(encrypted, key);
		
		//Print the decrypted string to decrypted.txt
		PrintWriter decryption = new PrintWriter("decrypted.txt");
		decryption.print(decrypted);
		decryption.close();
		
		System.out.println("Completed.");
	}
	
	
	//Encrypt a string using the given key
	public static String encryption(String plainText, final String key){
		//Initialise the return String
		String cipherText = "";
		plainText = plainText.toLowerCase();
		
		//Each loop, pick the next char of the text and substitute for appropriate char
		for(int i=0, j=0; i<plainText.length(); i++){
			char currentChar = plainText.charAt(i);		//Pick next char
			if(currentChar < 'a' || currentChar > 'z'){	//If char isn't a letter 
				cipherText+=currentChar;				//Add it as is 
				continue;								//Then continue to the next letter
			}
			//If the char is a letter, shift it based on current letter of the key
			cipherText+=(char)((currentChar + key.charAt(j) - 2*'a') % 26 + 'a');
			//Use the next letter of the key
			j = ++j%key.length();
		}		
		return cipherText;
	}
	
	//Decrypt a string using the given key
	public static String decryption(String cipherText, final String key){
		//Initialise the return String
		String plainText = "";
		cipherText = cipherText.toLowerCase();
		
		//Each loop, pick the next char of the text and subtitute it for appropriate char
		for(int i=0, j=0; i<cipherText.length();i++){
			char currentChar = cipherText.charAt(i);	//Pick next char
			if(currentChar < 'a' || currentChar > 'z'){	//If char isn't a letter
				plainText+=currentChar;					//Add it as is
				continue;								//Then continue to the next letter		
			}
			//If the char is a letter, shift it based on the current letter of the key
			plainText+=(char)((currentChar - key.charAt(j) + 26) % 26 + 'a');
			j = ++j%key.length();
		}
		
		return plainText;
	}
	
	
	//Helper function to read in a file
	static String readFile(String path, Charset encoding) throws IOException {
		
		byte[] encoded = Files.readAllBytes(Paths.get(path));
		return new String(encoded, encoding);
		
	}

}
