package ru.qwert21.labs.C2;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Locale;

import static ru.qwert21.labs.C2.MyToolkit.*;

public class MainFrame extends JFrame implements ActionListener {
  private final JTextField var1, var2, var3;
  private final JTextField arg1, arg2, arg3;
  private final JTextField result;
  private final JLabel image;

  private int formulaInd;

  private final Core core;

  public MainFrame(Core core) {
    super(Constants.WINDOW_TITLE);

    this.core = core;

    setSize(Constants.WINDOW_WIDTH, Constants.WINDOW_HEIGHT);

    centerFrame();

    Box topBox = Box.createHorizontalBox();
    {
      ButtonGroup formulasButtons = new ButtonGroup();
      formulaInd = 0;

      Box formulasBox = createColumn(
        Box.createVerticalGlue(),
        makeXCentered(createRadioButton(Constants.BUTTON_FORMULA1, true, formulasButtons, this)),
        Box.createVerticalStrut(10),
        makeXCentered(createRadioButton(Constants.BUTTON_FORMULA2, false, formulasButtons, this)),
        Box.createVerticalGlue()
      );
      formulasBox.setBorder(BorderFactory.createTitledBorder("Формулы"));

      image = new JLabel();
      image.setIcon(Constants.ICON_FORMULA1);

      Box formulaBox = createColumn(
        Box.createVerticalGlue(),
        image,
        Box.createVerticalGlue()
      );
      formulaBox.setBorder(BorderFactory.createTitledBorder("Формула"));

      topBox.add(formulasBox);
      topBox.add(formulaBox);
    }

    Box bottomBox = Box.createHorizontalBox();
    {
      ButtonGroup variablesButtons = new ButtonGroup();

      Box variablesBox = createColumn(
        Box.createVerticalGlue(),
        createRow(
          createRadioButton(Constants.BUTTON_VAR1, true, variablesButtons, this),
          var1 = createTextField(6, false)
        ),
        Box.createVerticalStrut(10),
        createRow(
          createRadioButton(Constants.BUTTON_VAR2, true, variablesButtons, this),
          var2 = createTextField(6, false)
        ),
        Box.createVerticalStrut(10),
        createRow(
          createRadioButton(Constants.BUTTON_VAR3, true, variablesButtons, this),
          var3 = createTextField(6, false)
        ),
        Box.createVerticalGlue()
      );
      variablesBox.setBorder(BorderFactory.createTitledBorder("Переменные"));

      Box memoryBox = createColumn(
        Box.createVerticalGlue(),
        makeXCentered(createButton(Constants.BUTTON_MEM_CLEAR, this)),
        Box.createVerticalStrut(10),
        makeXCentered(createButton(Constants.BUTTON_MEM_ADD, this)),
        Box.createVerticalGlue()
      );
      memoryBox.setBorder(BorderFactory.createTitledBorder("Память"));

      Box valuesBox = createColumn(
        Box.createVerticalGlue(),
        createRow(
          new JLabel("X: "),
          arg1 = createTextField(10, true)
        ),
        Box.createVerticalStrut(10),
        createRow(
          new JLabel("Y: "),
          arg2 = createTextField(10, true)
        ),
        Box.createVerticalStrut(10),
        createRow(
          new JLabel("Z: "),
          arg3 = createTextField(10, true)
        ),
        Box.createVerticalGlue()
      );
      valuesBox.setBorder(BorderFactory.createTitledBorder("Аргументы"));

      Box resultBox = createColumn(
        Box.createVerticalGlue(),
        makeXCentered(result = createTextField(12, false)),
        Box.createVerticalStrut(10),
        makeXCentered(createButton(Constants.BUTTON_EVAL, this)),
        Box.createVerticalStrut(10),
        makeXCentered(createButton(Constants.BUTTON_CLEAR, this)),
        Box.createVerticalGlue()
      );
      resultBox.setBorder(BorderFactory.createTitledBorder("Результат"));

      bottomBox.add(variablesBox);
      bottomBox.add(memoryBox);
      bottomBox.add(valuesBox);
      bottomBox.add(resultBox);
    }

    Box mainBox = createColumn(
      topBox,
      bottomBox
    );

    add(mainBox, BorderLayout.CENTER);

    updateVariables();
    clearEdits();

    setDefaultCloseOperation(EXIT_ON_CLOSE);
    setVisible(true);
  }

  private void centerFrame() {
    Toolkit kit = Toolkit.getDefaultToolkit();

    Dimension screen = kit.getScreenSize();

    setLocation((screen.width - Constants.WINDOW_WIDTH) / 2, (screen.height - Constants.WINDOW_HEIGHT) / 2);
  }

  private void clearEdits() {
    arg1.setText("0");
    arg2.setText("0");
    arg3.setText("0");

    result.setText("0");
  }

  private void updateVariables() {
    var1.setText(String.format(Locale.US, "%.4g", core.getMemory(0)));
    var2.setText(String.format(Locale.US, "%.4g", core.getMemory(1)));
    var3.setText(String.format(Locale.US, "%.4g", core.getMemory(2)));
  }

  private void updateResult() {
    double res = core.getResult();

    result.setText(String.format(Locale.US, "%.4g", res));
  }

  @Override
  public void actionPerformed(ActionEvent event) {
    switch(event.getActionCommand()){
      case Constants.BUTTON_FORMULA1 -> {
        if (formulaInd == 0) break;

        formulaInd = 0;
        image.setIcon(Constants.ICON_FORMULA1);
      }
      case Constants.BUTTON_FORMULA2 -> {
        if (formulaInd == 1) break;

        formulaInd = 1;
        image.setIcon(Constants.ICON_FORMULA2);
      }
      case Constants.BUTTON_MEM_CLEAR -> {
        core.clearMemory();
        updateVariables();
        updateResult();
      }
      case Constants.BUTTON_MEM_ADD -> {
        core.addToMemory();
        updateVariables();
        updateResult();
      }
      case Constants.BUTTON_VAR1 -> {
        core.setCurMemoryInd(0);
      }
      case Constants.BUTTON_VAR2 -> {
        core.setCurMemoryInd(1);
      }
      case Constants.BUTTON_VAR3 -> {
        core.setCurMemoryInd(2);
      }
      case Constants.BUTTON_EVAL -> {
        try {
          double x = Double.parseDouble(arg1.getText());
          double y = Double.parseDouble(arg2.getText());
          double z = Double.parseDouble(arg3.getText());

          core.eval(formulaInd, x, y, z);

          updateResult();
        } catch (NumberFormatException e) {
          System.out.println("Incorrect value");
        }
      }
      case Constants.BUTTON_CLEAR -> {
        clearEdits();
        core.clearResult();
      }
    }
  }
}
