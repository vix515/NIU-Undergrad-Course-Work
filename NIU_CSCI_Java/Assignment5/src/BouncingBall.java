//Victor Padilla
//Assigment 5
//November 2, 2017
//Z-1689628

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.util.ArrayList;
import javax.imageio.plugins.jpeg.JPEGHuffmanTable;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.TitledBorder;
import javax.swing.event.ChangeEvent;
import java.util.Scanner;


public class BouncingBall extends JFrame implements ActionListener{

    int counter = 0; //position in the array of balls

    //variables to set panel width and height
    int width;
    int height;

    //variable to save the radius length for the size of the ball, given by spinner
    float radius;

    //variable to let the program know whether the user has stopped or started the animation
    boolean startTrigger = false;

    //default color for ball
    Color color = Color.WHITE;


    JPanel optionsPanel = new JPanel(new GridLayout(1,2));//tha panel that holds the ball control and ball create
    JPanel topPanel = new JPanel(new BorderLayout());//panel that holds the menu bar and the options panel
    JPanel animationPanel = new JPanel(new BorderLayout());//panel where the balls are
    JPanel controlPanel = new JPanel(new GridLayout(3,1));//the panel that holds the three sliders
    JPanel ballSelectPanel= new JPanel(new FlowLayout());

    JSlider hSlider = new JSlider(JSlider.HORIZONTAL,0,25,10);//horizontal speed slider
    JSlider vSlider = new JSlider(JSlider.HORIZONTAL,0,25,10);//vertical speed slider
    JSlider ballSelectSlider = new JSlider(JSlider.HORIZONTAL,0,counter,counter);//slider to rotate through visible balls
    JMenuItem cut = new JMenuItem("Cut");//the cut option in the menu
    JMenuItem paste = new JMenuItem("Paste");//the paste option in the menu

    ArrayList<Ball> ballPit = new ArrayList<>();//array to hold all the created balls

    Ball cutBall;//hold the ball that we are cutting and later pasting



    public static void main(String[] args) {
        // Create and set up the window.
        SwingUtilities.invokeLater(() -> {
            JFrame main = new BouncingBall("Bouncing Balls");
            main.setVisible(true);
        });

    }

    //default contructor to add the panels to the main frame
    public BouncingBall (String title) {
        super(title);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(900, 600);

        add(topPanel(), BorderLayout.NORTH);
        add(animationPanel(),BorderLayout.CENTER);

    }

