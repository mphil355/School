/*
 * Author : Matt Phillips
 * Date : 1-14-13
 * Title : Prerequisite project
 * Info : This is the file for the DVDModel class.
 */
public class DVDModel
{
    private String title;
    private String category;
    private String runtime;
    private String year;
    private String price;
    public DVDModel()
    {
        title = "";
        category = "";
        runtime = "";
        year = "";
        price = "";
    }
    public DVDModel(String theTitle, String theCategory, String theRuntime, String theYear, String thePrice)
    {
        title = theTitle;
        category = theCategory;
        runtime = theRuntime;
        year = theYear;
        price = thePrice;
    }
    public DVDModel(DVDModel theDVD)
    {
        title = theDVD.title;
        category = theDVD.category;
        runtime = theDVD.runtime;
        year = theDVD.year;
        price = theDVD.price;
    }
    public void setTitle(String theTitle)
    {
        title = theTitle;
    }
    public void setCategory(String theCategory)
    {
        category = theCategory;
    }
    public void setRuntime(String theRuntime)
    {
        runtime = theRuntime;
    }
    public void setYear(String theYear)
    {
        year = theYear;
    }
    public void setPrice(String thePrice)
    {
        price = thePrice;
    }
    public String getTitle()
    {
        return title;
    }
    public String getCategory()
    {
        return category;
    }
    public String getRuntime()
    {
        return runtime;
    }
    public String getYear()
    {
        return year;
    }
    public String getPrice()
    {
        return price;
    }
    public String toString()
    {
        return ("Title : " + title + "\n" +
                "Category : " + category + "\n" +
                "Runtime : " + runtime + "\n" + 
                "Year : " + year + "\n" + 
                "Price : " + price + "\n");               
    }   
}
