

import junit.framework.TestCase;
import java.util.Scanner;
//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   //You can use this function to implement your manual testing	   
	   UrlValidator validator = new UrlValidator();
	   String urlToTest = "";
	   Scanner input = new Scanner(System.in);
	   String quit = "quit";
	   while(!(urlToTest.equals(quit)))
	   {
		   System.out.println("Enter an URL to test, or 'quit' to quit: ");
		   urlToTest = input.nextLine();
		   if(!(urlToTest.equals(quit)))
				   System.out.println(validator.isValid(urlToTest));
	   }
	   input.close();
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