    //function that returns menu bar
    /*
    1. Create a File menu item
        1.1 Read option to read from a file
        1.2 Write option to write object to file
    2. Create an Edit meny item
        2.1 Next option to go to next ball in the array
        2.2 Previous option to go to the previous ball in the array
        2.3 Cut option to cut a ball from the animation panel
        2.4 Paste option to put the cut ball into the array
    3. Animation menu item
        3.1 Start option to animate all displayed balls
        3.2 Stop option to stop all animation
     */
    JMenuBar menuBar(){

        JMenuBar bar = new JMenuBar(); //create menu bar

        //create file option with its suboptions
        JMenu file = new JMenu("File", true);
        JMenuItem read = new JMenuItem("Read from file");
        file.add(read);
        JMenuItem write = new JMenuItem("Export to file");
        file.add(write);
        file.addSeparator();
        JMenuItem exit = new JMenuItem("Exit");
        file.add(exit);
        JFileChooser fileChooser = new JFileChooser();

        bar.add(file);//add file option to menu bar

        //create edit option with its sub options
        JMenu edit = new JMenu("Edit", true);
        JMenuItem next = new JMenuItem("Next");
        edit.add(next);
        JMenuItem previous = new JMenuItem("Previous");
        edit.add(previous);
        edit.add(cut);
        edit.add(paste);
        paste.setEnabled(false);

        bar.add(edit);// add edit option to menu bar

        //create animation option with its sub options
        JMenu Animation = new JMenu("Animation", true);
        JMenuItem start = new JMenuItem("Start");
        Animation.add(start);
        JMenuItem stop = new JMenuItem("Stop");
        Animation.add(stop);

        // add animation option to menu bar
        bar.add(Animation);


        //listener for previous option
        //check if counter is not at its lowest possible
        //go to previous position in array
        previous.addActionListener((ActionEvent e) ->{
            if(counter != 0)
                counter--;

            ballSelectSlider.setValue(counter);
        });

        //listener for next option
        //check if counter is not at its highest possible
        //go to next position in array
        next.addActionListener((ActionEvent e) ->{
            if(counter != (ballPit.size() - 1))
                counter++;

            ballSelectSlider.setValue(counter);

        });

        //listener to start animation
        //change the animation boolean of the ball to true so it can be animated in the thread
        //send ball to Bouncing function to start thread of animation
        start.addActionListener((ActionEvent e) ->{
            for(int i=0; i<ballPit.size(); i++) {
                startTrigger = true;
                ballPit.get(i).animate = true;
                Bouncing(ballPit.get(i));
            }
        });

        //change balls animation boolean to false so it wont have animation
        stop.addActionListener((ActionEvent e) ->{
            for(int i=0; i<ballPit.size(); i++) {
                ballPit.get(i).animate = false;
                startTrigger = false;
            }
        });

        //function to cut a ball from the animation
        //place the ball in a place holder
        //enabled the paste option to paste the ball
        //remove ball and decrease counter
        cut.addActionListener((ActionEvent e)->{
            ballPit.get(counter).cut = true;
            cutBall = ballPit.get(counter);
            paste.setEnabled(true);
            ballPit.remove(counter);
            counter = ballPit.size() -1;

            draw();//redraw animation panel
            if(counter < 0)
                cut.setEnabled(false);//if cut last ball disabled cut option

            //reset ballselectslider
            if(counter >= 0) {
                ballSelectSlider.setMaximum(counter);
                ballSelectSlider.setValue(ballSelectSlider.getMaximum());
            }
        });

        //listener to paste ball into function
        paste.addActionListener((ActionEvent e)->{
            pasteItem();
        });

        //read listener to open a file with objects.
        read.addActionListener((ActionEvent e)->{
            int result = fileChooser.showOpenDialog(this);// open dialog to choose file
            if (result == JFileChooser.APPROVE_OPTION) {
                try {
                    FileInputStream file1 = new FileInputStream(fileChooser.getSelectedFile()); //put file in inputstream
                    ObjectInputStream in = new ObjectInputStream(file1); //turn it into an object input

                    Object obj = in.readObject();//create object

                    addFromFile((ArrayList<Ball>) obj);//cast to arraylist of balls and pass it to a function

                } catch (IOException e1) {
                    e1.printStackTrace();
                } catch (ClassNotFoundException e1) {
                    e1.printStackTrace();
                }

            }
        });

        //Listen to write balls to file
        write.addActionListener((ActionEvent e)->{
            int result = fileChooser.showSaveDialog(this);
            if (result == JFileChooser.APPROVE_OPTION) {
                try {
                    FileOutputStream outFile = new FileOutputStream(fileChooser.getSelectedFile());
                    ObjectOutputStream out = new ObjectOutputStream(outFile);

                    out.writeObject(ballPit);
                    out.close();
                } catch (Exception e1) {
                    e1.printStackTrace();
                }
            }
        });

        //listener to exit
        exit.addActionListener((ActionEvent e)->{
            System.exit(0);
        });

        return bar;
    }

