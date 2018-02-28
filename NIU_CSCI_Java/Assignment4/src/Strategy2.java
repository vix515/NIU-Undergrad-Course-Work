
import java.util.Scanner;

//Tit for Tat

public class Strategy2 extends PDGame {

    //Simple return users choice after one round where default is silent
    char playRound(Scanner file, char userChoice1, char userChoice2, int i){

        if(i == 1){
            return 's';
        }

        return userChoice1;

    }
}
