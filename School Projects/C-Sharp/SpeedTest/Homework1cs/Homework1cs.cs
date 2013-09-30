/* Author : Matt Phillips
 * Date : 9-23-13
 * Info : This program tests the timing of an unsuccessful recursive Binary Search
 * by performing 2,000,000 searches on the designated array, sample sizes provided
 */


using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Homework1cs
{
    class Homework1
    {
        static void Main(string[] args)
        {
	        //pick from these as needed
	        //128, 512, 2048, 8192, 32768, 131072, 524288, 2097152
            int ARRAY_SIZE = 2097152;

	        int i;

	        int[] theArray = new int[ARRAY_SIZE];	
	        fillArray(theArray, ARRAY_SIZE);

            int start = System.DateTime.Now.Millisecond;
	        //2,000,000 searches in the array 
	        for (i = 0;i <= 2000000; i++)
	        {
		        binarySearch(theArray, 0, ARRAY_SIZE -1, ARRAY_SIZE +1);
            }
            int finish = System.DateTime.Now.Millisecond;
            Console.WriteLine("\n\nSearch Complete");
            
            Console.WriteLine("\nTime: " + (double)(finish - start) + " milliseconds");

            //to keep from closing
            Console.Read();
        }

      static public bool binarySearch(int[] a, int start, int end, int searchItem)
        {
            int middle;
            if (start > end)
                return false;
            else
            {
                middle = (start + end) / 2;

                if (searchItem == a[middle])
                    return true;
                else if (searchItem < a[middle])
                    binarySearch(a, start, middle - 1, searchItem);
                else if (searchItem > a[middle])
                    binarySearch(a, middle + 1, end, searchItem);
                return false;
            }
        }

        static public void fillArray(int[] a, int size)
        {
            for (int i = 0; i < size; i++)
                a[i] = i;
        }
    }
}