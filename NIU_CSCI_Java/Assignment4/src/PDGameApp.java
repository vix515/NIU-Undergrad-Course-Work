/*

        Author: Victor Padilla
        Z-ID: z1689628

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

        FOR ALL OF THIS DEVELOPE A GUI FOR THE USER TO INTERACT WITH.
*/

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import java.io.IOException;
import java.util.Scanner;
import java.util.Random;
import java.util.Date;

import static java.lang.System.exit;

//Extend to Jframe and implement action listener
//this will allow the class to have frames and do actions on clicks
public class PDGameApp extends JFrame implements ActionListener{

    //This are variables that can be access through out the program from any function.
    JTextArea text;
    JButton gamebutton;
    JComboBox<String> gamebox;
    JLabel gamelabel;
    JButton userButtonSilent;
    JButton userButtonBetray;
    JLabel userLabel;
    JPanel secondPanel;
    PDGame game = null;
    GameStats statsForGame = new GameStats();
    Random  rand = new Random();
    Scanner file = null;
    int userOption;
    int rounds;
    int currentRound;
    DefaultListModel<Date> model = new DefaultListModel<Date>();

    //The main invokes a method to create the frame
    public static void main(String[] args) {
        // Create and set up the window.
        SwingUtilities.invokeLater(() -> {
            JFrame main = new PDGameApp("Prisoners Dilemma");
            main.setVisible(true);
        });
    }

    //the conctructor sets up the settings for the frame and call two other functions to get the panels for the tabs
    public PDGameApp (String title) {
        super(title);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(600, 400);

        //Create the tabbed pane
        JTabbedPane tabbedPane = new JTabbedPane();
        tabbedPane.addTab("Game", createFirstPanel());
        tabbedPane.addTab("Results", createSecondPanel());
        add(tabbedPane, BorderLayout.CENTER);
    }

    //This is the first tab
    //it contains the part where the game is played
    JPanel createFirstPanel() {

        //an array of string with the name of the type of games
        String[] gameNames = { "File", "Tit-for-Tat", "Tit-for-Two-Tats", "Tit-for-Tat w/ forgiveness", "Random"};

        //create a panel to return to the main frame
        JPanel panel = new JPanel(new BorderLayout());

        //initiliaze the main text area and put in inside a scroll box
        text = new JTextArea();
        JScrollPane testing = new JScrollPane(text);
        panel.add(testing, BorderLayout.CENTER);

        //create a subpanel that will hold the options the user will select from
        JPanel gameOptionsPanel = new JPanel();
        gamebutton = new JButton("Start New Game");
        gamebox = new JComboBox<>(gameNames);
        gamelabel = new JLabel("Select Game Mode: ");
        gameOptionsPanel.add(gamelabel);
        gameOptionsPanel.add(gamebox);
        gameOptionsPanel.add(gamebutton);

        //sub panel for more user options
        JPanel userOptionsPanel = new JPanel();
        userButtonSilent = new JButton("Stay Silent");
        userButtonBetray = new JButton("Betray");
        userLabel = new JLabel("Your decision this round? ");
        userOptionsPanel.add(userLabel);
        userOptionsPanel.add(userButtonSilent);
        userOptionsPanel.add(userButtonBetray);

        //layout of the panel where the user options will be displayed
        JPanel optionspanel = new JPanel(new GridLayout(2, 1));

        //add both subpanels
        optionspanel.add(gameOptionsPanel);
        optionspanel.add(userOptionsPanel);


        panel.add(optionspanel, BorderLayout.PAGE_START);

        //add action listeners to the buttons and gray out what we dont use at the very beginning
        gamebutton.addActionListener(this);
        userButtonBetray.addActionListener(this);
        userButtonSilent.addActionListener(this);
        userLabel.setEnabled(false);
        userButtonSilent.setEnabled(false);
        userButtonBetray.setEnabled(false);

        return panel;
    }

