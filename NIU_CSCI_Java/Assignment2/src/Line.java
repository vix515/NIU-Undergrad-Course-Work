
/**
 * Demonstrates a simple "Line" class. 
 * Line class is defined with its properties and interface (i.e., its methods).
 * The main method in class TestLine creates instances of this Line class 
 * and calls on the methods to demonstrate its behavior.
 */

import java.lang.Math;

public class Line {
    private int x1, y1, x2, y2;     //coordinates of the line
    private static int maxX = 1000; // x boundary value
    private static int maxY = 1000; // y boundary value

    private int thickness;
    /**
     * Constructor: sets head and tail point coordinates
     * @param xOne head point, x coordinate
     * @param yOne head point, y coordinate
     * @param xTwo tail point, x coordinate
     * @param yTwo tail point, y coordinate
     */
    public Line(int xOne, int yOne, int xTwo, int yTwo) {
        // each of these validates its argument - see below
        setXOne(xOne);
        setYOne(yOne);
        setXTwo(xTwo);
        setYTwo(yTwo);
    }

    /**
     * Constructor sets a line with two TwoD points
     * @param one the first TWoD point
     * @param two the second TwoD Point
     */

    public Line(TwoDPoint one, TwoDPoint two) {
        //get the values by calling the object
        setXOne(one.x);
        setYOne(one.y);
        setXTwo(two.x);
        setYTwo(two.y);
    }
    /**
     * draws line by printing head and tail coordinates
     */
    public void draw() {

        System.out.print("Line from (" + x1 + ", " + y1 + ") to (" + x2 + ", " + y2 + ")");
        System.out.print(" has Length: " + String.format( "%.2f", getLength() ));
        System.out.println(" and  Angle: " + String.format( "%.2f", getAngle() ));
    }
    /**
     * set coordinates of a line
     *
     * @param xOne head point, x coordinate
     * @param yOne head point, y coordinate
     * @param xTwo tail point, x coordinate
     * @param yTwo tail point, y coordinate
     */
    public void setLine(int xOne, int yOne, int xTwo, int yTwo) {
        setXOne(xOne);
        setYOne(yOne);
        setXTwo(xTwo);
        setYTwo(yTwo);
    }
    /**
     * set x coordinate of head point,
     * checks whether value is within bounds
     * @param xOne head point, x coordinate
     */
    public void setXOne(int xOne) {
        if (xOne < 0 || xOne > maxX) {
            x1 = 0;
        } else {
            x1 = xOne;
        }
    }
    /**
     * set y coordinate of head point,
     * checks whether value is within bounds
     * @param yOne head point, y coordinate
     */
    public void setYOne(int yOne) {
        if (yOne < 0 || yOne > maxY) {
            y1 = 0;
        } else {
            y1 = yOne;
        }
    }
    /**
     * set x coordinate of tail point,
     * checks whether value is within bounds
     * @param xTwo tail point, x coordinate
     */
    public void setXTwo(int xTwo) {
        if (xTwo > maxX || xTwo < 0) {
            x2 = 0;
        } else {
            x2 = xTwo;
        }
    }
    /**
     * set y coordinate of head point,
     * checks whether value is within bounds
     * @param yTwo tail point, y coordinate
     */
    public void setYTwo(int yTwo) {
        if (yTwo > maxY || yTwo < 0) {
            y2 = 0;
        } else {
            y2 = yTwo;
        }
    }   
    /**
     * access method
     * @return head point, x coordinate
     */
    public int getXOne() {
        return x1;
    }
    /**
     * access method
     * @return head point, y coordinate
     */
    public int getYOne() {
        return y1;
    }
    /**
     * access method
     * @return tail point, x coordinate
     */ 
    public int getXTwo() {
        return x2;
    }
    /**
     * access method
     * @return tail point, y coordinate
     */         
    public int getYTwo() {
        return y2;
    }

    public void setThickness(int z){thickness = z;}

    public int getThickness(){return thickness;}

    public double getLength(){
        return (Math.sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)));
    }

    public double getAngle(){
        return Math.toDegrees(Math.asin((y2-y1)/getLength()));
    }

}
