/*
 *
 *
 */

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class CatalogModel
{
    private static final int MAX_DVDS = 100;
    ArrayList<DVDModel> catalog = new ArrayList<> (MAX_DVDS);

    public boolean addDVD(DVDModel theDVD)
    {
        return catalog.add(theDVD);
    }
    public int removeDVD(String theTitle)
    {
       boolean found = false;
       String temp;
       int i = 0;

       while ((!found) && (i < catalog.size()))
       {
           temp = catalog.get(i).getTitle();
           if (temp.compareTo(theTitle) == 0)
           {
               catalog.remove(i);
               found = true;
           }
           else
               i++;
       }
       int result;
       if (found)
           result = catalog.size();
       else
           result = -1;
       return result;
    }
    public void editDVD(String theTitle, DVDModel newInfo)
    {
        DVDModel edited;
        for(int i = 0; i < catalog.size(); i++)
        {
            String temp = catalog.get(i).getTitle();
            if(temp.compareTo(theTitle) == 0)
            {
                edited = catalog.get(i);
                edited = newInfo;
            }// end if
        }// end for
    }
    public String listByCategory(String theCategory)
    {
        String result = "";
	for (int i = 0; i < catalog.size(); i++) // loop through the collection
	{
            String temp = catalog.get(i).getCategory();
            if ( temp.compareTo(theCategory) == 0) // if the category matches, output information for the dvd
               result += catalog.get(i).toString() + "\n";
	}
        return result;
    }
    public DVDModel lookupByTitle(String theTitle)
    {
        DVDModel result = null;
        boolean found = false;
        int i = 0;
	while (i < catalog.size() && !found) //loop through the collection
	{
            String temp = catalog.get(i).getTitle();
            if ( temp.compareTo(theTitle) == 0) // if the title matches, output information from the dvd
            {
                result = catalog.get(i);
                found = true;
            }
            else
                 i++;
	}
        return result;
    }
    //selection sort by year
    public void sortByYear()
    {
        Collections.sort(catalog, new DVDYearComparator());

        //this just prints the list after sorting
        for (int k = 0; k < catalog.size(); k++)
        {
            System.out.println("DVD number : " + (k+1));
            System.out.println(catalog.get(k).toString());
        }
    }
    //selection sort by title
    public void sortByTitle()
    {
        Collections.sort(catalog, new DVDTitleComparator());

        //this just prints the list after sorting
        for (int k = 0; k < catalog.size(); k++)
        {
            System.out.println("DVD number : " + (k+1));
            System.out.println(catalog.get(k).toString());
        }
    }
    public int size()
    {
        return catalog.size();
    }
    public void clear()
    {
        catalog.clear();
    }
    public DVDModel getDVD(int i)
    {
        return catalog.get(i);
    }
    public String toString()
    {
        String result = "";
        for (int i = 0; i < catalog.size(); i++)
            result += catalog.get(i).toString() + "\n";
        return result;
    }
    private class DVDYearComparator implements Comparator<DVDModel>
    {
        public int compare(DVDModel first, DVDModel second)
        {
            String firstYear = first.getYear();
            String secondYear = second.getYear();
            return (firstYear.compareTo(secondYear));
        }
    }
    private class DVDTitleComparator implements Comparator<DVDModel>
    {
        public int compare(DVDModel first, DVDModel second)
        {
            String firstTitle = first.getTitle();
            String secondTitle = second.getTitle();
            return (firstTitle.compareTo(secondTitle));
        }
    }

}