    //Create second panel for second tab
    JPanel createSecondPanel() {

        //initialization of panel.
        secondPanel = new JPanel(new BorderLayout());

        //a jlist of the content in the model array
        //this will display the date of the games played
        JList<Date> gameOutcomes = new JList<>(model);
        JScrollPane optionsScroll = new JScrollPane(gameOutcomes);
        secondPanel.add(optionsScroll, BorderLayout.LINE_START);

        //this is where the game information will be displayed
        JLabel roundsPlayed = new JLabel("Rounds Played ", SwingConstants.RIGHT);
        JTextField roundsPlayedAnswer = new JTextField();
        JLabel opponentsStrategy= new JLabel("Opponent's Strategy ", SwingConstants.RIGHT);
        JTextField opponentsStrategyAnswer = new JTextField();
        JLabel playesrSentence = new JLabel("Your Sentence", SwingConstants.RIGHT);
        JTextField playesrSentenceAnswer = new JTextField();
        JLabel opponentSentence = new JLabel("Opponents Sentence ", SwingConstants.RIGHT);
        JTextField opponentSentenceAnswer = new JTextField();
        JLabel winner = new JLabel("Winner ", SwingConstants.RIGHT);
        JTextField winnerAnswer = new JTextField();

        //make a grid layout for the information labels and textfields
        JPanel optionspanel = new JPanel(new GridLayout(5, 2));

        //add them in order so the grid can be fillout that way
        optionspanel.add(roundsPlayed);
        optionspanel.add(roundsPlayedAnswer);
        optionspanel.add(opponentsStrategy);
        optionspanel.add(opponentsStrategyAnswer);
        optionspanel.add(playesrSentence);
        optionspanel.add(playesrSentenceAnswer);
        optionspanel.add(opponentSentence);
        optionspanel.add(opponentSentenceAnswer);
        optionspanel.add(winner);
        optionspanel.add(winnerAnswer);

        //paneling for display purposes
        JPanel optionsPanelTop = new JPanel();
        optionsPanelTop.add(optionspanel, BorderLayout.PAGE_START);

        //add image
        BufferedImage myPicture = null;
        try {
            myPicture = ImageIO.read(new File("src/dilemma.png"));
        } catch (IOException e) {
            exit(0);
        }
        JLabel picLabel = new JLabel(new ImageIcon(myPicture));
        optionsPanelTop.add(picLabel, BorderLayout.PAGE_END);

        secondPanel.add(optionsPanelTop, BorderLayout.CENTER);

        //listen to what selection was made from the game list and change the values of the textfields accordingly.
        //basically just get the index of the item selected in Jlist and use the same index for the data in statforgame
        gameOutcomes.addListSelectionListener(new ListSelectionListener()
        {
            public void valueChanged(ListSelectionEvent ev)
            {
                roundsPlayedAnswer.setText("" + statsForGame.rounds.get(gameOutcomes.getSelectedIndex()));
                opponentSentenceAnswer.setText("" + statsForGame.opponentsYears.get(gameOutcomes.getSelectedIndex()));
                opponentsStrategyAnswer.setText(statsForGame.strategy.get(gameOutcomes.getSelectedIndex()));
                playesrSentenceAnswer.setText("" + statsForGame.playersYears.get(gameOutcomes.getSelectedIndex()));
                winnerAnswer.setText("" + statsForGame.gameOutcome.get(gameOutcomes.getSelectedIndex()));

            }
        });
        return secondPanel;
    }


