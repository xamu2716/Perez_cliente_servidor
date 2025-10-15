# 🚀 Perez_cliente_servidor

## 🌟 Introduction
This project is part of an Operative Systems course, aiming to implement a client-server communication model using named pipes (FIFO).  
The server receives strings from the client, processes them by reversing the text, and sends the modified strings back to the client.  
The communication ends when the client sends the string `"end"`.  

---

## 📋 Description
The implementation consists of two programs:

1. **🖥️ Server (`servidor.c`)**:
   - 📡 Listens for incoming strings from the client through a FIFO file.
   - 🔄 Reverses the received strings and sends them back to the client.
   - ❌ Terminates when the string `"end"` is received.

2. **💻 Client (`cliente.c`)**:
   - ✉️ Sends strings to the server through the FIFO file.
   - 📥 Receives the reversed strings from the server and displays them on the screen.
   - ❌ Terminates when the user inputs the string `"end"`.

---

## 🛠️ How It Works
1. 🛑 The server creates a FIFO file (`/tmp/CLASE_MARTES`) if it does not exist.
2. ✉️ The client opens the same FIFO file to send strings to the server.
3. 🔄 The server reads the strings, processes them by reversing their content, and writes the result back to the FIFO.
4. 📥 The client reads the reversed strings from the FIFO and displays them.
5. ❌ The communication ends when the client sends the string `"end"`.

---

## 📦 Requirements
- 🐧 Linux operating system.
- 🛠️ GCC compiler.
- 📖 Basic knowledge of C programming and inter-process communication.

---

## ⚙️ Compilation
To compile the programs, use the following commands:
```bash
make servidor
make cliente
```

Alternatively, you can compile manually:
```bash
gcc servidor.c -o servidor
gcc cliente.c -o cliente
```

---

## ▶️ Execution
1. Start the **server**:
   ```bash
   ./servidor
   ```
2. Start the **client**:
   ```bash
   ./cliente
   ```

---

## 📝 Example
### Server Output:
```plaintext
FIFOSERVER: Received string: "hello" and length is 5
FIFOSERVER: Sending Reversed String: "olleh" and length is 5
```

### Client Output:
```plaintext
FIFO_CLIENT: Send messages, infinitely, to end enter "end"
Enter string: hello
FIFOCLIENT: Sent string: "hello" and string length is 5
FIFOCLIENT: Received string: "olleh" and length is 5
```

---

## 👨‍💻 Author
**Xamuel Perez**  
📅 Date: October 14, 2025  
📚 Course: Operative Systems  
📂 Topic: Client-Server Communication with Named Pipes  

---

## 🔖 Notes
- ⚠️ Ensure the FIFO file `/tmp/CLASE_MARTES` has the correct permissions for reading and writing.
- 🛑 Run the server before the client to establish communication.
