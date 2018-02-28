/**
 * Creates a point with two axis, a TwoDPoint
 * Its contain by constraints between 0 and 1000
 */

public class TwoDPoint {
    public int x, y;    //coordinates of the line
    private static int maxX = 1000; // x boundary value
    private static int maxY = 1000; // y boundary value

    public TwoDPoint(int x, int y){
        if (x < 0 || x > maxX) {
            x = 0;
        } else {
            this.x = x;
        }

        if (y < 0 || y > maxY) {
            y = 0;
        } else {
            this.y = y;
        }
    }
}
