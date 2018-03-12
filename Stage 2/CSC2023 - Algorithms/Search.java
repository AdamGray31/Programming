
/************************************************/
/*** Purpose:   A program to search an array  ***/
/*** of ints for a given key using sequential ***/
/*** binary and hash searches.                ***/
/*** Author: Adam Gray                        ***/
/*** Date: 23/10/16                           ***/
/***                                          ***/
/*** Note: Based on skeleton code provided by ***/
/*** Jason Steggles 23/09/2016                ***/
/************************************************/

import java.io.*;
import java.text.*;
import java.util.*;

public class Search {

	/** Global variables for counting comparisons **/
	public int compSeq = 0;
	public int compBin = 0;
	public int compHash = 0;

	/** Array of values to be searched and size **/
	private int[] A;
	private int size;

	/** Hash array and size **/
	private int[] H;
	private int hSize;

	/** Constructor **/
	Search(int n, int hn) {
		/** set size of array **/
		size = n;
		hSize = hn;

		/** Create arrays **/
		A = new int[size];
		H = new int[hSize];

		/** Initialize hash array **/
		/** Assume -1 indicates a location is empty **/
		for (int i = 0; i < hSize; i++) {
			H[i] = -1;
		}
	}

	/********************************************/
	/*** Read a file of numbers into an array ***/
	/********************************************/
	public void readFileIn(String file) {
		try {
			/** Set up file for reading **/
			FileReader reader = new FileReader(file);
			Scanner in = new Scanner(reader);

			/** Loop round reading in data **/
			for (int i = 0; i < size; i++) {
				/** Get next value **/
				A[i] = in.nextInt();
			}
			
		} catch (IOException e) {
			System.out.println("Error processing file " + file);
		}

	}

	/*********************/
	/*** Hash Function ***/
	/*********************/
	public int hash(int key) {
		return key % hSize;
	}

	/*****************************/
	/*** Display array of data ***/
	/*****************************/
	public void displayData(int line, String header) {
		/* ** Integer Formatter ** */
		NumberFormat FI = NumberFormat.getInstance();
		FI.setMinimumIntegerDigits(3);

		/** Print header string **/
		System.out.print("\n\n" + header);

		/** Display array data **/
		for (int i = 0; i < size; i++) {
			/** New line? **/
			if (i % line == 0) {
				System.out.println();
			}

			/** Display value **/
			System.out.print(FI.format(A[i]) + " ");
		}
	}

	/**************************/
	/*** Display hash array ***/
	/**************************/
	public void displayHash(int line) {
		/** Integer Formatter **/
		NumberFormat FI = NumberFormat.getInstance();
		FI.setMinimumIntegerDigits(3);

		/** Print header string **/
		System.out.print("\n\nHash Array of size " + hSize);

		/** Display array data **/
		for (int i = 0; i < hSize; i++) {
			/** New line? **/
			if (i % line == 0) {
				System.out.println();
			}

			/** Display value **/
			System.out.print(FI.format(H[i]) + " ");
		}
	}

	/**************************/
	/*** Sequential Search ***/
	/**************************/
	public int seqSearch(int key) {
		for (int i = 0; i < size; i++) {
			if (key > A[i]) {
				// Continue search while A[i] is smaller than the key, if it's
				// equal or greater go to elseif
				// Add 1 to comparisons
				compSeq += 1;
			} else if (A[i] == key) {
				// Key found, return i
				compSeq += 2; // key>A[i] false, A[i]==key true, add 2
								// comparisons to counter
				return i;
			} else {
				// key not in array, break and return -1
				compSeq += 2; // key>A[i] false, A[i]==key false, add 2
								// comparisons to counter
				break;
			}
		}

		return -1;

	}

	/**************************/
	/***** Binary Search *****/
	/**************************/
	public int binSearch(int key, int L, int R) {
		if (R < L) {
			// key not found, return -1
			return -1;
		}

		// Calculate next midpoint
		int m = (R + L) / 2;

		if (key == A[m]) {
			// key found, return m
			compBin += 1; // Done one comparison in this recursion, add 1
							// comparisons to counter
			return m;
		} else if (key > A[m]) {
			// key>middle value, search upper half of array
			compBin += 2; // Done 2 comparisons in this recursion, add 2
							// comparisons to counter
			return binSearch(key, m + 1, R);
		} else {
			// key<middle value, search lower half of array
			compBin += 2; // Done 2 comparisons in this recursion, add 2
							// comparisons to counter
			return binSearch(key, L, m - 1);
		}

	}

	private void addToHash(int value) {

		int i = hash(value);

		while (H[i] != -1) { // if array index is already occupied, check the
								// next one
			i++;
			if (i == hSize) {// if reached the end of the array, loop back to
								// the start
				i = 0;
			}
		}
		H[i] = value; // place value in its correct place in the hash array

	}

	public void readIntoHash(String file) {

		try {
			/** Set up file for reading **/
			FileReader reader = new FileReader(file);
			Scanner in = new Scanner(reader);

			/** Loop round reading in data **/
			for (int i = 0; i < size; i++) {
				/** Get next value **/
				addToHash(in.nextInt());
			}
		} catch (IOException e) {
			System.out.println("Error processing file " + file);
		}

	}

	public int hashSearch(int key) {

		int i = hash(key);
		while (H[i] != -1) { // keep searching until an empty space is located
			if (H[i] == key) { // key found, add 2 to the compHash counter and
								// return the location of the key
				compHash += 2;
				return i;
			}
			compHash += 2; // 2 comparisons done (while and if statements)
			i += 1;
			if (i == hSize) {
				i = 0;
			}

		}
		compHash += 1; // 1 comparison done (failed at while statement)

		return -1;
	}

} /*** End of class Search ***/