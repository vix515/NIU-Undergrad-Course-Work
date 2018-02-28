import java.io.File;
import java.util.Random;
import java.util.Scanner;

//Random

public class Strategy5 extends PDGame {

    //Return a random answer
     char playRound(Scanner file, char userChoice1, char userChoice2, int i){
        Random rand = new Random();

        int choice = rand.nextInt(2);

        if(choice == 1){
            return 's';
        }
         return 'b';
    }

}
