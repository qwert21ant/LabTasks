package ru.qwert21.labs.C7;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class Server implements Runnable {
  public static final int SERVER_PORT = 4567;

  public static final int MESSAGE_OPT_SEND = 1;
  public static final int MESSAGE_OPT_CHECK = 2;

  private final ArrayList<Message> data = new ArrayList<>();

  @Override
  public void run() {
    try {
      final ServerSocket serverSocket = new ServerSocket(SERVER_PORT);

      while (!Thread.interrupted()) {
        final Socket socket = serverSocket.accept();

        final DataInputStream in = new DataInputStream(socket.getInputStream());
        final DataOutputStream out = new DataOutputStream(socket.getOutputStream());

        int op = in.read();

        if (op == MESSAGE_OPT_SEND) {
          onMessage(in, out);
        } else {
          onPoll(in, out);
        }

        socket.close();
      }
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  void onMessage(DataInputStream in, DataOutputStream out) throws IOException {
    String user = in.readUTF();
    String msg = in.readUTF();

    data.add(new Message(user, msg));
  }

  void onPoll(DataInputStream in, DataOutputStream out) throws IOException {
    String user = in.readUTF();
    int lastMessageInd = in.read();

    if (lastMessageInd > data.size()) {
      out.write(0);
      return;
    }

    out.write(data.size() - lastMessageInd);
    for (int i = lastMessageInd; i < data.size(); i++) {
      Message msg = data.get(i);
      out.writeUTF(msg.user);
      out.writeUTF(msg.msg);
    }
  }

  public static void main(String[] args) {
    System.out.println("server started");
    new Server().run();
  }
}
