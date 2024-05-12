import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.swing.border.EmptyBorder;

public class main {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Spell Checker");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 300);

        JTextField inputField = new JTextField(20);
        JButton checkButton = new JButton("Check");
        JTextArea suggestionArea = new JTextArea(10, 20);
        suggestionArea.setWrapStyleWord(true);
        suggestionArea.setLineWrap(true);

        checkButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String inputWord = inputField.getText().toLowerCase(); 
                SpellChecker spellChecker = new SpellChecker();
                try {
                    spellChecker.loadDictionary("dictionary.txt");
                    java.util.List<String> suggestions = spellChecker.suggestWords(inputWord);

                    suggestionArea.setText("Suggestions for: " + inputWord + "\n");
                    for (String suggestion : suggestions) {
                        suggestionArea.append(suggestion + "\n");
                    }
                } 
                    catch (IOException ex) {
                    ex.printStackTrace();
                }
            }
        });

        JPanel inputPanel = new JPanel();
        inputPanel.add(new JLabel("Enter a word:"));
        inputPanel.add(inputField);
        inputPanel.add(checkButton);

        JPanel suggestionPanel = new JPanel();
        suggestionPanel.setBorder(BorderFactory.createEmptyBorder(11, 11, 11, 11));
        suggestionPanel.add(new JScrollPane(suggestionArea));
        

        frame.setLayout(new BorderLayout());
        frame.add(inputPanel, BorderLayout.NORTH);
        frame.add(suggestionPanel, BorderLayout.CENTER);

        frame.setVisible(true);
    }
}
