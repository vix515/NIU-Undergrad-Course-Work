/*

Author: Victor Padilla
Z-ID: z1689628

September 28, 2017

Specification

The game is played against the computer in rounds. In each round both the user and the computer select whether they want to stay silent or betray their opponent. Based on the choice each will be given a prison sentence. The number of rounds is randomly selected from 5 to 10. The player with the lowest cumulative prison sentence wins.

The game starts by selecting the strategy to be used by the computer to determine its moves. These strategies must be implemented:

"From File" - reads choices from a file: the file contains a sequence of letters 's' and 'b'. The user is prompted for the name of the input file.
"Tit-For-Tat" - stays silent on the first move, then plays the users last move.
"Tit-For-Two-Tat" - stays silent on the first 2 moves, then betrays if the user's last 2 moves were betrayals.
"Tit-For-Tat with forgiveness" - same as Tit-For-Tat, but occasionally stays silent when it would normally betray.
"Random" - stays silent or betrays randomly, with equal probalility.
Once all rounds have been played, the winner is determined, and the user is given a choice to play again. Once the user chooses to not play anymore an overall summary of game play is displayed.

Program Structure

Your Java program must have at least these classes: PDGameApp, PDGame, and GameStats, plus subclasses, one each for each game strategy. You can add more classes as needed.

PDGameApp must contain the "main" method. All console input and output must be from this class. Make sure to validate the user's input. In this class an instance of class PDGame (or one of its subclasses) is created, plus one instance of class GameStats for each game. It must also record the history of played games.

PDGame must define method "playRound" with the user's move as parameter and return the computer's move. The subclasses will override this method to fill in the exact logic of the selected strategy.

GameStats must have instance variables to record the game strategy used, track the players' moves and the successive scores of prison sentence. It should also have methods to determine the result and winner of a game. Instances of this class record the history of played games.

For the "From File" strategy check that the file exists and can be opened in the PDGameApp class; the FileStrategy subclasss of PDGame in its playRound() method will read from the file: if it gets a 's' or 'b' fine, otherwise it reverts to random selection of the move. Here is an example of an input file (no need to submit your test file): history.txt
 */

import java.io.File;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.Random;

public class PDGameApp {

    public static void main(String[] args) {

        //Initialize so game can start in the while loop
        char playAgain = 'y';

        //Create 2 Objects let PDGame be empty so it can be initialize by the type of strategy selected by the user
        PDGame game = null;
        GameStats statsForGame = new GameStats();

        //Declare Scanner and random so we can use it later
        Scanner keyboard = new Scanner(System.in);
        Random  rand = new Random();

        //Declare empty file to be use through out the main
        Scanner file = null;

        while(playAgain == 'y') {

            //Start of the game
            System.out.println(" Welcome to the Prisoner's Dilemma Game \n Please Choose from your opponent;s strategy: ");
            System.out.println(" 1. From File \n 2. Tit for Tat \n 3. Tit for two Tats \n 4. Tit for Tat with forgiveness \n 5. Random \n");

            //Get user strategy to be played
            int userOption = getUserOption(keyboard);
            int rounds = rand.nextInt(6) + 5;

            //Options to do depending on what the user selected
            if(userOption == 1){

                //Here is where we declare what game is,
                game = new Strategy1();

                //declare that there is no file in existence
                boolean fileExist = false;

                //while file DNE
                while(fileExist == false){

                    //Try to see if file exists if not then exit
                    try{
                        System.out.println("Please Enter Name of File: ");
                        String file_name = keyboard.next();
                        file = new Scanner(new File(file_name));
                        fileExist = true;
                    }
                    //catch the error and ask user if they want to try again, hence the while loop
                    catch (Exception e){
                        System.out.println("No file, Try again? 'y' for YES");
                        char fileTryAgain = keyboard.next().charAt(0);

                        if(fileTryAgain == 'y') fileExist = false;
                        else printStats(statsForGame);
                    }
                }

                //add to stats what kind of strategy the user picked
                statsForGame.strategy.add("Opponent used a File");
            }

            //Set the type of game we want to use and save it in stats
            if(userOption == 2){

                game = new Strategy2();
                statsForGame.strategy.add("Opponent used Tit-For-Tat");
            }
            if(userOption == 3){

                game = new Strategy3();
                statsForGame.strategy.add("Opponent used Tit-For-Two-Tat");
            }
            if(userOption == 4){

                game = new Strategy4();
                statsForGame.strategy.add("Opponent used Tit-For-Tat with Forgiveness");
            }
            if(userOption == 5){

                game = new Strategy5();
                statsForGame.strategy.add("Opponent used Random");
            }


            //Do the strategy for the amount of rounds randomly set.
            //Ask the user for their choice input and send the appropriate data to the functions
            for (int i = 1; i <= rounds; i++) {

                System.out.println("Round " + i + ": will you stay silent(s) or betray(b)?");
                char userChoice = getUserChoice(keyboard);

                //Save users choices
                statsForGame.insertPMoves(userChoice);

                //send the information needed to the strategy to get a choice for the computer
                char computerMove = game.playRound(file, statsForGame.getLastMove(i), statsForGame.getSecondLastMove(i), i);

                //Get the stats for what happen during this round
                getRoundStats(userChoice, computerMove, statsForGame);

            }

            System.out.println("Game over: You got " + statsForGame.playerYears +", your opponent got " + statsForGame.computerYears +" years in prison");

            //Update the stats and insert who won the game.
            updateStats(statsForGame);

            //Ask the user if the want to play again.
            System.out.println("Would you like to play another game ? (answer 'y' or 'n')");
            playAgain = getUserPlayAgain(keyboard);
        }

        //Print the stats for the game once its over
        printStats(statsForGame);

    }