    //listen for actions in the first tab
    //usually button clicks
    public void actionPerformed(ActionEvent e)
    {
        //if the user start a new game the action goes here
        if(e.getActionCommand().equals("Start New Game")){
            //get the idex from the selected option and add 1 to it.
            //adding one is not neccessary (we can start our if statement down below from 0 if we want)
            int index = gamebox.getSelectedIndex() + 1;

            //once the game has started change the buttons display accordingly.
            userButtonSilent.setEnabled(true);
            userButtonBetray.setEnabled(true);
            userLabel.setEnabled(true);
            gamebutton.setEnabled(false);
            gamelabel.setEnabled(false);
            gamebox.setEnabled(false);

            //save the index to our global variable
            userOption = index;
            rounds = rand.nextInt(6) + 5;
            currentRound = 1;

            //Options to do depending on what the user selected
            if(userOption == 1){

                //here choose from a file from a filechooser window
                //convert to scanner because that what the previous assigment was coded in
                //exit if error
                JFileChooser fc = new JFileChooser();
                int result = fc.showOpenDialog(PDGameApp.this);
                if (result == JFileChooser.APPROVE_OPTION) {
                    File filein = fc.getSelectedFile();
                    try{file = new Scanner(filein);}
                    catch (Exception error){
                        exit(0);
                    }
                }

                //Here is where we declare what game is,
                game = new Strategy1();

                //add to stats what kind of strategy the user picked
                statsForGame.strategy.add("File");
                text.setText("Starting game with From File strategy");

            }

            //Set the type of game we want to use and save it in stats
            if(userOption == 2){

                game = new Strategy2();
                statsForGame.strategy.add("Tit-For-Tat");
                text.setText("Starting game with Tit-for-Tat strategy");
            }
            if(userOption == 3){

                game = new Strategy3();
                statsForGame.strategy.add("Tit-For-Two-Tat");
                text.setText("Starting game with Tit-for-two-Tat strategy");
            }
            if(userOption == 4){

                game = new Strategy4();
                statsForGame.strategy.add("Tit-For-Tat w/ Forgiveness");
                text.setText("Starting game with  Tit-For-Tat with Forgiveness strategy");
            }
            if(userOption == 5){

                game = new Strategy5();
                statsForGame.strategy.add("Random");
                text.setText("Starting game with Random strategy");
            }

            //display instructions for user
            text.append("\nMake your choice for round 1:");
        }

        //once the game is started this statement will listen to the users selection and do accordingly to his/her selection
        if(e.getActionCommand().equals("Betray")){
            char userChoice = 'b';

            //Save users choices
            statsForGame.insertPMoves(userChoice);

            //send the information needed to the strategy to get a choice for the computer
            char computerMove = game.playRound(file, statsForGame.getLastMove(currentRound), statsForGame.getSecondLastMove(currentRound), currentRound);

            //Get the stats for what happen during this round
            getRoundStats(userChoice, computerMove, statsForGame);

            currentRound++;

            //if the round is equal to the maximum amount allowed per game
            //then we quit the game and let the user know their score
            //we reenable the play again button and disable the game buttons
            //we also save the data to the stats object and refresh the second tab so the user can go to it an see its current game already there
            if(rounds + 1 == currentRound){
                userButtonSilent.setEnabled(false);
                userButtonBetray.setEnabled(false);
                userLabel.setEnabled(false);
                gamebutton.setEnabled(true);
                gamelabel.setEnabled(true);
                gamebox.setEnabled(true);

                text.append("\n\nGame over: You got " + statsForGame.playerYears +", your opponent got " + statsForGame.computerYears +" years in prison");
                updateStats(statsForGame, rounds);

                secondPanel.revalidate();
                secondPanel.repaint();
            }
            else {
                text.append("\nMake your choice for round: " + currentRound);
            }


        }

        //same as above just with silent
        if(e.getActionCommand().equals("Stay Silent")){
            char userChoice = 's';

            //Save users choices
            statsForGame.insertPMoves(userChoice);

            //send the information needed to the strategy to get a choice for the computer
            char computerMove = game.playRound(file, statsForGame.getLastMove(currentRound), statsForGame.getSecondLastMove(currentRound), currentRound);

            //Get the stats for what happen during this round
            getRoundStats(userChoice, computerMove, statsForGame);

            currentRound++;


            if(rounds + 1 == currentRound){
                userButtonSilent.setEnabled(false);
                userButtonBetray.setEnabled(false);
                userLabel.setEnabled(false);
                gamebutton.setEnabled(true);
                gamelabel.setEnabled(true);
                gamebox.setEnabled(true);

                text.append("\n\nGame over: You got " + statsForGame.playerYears +", your opponent got " + statsForGame.computerYears +" years in prison");
                updateStats(statsForGame, rounds);

                secondPanel.revalidate();
                secondPanel.repaint();
            }
            else {
                text.append("\nMake your choice for round: " + currentRound);
            }


        }

    }


    //get the stats too see who won the round and how many years in jail each got
    void getRoundStats(char player, char computer, GameStats gameStats){



        if(player == 's' && computer == 's'){
            text.append("\n\tYou selected: silent, opponent selected: silent");
            text.append("\n\tPrison sentence: you get 1, opponents gets 1 years");

            gameStats.playerYears++;
            gameStats.computerYears++;
        }
        if(player == 's' && computer =='b'){
            text.append("\n\tYou selected: silent, opponent selected: betray");
            text.append("\n\tPrison sentence: you get 3, opponents gets 0 years");

            gameStats.playerYears += 3;
        }
        if(player == 'b' && computer =='s'){
            text.append("\n\tYou selected: betray, opponent selected: silent");
            text.append("\n\tPrison sentence: you get 0, opponents gets 3 years");

            gameStats.computerYears += 3;
        }
        if(player == 'b' && computer == 'b') {
            text.append("\n\tYou selected: betray, opponent selected: betray");
            text.append("\n\tPrison sentence: you get 2, opponents gets 2 years");

            gameStats.playerYears += 2;
            gameStats.computerYears += 2;
        }

    }

    //insert into stats whether user won, lost or tied
    void updateStats(GameStats statsForGame, int rounds){

        if(statsForGame.playerYears < statsForGame.computerYears){
            statsForGame.gameOutcome.add("You Won");
        }
        if(statsForGame.playerYears > statsForGame .computerYears){
            statsForGame.gameOutcome.add("You lost");
        }
        if(statsForGame.playerYears == statsForGame.computerYears){
            statsForGame.gameOutcome.add("Tied");
        }
        statsForGame.gamesPlayed++;
        statsForGame.timeStamp.add(new java.util.Date());
        model.addElement(new java.util.Date());
        statsForGame.rounds.add(rounds);
        statsForGame.playersYears.add(statsForGame.playerYears);
        statsForGame.opponentsYears.add(statsForGame.computerYears);

        //reset the years in jail for the next game
        statsForGame.playerYears = 0;
        statsForGame.computerYears = 0;
    }

}
