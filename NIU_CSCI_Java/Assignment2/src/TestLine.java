/**
 * Test driver for Line class
 * Contains main method where execution starts.
 * Creates instances of the Line and calls its methods.
 * 
 * @author Victor Padilla
 *
 *
 * Add additional methods and variables to the Line class to implement the following behaviors:
Add an instance variable to hold the thickness of the line. You may implement it as an int. Then add 2 access methods for this variable: a) set the thickness for a Line. b) get a Line's thickness.
Calculate and return (get) the length of a Line. Do not add an instance variable to hold the length. Instead, you are asked to add a method for calculating the length based on its coordinates. The method returns a double. The formula is sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)). You can use the java.lang.Math class for calculating the square root (The method in Math is sqrt(), you need to check the API doc for its usage).
Calculate and return (get) the angle of a Line, which is defined as the angle between that line and the horizontal line that starts from (x1, y1) and goes to right. Return value is between -pi/2 and pi/2. e.g.: If a line is from (10, 10) to (20, 20), the angle is pi/4 (45 degree); If a line is from (10,10) to (15, 5), then the angle is -pi/4. Math class is again used. One way of calculating the angle is asin((y2-y1)/length).
Create a new class and add another constructor to the Line class.
Write a class called TwoDPoint. It is very simple: It has 2 public data members called x and y and a constructor that accepts two integer arguments and stores them in x and y. That's all there is to the class.
Add another constructor for Line that will accept 2 TwoDPoint objects instead of 4 ints.
Add code to main() of TestLine to test the new features. Each new method or constructor must be called at least once.
 *
 */
public class TestLine {
    /**
     * test driver program for Line class 
     * 
     * @param args array of strings for command line arguments 
     */
    public static void main(String args[]) {
        //declare 2 variables of class Line
        Line l1, l2;  
        //create first Line object, and draw it
        l1 = new Line(10, 10, 100, 100);
        l1.draw();
        //change start point with valid values, and draw it 
        l1.setLine(5, 5, l1.getXTwo(), l1.getYTwo());
        l1.draw();
        //try to change xOne (x1) to an illegal value, then draw it
        l1.setXOne(3000);
        l1.draw();
        //create a second Line object, and draw it
        l2 = new Line(100, 100, 400, 400);
        l2.draw();
        //set a new valid yTwo for line 2, and draw it 
        l2.setYTwo(479);
        l2.draw();
        //Create two points of the type TwoD
        TwoDPoint p1, p2;
        //Initialize the points with one x and one y coordinate
        p1 = new TwoDPoint(10, 10);
        p2 = new TwoDPoint(100, 100);
        //Create a line with the two new TwoD points  and draw it
        Line l3 = new Line(p1, p2);
        l3.draw();
    }
}
