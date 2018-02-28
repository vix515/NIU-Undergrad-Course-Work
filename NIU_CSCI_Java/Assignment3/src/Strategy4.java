import java.util.Random;
import java.util.Scanner;

//Tit for tat with forgiveness

public class Strategy4 extends PDGame {

    //if user betrays then randomly choose whether to betray or not
    char playRound(Scanner file, char userChoice1, char userChoice2, int i){

        if(i == 1){
            return 's';
        }

        if(userChoice1 == 's'){
            return 's';
        }
        else{
            Random rand = new Random();
            int choice = rand.nextInt(2);

            if(choice == 1){
                return 'b';
            }
            else{
                return 's';
            }
        }

    }
}