    //Get user option to see what strategy they want to use
    static int getUserOption(Scanner keyboard){
        int userOption = 0;

        while(userOption <1 || userOption > 5 ){
            System.out.println("Enter number (1-5)");

            try{
                userOption = keyboard.nextInt();
            } catch(InputMismatchException e) {
                keyboard.next();
            }
        }

        return userOption;
    }

    //get the choice from the user to betray or be silent
    static char getUserChoice(Scanner keyboard){

        char userChoice = 'a';

        while(userChoice != 's' && userChoice != 'b'){
            userChoice = keyboard.next().charAt(0);
            if(userChoice != 's' && userChoice != 'b'){
                System.out.println("Try Again!");
            }
        }

        return userChoice;
    }

    //get user option to play again
    static char getUserPlayAgain(Scanner keyboard){

        char userChoice = 'a';

        while(userChoice != 'y' && userChoice != 'n'){
            userChoice = keyboard.next().charAt(0);
            if(userChoice != 'y' && userChoice != 'n'){
                System.out.println("Would you like to play another game ? (answer 'y' or 'n')");
            }
        }

        return userChoice;
    }

    //get the stats too see who won the round and how many years in jail each got
    static void getRoundStats(char player, char computer, GameStats gameStats){



        if(player == 's' && computer == 's'){
            System.out.println("You selected: silent, opponent selected: silent");
            System.out.println("Prison sentence: you get 1, opponents gets 1 years");

            gameStats.playerYears++;
            gameStats.computerYears++;
        }
        if(player == 's' && computer =='b'){
            System.out.println("You selected: silent, opponent selected: betray");
            System.out.println("Prison sentence: you get 3, opponents gets 0 years");

            gameStats.playerYears += 3;
        }
        if(player == 'b' && computer =='s'){
            System.out.println("You selected: betray, opponent selected: silent");
            System.out.println("Prison sentence: you get 0, opponents gets 3 years");

            gameStats.computerYears += 3;
        }
        if(player == 'b' && computer == 'b') {
            System.out.println("You selected: betray, opponent selected: betray");
            System.out.println("Prison sentence: you get 2, opponents gets 2 years");

            gameStats.playerYears += 2;
            gameStats.computerYears += 2;
        }

        System.out.println();
    }

    //insert into stats whether user won, lost or tied
    static void updateStats(GameStats statsForGame){

        if(statsForGame.playerYears > statsForGame.computerYears){
            statsForGame.gameOutcome.add("You Won");
        }
        if(statsForGame.playerYears < statsForGame .computerYears){
            statsForGame.gameOutcome.add("You lost");
        }
        if(statsForGame.playerYears == statsForGame.computerYears){
            statsForGame.gameOutcome.add("Tied");
        }
        statsForGame.gamesPlayed++;
        statsForGame.timeStamp.add(new java.util.Date());
    }

    //print all the stats at the end of the game
    static void printStats(GameStats statsForGame){

        for(int i=0; i < statsForGame.gamesPlayed; i++){

            System.out.println(statsForGame.timeStamp.get(i) + ": " + statsForGame.gameOutcome.get(i) + ". " + statsForGame.strategy.get(i));
        }

        System.exit(0);
    }

}
