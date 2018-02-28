import java.util.ArrayList;
import java.util.Date;

public class GameStats {

    ArrayList<String> strategy = new ArrayList<>();
    ArrayList<String> gameOutcome = new ArrayList<>();
    ArrayList<Date> timeStamp = new ArrayList<>();
    ArrayList<Integer> playersYears = new ArrayList<>();
    ArrayList<Integer> opponentsYears = new ArrayList<>();
    ArrayList<Integer> rounds = new ArrayList<>();


    ArrayList<Character> pMoves = new ArrayList<>();


    int gamesPlayed = 0;

    int playerYears = 0;
    int computerYears = 0;


    public void insertPMoves(char move){
        pMoves.add(move);
    }

    public char getLastMove(int gameRound){

        if(gameRound == 1){
            gameRound++;
            return pMoves.get(pMoves.size() - 1);
        }
        return pMoves.get(pMoves.size() - 2);
    }

    public  char getSecondLastMove(int gameRound){
        if (gameRound <= 2){
            return  pMoves.get(pMoves.size() - 1);
        }

        return pMoves.get(pMoves.size() - 3);
    }


}
