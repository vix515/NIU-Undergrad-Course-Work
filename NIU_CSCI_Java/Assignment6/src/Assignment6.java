//Victor Padilla
//November 30, 2017
//z1689628

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.*;
import java.sql.*;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import javax.imageio.plugins.jpeg.JPEGHuffmanTable;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.border.TitledBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.table.DefaultTableModel;
import java.util.Properties;
import java.util.Scanner;
import java.util.Date;

public class Assignment6 extends JFrame implements ActionListener{

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            JFrame main = new Assignment6 ("Automobile Database");
            main.setLocationRelativeTo(null);
            main.setVisible(true);

        });
    }

    //Textfields that we can access from anywhere to save their text
    JTextField yearT = new JTextField(15);
    JTextField makeT = new JTextField(15);
    JTextField modelT = new JTextField(15);
    JPanel centered = new JPanel();

    //a universal table that we will populate with data
    JTable table;

    //list of arrays to hold the old queries
    ArrayList<OldQueries> oldQs = new ArrayList<>();

    //count the amount of results returned
    int count = 0;

    public Assignment6(String title) {
        super(title);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(900, 600);

        //Add top buttons and center display(table)
        add(topBar(), BorderLayout.NORTH);
        add(centered, BorderLayout.CENTER);


    }

    //Create a tool bar with the 3 main buttons we will be using
    JToolBar topBar(){
        JToolBar topBar = new JToolBar();
        JButton run = new JButton("Run");
        JButton old = new JButton("Old");
        JButton database = new JButton("All");

        topBar.add(new JLabel("Queries"));
        topBar.addSeparator();
        topBar.add(run);
        topBar.add(old);
        topBar.add(database);

        //open a dialog
        run.addActionListener((ActionEvent e)->{
            dialog();
        });

        //Select all from DB and display results
        database.addActionListener((ActionEvent e)->{
            SelectAll("Select * From VehicleModelYear;");
        });

        //display all previous saved queries
        old.addActionListener((ActionEvent e)->{
            displayOld();
        });

        return topBar;//return to display
    }

    //connect to DB and get results in a ResultSet form
    //takes in a string which is the query we want to run
    ResultSet doQuery(String queryString) throws SQLException {
        /* set user id and password on server */
        Properties props = new Properties();
        props.put("user", "z1689628");
        props.put("password", "gs0yCAS3");

        /* establish connections to DB */
        String dbURL = "jdbc:mysql://blitz.cs.niu.edu/AutoDB";
        Connection connection = DriverManager.getConnection(dbURL, props);

        /* create SQL query */
        Statement stmt = connection.createStatement();
        System.out.println("SQL Query: " + queryString);

        /* execute SQL query and process result */
        return stmt.executeQuery(queryString);
    }

    //get results from DB and populate table with data
    void SelectAll(String queryString){

        //set up the table so we can store the data
        DefaultTableModel model = new DefaultTableModel();
        table = new JTable(model);
        JScrollPane scroll = new JScrollPane(table);

        //reset the panel to an empty table
        centered.removeAll();
        centered.add(scroll, BorderLayout.CENTER);
        count = 0;

        try {
            // run DB query to get result set
            ResultSet rs = doQuery(queryString);
            ResultSetMetaData meta = rs.getMetaData();

            // add columns to table model
            int colCount = meta.getColumnCount();
            for (int i = 1; i <= colCount; i++) {
                model.addColumn(meta.getColumnName(i));
            }
            // row data to table model
            while (rs.next()) {
                Object[] row = new Object[colCount];
                for (int i = 0; i < colCount; i++) {
                    row[i] = rs.getString(i + 1);
                }
                model.addRow(row);
                count++;
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }

        //once we repopulate table display again
        centered.revalidate();

    }

    //dialog to let user enter a query of their choice
    void dialog(){
        JDialog dlog = new JDialog(this , "Run New", true);
        dlog.setLayout( new FlowLayout() );

        //all elements for the UI
        JPanel query = new JPanel(new GridLayout(3,1));
        query.setBorder(new TitledBorder("Enter Query"));
        JPanel year1 = new JPanel(new FlowLayout());
        year1.add( new JLabel ("Year: "));
        year1.add( yearT);
        JPanel make1 = new JPanel(new FlowLayout());
        make1.add( new JLabel ("Make: "));
        make1.add( makeT);
        JPanel model1 = new JPanel(new FlowLayout());
        model1.add( new JLabel ("Model: "));
        model1.add( modelT );

        //add to main panel
        query.add(year1);
        query.add(make1);
        query.add(model1);

        dlog.add(query);

        JButton run = new JButton("Run");//finally a button to execute the query
        dlog.add(run);

        //listen to button
        //when pressed send the parse the query and sent it to SelectAll to run and display
        //ask user if they want to store the query for future use
        run.addActionListener((ActionEvent e)->{
            String newQuery = "Select * from VehicleModelYear WHERE year LIKE '" + yearT.getText() + "' AND make LIKE '" + makeT.getText() + "' AND model LIKE '" + modelT.getText() + "';";
            SelectAll(newQuery);

            //get an option to save the query.
            //if yes call function to store queries
            //else just display query and dont save
            String message = "Entries: " + count + " \nWould you like to save?";
            int reply = JOptionPane.showConfirmDialog(null, message, "Confirm", JOptionPane.YES_NO_OPTION);
            if (reply == JOptionPane.YES_OPTION) {
                JOptionPane.showMessageDialog(null, "Saved!");
                addQ(yearT.getText(), makeT.getText(), modelT.getText(), count);
            }
            else {
                JOptionPane.showMessageDialog(null, "Not Saved");
            }

            dlog.setVisible(false);//hide(close) dialog


        });

        dlog.setSize(300,300);
        dlog.setLocationRelativeTo(null);
        dlog.setVisible(true);
    }

    //create old query object and store in the array.
    void addQ(String year, String make, String model, int total){

        OldQueries oldQ = new OldQueries();
        oldQ.year = year;
        oldQ.make = make;
        oldQ.model = model;
        oldQ.timeStamp = new SimpleDateFormat("yyyy.MM.dd.HH.mm.ss").format(new Date());
        oldQ.count = total;

        oldQs.add(oldQ);
    }

    //display in the table all the queries saved by the user
    void displayOld(){
        DefaultTableModel model = new DefaultTableModel();
        table = new JTable(model);
        JScrollPane scroll = new JScrollPane(table);

        //reset table
        centered.removeAll();
        centered.add(scroll, BorderLayout.CENTER);

        try {
            //set column names
            model.addColumn("Time");
            model.addColumn("Year");
            model.addColumn("Make");
            model.addColumn("Model");
            model.addColumn("Count");

            //go through array and display the query objects as rows
            for(int j = 0; j<oldQs.size(); j++){
                Object[] row = new Object[5];

                row[0] = oldQs.get(j).timeStamp;
                row[1] = oldQs.get(j).year;
                row[2] = oldQs.get(j).make;
                row[3] = oldQs.get(j).model;
                row[4] = oldQs.get(j).count;

                model.addRow(row);
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        centered.revalidate();//refresh table

        //items for the popup meny
        JPopupMenu popup = new JPopupMenu();
        JMenuItem delete = new JMenuItem("Delete");
        JMenuItem run = new JMenuItem("Run");
        popup.add(delete);
        popup.add(run);

        //add a listener and only display popup if right clicked
        table.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent e) {
                if (e.getButton() == MouseEvent.BUTTON3) {
                    popup.show(table, e.getX(), e.getY());
                }
            }
        });

        //if user choose delete then delete by index and redisplay table
        delete.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                oldQs.remove(table.getSelectedRow());
                displayOld();
            }
        });

        //if user wants to rerun query simple parse the statement and send it to the correct function
        run.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                String newQuery = "Select * from VehicleModelYear WHERE year LIKE '" + oldQs.get(table.getSelectedRow()).year + "' AND make LIKE '" + oldQs.get(table.getSelectedRow()).make + "' AND model LIKE '" + oldQs.get(table.getSelectedRow()).model + "';";
                SelectAll(newQuery);
            }
        });
    }

    @Override
    public void actionPerformed(ActionEvent e) {

    }
}