    //Panel where we can add balls.
    /*
    1. Set a spinner with values increasing or decreasing in 5's
    2. Button to select color for the fill color of ball.
    3. Button to add ball
     */
    JPanel ballCreatePanel(){

        JPanel ballcreate = new JPanel(new GridLayout(2,1)); //create panel
        ballcreate.setBorder(new TitledBorder("Create Ball")); //set panel border with title

        JLabel createLabel = new JLabel("Balls are inserted in the center.");
        ballcreate.add(createLabel);//insert label

        JPanel ballCreateOptions = new JPanel(new FlowLayout());//panel with flowlayout to hold buttons and spinner
        JLabel spinnerLabel = new JLabel("Size: ");
        JSpinner spinner = new JSpinner(new SpinnerNumberModel(25,1,100,5)); // spinner with default at 25 and low 5 and high 100
        ballCreateOptions.add(spinnerLabel);//add spinner label to panel
        ballCreateOptions.add(spinner);//add spinner to panel

        //create elements and add them to panel
        JLabel colorLabel = new JLabel("Color: ");
        JButton selectColor = new JButton("Pick");
        JButton addBall = new JButton("Add Ball");
        ballCreateOptions.add(colorLabel);
        ballCreateOptions.add(selectColor);
        ballCreateOptions.add(addBall);

        //add sub panel to main panel
        ballcreate.add(ballCreateOptions);

        //listener for button to add ball
        addBall.addActionListener((ActionEvent e)->{
            String holdRadius = spinner.getValue() + "";
            radius = Float.parseFloat(holdRadius);
            createBall();
        });

        //listener to set color
        selectColor.addActionListener((ActionEvent e)-> {
            color = JColorChooser.showDialog(null, "Pick a Color", Color.WHITE);

            //change the color of the button itself
            selectColor.setForeground(color);
            selectColor.setBackground(color);
            selectColor.setOpaque(true);
        });

        return ballcreate;

    }


    //Panel where all the sliders are located.
    //1. Slider to control the rate of change for horizontal movement
    //2. Slider to control the rate of change for vertical movement
    //3/ Slider to select a ball
    JPanel ballControlPanel(){

        controlPanel.setBorder(new TitledBorder("Ball Control"));

        //horizontal slider
        JPanel hSpeedPanel = new JPanel(new FlowLayout());
        JLabel hLabel = new JLabel("Horizontal Speed: ");
        hSlider.setMinorTickSpacing(1);
        hSlider.setPaintTicks(true);
        hSpeedPanel.add(hLabel);
        hSpeedPanel.add(hSlider);
        controlPanel.add(hSpeedPanel);

        //Vertical slider
        JPanel vSpeedPanel = new JPanel(new FlowLayout());
        JLabel vLabel = new JLabel("Vertical Speed: ");
        vSlider.setMinorTickSpacing(1);
        vSlider.setPaintTicks(true);
        vSpeedPanel.add(vLabel);
        vSpeedPanel.add(vSlider);
        controlPanel.add(vSpeedPanel);

        //ball select slider
        JLabel bLabel = new JLabel("Choose Ball: ");
        ballSelectSlider.setMinorTickSpacing(1);
        ballSelectSlider.setPaintTicks(true);
        ballSelectSlider.setSnapToTicks(true);
        ballSelectPanel.add(bLabel);
        ballSelectPanel.add(ballSelectSlider);
        controlPanel.add(ballSelectPanel);

        //listener to update the horizontal and vertical speed of selected ball
        hSlider.addChangeListener((ChangeEvent e) -> {
            ballPit.get(counter).horizontalMovement = hSlider.getValue();
        });
        vSlider.addChangeListener((ChangeEvent e) -> {
            ballPit.get(counter).verticalMovement = vSlider.getValue();
        });

        //set the ball that we selected via slider
        ballSelectSlider.addChangeListener((ChangeEvent e) -> {
            counter = ballSelectSlider.getValue();
        });

        return controlPanel;

    }

    //Panel for where the balls will be located
    JPanel animationPanel(){
        return animationPanel;
    }


    //panel that holds the two ball options panels
    JPanel optionsPanel(){
        optionsPanel.add(ballCreatePanel());
        optionsPanel.add(ballControlPanel());

        return optionsPanel;
    }

    //panel with menubar and options panel
    JPanel topPanel(){
        topPanel.add(menuBar(), BorderLayout.NORTH);
        topPanel.add(optionsPanel(), BorderLayout.CENTER);

        return topPanel;
    }

