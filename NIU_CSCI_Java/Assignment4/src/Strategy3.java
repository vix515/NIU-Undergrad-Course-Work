import java.util.Random;
import java.util.Scanner;

//Tit for two Tat

public class Strategy3 extends PDGame {

    //Return silent for the first two rounds from there check what the users last two choices are
    char playRound(Scanner file, char userChoice1, char userChoice2, int i){

        if(i<= 2){
            return 's';
        }

        if(userChoice1 == 'b' && userChoice2 == 'b'){
            return 'b';
        }

        return 's';
    }
}
