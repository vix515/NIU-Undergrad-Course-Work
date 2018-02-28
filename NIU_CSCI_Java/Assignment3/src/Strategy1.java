import java.util.ArrayList;
import java.util.Scanner;
import java.util.Random;

//Strategy to choose from file

public class Strategy1 extends PDGame {

    //Save all the options to the array make it easier to access in the future
    ArrayList<Character> fileMoves = new ArrayList<>();

    char playRound(Scanner file, char userChoice1, char userChoice2, int i){

        //loop to go through file and save choices in array
        if(i == 1) {
            while (file.hasNextLine()) {
                char a = file.next().charAt(0);
                fileMoves.add(a);
            }
            file.close();
        }

        //logic to return choice of computer
        if(fileMoves.get(0) == 's' || fileMoves.get(0) == 'b'){

            return fileMoves.get(i-1);
        }
        else{
            Random rand = new Random();

            int choice = rand.nextInt(2);

            if(choice == 1){
                return 's';
            }
            return 'b';
        }
    }
}