    //create ball function
    //create new ball, with the set radius and color preset in caller function
    //redraw canvas
    //reset ball select slider
    //set current ball
    //start thread to animate if start boolean is true
    public void createBall(){

        //create ball with set values
        Ball ball = new Ball();
        ball.radius = radius;
        ball.diameter = radius * 2;
        ball.color = color;

        //add to arraylist
        ballPit.add(ball);

        //set current ball
        counter = ballPit.size() - 1;

        //repaint canvas
        JPanel ballCanvas = draw();

        //with balls existing we can cut an object
        cut.setEnabled(true);

        //reset slider.
        ballSelectSlider.setMaximum(counter);
        ballSelectSlider.setValue(ballSelectSlider.getMaximum());

        //repaint panel
        animationPanel.add(ballCanvas, BorderLayout.CENTER);
        animationPanel.revalidate();

        //if start is enabled start threads
        if(startTrigger)
            Bouncing(ballPit.get(counter));
    }

    //function to past ball
    public void pasteItem(){

        cutBall.cut = false;//so theres only one thread for this item, because once we paste it we create a thread ontop of the one that existed before we cut it
        ballPit.add(cutBall);//add to ballpit
        counter = ballPit.size() - 1; // set current ball selected

        JPanel ballCanvas = draw();//repaint canvas with new ball

        //reset sliders
        ballSelectSlider.setMaximum(counter);
        ballSelectSlider.setValue(ballSelectSlider.getMaximum());

        //reinsert canvas
        animationPanel.add(ballCanvas, BorderLayout.CENTER);
        animationPanel.revalidate();

        if(startTrigger)
            Bouncing(ballPit.get(counter));

        paste.setEnabled(false);
        cut.setEnabled(true);
    }

    //Just like that add addball function but we go through a arraylist from a file and push in the balls
    public void addFromFile(ArrayList<Ball> inputPit){

        for(int i=0; i<inputPit.size(); i++){
            inputPit.get(i).animate = true;
            ballPit.add(inputPit.get(i));
            counter = ballPit.size() - 1;
            JPanel ballCanvas = draw();
            cut.setEnabled(true);
            ballSelectSlider.setMaximum(counter);
            ballSelectSlider.setValue(ballSelectSlider.getMaximum());
            animationPanel.add(ballCanvas, BorderLayout.CENTER);
            animationPanel.revalidate();
        }

        for(int i=0; i<ballPit.size(); i++) {
            startTrigger = true;
            ballPit.get(i).animate = true;
            Bouncing(ballPit.get(i));
        }

    }

    //draw the balls in the canvas
    JPanel draw(){
        JPanel ballCanvas = new JPanel() {
            @Override
            public void paintComponent(Graphics g) {
                for(int i=0; i<ballPit.size(); i++){
                    if(i == counter) {
                        ballPit.get(i).current = true;
                        if(ballPit.get(i).horizontalMovement >= 0)
                            hSlider.setValue((int)ballPit.get(i).horizontalMovement);
                        if(ballPit.get(i).verticalMovement >= 0)
                            vSlider.setValue((int)ballPit.get(i).verticalMovement);

                    }
                    else
                        ballPit.get(i).current = false;

                    ballPit.get(i).draw(g);
                }
            }
        };

        return ballCanvas;
    }

    //thread for each ball
    //change directions movement based on balls position

    public void Bouncing(Ball ball) {
        Thread thread = new Thread() {
            public void run() {
                while (ball.animate && !ball.cut) {

                    //set dimension where the balls will bounced from
                    width = animationPanel.getWidth();
                    height = animationPanel.getHeight();

                    ball.X = ball.X + ball.horizontalMovement ;
                    ball.Y = ball.Y + ball.verticalMovement;

                    if (ball.X - ball.radius < 0) {
                        ball.horizontalMovement = -ball.horizontalMovement;
                        ball.X = ball.radius;
                    } else if (ball.X + ball.radius > width) {
                        ball.horizontalMovement = -ball.horizontalMovement;
                        ball.X = width - ball.radius;
                    }

                    if (ball.Y - ball.radius < 0) {
                        ball.verticalMovement = -ball.verticalMovement;
                        ball.Y = ball.radius;
                    } else if (ball.Y + ball.radius > height) {
                        ball.verticalMovement = -ball.verticalMovement;
                        ball.Y = height - ball.radius;
                    }
                    repaint();
                    try {
                        Thread.sleep(50);
                    } catch (InterruptedException ex) {
                    }

                }
            }
        };
        thread.start();
    }

    @Override
    public void actionPerformed(ActionEvent e) {

    }
}