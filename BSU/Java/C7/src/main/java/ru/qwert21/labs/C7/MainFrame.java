package ru.qwert21.labs.C7;


import javax.swing.*;

import java.util.function.Consumer;

import static ru.qwert21.labs.C7.MyToolkit.*;

public class MainFrame extends JFrame {
  public static final int WINDOW_WIDTH = 500;
  public static final int WINDOW_HEIGHT = 500;
  private static final int TO_FIELD_DEFAULT_COLUMNS = 20;
  private static final int INCOMING_AREA_DEFAULT_ROWS = 10;
  private static final int OUTGOING_AREA_DEFAULT_ROWS = 5;
  private static final int SMALL_GAP = 5;
  private static final int MEDIUM_GAP = 10;

  private JTextArea textAreaIncoming;
  private JTextArea textAreaOutgoing;

  private final Consumer<String> onSendMessage;
  private final String name;

  public MainFrame(String name, Consumer<String> onSendMessage) {
    super("Client: " + name);

    setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    centerFrame(this);

    createLayout();

    this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    this.setVisible(true);

    // ===========

    this.onSendMessage = onSendMessage;
    this.name = name;
  }

  private void createLayout() {
    textAreaIncoming = new JTextArea(INCOMING_AREA_DEFAULT_ROWS, 0);
    textAreaIncoming.setEditable(false);

    final JScrollPane scrollPaneIncoming = new JScrollPane(textAreaIncoming);

    textAreaOutgoing = new JTextArea(OUTGOING_AREA_DEFAULT_ROWS, 0);

    final JScrollPane scrollPaneOutgoing = new JScrollPane(textAreaOutgoing);

    final JPanel messagePanel = new JPanel();
    messagePanel.setBorder(BorderFactory.createTitledBorder("Сообщение"));

    final JButton sendButton = createButton("Отправить", e -> sendMessage());

    final GroupLayout layout2 = new GroupLayout(messagePanel);
    messagePanel.setLayout(layout2);
    layout2.setHorizontalGroup(
      layout2.createSequentialGroup()
        .addContainerGap()
        .addGroup(
          layout2.createParallelGroup(GroupLayout.Alignment.TRAILING)
            .addComponent(scrollPaneOutgoing)
            .addComponent(sendButton))
        .addContainerGap()
    );
    layout2.setVerticalGroup(
      layout2.createSequentialGroup()
        .addContainerGap()
        .addGap(MEDIUM_GAP)
        .addComponent(scrollPaneOutgoing)
        .addGap(MEDIUM_GAP)
        .addComponent(sendButton)
        .addContainerGap()
    );

    final GroupLayout layout1 = new GroupLayout(getContentPane());
    setLayout(layout1);
    layout1.setHorizontalGroup(
      layout1.createSequentialGroup()
        .addContainerGap()
        .addGroup(
          layout1.createParallelGroup()
            .addComponent(scrollPaneIncoming)
            .addComponent(messagePanel)
        )
        .addContainerGap()
    );
    layout1.setVerticalGroup(
      layout1.createSequentialGroup()
        .addContainerGap()
        .addComponent(scrollPaneIncoming)
        .addGap(MEDIUM_GAP)
        .addComponent(messagePanel)
        .addContainerGap()
    );
  }

  private void sendMessage() {
    String msg = textAreaOutgoing.getText();

    if (msg.isEmpty()) {
      JOptionPane.showMessageDialog(this,
        "Введите текст сообщения", "Ошибка",
        JOptionPane.ERROR_MESSAGE);
      return;
    }

    onSendMessage.accept(msg);
  }

  public void receiveMessage(String source, String msg) {
    textAreaIncoming.append(source + ": " + msg + "\n");
  }
}