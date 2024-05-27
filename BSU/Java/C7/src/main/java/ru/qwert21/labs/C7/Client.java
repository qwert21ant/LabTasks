package ru.qwert21.labs.C7;

import javax.swing.*;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.function.BiConsumer;

import static ru.qwert21.labs.C7.MyToolkit.*;

public class Client {
  private final String name;
  private final String serverHost;
  private BiConsumer<String, String> onMessage;
  private int lastMessageInd = 0;

  public Client(String name, String server) {
    this.name = name;
    this.serverHost = server;
  }

  public void sendMessage(String msg) {
    try {
      final Socket socket = new Socket(serverHost, Server.SERVER_PORT);

      final DataOutputStream out = new DataOutputStream(socket.getOutputStream());

      out.write(Server.MESSAGE_OPT_SEND);
      out.writeUTF(name);
      out.writeUTF(msg);

      socket.close();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  public void setOnMessage(BiConsumer<String, String> onMessage) {
    this.onMessage = onMessage;
  }

  private void checkMessage() {
    try {
      final Socket socket = new Socket(serverHost, Server.SERVER_PORT);

      final DataInputStream in = new DataInputStream(socket.getInputStream());
      final DataOutputStream out = new DataOutputStream(socket.getOutputStream());

      out.write(Server.MESSAGE_OPT_CHECK);
      out.writeUTF(name);
      out.write(lastMessageInd);

      int msgCount = in.read();
      for (int i = 0; i < msgCount; i++) {
        String user = in.readUTF();
        String msg = in.readUTF();

        onMessage.accept(user, msg);
      }

      lastMessageInd += msgCount;

      socket.close();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  public void startPolling() {
    while (!Thread.currentThread().isInterrupted()) {
      checkMessage();

      try {
        Thread.sleep(100);
      } catch (InterruptedException e) {
        return;
      }
    }
  }

  public static void main(String[] args) {
    String name = JOptionPane.showInputDialog("Enter username");
    if (name == null) {
      showError(null, "Username must be specified");
      return;
    }

    Client client = new Client(name, "localhost");

    MainFrame mf = new MainFrame(name, client::sendMessage);

    client.setOnMessage(mf::receiveMessage);

    client.startPolling();
  }
}
