
/******************************************************/
/*** Purpose: Test class to illustrate Search class ***/
/***                                                ***/
/*** Author: L. J. Steggles                         ***/
/*** Date: 23/09/2016                               ***/
/******************************************************/

import java.io.*;
import java.util.Scanner;

public class TestSearch {
	
	public static void main(String[] args) {

		Search S1 = new Search(100, 151);
		Search S2 = new Search(1000, 1499);

		/** Read in test data **/
		S1.readFileIn("src/data1.txt");
		S2.readFileIn("src/data2.txt");
		S1.readIntoHash("src/data1.txt");
		S2.readIntoHash("src/data2.txt");

		/** Read in search data **/
		int A1[] = readSearchValues("src/search1.txt");
		int A2[] = readSearchValues("src/search2.txt");

		/** Comparison total initialisation **/
		double seqTotal = 0;
		double binTotal = 0;
		double hashTotal = 0;

		/** Array 1 **/

		System.out.print("\n\nArray 1 Searches\n\n");

		S1.displayData(20, "Search1 data");
		S1.displayHash(20);
		System.out.println();
		System.out.println();

		for (int i = 0; i < A1.length; i++) {
			System.out.println("Value " + A1[i] + " found at position (" + S1.seqSearch(A1[i])
					+ ") using Sequential Search after " + S1.compSeq + " comparisons. (-1 means not found)");
			System.out.println("Value " + A1[i] + " found at position (" + S1.binSearch(A1[i], 0, 99)
					+ ") using Binary Search after " + S1.compBin + " comparisons. (-1 means not found)");
			System.out.println("Value " + A1[i] + " found at HashArray position (" + S1.hashSearch(A1[i])
					+ ") using Hash Search after " + S1.compHash + " comparisons. (-1 means not found)");
			System.out.println();
			seqTotal += S1.compSeq;
			binTotal += S1.compBin;
			hashTotal += S1.compHash;
			S1.compSeq = 0;
			S1.compBin = 0;
			S1.compHash = 0;
		}

		System.out.println();

		System.out.println("Average Sequential Search Comparisons: " + seqTotal / 10.0);
		System.out.println("Average Binary Search Comparisons: " + binTotal / 10.0);
		System.out.println("Average Hash Search Comparisons: " + hashTotal / 10.0);
		seqTotal = 0;
		binTotal = 0;
		hashTotal = 0;
		System.out.print("\n\n\nEnd of Array 1 Searches\n\n");

		/** End of Array 1 **/

		/** Array 2 **/

		System.out.print("\n\nArray 2 Searches\n\n");

		S2.displayData(25, "Search2 data");
		S2.displayHash(25);
		System.out.println();
		System.out.println();

		for (int i = 0; i < A2.length; i++) {
			System.out.println("Value " + A2[i] + " found at position (" + S2.seqSearch(A2[i])
					+ ") using Sequential Search after " + S2.compSeq + " comparisons. (-1 means not found)");
			System.out.println("Value " + A2[i] + " found at position (" + S2.binSearch(A2[i], 0, 999)
					+ ") using Binary Search after " + S2.compBin + " comparisons. (-1 means not found)");
			System.out.println("Value " + A2[i] + " found at HashArray position (" + S2.hashSearch(A2[i])
					+ ") using Hash Search after " + S2.compHash + " comparisons. (-1 means not found)");
			System.out.println();
			seqTotal += S2.compSeq;
			binTotal += S2.compBin;
			hashTotal += S2.compHash;
			S2.compSeq = 0;
			S2.compBin = 0;
			S2.compHash = 0;
		}

		System.out.println();

		System.out.println("Average Sequential Search Comparisons: " + seqTotal / 10.0);
		System.out.println("Average Binary Search Comparisons: " + binTotal / 10.0);
		System.out.println("Average Hash Search Comparisons: " + hashTotal / 10.0);

		System.out.print("\n\n\nEnd of Array 2 Searches\n\n");

		/** End of Array 2 **/

	}

	public static int[] readSearchValues(String file) {

		int A[] = new int[10];
		try {
			/** Set up file for reading **/
			FileReader reader = new FileReader(file);
			Scanner in = new Scanner(reader);

			/** Loop round reading in data **/
			for (int i = 0; i < 10; i++) {
				/** Get next value **/
				A[i] = in.nextInt();
			}
		} catch (IOException e) {
			System.out.println("Error processing file " + file);
		}
		return A;
	}

}