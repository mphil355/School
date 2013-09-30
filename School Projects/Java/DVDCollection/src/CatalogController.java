/*
 * Author : Matt Phillips
 * Date : 1-14-13
 * Title : Prerequisite project
 * Info : This is the file for the CatalogController class.
 */
import java.util.Scanner;
import java.util.StringTokenizer;
import java.io.PrintWriter;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

public class CatalogController
{
    private CatalogModel theCatalog = new CatalogModel();

    public boolean UCaddDVD(DVDModel theDVD)
    {
        return theCatalog.addDVD(theDVD);
    }
    public int UCremoveDVD(String theTitle)
    {
        return theCatalog.removeDVD(theTitle);
    }
    public void UCeditDVD(String theTitle,DVDModel newInfo)
    {
       theCatalog.editDVD(theTitle, newInfo);
    }
    public String UClistByCategory(String theCategory)
    {
        return theCatalog.listByCategory(theCategory);
    }
    public DVDModel UClookupByTitle(String theTitle)
    {
        return theCatalog.lookupByTitle(theTitle);
    }
    public void UCsortByYear()
    {
        theCatalog.sortByYear();
    }
    public void UCsortByTitle()
    {
        theCatalog.sortByTitle();
    }
    public int UCloadCollection()
    {
        theCatalog.clear();

        Scanner in = null;
        
        try
        {
            in = new Scanner(new FileInputStream("catalog.txt"));
        }
        catch (FileNotFoundException e)
        {
            System.out.println("File could not be opened.");
            System.exit(0);
        }
        
        DVDModel theDVD = new DVDModel();
        StringTokenizer temp;
        String temp2;
        
        System.out.println("File loaded.");
        System.out.println("Attempting to load collection. . .");
        
        
        while (in.hasNextLine())
        {
            theDVD = new DVDModel();
            temp = new StringTokenizer(in.nextLine(), ",\n");
            temp2 = temp.nextToken();
            theDVD.setTitle(temp2);
            temp2 = temp.nextToken();
            theDVD.setCategory(temp2);
            temp2 = temp.nextToken();
            theDVD.setRuntime(temp2);
            temp2 = temp.nextToken();
            theDVD.setYear(temp2);
            temp2 = temp.nextToken();
            theDVD.setPrice(temp2);
                        
            if (!in.hasNextLine())
            {
                theCatalog.addDVD(theDVD);
                System.out.println("Collection loaded.\n");       
            }
            else
                theCatalog.addDVD(theDVD);
        }
        
        System.out.println("Collection loaded.\n");
        in.close();
        return theCatalog.size();
    }   
    public void UCwriteCollection()
    {
        PrintWriter out = null;
        try
        {
            out = new PrintWriter( new FileOutputStream("catalog.txt"));
        }
        catch (FileNotFoundException e)
        {
            System.out.println("File could not be opened.");
            System.exit(0);
        }
        
        DVDModel theDVD;
        System.out.println("Writing to file. . .");
        for (int i = 0; i < theCatalog.size(); i++)
        {
            theDVD = new DVDModel(theCatalog.catalog.get(i));
            out.println(theDVD.getTitle() + "," +
                      theDVD.getCategory() + "," +
                      theDVD.getRuntime() + "," +
                      theDVD.getYear() + "," + 
                      theDVD.getPrice());
        }
        
        System.out.println("Complete.");
        out.close();
    }
    public String toString()
    {
        return theCatalog.toString();
    }
}
