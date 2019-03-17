

import junit.framework.TestCase;
import java.util.Scanner;
import org.junit.Test;
import java.util.Random; 
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
     long options =
              UrlValidator.ALLOW_2_SLASHES
                  + UrlValidator.ALLOW_ALL_SCHEMES
                  + UrlValidator.NO_FRAGMENTS;

     UrlValidator validator = new UrlValidator(null,null,options);
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
   
   
    @Test
    public void testNullEmptyURL() {
      long options =
                UrlValidator.ALLOW_2_SLASHES
                    + UrlValidator.ALLOW_ALL_SCHEMES
                    + UrlValidator.NO_FRAGMENTS;
    
       UrlValidator validator = new UrlValidator(null,null,options);
       String urlToTest = null;
       System.out.println("Testing null/empty URLs...");
       System.out.println("null: ");
       if(validator.isValid(urlToTest) ==  false) {
         System.out.println("passed");
       }
       else {
         System.out.println("failed");
       }
       urlToTest = "";
       System.out.println("empty string: ");
       if(validator.isValid(urlToTest) ==  false) {
         System.out.println("passed\n");
       }
       else {
         System.out.println("failed\n");
       }
    }
    
    @Test
    public void testPattern() {
      System.out.println("Testing patterns ...");
      long options =
                UrlValidator.ALLOW_2_SLASHES
                    + UrlValidator.ALLOW_ALL_SCHEMES
                    + UrlValidator.NO_FRAGMENTS;
    
       UrlValidator validator = new UrlValidator(null,null,options);
       System.out.println("Invalid characters in groups 1 - (!?)");
       String urlToTest = "!?//abc.com";
      
       if(validator.isValid(urlToTest) ==  false) {
         System.out.println("passed\n");
       }
       else {
         System.out.println("failed\n");
       }
      
    }
    
    
    @Test
    public void testSchemes() {
      System.out.println("Testing schemes ...");
      System.out.println("Settings - ALLOW_ALL_SCHEMES");
      try {
           long options =
                    UrlValidator.ALLOW_ALL_SCHEMES;
           UrlValidator validator = new UrlValidator(null, null, options);
           System.out.println("null scheme:");
           String urlToTest = "://www.google.com";
           if(validator.isValid(urlToTest) == false) {
             System.out.println("passed");
           }
           else {
             System.out.println("failed");
           }
         }
         catch(ExceptionInInitializerError e) {
           System.out.println("Exception occurred: " + e.getCause() + "\n");
         }
         try {
           long options =
                  UrlValidator.ALLOW_ALL_SCHEMES;
           UrlValidator validator = new UrlValidator(null, null, options);
           System.out.println("ftp:");
           String urlToTest = "ftp://ftp.funet.fi/pub/standards/RFC/rfc959.txt";
           if(validator.isValid(urlToTest) == true) {
             System.out.println("passed");
           }
           else {
             System.out.println("failed");
           }
         }
         catch(ExceptionInInitializerError e) {
             System.out.println("Exception occurred: " + e.getCause());
         }
         try {
           long options =
                    UrlValidator.ALLOW_ALL_SCHEMES;
           UrlValidator validator = new UrlValidator(null, null, options);
           System.out.println("http:");
           String urlToTest = "http://google.com";
           if(validator.isValid(urlToTest) == true) {
             System.out.println("passed");
           }
           else {
             System.out.println("failed");
           }
         }
         catch(ExceptionInInitializerError e) {
           System.out.println("Exception occurred: " + e.getCause());
         }
         try {
           long options =
                    UrlValidator.ALLOW_ALL_SCHEMES;
           UrlValidator validator = new UrlValidator(null, null, options);
           System.out.println("https:");
           String urlToTest = "https://www.google.com";
           if(validator.isValid(urlToTest) == true) {
             System.out.println("passed\n");
           }
           else {
             System.out.println("failed\n");
           }
         }
         catch(NoClassDefFoundError e) {
           e.printStackTrace();
         }
         System.out.println("Default settings - http, https, and ftp allowed");
         
         String urlToTest2 = "http://www.google.com";
         UrlValidator validator2 = new UrlValidator();
         try{
           System.out.println("http:");
           if(validator2.isValid(urlToTest2)) {
             System.out.println("passed\n");
           }
           else {
             System.out.println("failed\n");
           }
         }
         catch(ExceptionInInitializerError e) {
           System.out.println("Exception occurred: " + e.getCause());
         }
      try {
         UrlValidator validator = new UrlValidator();
         System.out.println("ftp:");
         String urlToTest = "ftp://ftp.funet.fi/pub/standards/RFC/rfc959.txt";
         if(validator.isValid(urlToTest) == true) {
           System.out.println("passed");
         }
         else {
           System.out.println("failed");
         }
       }
       catch(ExceptionInInitializerError e) {
           System.out.println("Exception occurred: " + e.getCause());
       }
      try{
          UrlValidator validator = new UrlValidator();
         System.out.println("https:");
         String urlToTest = "https://www.google.com";
         if(validator.isValid(urlToTest)) {
           System.out.println("passed\n");
         }
         else {
           System.out.println("failed\n");
         }
       }
       catch(ExceptionInInitializerError e) {
         System.out.println("Exception occurred: " + e.getCause());
       }
    }
    
    @Test
    public void testAuthority() {
      System.out.println("Testing invalid authority (using http scheme) ...");
      long options =
                UrlValidator.ALLOW_ALL_SCHEMES;
       UrlValidator validator = new UrlValidator(null, null, options);
       String urlToTest = "http://g:?o&gl:e.com";
       if(validator.isValid(urlToTest) == false) {
         System.out.println("passed");
       }
       else {
         System.out.println("failed");
       }
       System.out.println("Testing valid authority ...");
       urlToTest = "http://google-five.com";
       if(validator.isValid(urlToTest) == true) {
         System.out.println("passed\n");
       }
       else {
         System.out.println("failed\n");
       }
       
    }



   @Test
   public void testPath() {
    System.out.println("Testing valid path (http://oregonstate.instructure.com/courses) ...");
    long options =
               UrlValidator.ALLOW_ALL_SCHEMES;
      UrlValidator validator = new UrlValidator(null, null, options);
      String urlToTest = "http://oregonstate.instructure.com/courses";
      if(validator.isValid(urlToTest) == true) {
       System.out.println("passed");
      }
      else {
       System.out.println("failed");
      }
      System.out.println("Testing valid longer path (http://oregonstate.instructure.com/courses/....)");
      urlToTest = "http://oregonstate.instructure.com/courses/1706550/grades";
      if(validator.isValid(urlToTest) == true) {
       System.out.println("passed\n");
      }
      else {
       System.out.println("failed\n");
      }

   }


   @Test
   public void testQuery() { 
    System.out.println("Testing valid query (using http scheme)...");
    long options =
               UrlValidator.ALLOW_ALL_SCHEMES;
    UrlValidator validator = new UrlValidator(null, null, options);
     
    String urlToTest = "http://www.google.com/search?q=query";
    if(validator.isValid(urlToTest) == true) {
      System.out.println("passed");
      }
    else {
      System.out.println("failed");
    }
    System.out.println("Testing invalid query ...");
       urlToTest = "http://www.google.com/search?q=qu   ery";
       if(validator.isValid(urlToTest) == false) {
         System.out.println("passed\n");
       }
       else {
         System.out.println("failed\n");
       }
   }


   @Test
   public void testFragments() {
    System.out.println("Testing Fragments (NO_FRAGMENTS option engaged, using http scheme) ...");
    long options =
               UrlValidator.ALLOW_ALL_SCHEMES
                   + UrlValidator.NO_FRAGMENTS;
      UrlValidator validator = new UrlValidator(null, null, options);
      String urlToTest = "http://oregonstate.instructure.com/courses#karate";
      if(validator.isValid(urlToTest) == false) {
       System.out.println("passed");
      }
      else {
       System.out.println("failed");
      }
      System.out.println("Testing valid Fragment (NO_FRAGMENTS option off)");
      long options2 =
              UrlValidator.ALLOW_ALL_SCHEMES;
      UrlValidator validator2 = new UrlValidator(null, null, options2);
      urlToTest = "http://oregonstate.instructure.com/courses#karate";
      if(validator2.isValid(urlToTest) == true) {
       System.out.println("passed\n");
      }
      else {
       System.out.println("failed\n");
      }

   }
   
   public void testPort() {
      System.out.println("Testing ports ...");
      long options =
                UrlValidator.ALLOW_2_SLASHES
                    + UrlValidator.ALLOW_ALL_SCHEMES
                    + UrlValidator.NO_FRAGMENTS;
    
       UrlValidator validator = new UrlValidator(null,null,options);
       String urlToTest = "http://www.google.com:80";
      
       if(validator.isValid(urlToTest) ==  true) {
         System.out.println("passed\n");
       }
       else {
         System.out.println("failed\n");
       }
      
    }

	   String[] validSchemes = new String[] {"https://", "http://", "ftp://"};
	   String[] invalidSchemes = new String[] {"9ht://", "h9t://", "ht9://", "http:/", "http//", "http/", "://", ""};
	   
	   String[] validAuthorities = new String[] {"www.google.com", "google.au", "localhost"};
	   String[] invalidAuthorities = new String[] {"google.clmo", "", "aaa", "1.2.3.4.5"};
	   
	   String[] validPorts = new String[] {":80", ":20", ":0", ""};
	   String[] invalidPorts = new String[] {":mkal", "92kdl", ":-10"};
	   
	   String[] validPaths = new String[] {"/test", "/test/", "/123456", "", "/test/random"};
	   String[] invalidPaths = new String[] {"//test", "/test//random", "/.../"};
	   
	   String[] queries = new String[] {"", "?action=view"};
	   
	   private static final int NUM_TESTS = 10;

	   
	public static String select(Random random, String[] array){
			int n = random.nextInt(array.length);
			return array[n];
	}
	   
	public void testValidRandom(){
		long randomseed = 7;
		Random random = new Random(randomseed);
	    long options =
	                UrlValidator.ALLOW_2_SLASHES
	                    + UrlValidator.ALLOW_ALL_SCHEMES
	                    + UrlValidator.NO_FRAGMENTS;
		UrlValidator validator = new UrlValidator(null, null, options);
		for(int i = 0; i < NUM_TESTS; i++){
			String Scheme = select(random, validSchemes);
			String Authority = select(random, validAuthorities);
			String Ports = select(random, validPorts);
			String Paths = select(random, validPaths);
			String Query = select(random, queries);
			String testURL = Scheme + Authority + Ports + Paths + Query;
			System.out.println("Testing valid URL... " + testURL + "	");
			if(validator.isValid(testURL) == true){
				System.out.print("passed\n");
			}
			else{
				System.out.print("failed\n");
			}
		}
	}

	public void testInvalidRandom(){
		long randomseed = 7;
		Random random = new Random(randomseed);
	    long options =
                UrlValidator.ALLOW_2_SLASHES
                    + UrlValidator.ALLOW_ALL_SCHEMES
                    + UrlValidator.NO_FRAGMENTS;
	    UrlValidator validator = new UrlValidator(null, null, options);
		for(int i = 0; i < NUM_TESTS; i++){
			String Scheme = select(random, invalidSchemes);
			String Authority = select(random, invalidAuthorities);
			String Ports = select(random, invalidPorts);
			String Paths = select(random, invalidPaths);
			String Query = select(random, queries);
			String testURL = Scheme + Authority + Ports + Paths + Query;
			System.out.println("Testing invalid URL... " + testURL + "	");
			if(validator.isValid(testURL) == false){
				System.out.print("passed\n");
			}
			else{
				System.out.print("failed\n");
			}
		}
	}

}



